#include "http_conn.h"

#include <mysql/mysql.h>
#include <fstream>

//定义http响应的一些状态信息
const char *ok_200_title = "OK";
const char *error_400_title = "Bad Request";
const char *error_400_form = "Your request has bad syntax or is inherently impossible to staisfy.\n";
const char *error_403_title = "Forbidden";
const char *error_403_form = "You do not have permission to get file form this server.\n";
const char *error_404_title = "Not Found";
const char *error_404_form = "The requested file was not found on this server.\n";
const char *error_500_title = "Internal Error";
const char *error_500_form = "There was an unusual problem serving the request file.\n";

locker m_lock;
std::map<string, string> users;

void http_conn::initmysql_result(connection_pool *connPool)
{
    //先从连接池中取一个连接
    MYSQL *mysql = NULL;
    connectionRAII mysqlcon(&mysql, connPool); // 调用初始化函数，并且调用获取链接函数使得mysql变量赋予一个连接。

    //在user表中检索username，passwd数据，浏览器端输入
    if (mysql_query(mysql, "SELECT username,passwd FROM user"))
    {
        LOG_ERROR("SELECT error:%s\n", mysql_error(mysql));
    }

    //从表中检索完整的结果集，将检索到的东西赋给result。
    MYSQL_RES *result = mysql_store_result(mysql);

    //返回结果集中的列数
    int num_fields = mysql_num_fields(result);

    //返回所有字段结构的数组
    MYSQL_FIELD *fields = mysql_fetch_fields(result);

    //从结果集中获取下一行，将对应的用户名和密码，存入map中
    while (MYSQL_ROW row = mysql_fetch_row(result))
    {
        string temp1(row[0]);//用户名
        string temp2(row[1]);//密码
        users[temp1] = temp2;
    }

    for(map<string,string>::iterator i = users.begin();i!=users.end();i++){
        cout<<"user:"<<(*i).first<<" pass: "<<(*i).second<<endl;
    }
}

//对文件描述符设置非阻塞
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

//将内核事件表注册读事件，ET模式，选择开启EPOLLONESHOT，oneshot一个请求只能由一个线程进行处理
void addfd(int epollfd, int fd, bool one_shot, int TRIGMode)
{
    epoll_event event;
    event.data.fd = fd;

    if (1 == TRIGMode)//m_CONNTrigmode = 1;
        event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    else
        event.events = EPOLLIN | EPOLLRDHUP;//EPOLLRDHUP事件，表示对方关闭链接的时候，本端对应fd会被触发这个事件，可以通过这个码来判断对方关闭了链接，不然只能通过read返回0来判断

    if (one_shot)
        event.events |= EPOLLONESHOT;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

//从内核时间表删除描述符
void removefd(int epollfd, int fd)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}

//将事件重置为EPOLLONESHOT，处理完之后需要重新设置oneshot
void modfd(int epollfd, int fd, int ev, int TRIGMode)
{
    epoll_event event;
    event.data.fd = fd;

    if (1 == TRIGMode)
        event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
    else
        event.events = ev | EPOLLONESHOT | EPOLLRDHUP;

    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

int http_conn::m_user_count = 0;
int http_conn::m_epollfd = -1;

//关闭连接，关闭一个连接，客户总量减一
void http_conn::close_conn(bool real_close)
{
    if (real_close && (m_sockfd != -1))
    {
        printf("close %d\n", m_sockfd);
        removefd(m_epollfd, m_sockfd);
        m_sockfd = -1;
        m_user_count--;
    }
}

//初始化连接,外部调用初始化套接字地址 WebServer::timer()中调用
void http_conn::init(int sockfd, const sockaddr_in &addr, char *root, int TRIGMode,
                     int close_log, string user, string passwd, string sqlname)
{
    m_sockfd = sockfd;
    m_address = addr;

    addfd(m_epollfd, sockfd, true, m_TRIGMode);//默认oneshot模式，该fd只能由一个线程处理
    m_user_count++;

    //当浏览器出现连接重置时，可能是网站根目录出错或http响应格式出错或者访问的文件中内容完全为空
    doc_root = root;
    m_TRIGMode = TRIGMode;
    m_close_log = close_log;

    strcpy(sql_user, user.c_str());
    strcpy(sql_passwd, passwd.c_str());
    strcpy(sql_name, sqlname.c_str());

    init();
}

//初始化新接受的连接
//check_state默认为分析请求行状态
void http_conn::init()
{
    mysql = NULL;
    bytes_to_send = 0;
    bytes_have_send = 0;
    m_check_state = CHECK_STATE_REQUESTLINE;
    m_linger = false;
    m_method = GET;
    m_url = 0;
    m_version = 0;
    m_content_length = 0;
    m_host = 0;
    m_start_line = 0;
    m_checked_idx = 0;
    m_read_idx = 0;
    m_write_idx = 0;
    cgi = 0;
    m_state = 0;
    timer_flag = 0;
    improv = 0;

    memset(m_read_buf, '\0', READ_BUFFER_SIZE);//请求报文的内容
    memset(m_write_buf, '\0', WRITE_BUFFER_SIZE);//响应报文的内容
    memset(m_real_file, '\0', FILENAME_LEN);//资源文件名？
}

//从状态机，用于分析出一行内容
//返回值为行的读取状态，有LINE_OK,LINE_BAD,LINE_OPEN
http_conn::LINE_STATUS http_conn::parse_line()
{
    char temp;
    for (; m_checked_idx < m_read_idx; ++m_checked_idx)
    {
        temp = m_read_buf[m_checked_idx];//只要check_idx找到了\r,那么就很有可能读取到了一整行
        if (temp == '\r')
        {
            if ((m_checked_idx + 1) == m_read_idx)//这里说明下一字节是还没读取的，也就是这一行还没从socket中接受完。
                return LINE_OPEN;
            else if (m_read_buf[m_checked_idx + 1] == '\n')
            {
                m_read_buf[m_checked_idx++] = '\0';
                m_read_buf[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
        else if (temp == '\n')
        {
            /*1234\r
              sdwd\n
              这种就是语法错误LINE_BAD*/
            if (m_checked_idx > 1 && m_read_buf[m_checked_idx - 1] == '\r')            {
                m_read_buf[m_checked_idx - 1] = '\0';
                m_read_buf[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
    }
    return LINE_OPEN;
}

//循环读取客户数据，直到无数据可读或对方关闭连接
//非阻塞ET工作模式下，需要一次性将数据读完
/*read_once读取浏览器端发送来的请求报文，
直到无数据可读或对方关闭连接，
读取到m_read_buffer中，并更新m_read_idx。*/
bool http_conn::read_once()
{
    if (m_read_idx >= READ_BUFFER_SIZE)//对方发过来的数据一定大于2048字节吗？
    {
        return false;
    }
    int bytes_read = 0;

    //LT读取数据
    if (0 == m_TRIGMode)
    {
        bytes_read = recv(m_sockfd, m_read_buf + m_read_idx, READ_BUFFER_SIZE - m_read_idx, 0);
        m_read_idx += bytes_read;

        if (bytes_read <= 0)
        {
            return false;
        }

        return true;
    }
    //ET读数据
    else
    {
        while (true)//一直读，直到EAGAIN或者EWOULDBLOCK
        {
            bytes_read = recv(m_sockfd, m_read_buf + m_read_idx, READ_BUFFER_SIZE - m_read_idx, 0);
            if (bytes_read == -1)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break;
                return false;
            }
            else if (bytes_read == 0)
            {
                return false;
            }
            //修改m_read_idx的读取字节数
            m_read_idx += bytes_read;
        }
        return true;
    }
}

//解析http请求行，获得请求方法，目标url及http版本号
http_conn::HTTP_CODE http_conn::parse_request_line(char *text)//text="GET / HTTP/1.0\r\n"
{   //https://zhuanlan.zhihu.com/p/164859606
    //在HTTP报文中，请求行用来说明请求类型，要访问的资源以及所使用的HTTP版本，
    //其中各个部分之间通过\t或空格分隔。
    //请求行中最先含有空格和\t任一字符的位置并返回
    m_url = strpbrk(text, " \t");// / HTTP/1.1\r\n
    if (!m_url)
    {
        return BAD_REQUEST;
    }
    *m_url++ = '\0';//'0'/ HTTP/1.1\r\n
    //m_url = "/ HTTP/1.1\r\n"
    //因为有\0的存在，text被截断了
    char *method = text;//text="GET"
    if (strcasecmp(method, "GET") == 0)//这里windows怎么也实现不了。。https://blog.csdn.net/stpeace/article/details/44836801
        //if(strncmp("GET / HTTP/1.0\r\n","GET",3)==0) //windows下这么写咯、、#include <string.h>
        m_method = GET;
        //' '字符的ascii码为32.
    else if (strcasecmp(method, "POST") == 0)
    {
        m_method = POST;
        cgi = 1;
    }
    else
        return BAD_REQUEST;
    m_url += strspn(m_url, " \t");//"123456.jpg HTTP/1.0"
    m_version = strpbrk(m_url, " \t");
    if (!m_version)
        return BAD_REQUEST;
    *m_version++ = '\0';//这样子，m_url又被截断了，m_url=123456.jpg
    m_version += strspn(m_version, " \t");
    //仅支持HTTP/1.1
    if (strcasecmp(m_version, "HTTP/1.1") != 0)
        return BAD_REQUEST;
    if (strncasecmp(m_url, "http://", 7) == 0)//"123456.jpg"
    {
        m_url += 7;
        m_url = strchr(m_url, '/');//指向m_url中第一个出现'/'的位置
    }

    if (strncasecmp(m_url, "https://", 8) == 0)
    {
        m_url += 8;
        m_url = strchr(m_url, '/');
    }

    if (!m_url || m_url[0] != '/')
        return BAD_REQUEST;
    //当url为/时，显示判断界面
    if (strlen(m_url) == 1)///
        strcat(m_url, "judge.html");///judge.html
    m_check_state = CHECK_STATE_HEADER;//解析完成后主状态机的状态变为CHECK_STATE_HEADER
    return NO_REQUEST;
}

//解析http请求的一个头部信息
http_conn::HTTP_CODE http_conn::parse_headers(char *text)
{
    /*解析完请求行后，主状态机继续分析请求头。
    在报文中，请求头和空行的处理使用的同一个函数，这里通过判断当前的text首位是不是\0字符，
    若是，则表示当前处理的是空行，
    若不是，则表示当前处理的是请求头。

    判断是空行还是请求头，若是空行，进而判断content-length是否为0，
    如果不是0，表明是POST请求，则状态转移到CHECK_STATE_CONTENT，
    否则说明是GET请求，则报文解析结束。*/
    if (text[0] == '\0')
    {
        if (m_content_length != 0)
        {
            m_check_state = CHECK_STATE_CONTENT;
            return NO_REQUEST;
        }
        return GET_REQUEST;
    }
    /*若解析的是请求头部字段，则主要分析connection字段，content-length字段，
    其他字段可以直接跳过，各位也可以根据需求继续分析。*/
    else if (strncasecmp(text, "Connection:", 11) == 0)
    {//connection字段判断是keep-alive还是close，决定是长连接还是短连接
        text += 11;
        text += strspn(text, " \t");
        if (strcasecmp(text, "keep-alive") == 0)
        {
            m_linger = true;
        }
    }
    else if (strncasecmp(text, "Content-length:", 15) == 0)
    {//content-length字段，这里用于读取post请求的消息体长度
        text += 15;
        text += strspn(text, " \t");
        m_content_length = atol(text);
    }
    else if (strncasecmp(text, "Host:", 5) == 0)
    {
        text += 5;
        text += strspn(text, " \t");
        m_host = text;
    }
    else
    {
        LOG_INFO("oop!unknow header: %s", text);
    }
    return NO_REQUEST;
}

//判断http请求是否被完整读入
//服务器端解析浏览器的请求报文，当解析为POST请求时，cgi标志位设置为1，
//并将请求报文的消息体赋值给m_string，进而提取出用户名和密码
http_conn::HTTP_CODE http_conn::parse_content(char *text)
{
    if (m_read_idx >= (m_content_length + m_checked_idx))
    {
        text[m_content_length] = '\0';
        //POST请求中最后为输入的用户名和密码
        m_string = text;
        return GET_REQUEST;
    }
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::process_read()
{   //https://mp.weixin.qq.com/s/wAQHU-QZiRt1VACMZZjNlw
    //初始化从状态机状态、HTTP请求解析结果
    LINE_STATUS line_status = LINE_OK;
    HTTP_CODE ret = NO_REQUEST;
    char *text = 0;

    //这里为什么要写两个判断条件？第一个判断条件为什么这样写？
    //具体的在主状态机逻辑中会讲解

    //但后续的登录和注册功能，为了避免将用户名和密码直接暴露在URL中，
    //我们在项目中改用了POST请求，将用户名和密码添加在报文中作为消息体进行了封装。

    //parse_line为从状态机的具体实现
    while ((m_check_state == CHECK_STATE_CONTENT && line_status == LINE_OK) || ((line_status = parse_line()) == LINE_OK))
    {
        text = get_line();
        //m_start_line 是每一个数据行在m_read_buf中的起始位置
        //m_checked_idx表示从状态机在m_read_buf中已经处理 读取的位置
        m_start_line = m_checked_idx;
        LOG_INFO("%s", text);
        switch (m_check_state)
        {
        case CHECK_STATE_REQUESTLINE:
        {
            ret = parse_request_line(text);
            if (ret == BAD_REQUEST)
                return BAD_REQUEST;
            break;
        }
        case CHECK_STATE_HEADER:
        {
            ret = parse_headers(text);
            if (ret == BAD_REQUEST)
                return BAD_REQUEST;
            else if (ret == GET_REQUEST)
            {
                return do_request();
            }
            break;
        }
        case CHECK_STATE_CONTENT:
        {
            ret = parse_content(text);
            if (ret == GET_REQUEST)
                return do_request();
            line_status = LINE_OPEN;//用这个作为post的结束条件
            break;
        }
        default:
            return INTERNAL_ERROR;
        }
    }
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::do_request()
{
    //将初始化的m_real_file赋值为网站的根目录
    strcpy(m_real_file, doc_root);//假设doc_root=/home
    int len = strlen(doc_root);
    //printf("m_url:%s\n", m_url);

    //找到m_url中/的位置
    const char *p = strrchr(m_url, '/');//strrchr找最后出现/的位置

    //如果是POST方法则处理cgi
    if (cgi == 1 && (*(p + 1) == '2' || *(p + 1) == '3'))
    {// m_url=/2CGISQL.cgi  或/3CGISQL.cgi

        //根据标志判断是登录检测还是注册检测
        char flag = m_url[1];//废弃？

        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/");//m_url_real=/
        strcat(m_url_real, m_url + 2);//m_url_real=/CGISQL.cgi
        strncpy(m_real_file + len, m_url_real, FILENAME_LEN - len - 1);//m_real_file=/home/CGISQL.cgi
        free(m_url_real);

        //将用户名和密码提取出来
        //user=123&password=123
        char name[100], password[100];
        int i;
        for (i = 5; m_string[i] != '&'; ++i)
            name[i - 5] = m_string[i];
        name[i - 5] = '\0';//name=123\0

        int j = 0;
        for (i = i + 10; m_string[i] != '\0'; ++i, ++j)//为什么加10？？
            password[j] = m_string[i];
        password[j] = '\0';

        std::string pass_bcrypt = BCrypt::generateHash(password);
        
        //"$2a$12$w5froGB28qKjlIg8CQNrOuWFWt7MWLueGVKHoeBzMA3jEsMQJrNXq"
        if (*(p + 1) == '3')
        {
            //如果是注册，先检测数据库中是否有重名的
            //没有重名的，进行增加数据
            //INSERT INTO user(username, passwd) VALUES('name', 'password')
            char *sql_insert = (char *)malloc(sizeof(char) * 200);
            strcpy(sql_insert, "INSERT INTO user(username, passwd) VALUES(");
            strcat(sql_insert, "'");
            strcat(sql_insert, name);
            strcat(sql_insert, "', '");
            strcat(sql_insert, pass_bcrypt.c_str());
            strcat(sql_insert, "')");

            if (users.find(name) == users.end())//map<string, string> users
            {//如果找不到
                cout<<"正在向数据库注册"<<endl;
                m_lock.lock();
                int res = mysql_query(mysql, sql_insert);//向数据库注册用户
                users.insert(pair<string, string>(name, pass_bcrypt));
                m_lock.unlock();

                if (!res)//如果向数据库注册用户成功
                {
                    cout<<"注册成功"<<endl;
                    // strcpy(m_url, "/log.html"); //源代码
                    strcpy(m_url, "/welcome.html"); //注册成功直接跳转到欢迎页面才对啊。。。
                }
                    
                else
                {
                    cout<<"注册失败"<<endl;
                    strcpy(m_url, "/registerError.html");
                }
                    
            }//如果找到了，那还注册个屁
            else
                strcpy(m_url, "/registerError.html");
        }
        //如果是登录，直接判断
        //若浏览器端输入的用户名和密码在表中可以查找到，返回1，否则返回0
        else if (*(p + 1) == '2')
        {
            // if (users.find(name) != users.end() && users[name] == password&& BCrypt::validatePassword(password,users[name]))
            if (users.find(name) != users.end() && BCrypt::validatePassword(password,users[name]))//传过来的明文密码和加密密码解密后是相同的，则成功。
                strcpy(m_url, "/welcome.html");
            else
                strcpy(m_url, "/logError.html");
        }
    }

    //如果请求资源为/0，表示跳转注册界面
    if (*(p + 1) == '0')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/register.html");

        //将网站目录和/register.html进行拼接，更新到m_real_file中
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    //如果请求资源为/1，表示跳转登录界面
    else if (*(p + 1) == '1')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/log.html");
        //将网站目录和/log.html进行拼接，更新到m_real_file中
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    else if (*(p + 1) == '5')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/picture.html");
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    else if (*(p + 1) == '6')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/video.html");
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    else if (*(p + 1) == '7')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/fans.html");
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));

        free(m_url_real);
    }
    else
    //如果以上均不符合，即不是登录和注册，直接将url与网站目录拼接
    //这里的情况是welcome界面，请求服务器上的一个图片
        strncpy(m_real_file + len, m_url, FILENAME_LEN - len - 1);
    
    //通过stat获取请求资源文件信息，成功则将信息更新到m_file_stat结构体
    //失败返回NO_RESOURCE状态，表示资源不存在
    if (stat(m_real_file, &m_file_stat) < 0)
        return NO_RESOURCE;

    //判断文件的权限，是否可读，不可读则返回FORBIDDEN_REQUEST状态
    if (!(m_file_stat.st_mode & S_IROTH))
        return FORBIDDEN_REQUEST;

    //判断文件类型，如果是目录，则返回BAD_REQUEST，表示请求报文有误
    if (S_ISDIR(m_file_stat.st_mode))
        return BAD_REQUEST;

    //以只读方式获取文件描述符，通过mmap将该文件映射到内存中
    int fd = open(m_real_file, O_RDONLY);
    m_file_address = (char *)mmap(0, m_file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    //避免文件描述符的浪费和占用
    close(fd);
    //表示请求文件存在，且可以访问
    return FILE_REQUEST;
}
void http_conn::unmap()
{
    if (m_file_address)
    {
        munmap(m_file_address, m_file_stat.st_size);
        m_file_address = 0;
    }
}
bool http_conn::write()
{//https://mp.weixin.qq.com/s/451xNaSFHxcxfKlPBV3OCg#:~:text=%E5%9C%A8%E7%94%9F%E6%88%90%E5%93%8D%E5%BA%94%E6%8A%A5%E6%96%87%E6%97%B6%E5%88%9D%E5%A7%8B%E5%8C%96byte_to_send
    int temp = 0;

    //若要发送的数据长度为0
    //表示响应报文为空，一般不会出现这种情况
    if (bytes_to_send == 0)
    {
        modfd(m_epollfd, m_sockfd, EPOLLIN, m_TRIGMode);
        init();
        return true;
    }

    while (1)
    {
        //将响应报文的状态行，消息头，空行和响应正文发送给浏览器端
        temp = writev(m_sockfd, m_iv, m_iv_count);

        if (temp < 0)
        {   //判断缓冲区是否满了
            if (errno == EAGAIN)
            {   //重新注册写事件
                modfd(m_epollfd, m_sockfd, EPOLLOUT, m_TRIGMode);
                return true;//不是在这睡眠等带缓冲区有空了继续写，而是返回，等待下一次的epollOUT事件。
            }
            //如果发送失败，但不是缓冲区的问题，取消映射
            unmap();
            return false;
        }
        //正常发送，temp为发送的字节数
        bytes_have_send += temp;
        //更新已发送字节数
        bytes_to_send -= temp;
        //第一个iovec头部信息的数据已经发送完，发送第二个iovec数据
        if (bytes_have_send >= m_iv[0].iov_len)
        {
            //不在继续发送头部信息
            m_iv[0].iov_len = 0;
            ////bytes_have_send - m_write_idx表示已经发出的长度超出头部多长，来计算大文件的起始偏移量
            m_iv[1].iov_base = m_file_address + (bytes_have_send - m_write_idx);
            m_iv[1].iov_len = bytes_to_send;
        }
        else
        {
            m_iv[0].iov_base = m_write_buf + bytes_have_send;
            m_iv[0].iov_len = m_iv[0].iov_len - bytes_have_send;
        }
        //判断条件，数据已全部发送完
        if (bytes_to_send <= 0)
        {
            unmap();
            //在epoll树上重置EPOLLONESHOT事件
            modfd(m_epollfd, m_sockfd, EPOLLIN, m_TRIGMode);
            //浏览器的请求为常连接
            if (m_linger)
            {   //重新初始化HTTP对象
                init();
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
bool http_conn::add_response(const char *format, ...)
{
    //如果写入内容超出m_write_buf大小则报错
    if (m_write_idx >= WRITE_BUFFER_SIZE)
        return false;
    va_list arg_list;//可变参数列表
    va_start(arg_list, format);//将变量arg_list初始化为传入参数
    //将数据format从可变参数列表写入缓冲区写，返回写入数据的长度
    int len = vsnprintf(m_write_buf + m_write_idx, WRITE_BUFFER_SIZE - 1 - m_write_idx, format, arg_list);
    //如果写入的数据长度超过缓冲区剩余空间，则报错
    if (len >= (WRITE_BUFFER_SIZE - 1 - m_write_idx))
    {
        va_end(arg_list);
        return false;
    }
    //更新m_write_idx位置
    m_write_idx += len;
    //清空可变参列表
    va_end(arg_list);

    LOG_INFO("request:%s", m_write_buf);

    return true;
}
//添加状态行
bool http_conn::add_status_line(int status, const char *title)
{
    return add_response("%s %d %s\r\n", "HTTP/1.1", status, title);
}

//添加消息报头，具体的添加文本长度，连接状态和空行
bool http_conn::add_headers(int content_len)
{
    return add_content_length(content_len) && add_linger() &&
           add_blank_line();
}

//添加Content-Length,表示响应报文的长度
bool http_conn::add_content_length(int content_len)
{
    return add_response("Content-Length:%d\r\n", content_len);
}

//添加文本类型，这里是html
bool http_conn::add_content_type()
{
    return add_response("Content-Type:%s\r\n", "text/html");
}
//添加连接状态，通知浏览器端是保持连接还是关闭
bool http_conn::add_linger()
{
    return add_response("Connection:%s\r\n", (m_linger == true) ? "keep-alive" : "close");
}
//添加空行
bool http_conn::add_blank_line()
{
    return add_response("%s", "\r\n");
}
//添加文本content
bool http_conn::add_content(const char *content)
{
    return add_response("%s", content);
}
bool http_conn::process_write(HTTP_CODE ret)
{//均是内部调用add_response函数更新m_write_idx指针和缓冲区m_write_buf中的内容
    switch (ret)
    {
    //内部错误,500
    case INTERNAL_ERROR:
    {
        //状态行
        add_status_line(500, error_500_title);
        //消息报头
        add_headers(strlen(error_500_form));
        if (!add_content(error_500_form))
            return false;
        break;
    }
    //报文语法有误,404
    case BAD_REQUEST:
    {
        add_status_line(404, error_404_title);
        add_headers(strlen(error_404_form));
        if (!add_content(error_404_form))
            return false;
        break;
    }
    //资源没有权限访问，403
    case FORBIDDEN_REQUEST:
    {
        add_status_line(403, error_403_title);
        add_headers(strlen(error_403_form));
        if (!add_content(error_403_form))
            return false;
        break;
    }
    //文件存在，200
    case FILE_REQUEST:
    {
        add_status_line(200, ok_200_title);
        //如果请求的资源存在
        if (m_file_stat.st_size != 0)
        {
            add_headers(m_file_stat.st_size);
            //第一个iovec指针指向响应报文缓冲区，长度指向m_write_idx
            m_iv[0].iov_base = m_write_buf;
            m_iv[0].iov_len = m_write_idx;
            //第二个iovec指针指向mmap返回的文件指针，长度指向文件大小
            m_iv[1].iov_base = m_file_address;
            m_iv[1].iov_len = m_file_stat.st_size;
            m_iv_count = 2;
            bytes_to_send = m_write_idx + m_file_stat.st_size;
            return true;
        }
        else
        {
            //如果请求的资源大小为0，则返回空白html文件
            const char *ok_string = "<html><body></body></html>";
            add_headers(strlen(ok_string));
            if (!add_content(ok_string))
                return false;
        }
    }
    default:
        return false;
    }
    //除了FILE_REQUEST状态外，其余状态只申请一个iovec，指向响应报文缓冲区
    m_iv[0].iov_base = m_write_buf;
    m_iv[0].iov_len = m_write_idx;
    m_iv_count = 1;
    bytes_to_send = m_write_idx;
    return true;
}
void http_conn::process()
{
    HTTP_CODE read_ret = process_read();//报文解析
    if (read_ret == NO_REQUEST)//请求不完整，需要即许接受请求数据
    {
        modfd(m_epollfd, m_sockfd, EPOLLIN, m_TRIGMode);
        return;
    }
    /*服务器子线程调用process_write完成响应报文，随后注册epollout事件。
    服务器主线程检测写事件，并调用http_conn::write函数将响应报文发送给浏览器端。*/
    bool write_ret = process_write(read_ret);//报文响应
    if (!write_ret)
    {
        close_conn();
    }
    modfd(m_epollfd, m_sockfd, EPOLLOUT, m_TRIGMode);
}

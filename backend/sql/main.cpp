#include <winsock2.h>
#include <mysql.h>
#include <iostream>
using namespace std;
// #pragma comment(lib,"libmysql.lib")
// #pragma comment(lib,"mysqlclient.lib")

int main(){
    //创建MYSQL变量
    MYSQL m;
    //初始化MYSQL变量
    mysql_init(&m);
    //调用mysql_real_connect函数连接Mysql数据库。
    if(!mysql_real_connect(&m,"localhost","root","1234567890","webserver",3306,0,0)){
        cout<<"mysql_real_connect failure!"<<endl;
        return 0;
    };
    //查询mysql数据库中的user表
    if(mysql_real_query(&m,"select * from user",(unsigned long)strlen("select * from user"))){
        cout<<"mysql_real_query failure!"<<endl;
        return 0;
    }

    //存储结果集
    MYSQL_RES *res;//不要赋值，要指针
    res = mysql_store_result(&m);
    if(NULL==res){
        cout<<"mysql_store_result failure!"<<endl;
        return 0 ; 
    }
    //重复读取行，并输出第一个字段的值，直到row为NULL
    MYSQL_ROW row;//char**类型
    while(row = mysql_fetch_row(res)){
        cout<<row[0]<<" "<<row[1]<<" "<<endl;
    }

    //释放结果集
    mysql_free_result(res);
    //关闭Mysql连接
    mysql_close(&m);
    return 0;
}
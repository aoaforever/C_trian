#include <bits/stdc++.h>
using namespace std;



/*        
^ 在c++中是表示异或。。。。。。
只有pow()函数才是求幂的

*/

/*
[编程题]进制转换
时间限制：C/C++ 1秒，其他语言2秒

空间限制：C/C++ 32M，其他语言64M

写出一个程序，接受一个十六进制的数，输出该数值的十进制表示。

数据范围：保证结果在 

输入描述:
输入一个十六进制的数值字符串。


输出描述:
输出该数值的十进制字符串。不同组的测试用例用\n隔开。


输入例子1:
0xAA

输出例子1:
170
*/
unordered_map<char,int> keytoint;


void run(string& s){
    cout<<"s.size():"<<s.size()<<endl;
    int m = s.size()-2;
    int res=0;
    
    for(int i=2;i<s.size();i++){
        // cout<<"keytoint[s[i]]："<<keytoint[s[i]]<<"  m:"<<m<<endl;
        res += keytoint[s[i]]*(pow(16,--m));
     
    }
    cout<<to_string(res)<<endl;
}

int main(){
    for(char i='0';i<='9';i++){
        keytoint[i] = i-'0';
    }
    int t = 10;
    for(char i='A';i<='F';i++){
        keytoint[i] = t++;
    }
    // cout<<keytoint.size()<<endl;
    string input;
    while(cin>>input){
       run(input);
    }
    return 0;
}

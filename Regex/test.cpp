#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <stdio.h>
using namespace std;




bool isMask(string mask){ //单独检查掩码是否是先1后0
    if(mask == "0.0.0.0" || mask == "255.255.255.255") //全0全1不合法
        return false;
    //这里的^不是非得意思，而是字符串得开头，不匹配任何字符，只是表达意思而已
    // [^asdasdasd]，这里得^才是表示非得意思
    string re = "^((0|128|192|224|240|248|252|254)\\.0\\.0\\.0|255\\.(0|128|192|224|240|248|252|254)\\.0\\.0|255\\.255\\.(0|128|192|224|240|248|252|254)\\.0|255\\.255\\.255\\.(0|128|192|224|240|248|252|254|255))$";
    regex pattern(re);
    if(regex_match(mask, pattern)) //正则表达式匹配正确的掩码
        return true;
    else
        return false;
}
int main()
{
	string a ="192.0.0.0";
	cout<<isMask(a);
	return 0;
}
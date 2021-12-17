#include <algorithm>

/*给定一个非负整数c，你要判断是否存在两个整数a和b，使得a^2+b^2 = c*/
class Solution{
public:
    bool judgeSquareSum(int c){
        long int a=0;//用long，不然测试用例数值太大过不了
        long int b =sqrt(c);

        if((a*a+b*b) == c ){
            return true;
        }

        while(a<=b){//判断条件不应该是(a*a+b*b)!=c，而是双指针是否碰到了。
            if((a*a+b*b) < c)
                a++;
            else if((a*a+b*b)>c){
                b--;
            }
            else 
                return true;
        }
        return false;
    }

};
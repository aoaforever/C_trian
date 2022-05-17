#include <string>
#include <vector>

using namespace std;
/*
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/regular-expression-matching
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// . 是与当前字符有关
// * 是与之前字符有关
// s = "baa", p = ".a*"
// s= "baa", p="b*a"
// s= "caa", p="b*a"
//匹配零次应该怎么写？ dp(s,i,p,j+2) 跳过*,用p[j+2]重新匹配当前s[i]
//匹配多次 dp(s,i+1,p,j)  //p[j]继续匹配s[i+1]
class Solution {
public:
    bool isMatch(string s, string p) {
        return dp(s,0,p,0);
    }

    //当i,j搞到最后了，那就是成功了。
    bool dp(string& s, int i, string& p, int j){
        if(j==p.size()){
            return i==s.size();
        }

        if(i==s.size()){
            if((p.size()-j)%2 == 1){
                return false;
            }

            for(;j+1<p.size();j+=2){
                if(p[j+1]!='*'){
                    return false;
                }
            }
            return true;
        }

        if(s[i]==p[j]||p[j]=='.'){
            if( j+1 < p.size() && p[j+1]=='*' ){
                //那么就有两种情况，匹配多次或者匹配零次
                return dp(s,i+1,p,j)||dp(s,i,p,j+2); // || 表示只要有一种情况成功就可以了。
            }
            else return dp(s,i+1,p,j+1);//正常匹配1次。
        }
        else {//这里也分情况
            if(j+1<p.size() && p[j+1]=='*'){//当当前字符不匹配，并且后面是*。只能匹配零次
                return dp(s,i,p,j+2);
            }
            //不相同肯定不匹配吧。
            else return false;
        }
    }
};


class Solution {
public:
    int n,m;
    unordered_map<string,bool> memo;
    bool isMatch(string s, string p) {
        n = s.size(), m = p.size();
        return dp(s,0,p,0);
    }
    bool dp(string& s, int i, string& p, int j){
        if(j==m){
            return i==n;
        }
        if(i==n){
            if((m-j)%2==1) return false;
            for(;j+1<m;j=j+2){
                if(p[j+1]!='*') return false;
            }
            return true;
        }

        string key = to_string(i)+","+to_string(j);
        if(memo.count(key)) return memo[key];
        bool res =false;
        if(s[i]==p[j]||p[j]=='.'){
            if(p[j+1]=='*'){
                res = dp(s,i,p,j+2)||dp(s,i+1,p,j);//匹配0次或者多次
            }
            else res = dp(s,i+1,p,j+1);
        }
        else{
            if(p[j+1]=='*')  res = dp(s,i,p,j+2);//匹配0次
            else res =  false;
        } 
        memo[key] = res;
        return memo[key];
    }
};
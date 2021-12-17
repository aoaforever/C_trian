#include <string>
#include <vector>

using namespace std;
/*给你一个字符串 s 、一个字符串 t 。
返回 s 中涵盖 t 所有字符的最小子串。
如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
https://leetcode-cn.com/problems/minimum-window-substring/
*/
class Solution{
public:
    string minWindow(string S, string T){
        vector<int> chars(128,0);//128个int，值为0
        vector<bool> flag(128,false);//128个bool，值为false

        //先统计T中的字符情况。
        for(int i =0; i<T.size(); ++i){//T[i]表示遍历T中的字符，对应的字符在flag中为true。
            flag[T[i]] =true;
            ++chars[T[i]];//T[i]对应的字符在chars中++，表示这个字符出现了多少次。
        }

        //移动滑动窗口，不断更改统计数据。
        int cnt=0, l = 0 , min_l=0, min_size =S.size()+1;
        for(int r=0; r<S.size();++r){//每次r向右滑动判断该字符在不在T中
            if(flag[S[r]]){
                if(--chars[S[r]] >=0 ){//假如T中有两个A，现在已经找到两个A了，那么cnt不会自增。
                    ++cnt;
                }

                //若目前滑动窗口已包含T中全部字符
                //则尝试将l右移，在不影响结果的情况下获得最短子字符串
                while(cnt==T.size()){
                    if(r-l+1 <min_size){//如果当前窗口小于最小窗口，则更新最小窗口
                        min_l=l;//记录最小窗口的l左位置
                        min_size = r-l+1;//更新最小窗口
                    }

                    if(flag[S[l]] && ++chars[S[l]] >0 ){//在上面，如果包含了多个同一字母，那么chars对应的字母的值会<0,这里如果移除了这个字母，需要加回去
                        --cnt;
                    }
                    ++l;//右移左指针，然后进入下一次while判断是否包含T。
                }
            }

        }
        return min_size > S.size() ? "": S.substr(min_l,min_size);
    }
};
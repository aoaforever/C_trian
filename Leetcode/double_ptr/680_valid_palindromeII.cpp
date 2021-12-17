#include  <string>
using namespace std;

class Solution{
public:
    bool checkPalindrome(const string &s, int low, int high){
        while(low<high){
            if(s[low]==s[high]){
                ++low;
                --high;
            }
            else 
                return false;
        }
        return true;
    }

    bool validPalindrome(string s){
        int start = 0, end=s.size()-1;

        while(start<end){
            if(s[start]==s[end]){
                ++start;
                --end;
            }
            else{
                return checkPalindrome(s,start+1,end)||checkPalindrome(s,start,end-1);//只改变一次体现在这里。贪心法。
            }
        
        }
        return true;
    }

};
#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。返回一个表示每个字符串片段的长度的列表。
 */
class Solution{
public:
    vector<int> partitionLabels(string s){
        int last[26];
        int length = s.size();

        for(int i =0;i<length;i++){
            last[s[i]-'a']=i;
        }

        vector<int> partition;
        int start =0 ,end=0;
        for (int i =0; i<length; i++){
            //当前字母s[i]的最后出现位置为last[s[i]-'a']。
            //
            end = max(end, last[s[i]-'a']);

            if( i == end) {
                partition.push_back(end-start+1);
                start = end+1;
            }
        }
        return partition;

    }
};
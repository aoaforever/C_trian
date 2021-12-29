#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;
//给定一个字符串，请将字符串里的字符按照出现的频率降序排列。
class Solution{
public:
    string frequencySort(string s){
        //这种做法太占空间。
        // // cout<<s.size();
        // int store[52]={};
        // //特定字母放在哪个位置： ++store[s[i]-'a'];
        // for(int i=0;i<s.size();i++){
        //     ++store[s[i]-'a'];
        // }

        // for(int i =0;i<52;i++){
        //     cout<<store[i]<<" ";
        // }

        int max_counts = 0;
        unordered_map<char,int> mymap;
        for(int i=0;i<s.size();i++){
            max_counts= max(max_counts,++mymap[s[i]]);
        }//[ "t":1, "t":1, "e":2 ]

        // vector< vector<char> > buckets(max_counts+1);
        // for(auto &p : mymap){
        //     buckets[p.second].push_back(p.first);
        //     //[0,  1   , 2 ]
        //     //[[],[t,r],[e]]
            
        // }

        vector<string> buckets(max_counts+1);
        for(auto &[ch,num]:mymap){
            buckets[num].push_back(ch);
        }

        string ans;
        for(int i =max_counts;i>0;i--){
            string &bucket = buckets[i];// "e"
            for(auto &ch: bucket){
                for(int k =0; k<i ; k++){//多一层循环，用来输出所有个数的某个字符
                    ans.push_back(ch);
                }
            }
        }
        return ans;
    }

};

/*
复杂度分析

时间复杂度：O(n + k)，其中 n 是字符串 s 的长度，k 是字符串 s 包含的不同字符的个数。
遍历字符串统计每个字符出现的频率需要 O(n) 的时间。
创建桶并将不同字符加入桶需要 O(k) 的时间。
生成排序后的字符串，需要 O(k) 的时间遍历桶，以及 O(n) 的时拼接字符串间。
因此总时间复杂度是 O(n + k)。

空间复杂度：O(n + k)，其中 n 是字符串 s 的长度，k 是字符串 s 包含的不同字符的个数。
空间复杂度主要取决于桶和生成的排序后的字符串。

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/sort-characters-by-frequency/solution/gen-ju-zi-fu-chu-xian-pin-lu-pai-xu-by-l-zmvy/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
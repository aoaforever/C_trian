#include <vector>
#include <queue>
/*给定两个大小相等的数组 A 和 B，A 相对于 B 的优势可以用满足 A[i] > B[i] 的索引 i 的数目来描述。

返回 A 的任意排列，使其相对于 B 的优势最大化。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/advantage-shuffle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
#include <algorithm>
#include <iostream>
using namespace std;

//nums2不能动
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        vector<pair<int,int>> n1(nums1.size()),n2(nums2.size());
        for(int i = 0 ; i<nums1.size(); i++){
            n1[i] = pair<int,int>{i,nums1[i]};
            n2[i] = pair<int,int>{i,nums2[i]};
        }
        sort(n1.begin(),n1.end(),[](const pair<int,int>&a, const pair<int,int>&b){
            return a.second<b.second;//升序
        });
        sort(n2.begin(),n2.end(),[](const pair<int,int>&a, const pair<int,int>&b){
            return a.second<b.second;//升序
        });
        // for(pair<int,int> i: n1){
        //     cout<<i.second<<" ";
        // }
        // cout<<endl;
        // for(pair<int,int> i: n2){
        //     cout<<i.second<<" ";
        // }
        //那n2来对比，放nums1
        //双指针
        int left = 0 , right = n1.size()-1;
        for(int i =n2.size()-1;i>=0;i--){
            int loc = n2[i].first;
            if(n1[right].second>n2[i].second){
                nums1[loc] = n1[right--].second;
            }
            else {
                nums1[loc] = n1[left++].second;
            }
        }

        return nums1;
    }
};

//用优先队列存储nums2
class Solution {
private:
    struct cmp{
        bool operator()(const pair<int,int>& a, const pair<int,int>& b){
            return a.second<b.second; //less,升序，但是返回头顶最大值
        }
    };

public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        vector<pair<int,int>> n1(nums1.size());
        priority_queue<pair<int,int>,vector<pair<int,int>>,cmp> n2;
        for(int i = 0 ; i<nums1.size(); i++){
            n1[i] = pair<int,int>{i,nums1[i]};
            n2.push(pair<int,int>{i,nums2[i]});
        }
        sort(n1.begin(),n1.end(),[](const pair<int,int>&a, const pair<int,int>&b){
            return a.second<b.second;//升序
        });

        // for(pair<int,int> i: n1){
        //     cout<<i.second<<" ";
        // }
        // cout<<endl;
        // for(pair<int,int> i: n2){
        //     cout<<i.second<<" ";
        // }
        //那n2来对比，放nums1
        //双指针
        int left = 0 , right = n1.size()-1;
        while(!n2.empty()){
            pair<int,int> tmp = n2.top();
            n2.pop();
            int loc = tmp.first;
            if(n1[right].second>tmp.second){
                nums1[loc] = n1[right--].second;
            }
            else {
                nums1[loc] = n1[left++].second;
            }
        }
        

        return nums1;
    }
};
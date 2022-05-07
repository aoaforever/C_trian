#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;
//判断s是否为子序列
class Solution {
public:
    bool isSubsequence(string s, string t) {
        //不是叫你找出所有子序列，而是直接判断s是不是
        //双指针
        int i=0,j=0;
        while(i<s.size()&&j<t.size()){
            if(s[i]==t[j]){
                i++;
                j++;
            }
            else j++;
        }
        if(i==s.size()) return true;
        return false;
    }
};

class Solution {
public:
    bool isSubsequence(string s, string t) {
        unordered_map<char,vector<int>> index;
        for(int i=0;i<t.size();i++){
            index[t[i]].push_back(i);
        }
        int j = 0 ; 
        for(int i=0;i<s.size();i++){
            char c = s[i];
            if(!index.count(c)) return false;
            int pos = left_bound(index[c],j);//根据c字符，找一个比j大的最小下标
            //根据字符c，找出来的下标肯定指向c。
            //如果越界，表示找不到
            if(pos==index[c].size()) return false;
            //pos只是vector的下标，并不是t的下标，index[c][pos]才是t的下标
            j = index[c][pos] +1;//为什么+1，因为找到了，先指向那个字符，然后下一个循环i++,因此j也要++；
        }
        return true;
    }
    int left_bound(vector<int>& nums, int target){
        int l=0,r=nums.size();
        while(l<r){
            int mid = l + (r-l)/2;
            if(nums[mid]<target){
                l = mid+1;
            }
            else if(nums[mid]>target){
                r =mid;
            }
            else{
                r=mid;//找左边界
            }
        }
        return l;
    }
};
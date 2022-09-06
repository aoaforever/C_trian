#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> tmp1;
        vector<int> tmp2;
        vector<int> res(k,0),tmp;
        int m = nums1.size(), n = nums2.size();
        int start = max(0,k-n), end = min(k,m);

        for(int i=start;i<=end;i++){
            tmp1 = find(nums1,i);
            tmp2 = find(nums2,k-i);
            tmp = merge(tmp1,tmp2);
            if(comp(tmp,0,res,0)>0){
                res = tmp;
            }
        }
        return res;

    }

    int comp(vector<int>& n1,int i,vector<int>& n2, int j){
        int x = n1.size(), y = n2.size();
        //n1的元素大于n2，返回true
        while(i<x&&j<y){
            int diff = n1[i]-n2[j];
            if(diff!=0) return diff;
            i++;
            j++;
        }
        return (x-i) - (y - j);
        
    }

    //找出这个数组的最大数，要弹size - k次
    vector<int> merge(vector<int>&tmp1, vector<int>& tmp2){
        if(tmp1.empty()) return tmp2;
        if(tmp2.empty()) return tmp1;

        int i=0,j=0;
        vector<int> res(tmp1.size()+tmp2.size());
        for(int k=0;k<res.size();k++)
            if(comp(tmp1,i,tmp2,j)>0){
                res[k] = (tmp1[i++]);
            }
            else{
                res[k]= (tmp2[j++]);
            }
        return res;
    }

    vector<int> find(vector<int>& nums,int k){
        if(k==0) return {};
        k = nums.size()-k;//需要弹出的次数
        stack<int> s;

        for(int i=0;i<nums.size();i++){
            int & n = nums[i];
            while(!s.empty()&&n>s.top()&&k>0){
                s.pop();
                k--;
            }
            s.push(n);
        }

        while(k--){
            s.pop();
        }

        vector<int> t;
        while(!s.empty()){
            t.push_back(s.top());
            s.pop();
        }

        reverse(t.begin(),t.end());
        return t;

    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    vector<int> c{3, 4, 6, 5};
    vector<int> d{9, 1, 2, 5, 8, 3};
    vector<int> a = s.maxNumber(c,d,5)   ; 
    return 0;
}

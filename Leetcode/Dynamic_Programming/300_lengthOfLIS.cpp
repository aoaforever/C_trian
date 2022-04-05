/*
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

 
示例 1：

输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
示例 2：

输入：nums = [0,1,0,3,2,3]
输出：4
示例 3：

输入：nums = [7,7,7,7,7,7,7]
输出：1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-increasing-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <vector>
using namespace std;


//这题确实不能用双指针，因为它可以删除其中的元素，但是不饿能改变相对位置。

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int res=-1;
        int left=0;
        int right = 0;
        int size = nums.size();
        int len =0;//初始值应该为多少？
        while (left<size)
        {
            //右指针取出元素，然后 往右移
            int cur = nums[++right];
            if(cur<= nums[right-1]){
                //如果不是递增，则记录最长
                len = max(len,right-left);
                left = right;
            }
            else{
                //如果是递增，记录长度
                // len++;
                right++;
            }
        }
        return len;
        
    }
};


//明确dptable的定义，dptable[i]表示当前i元素为结尾的最长子序列。
//如果确定dptable[i]的值，从肉眼看，你需要对比多次取出最长的答案，因此算法也要模拟这样。

class Solution {
public:
    
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dptable(nums.size(),1);
        for(int i=1;i<nums.size();i++){
            //确定dptable[i]的值
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){
                    dptable[i] = max(dptable[i],dptable[j]+1);
                }
            }
        }
        //  最终答案是整个dptable[]的某个最大值》
        int res =-9999;
        for(int i=0;i<dptable.size();i++){
            res = max(res,dptable[i]);
        }
        return res;
        

        
    }

};
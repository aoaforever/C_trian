/*给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，
分别表示 nums1 和 nums2 中的元素数目。

请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。
为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，
应忽略。nums2 的长度为 n 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

//题目解析
// 1. 两个数组都有序，关键！
// 2. 不能创建新数组

#include <vector>
using namespace std;

// [1,2,3,0,0,0] [3,4,5]
//这种做法有一个问题：当一个数组全部放完了，而另一个数组还剩很多。。。就会越界了。

// class Solution{
// public:
//     void merge(vector<int>& nums1, int m, vector<int>& nums2, int n){
//         int p = m + n -1;
//         int cur_val=0;
//         m--;
//         n--;
//         while(p>=0){
//             if (nums1[m]>nums2[n]) {
//                 cur_val = nums1[m-1];
//                 m--;
//                 }
//             else {
//                 cur_val = nums2[n-1];
//                 n--;
//             } 
                
//             nums1[p]=cur_val;
//             p--;
//         }
//     }
// };

//根据第一点，如果第二个数组首先放完，就表示第一个数组也已经排好序了。
//如果第一个数组先放完，表示还要将第二个数组剩下的元素放在头部。
class Solution{
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n){
        int p = m + n -1;
        m--;
        n--;
        while( m>=0 && n>=0 ){
            nums1[p--] = nums1[m]>nums2[n] ? nums1[m--]: nums2[n--];
        }
        while(n>=0){
            nums1[p--] = nums2[n--];
        }
    }
};

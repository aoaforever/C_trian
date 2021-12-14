/*给你一个长度为 n 的整数数组，请你判断在 最多 改变 1 个元素的情况下，该数组能否变成一个非递减数列。

我们是这样定义一个非递减数列的： 对于数组中任意的 i (0 <= i <= n-2)，总满足 nums[i] <= nums[i + 1]。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/non-decreasing-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

#include <vector>
#include <algorithm>
using namespace std;
//最左边的元素一定是最小的元素 

//只判断是否只出现一次下降， 这个做法是不完善的。 [3,4,2,3]
// class Solution {
// public:
//     bool checkPossibility(vector<int>& nums) {
//         int count=0;
//         int min=nums[0];

//         for(auto &i :nums){
//             if(i<min){
//                 count++;
//                 min=i;
//             }
//         }

//         if (count>1)
//             return false;
//         return true;
//     }
// };

/*原则：
1.发现当前元素比之前小，先把前一个元素的值修改为当前元素。判断数组是否有序
2. 在1下不满足，则把当前元素的值修改为前一个元素的值，判断数组是否有序
*/

class Solution{
public:
    bool checkPossibility(vector<int>& nums){
        int tmp=0;
        for (int i = 1; i<nums.size();i++){
            if(nums[i]<nums[i-1]){
                tmp=nums[i-1];
                nums[i-1]=nums[i];
                if(is_sorted(nums.begin(),nums.end()))
                    return true;

                nums[i-1]=tmp;
                nums[i]=nums[i-1];
                return is_sorted(nums.begin(),nums.end());
                    
            }


        }
        return true;//for 外面是return true,因为，当数组大小为1时，不会进入for循环。
    }
};
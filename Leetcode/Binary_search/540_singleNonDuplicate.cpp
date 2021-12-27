#include <vector>
#include <iostream>
/*给你一个仅由整数组成的有序数组，其中每个元素都会出现两次，唯有一个数只会出现一次。

请你找出并返回只出现一次的那个数。

你设计的解决方案必须满足 O(log n) 时间复杂度和 O(1) 空间复杂度。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/single-element-in-a-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

//规律：
/*
1. 数组个数必为奇数个
2. 包含单个数的数组必为奇数个
3. 去除中间一对，剩下的必为偶数组和奇数组，往奇数组继续二分
*/

/*另外，你会发现即使数组没有经过排序，只要将同一元素放在一起，该算法仍然起作用（例：[10, 10, 4, 4, 7, 11, 11, 12, 12, 2, 2]）。他们的顺序无关紧要，重要的是含有单个元素的子数组元素个数为奇数。

作者：LeetCode
链接：https://leetcode-cn.com/problems/single-element-in-a-sorted-array/solution/you-xu-shu-zu-zhong-de-dan-yi-yuan-su-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/


/*还可以用异或法，O(n)复杂度*/
using namespace std;
class Solution{
public:
    int singleNonDuplicate(vector<int>& nums){
        int left =0, right = nums.size()-1, mid;
        while (left<right){//不相等，保证长度为1时直接返回。
            mid = left+(right-left)/2;
            if(nums[mid]!=nums[mid-1] && nums[mid]!= nums[mid+1]) return nums[mid];
            if(nums[mid]==nums[mid-1]){//如果等于左边的数
                // int left_nums = mid-2-left+1;
                if((mid-2-left+1)%2==0){
                    //左边是偶数
                    left = mid+1;
                }
                else{
                    right=mid-2;
                }
            }
            else if(nums[mid]==nums[mid+1]){//如果等于右边的数
                if((mid-1-left+1)%2==0){
                    //左边是偶数
                    left = mid+2;
                }
                else{
                    right=mid-1;
                }


            }
            
        }
        return nums[left];
    }
};

int main(){
    cout<<1/2;
    cout<<1%2;//是奇数
    return 0;
}
#include <vector>
/*给定一个已按照 非递减顺序排列  的整数数组 numbers ，请你从数组中找出两个数满足相加之和等于目标数 target 。

函数应该以长度为 2 的整数数组的形式返回这两个数的下标值。numbers 的下标 从 1 开始计数 ，所以答案数组应当满足 1 <= answer[0] < answer[1] <= numbers.length 。

你可以假设每个输入 只对应唯一的答案 ，而且你 不可以 重复使用相同的元素。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
using namespace std;

class Solution{
public:
    vector<int> twoSum(vector<int>& numbers, int target){
        int start = 0 ;
        int end=numbers.size()-1;

        while(start!=end){
            if((numbers[start]+numbers[end])<target)
            {
                start++;
            }
            else if ((numbers[start]+numbers[end])>target){
                end--;
            }
            else
                break;
        }
        vector<int> a;
        a.push_back(start+1);
        a.push_back(end+1);
        return a ;
    }

};
//https://leetcode-cn.com/problems/minimum-operations-to-make-the-array-alternating/

#include <vector>
#include <unordered_map>
#include <cstdio>
#include <tuple>
using namespace std;

/*
但这样做并不能保证「奇数下标的元素和偶数下标的元素不能相同」。
如果两个键表示的元素不相同，那么上述方法就是正确的，但如果两个键表示的元素相同，那么最终数组并不满足题目要求。
因此除了值最大的键以外，我们还需要筛选出值次大的键。
如果两个最大键表示的元素相同，那么一个最大键和另一个次大键表示的元素一定不相同，
因此修改次数即为「奇数哈希映射最大键对应的值」加上「偶数哈希映射次大键对应的值」与
「奇数哈希映射次大键对应的值」加上「偶数哈希映射最大键对应的值」二者中的较大值，
再用 n 减去该值。

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/minimum-operations-to-make-the-array-alternating/solution/shi-shu-zu-bian-cheng-jiao-ti-shu-zu-de-gd9u9/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/

/*怎么理解数组长度-max(e1val+o2val,e2val+o1val)就是答案？
  一个例子：固定奇数下标出现次数最多的键值和偶数下标出现次数第二多的键值，除了这两个键值，其他都是
  需要改变的。因此总长度-这两个键值的长度 = 需要修改的次数。
*/
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int e1stkey,e1stval,e2ndkey,e2ndval,o1stkey,o1stval,o2ndkey,o2ndval;
        tie(e1stkey,e1stval,e2ndkey,e2ndval) = get(nums,0);
        tie(o1stkey,o1stval,o2ndkey,o2ndval) = get(nums,1);
        if(e1stkey!=o1stkey){
            return nums.size()-e1stval-o1stval;
        }
        return nums.size()-max((e1stval+o2ndval),(e2ndval+o1stval));
        
    }
    tuple<int,int,int,int> get(vector<int>& nums,int index){
        unordered_map<int,int> freq;
        for(;index<nums.size();index += 2){
            freq[nums[index]]++;
        }
        int fkey=0, fval=0, skey=0, sval=0;
        for(const auto &a :freq){
            int val = a.second;//键值出现次数
            int key = a.first;//键值
            if (val>fval){
                skey = fkey;
                sval = fval;
                fkey = key;
                fval = val;
            }
            else {
                skey = key;
                sval = val;
            }
        }
        return tuple<int,int,int,int>{fkey,fval,skey,sval};
    }
};
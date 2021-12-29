#include <vector>
#include <unordered_map>
using namespace std;
/*给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。*/

/*
1. 先为每个元素设置一个桶
2. 为每个桶统计每个元素出现多少次
3. 桶排序，任意的排序算法
*/

class Solution{

public:
    vector<int> topKFrequent(vector<int>& nums, int k){//k表示前k个高频元素
        unordered_map<int,int> counts; //哈希表构建桶, counts的大小是nums不同元素的个数
        int max_count =0;
        for (const int & num : nums){//这里可以用引用，不用复制
            max_count = max(max_count,++counts[num]);//num表示键，counts[num]表示值
        }

        //执行完上面后，counts这个桶就包含了某个元素出现的次数，和最大次数为max_count

        vector< vector<int> > buckets(max_count+1);//为什么要size多加一个1,因为如果最大次数为4，就有[4,3,2,1,0]5个桶,0肯定不放元素
        for (const auto &p : counts){
            buckets[p.second].push_back(p.first);//p.second 表示元素出现的次数，p.first表示该元素，这里的意思是，根据不同的次数构建第二个桶，不同的次数放对应次数的元素。
        }

        vector<int> ans;
        for(int i = max_count;i>=0 && ans.size()<k ; --i ){
            for(const int & num: buckets[i]){
                ans.push_back(num);
                if(ans.size()==k){
                    break;
                }
            }
        }

        return ans;
    }
};
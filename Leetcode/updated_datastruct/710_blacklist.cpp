#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int sz;
    unordered_map<int,int> mapping;

    Solution(int n, vector<int>& blacklist) {
        //先把黑名单添加到键值中
        for(int b: blacklist){
            mapping[b] = 666;
        }

        //最终数组中的元素个数
        sz = n - blacklist.size();
        //最后一个元素的索引
        int last = n -1;
        //将黑名单中的索引换到最后去
        for(int b: blacklist){
            //如果b已经在区间[sz,n)，可以直接忽略
            if(b>=sz){
                continue;
            }
            //跳过所有黑名单中的数字
            while (mapping.count(last))
            {
                last--;
            }
            
            mapping[b] = last;
            last--;
        }
    }
    
    int pick() {
        //随机选取一个索引
        int index = rand() % sz;
        //这个索引命令了黑名单，需要被映射到其他位置
        if(mapping.count(index)){
            return mapping[index];
        }
        //若没有命中黑名单，则直接返回
        return index;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */
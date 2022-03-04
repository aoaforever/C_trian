#include <vector>
#include <unordered_map>

using namespace std;
class RandomizedSet {
public:
    //记录元素的值
    vector<int> nums;
    //记录元素的索引
    unordered_map<int, int> valToIndex;

    RandomizedSet() {
        valToIndex.clear();
        nums.clear();
    }
    
    bool insert(int val) {
        //不允许插入重复值，而只插入不存在的值
        if(valToIndex.count(val)){
            //如果有重复值，不插入
            return false;
        }
        else{
            nums.push_back(val);
            valToIndex[val] = nums.size()-1;
            return true;
        }

    }
    
    bool remove(int val) {
        //元素不存在时，不能移除，返回false
        if(!valToIndex.count(val)){
            return false;
        }
        //元素存在，交换到数组尾，然后进行删除
        int valindex = valToIndex[val];
        // if(valindex==nums.size()-1){
        //     //直接删除
        //     nums.pop_back();
        //     valToIndex.erase(val);
        //     return true;
        // }

        //将最后一个元素的下标更改以下
        valToIndex[nums.back()] = valindex;

        swap(nums[valindex],nums.back());
        //交换完，删除元素
        nums.pop_back();
        valToIndex.erase(val);
        return true;
    }
    
    int getRandom() {
        //随机获取nums中的一个元素
        return nums[rand()%nums.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
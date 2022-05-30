#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;





int erase(vector<int>& nums, int i){
    //如果不在意数组顺序，才能够用这种方法，不然只能用erase内置方法
        //删除位置i的元素
        int tmp=nums[i];
        swap(nums[i],*(nums.end()-1));
        nums.pop_back();
        return tmp;
}

int main(){
    string s;
    getline(cin,s);
    stringstream ss;
    ss<<s;
    int tmp;
    vector<int> nums;
    while (ss>>tmp)
    {
        nums.push_back(tmp);
    }
    tmp = erase(nums,2);
    nums.insert(nums.begin()+2,tmp);
    cout<<nums.size();
    
    return 0;
}
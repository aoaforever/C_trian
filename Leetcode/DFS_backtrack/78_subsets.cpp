#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


class Solution {
public:
    vector<vector<int>> res;
    vector<int> track;
    vector<vector<int>> subsets(vector<int>& nums) {
        backtrack(nums,0);
        return res;
    }
    void backtrack(vector<int>& nums, int start){
        //start规定从数组的哪一位置开始，避免重复。

        //每次递归都是一个子集，并且不会重复
        res.push_back(track);
        //怎么遍历？
        for(int i=start; i<nums.size(); i++){
            
            //做选择，
            track.push_back(nums[i]);
            backtrack(nums,i+1);//是i+1而不是start+1.画个图就知道了。
            track.pop_back();
        }
    }
};

int main(){
    //有无数组输入，每次输入一行不定，作为数组。
    
    while(1){
        string s;
        while(getline(cin,s)){
            Solution fun;
            cout<<&fun;
            //输入一行后进行解析
            stringstream ss;
            ss<<s;
            //类型转换
            int tmp;
            vector<int> nums;
            while (ss>>tmp)
            {
                nums.push_back(tmp);
            }
            vector<vector<int>> res = fun.subsets(nums);
            cout<<"[";
            for(auto& n:res){
                cout<<"[";
                for(auto& a:n){
                    cout<<a<<",";
                }
                cout<<"],";
            }
            cout<<"]"<<endl;
            s.clear();
            cin.clear();
        }
        
    }
    return 0;
}
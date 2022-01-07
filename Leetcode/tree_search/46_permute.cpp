#include <vector>
#include <iostream>
using namespace std;

class Solution{
public:
    vector<vector<int>> permute(vector<int>& nums){
        vector<vector<int>> ans;
        backtracking(nums,0,ans);//回溯法
        return ans;
    }

    void backtracking(vector<int>& nums, int level, vector<vector<int>>& ans){
        if(level == nums.size()-1){
            cout<<"level:"<<level;
            ans.push_back(nums);
            return ;
        }

        for(int i=level; i< nums.size(); i++){
            cout<<"i:"<<i<<"  "<<"level:"<<level<<endl;
            swap(nums[i],nums[level]);
            backtracking(nums,level+1,ans);
            cout<<"back"<<endl;
            swap(nums[i],nums[level]);
        }
    }
};

//方法二：

class Solution2{
public:
    vector< vector<int> > res;

    vector<vector<int>> permute(vector<int>& nums){
        vector<int> track;
        backtrack(nums,track);
        return res;
    }

    void backtrack(vector<int>& nums, vector<int> &track){
        if(track.size() == nums.size()){
            res.push_back(track);
            return;
        }


        for(int i =0; i< nums.size(); ++i){
            if(vector_find(nums[i],track)){
                continue;
            }

            track.push_back(nums[i]);
            backtrack(nums,track);
            track.pop_back();
        }
    }

    int vector_find(const int &a, const  vector<int> &track){
        int res = 0 ; 
        for(int i = 0 ; i<track.size(); i++){
            if(track[i]==a){
                res=1;
                break;
            }
        }
        return res;
    }

};

int main(){

    vector<int> a{1,2,3,4};
    Solution solution;  
    solution.permute(a);
    return 0;
}
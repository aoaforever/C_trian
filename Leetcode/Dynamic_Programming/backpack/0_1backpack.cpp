/*大概意思是 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：

所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。 

示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
————————————————
版权声明：本文为CSDN博主「52it.club」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/xia296/article/details/116095184  
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include <string>
#include <sstream>
using namespace std;

vector<vector<int>> res;
vector<int> tmp;




void dfs(vector<int>& candidates,int index , int target){
    if(target==0) 
    {
      res.push_back(tmp);
      return;
    }
    if(target<0||index<0) return;

    // 前i 个物品， 背包容量为target
    if(target>=candidates[index]){
        //既可以装也可以不装
        tmp.push_back(candidates[index]);
        dfs(candidates,index-1,target-candidates[index]);
        tmp.pop_back();

        // dfs(canddates,index-1, target);//因此这个可以省去
    }
    // else {
      //只能不装
      dfs(candidates,index-1, target);
    // }
}


void backtrack(vector<int>& candidates,int index , int target){
    if(target==0) {
        res.push_back(tmp);
        return ;
    }
    if(target<0){

      return ;
    }

    for(int i = index; i<candidates.size();i++){
        if(i!=index&& candidates[i]==candidates[i-1]){
            continue;
        }
        tmp.push_back(candidates[i]);
        backtrack(candidates,i+1,target-candidates[i]);
        tmp.pop_back();
    }
}

vector<vector<int>> help(vector<int>&candiates, int target){
    sort(candiates.begin(),candiates.end());
    // dfs(candiates,candiates.size()-1, target);
    backtrack(candiates,0,target);
    return res;
}


int main(int argc, char const *argv[])
{
      // string s;
      // getline(cin,s);    
      // int target;
      // cin>>target;
      // stringstream ii;
      // ii<<s;
      // vector<int> nums;
      // string a;
      // while(getline(ii,a,',')){
      //     nums.push_back(stoi(a));
      // }

      // vector<vector<int>> ans = help(nums,target);


      string a="asdasd";
      string b = a.substr(6);
      cout<<b.empty()<<endl;
      return 0;
}

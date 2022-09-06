// https://leetcode.cn/problems/brick-wall/ 砌墙
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        //先算出每个墙的具体位置
        
        unordered_map<int,int> c;
        for(auto& w:wall){
            int sum=0;
            for(int i=0;i<w.size()-1;i++){
                sum +=w[i];
                c[sum]++; 
            }
        }

        int max_ = INT_MIN;
        for(auto& d:c){
            max_ = max(d.second,max_);
        }

        if(max_==INT_MIN) return wall.size();
        return wall.size()-max_;

    }
};
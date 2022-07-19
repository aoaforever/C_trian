#include <bits/stdc++.h>

using namespace std;

class RangeModule {
public:
    vector<vector<int>> range;
    RangeModule() {

    }
    
    void addRange(int left, int right) {
        
        for(auto& r:range){
            cout<<r[0]<<" "<<r[1]<<endl;
        }

        //判断有无重叠，相交区间
        if(range.size()==0){
            range.emplace_back(vector<int>{left,right});
            return;
        }
        //应该先插入，再去重
        range.emplace_back(vector<int>{left,right});
        sort(range.begin(),range.end(),[](vector<int>&a, vector<int>&b){
            if(a[0]==b[0]) return a[1]>b[1];
            return a[0]<b[0];
        });
        vector<vector<int>> tmp;
        
        int l = range[0][0], r = range[0][1];
        tmp.emplace_back(vector<int>{l,r});
        for(int i=1;i<range.size();i++){
            int cur_l = range[i][0], cur_r = range[i][1];
            if(cur_r<=l||cur_l>=r){
                //不重叠
                l = cur_l;
                r = cur_r;
                tmp.emplace_back(vector<int>{cur_l,cur_r});
                
            }
            else{
                //相交
                l = min(cur_l,l);
                r = max(cur_r,r);
                tmp.back()[0] = l;
                tmp.back()[1] = r;
            }

        }

        range = tmp;
    }
    
    bool queryRange(int left, int right) {
        for(vector<int>& r:range){
            if(left>=r[0]&&right<=r[1]){
                return true;
            }
        }
        return false;
    }
    
    void removeRange(int left, int right) {
        vector<vector<int>> tmp;
        for(vector<int>& r:range){
            if(right<=r[0]||left>=r[1]){
                tmp.emplace_back(r);
                continue;
            }
            else if(left>=r[0]&&right<=r[1]){
                tmp.emplace_back(vector<int>{r[0],left});
                tmp.emplace_back(vector<int>{right,r[1]});
            }

        }
        range = tmp;
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
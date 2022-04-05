#include <vector>
#include <iostream>
using namespace std;
//错在左右区间, 计算天数的函数
//left一定要大于其中的货物最大重量，这样子船才不会装不下
//right可以是船中所有货物的重量+1.
class Solution {
public:
    int countDays(int ship,vector<int>&weights){
        int days=1;//不管如果肯定大于1天
        int w =0;
        for(int i = 0 ; i<weights.size();i++){
            // cout<<"w:"<<w<<endl;
            if((w + weights[i]) > ship){//先判断会不会满，满的话清空，下一天。你如果先强塞进去，在判断，肯定会超载。
                w = 0 ; 
                days++;
            }
            w += weights[i];
        }
        return days;
    }
    int countDays(int ship,vector<int>&weights){
        int days=0;
        //有个上限，超过ship了，就+1天。
        //假如上限太大，
        for(int i = 0 ; i<weights.size();){
            while (i<weights.size())
            {//就一直装到满，然后下一天
                // cout<<i<<endl;
                int cap = ship;
                if(cap <weights[i]) break;
                else cap -= weights[i];
                i++;
            }
            days++;
            
        }
        return days;
    }
    int shipWithinDays(vector<int>& weights, int days) {
        int left = 0, right = 0;
        for(int& weight:weights){
            left = max(left,weight);
            right += weight;
        }
        while(left<=right){
            int mid = left+ (right-left)/2;
            int cday = countDays(mid,weights);
            cout<<"cady:"<<cday<<" mid:"<<mid<<endl;
            if(cday == days){
                right = mid-1;
            }
            else if(cday<days){//上限太大了，减少一些
                right = mid-1;
            }
            else{
                left = mid+1;
            }
        }

        return left;
    }
};

int main(){
    Solution solution;
    vector<int> weights{1,2,3,4,5,6,7,8,9,10};

    int a = solution.shipWithinDays(weights,5);
    cout<<a<<endl;
    return 0 ; 
}
#include <iostream>
#include <vector>

using namespace std;
/*给定一个数组 prices ，其中 prices[i] 是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        bool buy=false;
        prices.push_back(-1);
        int cur_price=0;
        int total_profit=0;

        for(int i = 0; i< (prices.size()-1);i++){
            cout<<prices[i];
            if(prices[i]<=prices[i+1]){
                if (!buy){
                    cout<<"buy";
                    cur_price = prices[i];
                    buy=true;
                    
                }
                }

            if(prices[i] > prices[i+1]){
                cout<<buy;
                if(buy){
                    cout<<"sell";
                    total_profit = total_profit + (prices[i]-cur_price);
                    cur_price=0;
                    buy=false;
                }
            }
            
        }
        return total_profit;
    }
};

int main(){
    // int a[6]={7,1,5,3,6,4};
    vector<int> prices={7,1,5,3,6,4};
    Solution a;
    int b = a.maxProfit(prices);
    cout<<b;

    return 0;
}
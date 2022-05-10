/*
珂珂喜欢吃香蕉。这里有 N 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 H 小时后回来。

珂珂可以决定她吃香蕉的速度 K （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 K 根。如果这堆香蕉少于 K 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。  

珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。

返回她可以在 H 小时内吃掉所有香蕉的最小速度 K（K 为整数）。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/koko-eating-bananas
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int hours(const int x, vector<int>&nums){
        int hours =0;
        for(int & num:nums){
            int yu = num%x;
            int zheng = num/x;
            hours += zheng;
            if (yu!=0){
                hours++;
            }
        }
        // cout<<"hours:"<<hours<<endl;
        return hours;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1,right = 1000000000;//1 <= piles.length <= 10^4, 左右标识速度的取值

        while(left<=right){
            int mid = left+ (right-left)/2;
            cout<<"mid:"<<mid<<endl;
            if(hours(mid,piles)==h){
                right = mid-1;
            }
            else if (hours(mid,piles)<h){//说明速度太快，因该减少速度
                right = mid-1;
            }
            else {
                left = mid+1;
            }
        }

        cout<<"left="<<left<<endl;;
        cout<<hours(left,piles)<<endl;
        if(hours(left,piles)>h || left>1000000000){//边界问题。边界问题：hours(left,piles)>h ，如果速度太慢，导致超时，则失败。
            return -1;
        }
        return left;

    }
};


int main(){
    Solution solution;
    vector<int> vec{312884470};
    int a =solution.minEatingSpeed(vec,312884469);
    cout<<a;
    return 0;
}
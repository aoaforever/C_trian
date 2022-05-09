#include <vector>

using namespace std;

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> diff(n,0);
        for(vector<int> b : bookings){
            book(b,diff);
        }
        return ans(diff);
    }

    void book(vector<int>& bookings, vector<int>& diff){
        //bookings=[i,j,k]
        //i为第i航班
        //j为第j航班
        //k为定了多少个座位

        int i =bookings[0];
        int j =bookings[1];
        int k =bookings[2];

        diff[i-1] += k;
        if(j-1+1<diff.size()){
            diff[j-1+1] -= k;
        }
    }

    vector<int> ans(const vector<int>& diff){
        vector<int> ans(diff.size(),0);
        ans[0]=diff[0];
        for(int i =1;i<diff.size();i++){
            ans[i] = ans[i-1]+diff[i];
        }
        return ans;

    }
};
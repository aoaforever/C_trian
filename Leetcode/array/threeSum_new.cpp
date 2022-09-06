// 3a[j] - a[i] = a[k]
// i<j<k
// [1,2,3,4,5,6,7,8,9,10]
//  i                j  k

//由于是减法、并不能用双端指针

#include <bits/stdc++.h>

using namespace std;

void help(vector<int>& nums){
    int n = nums.size();
    unordered_map<int,int> m;
    m[nums[n-1]]++;
    int res=0;

    for(int j=n-2;j>=1;j--){
        for(int i=j-1;i>=0;i--){
            if(m.count(3*nums[j]-nums[i])){
                res += m[3*nums[j]-nums[i]];
            }
        }
        //轮询完一遍i，则将当前的j放入哈希表作为下一个k
        m[nums[j]]++;
    }
    cout<<res<<endl;
}


int main(int argc, char const *argv[])
{
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    help(nums);
    return 0;
}

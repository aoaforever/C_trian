//hard

#include <vector>
#include <algorithm>

using namespace std;
class Solution{
private :
    vector<int> f;//存储下标为id时，能够访问的最多的下标。
public:
    void dfs(vector<int>& arr, int id, int d, int n){//传入数组，下标位置，范围d，和长度n
        if(f[id] != -1){
            return ;//如果已经搜索过，那么直接返回值,这里由于是对f进行引用，所以不用返回
        }

        f[id]=1;//id的下标能够访问到的所有下标，初始化为1

        //向左访问
        for(int i = id-1;i>=0 && id-i<=d && arr[id]>arr[i]; --i){
            dfs(arr,i,d,n);//向左搜索下标为i时，能够访问的最多的下标
            f[id]=max(f[id],f[i]+1);//更新
        }

        //向右访问
        for(int i = id+1; i<n && i-id<=d&& arr[id]> arr[i]; ++i){
            dfs(arr,i,d,n);
            f[id]=max(f[id],f[i]+1);
        }
    }

    int maxJumps(vector<int>& arr, int d){
        int n = arr.size();
        f.resize(n,-1);//初始化f为n个-1的数组。
        for(int i =0 ; i<n; i++){
            dfs(arr,i,d,n);
        }
        return *max_element(f.begin(),f.end());
    }
};
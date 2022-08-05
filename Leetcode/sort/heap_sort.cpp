/*
输入描述:
第一行为数据个数 第二行为输入数据


输出描述:
排序过程的中间数据，及已经排好序的数据
示例1
输入
10
100 32 3 6 24 86 23 90 78 3
*/

#include <bits/stdc++.h>

using namespace std;

//编写一个下沉操作
void sink(vector<int>& nums, int i, int len){
    if(i>len) return;
    //给第i个元素进行下沉
    //大根堆
    int j = i*2;
    if(j>len) return ;
    if( (j+1)<=len && nums[j]<nums[j+1]){
        j=j+1;
    }
    if(nums[i]<nums[j]){
        swap(nums[i],nums[j]);
        sink(nums,j,len);    //如果交换了，才继续往下沉，没交换就不下沉
    }

    return ;
    
}

void heap_sort(vector<int>&nums){
    int len = nums.size();
    vector<int> ans(len+1);
    for(int i=0;i<len;i++){
        ans[i+1] = nums[i];
    }
    //ans从下标1开始，一直到len 下标
    /*
    1.建堆，通过下沉操作建堆效率更高，具体过程是，找到最后一个非叶子节点，然后从后往前遍历执行下沉操作。*/
    for(int i = len/2; i>=1;i--){
        sink(ans,i,len);
    }

    //建完堆后，目前堆顶是大根堆，最大元素
    //2.排序，将堆顶元素（代表最大元素）与最后一个元素交换，然后新的堆顶元素进行下沉操作，遍历执行上诉操作，则可以完成排序。

    int k = len;
    while(k>1){
        swap(ans[1],ans[k]);
        --k;
        sink(ans,1,k);
    }

    for(int i=1;i<=len;i++){
        cout<<ans[i]<<" ";
    }
}

int main(){
    int n;
    cin >>n;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    heap_sort(nums);

    return 0;
}
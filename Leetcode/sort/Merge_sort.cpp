#include <vector>
#include <iostream>

using namespace std;

/*归并排序：把两个或多个已经有序的序列合并成一个。*/
//给定一个大数组，取中间，分别对左边进行归并排序，右边进行归并排序。
//当退化成最后一个大数组的时候，左右两边已经排好序了，最后进行一次归并排序

//说到底是分治算法，分治算法呢，可以认为是⼀种算法思想，通过将原问题分解成⼩规模的⼦问题，然后根据⼦问题的结果构造
//出原问题的答案。这⾥有点类似动态规划，所以说运⽤分治算法也需要满⾜⼀些条件，你的原问题结果应该
//可以通过合并⼦问题结果来计算。
void merge_sort(vector<int> &nums, int l , int r, vector<int> &temp){
    if(l+1>=r){
        return ;
    }
    //先从两个元素起，慢慢叠加。
    //divide 
    int m = l+(r-l)/2;
    
    merge_sort(nums,l,m,temp);
    merge_sort(nums,m,r,temp);
    // cout<<l<<" "<<m<<endl;
    //conquer 
    int p =l, q=m, i=l;
    while(p<m || q<r){//只要有其中一个数组没搞定，就继续循环下去
    cout<<p<<endl;
        if(q >= r || (p<m && nums[p]<=nums[q])){
            temp[i++] = nums[p++];
        }
        else{
            temp[i++] = nums[q++];
        }
    }

    for(i=l;i<r;++i){
        // cout<<temp[i]<<" ";
        nums[i] = temp[i];
    }
    // cout<<endl;
}

int main(){
    vector<int> a{1,2,3,9,8,7,6,5,4,3};
    vector<int> tmp(a.size());
    merge_sort(a,0,a.size(),tmp);
    // cout<<"asdas";
    for(auto i : a){
        cout<<i<<" ";
    }
    return 0;
}
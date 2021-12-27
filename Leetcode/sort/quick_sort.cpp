#include <vector>
#include <iostream>
using namespace std;
/*
快速排序：属于交换排序，根据序列中两个元素关键字的比较结果来对换这两个记录在序列中的位置。
*/
void quick_sort(vector<int>&nums, int l, int r){
    if (l+1 >= r){
        return ;
    }

    int first =l, last = r-1, key = nums[first];
    while(first<last){
        while(first<last && nums[last]>=key ){
            //什么时候右指针往左移？　右边元素>key时。因为key总是要放在中间
            --last;
        }//结束时交换元素。
        nums[first] = nums[last];
        //轮到左边元素放右边了
        while(first<last && nums[first]<=key){
            //什么时候左指针往右移？  左边元素<key时
            ++first;
        }
        nums[last]=nums[first];

    }
    //给key放在中间
    nums[first]=key;
    //继续递归左右两边的元素
    quick_sort(nums,l,first);//last会自动减一
    quick_sort(nums,first+1,r);
}


// int main(){
//     vector<int> a{23,45,235,2,23,4,5,6,7,3,22};
//     quick_sort(a,0,a.size());
//     for(auto i:a){
//         cout<<i<<" ";
//     }
//     return 0;
// }
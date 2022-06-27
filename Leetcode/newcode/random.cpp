/*
明明生成了N个1到500之间的随机整数。请你删去其中重复的数字，即相同的数字只保留一个，把其余相同的数去掉，然后再把这些数从小到大排序，按照排好的顺序输出。

数据范围：  ，输入的数字大小满足 

输入描述:
第一行先输入随机整数的个数 N 。
接下来的 N 行每行输入一个整数，代表明明生成的随机数。
具体格式可以参考下面的"示例"。

输出描述:
输出多行，表示输入数据处理后的结果


输入例子1:
3
2
2
1

输出例子1:
1
2

例子说明1:
输入解释：
第一个数字是3，也即这个小样例的N=3，说明用计算机生成了3个1到500之间的随机整数，接下来每行一个随机数字，共3行，也即这3个随机数字为：
2
2
1
所以样例的输出为：
1
2       
*/


#include <vector>
#include<iostream>
#include <set>
#include <algorithm>
using namespace std;

int main(){
    int N;
    cin>>N;
    set<int> used;
    vector<int> res;
    while(N--){
        int tmp;
        cin>>tmp;
        if(used.count(tmp)) continue;
        res.emplace_back(tmp);
        used.insert(tmp);
    }
    // sort(res.begin(),res.end());
    // for(int& r:res){
    //     cout<<r<<endl;
    // }

    //set本来就是红黑树，本来就是有序的啊！！！！！！！！！！！！！！！！
    for(auto i:used){
        cout<<i<<endl;
    }
    return 0;
}
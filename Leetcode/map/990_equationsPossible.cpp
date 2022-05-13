/*
 * @lc app=leetcode.cn id=990 lang=cpp
 *
 * [990] 等式方程的可满足性
 *
 * https://leetcode-cn.com/problems/satisfiability-of-equality-equations/description/
 *
 * algorithms
 * Medium (51.66%)
 * Likes:    233
 * Dislikes: 0
 * Total Accepted:    41K
 * Total Submissions: 79K
 * Testcase Example:  '["a==b","b!=a"]'
 *
 * 给定一个由表示变量之间关系的字符串方程组成的数组，每个字符串方程 equations[i] 的长度为 4，并采用两种不同的形式之一："a==b" 或
 * "a!=b"。在这里，a 和 b 是小写字母（不一定不同），表示单字母变量名。
 * 
 * 只有当可以将整数分配给变量名，以便满足所有给定的方程时才返回 true，否则返回 false。 
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：["a==b","b!=a"]
 * 输出：false
 * 解释：如果我们指定，a = 1 且 b = 1，那么可以满足第一个方程，但无法满足第二个方程。没有办法分配变量同时满足这两个方程。
 * 
 * 
 * 示例 2：
 * 
 * 输入：["b==a","a==b"]
 * 输出：true
 * 解释：我们可以指定 a = 1 且 b = 1 以满足满足这两个方程。
 * 
 * 
 * 示例 3：
 * 
 * 输入：["a==b","b==c","a==c"]
 * 输出：true
 * 
 * 
 * 示例 4：
 * 
 * 输入：["a==b","b!=c","c==a"]
 * 输出：false
 * 
 * 
 * 示例 5：
 * 
 * 输入：["c==c","b==d","x!=z"]
 * 输出：true
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= equations.length <= 500
 * equations[i].length == 4
 * equations[i][0] 和 equations[i][3] 是小写字母
 * equations[i][1] 要么是 '='，要么是 '!'
 * equations[i][2] 是 '='
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
class UF{
private:
    vector<int> parent;//每个节点的父节点
    int count;//通量
    vector<long> size;//每个节点为根的size// 居然会有溢出的情况，所以用long
public:
    UF(int n){
        //n个节点
        parent.resize(n);
        size.resize(n);//你忘了这个
        for(int i=0;i<n;i++){
            parent[i] =i;//先每个节点都指向自己。
            size[i] =1;//每个节点的size都为1.
        }
        count = n;

    }
    bool connected(int a,int b){
        int roota = find(a);
        int rootb = find(b);
        if(roota==rootb) return true;
        return false;
    };
    void union_(int a,int b){
        int roota= find(a);
        int rootb = find(b);
        if(size[roota]>=size[rootb]){
            //那就挂在roota下
            parent[rootb] = roota;
            count--;
            size[roota] += size[rootb];
        }else{
            parent[roota] = rootb;
            count--;
            size[rootb] += size[roota];
        }
    };
    int find(int a){
        while(a!=parent[a]){
            parent[a] = parent[parent[a]];
            a= parent[a];
        }
        return a;
    };
};
    bool equationsPossible(vector<string>& equations) {
        //先找出所有的字母有多少个
        //不，不用，我直接26个字母都给你
        UF uf(26);
        for(string& s:equations){
            if(s[1]=='='){
                char x = s[0];
                char y = s[3];
                uf.union_(x-'a',y-'a');
            }
        }
        for(string& s:equations){
            if(s[1]=='!'){
                char x = s[0];
                char y = s[3];
                if(uf.connected(x-'a',y-'a')){
                    return false;
                }
            }
        }
        return true;
    }
};

// @lc code=end


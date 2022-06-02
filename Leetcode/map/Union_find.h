#include <vector>

using namespace std;
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
    int get_count(){
        return count;
    }
};
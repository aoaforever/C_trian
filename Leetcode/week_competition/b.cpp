#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;
int zuozuowei(char a,vector<int>& b){
    switch(a){
        case 'M':{
                //男人：优先有人
            int i=0;
            for(;i<b.size();i++){
                if(b[i]==2) continue;
                else if(b[i]==1){
                    b[i]++;
                    break;
                }
                else if(b[i]==0){
                    b[i]++;
                    break;
                }
            }
            return i+1;
            break;
            }
        case 'F':{
            int i=0;
            for(;i<b.size();i++){
                if(b[i]==2) continue;
                else if(b[i]==0){
                    b[i]++;
                    break;
                }
                else if(b[i]==1){
                    b[i]++;
                    break;
                }
            }
            return i+1;
            break;
        }
    }
    return 0;
}

int main(){
    int zu;
    cin>>zu;
    int zhuozishu;
    cin>>zhuozishu;
    vector<int> z1;
    char z[zhuozishu];
    scanf("%s",z);
    for(int i=0;i<zhuozishu;i++){
        z1.push_back((int)(z[i]-'0'));
    }
    int renshu;
    cin>>renshu;
    vector<char> xingbie1;
    char xingbie[renshu];
    scanf("%s",xingbie);
    for(int i=0;i<renshu;i++){
        xingbie1.push_back(xingbie[i]);
    }
    for(int i=0;i<renshu;i++){
        int ans;
        ans = zuozuowei(xingbie[i],z1);
        cout<<ans<<endl;
    }
    
    return 0;
}
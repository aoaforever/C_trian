
//https://www.nowcoder.com/test/question/done?tid=52750861&qid=1371129#summary
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<int>&a,vector<int>&b){
  
  int nums = a[0];
  int min_t = a[1];
  int max_t = a[2];
  int taotai_tmp=0;
  int jinji_tmp=0;  
    int taotai;
    int jinji;
  sort(b.begin(),b.end());
  int ans =b[nums-1];
  for(const int &tmp:b){
      for(int i=0;i<nums;i++){
          if(tmp>=b[i]){
              taotai_tmp++;
          }
      }
      jinji_tmp = nums-taotai_tmp;
      if(taotai_tmp>=min_t&&taotai_tmp<=max_t&&jinji_tmp>=min_t&&jinji_tmp<=max_t){
        ans = min(ans,tmp);
        cout<<"ans:"<<ans<<endl;
      }
      taotai_tmp=0;
  }
  return ans;
};
int main(){
    int T =3;
    vector<int> a;
    while(T--){
        int b ;
        cin>>b;
        a.push_back(b);
    }
    int nums = a[0];
    vector<int> c;
    for(int i =0; i<nums;i++){
        int d;
        cin>>d;
        c.push_back(d);
    }
    int ans = solution(a,c);
    cout<<ans;
    return 0;
}
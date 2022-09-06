#include <string>
#include <iostream>
#include <vector>

using namespace std;


vector<int> getnext(const string& needle){
    vector<int> next(needle.size());
    int j=-1;
    next[0] =j;
    for(int i=1;i<needle.size();i++){
        
        while(j>0&& needle[i]!=needle[j+1]){
            j = next[j];
        }

        if(needle[i]==needle[j+1]){
            j++;
        }
        next[i] = j;
    }
    return next;
}

int find(const string& haystack, const string & needle){
    //返回匹配的下标
    if(needle.size()==0) return 0;
    vector<int> next = getnext(needle);
    int j=-1;
    for(int i=0;i<haystack.size();i++){
        while(j>0&& haystack[i]!=needle[j+1]){
            j = next[j];
        }

        if(haystack[i]==needle[j+1]){
            j++;
        }
        if(j==needle.size()-1){
            return i+1-needle.size();
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    // string needle = "aaabcd";
    // vector<int> next = getnext(needle);
    // cout<<find("ababcd","cd");

    string a  = "asdasdwfawfwqedvgvgggggg";
    auto s = a.find("zz");
    /*
    if(s == std::string::npos) {
        std::cout << "not found\n";
    */
    // cout<<boolalpha<<(s==string::npos)<<endl;
    printf("%d",true);
    return 0;
}

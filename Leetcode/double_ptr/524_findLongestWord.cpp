#include <vector>
#include <string>

using namespace std;

class Solution{
public:
    string findLongestWord(string s, vector<string>& dictionary){
        int d_size = dictionary[0].size();
        int s_size = s.size();
        int j = 0;
        for(int i =0; i<s_size;i++){
            if(s[i]==dictionary[0][j]){
                j++;
                continue;
            }
        }

        if(j==d_size)
            return dictionary[0];

    }
};
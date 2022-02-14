#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size());
        stack<int> s;//s存的是高元素的下标

        for(int i =temperatures.size()-1;i>=0;i--){

            while (!s.empty() &&   temperatures[s.top()] <=  temperatures[i] )
            {
                s.pop();
            }
            res[i] = s.empty() ? 0 : (s.top()-i);
            s.push(i);
            
        }

        return res;
    }
};
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char,int> need,window;
        for(char c:s1){
            need[c]++;
        }

        int left=0, right=0, valid=0;
        while(right<s2.size()){
            char c = s2[right];
            right++;

            if(need.count(c)){
                window[c]++;
                if(need[c]==window[c]){//只有重复的都找完了，有效才+1，valid=need.size表示全找到了
                    valid++;
                }
            }

            while(right-left>=s1.size()){//这里保证每次只搜寻尺寸为2的窗口
                if(valid==need.size()){
                    return true;
                }
                char d = s2[left];
                left++;
                if(need.count(d)){
                    if(window[d]==need[d]){
                        valid--;
                    }
                    window[d]--;
                }

            }

        }
        return false;
    }
};
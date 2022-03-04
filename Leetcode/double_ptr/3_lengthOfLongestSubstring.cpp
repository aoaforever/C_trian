class Solution{
public:
    int lengthOfLongestSubstring(string s){
        unordered_map<char,int> window;

        int left=0, right=0;
        int ans;

        while(right<s.size()){
            char c = s[right];
            right++;
            
            window[c]++;
            while(window[c]>1){//当有重复字符时。
                char d = s[left];
                left++;
                window[d]--;
            }
            //在尾部更新长度，表示上面操作完成后，窗口不包含重复字符。
            ans = max(ans,right-left);
        }
        return ans;
    }

};
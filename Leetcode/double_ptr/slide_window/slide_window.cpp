#include <unordered_map>
#include <string>
using namespace std;

/*其中两处 ... 表示的更新窗⼝数据的地⽅，到时候你直接往⾥⾯填就⾏了。
⽽且，这两个 ... 处的操作分别是右移和左移窗⼝更新操作，等会你会发现它们操作是完全对称的。*/
void slidingWindow(string s, string t){
    unordered_map<char,int> need, window;
    for(char c: t){ 
        need[c]++;
    }

    int left = 0 , right = 0 ; 
    int valid = 0 ; //valid 变量表示窗⼝中满⾜ need 条件的字符个数，如果 valid 和 need.size 的⼤⼩相同，则说明窗⼝已满⾜条件，已经完全覆盖了串 T。
    while(right<s.size()){
        //c是将要移入窗口的字符
        char c = s[right];
        //右移窗口
        right++;
        //进行窗口内数据的一系列更新
        //。。。

        /* debug 输出位置 */
        printf("window: [%d, %d) \n", left, right);

        //判断左侧窗口是否要收缩
        while(window needs shrink){
            //d是将要移除窗口的字符
            char d = s[left];
            left++;
            //进行窗口内数据的一些列更新
            //....
        }
    }
}

/*
现在开始套模板，只需要思考以下四个问题：
1、当移动 right 扩⼤窗⼝，即加⼊字符时，应该更新哪些数据？
2、什么条件下，窗⼝应该暂停扩⼤，开始移动 left 缩⼩窗⼝？
3、当移动 left 缩⼩窗⼝，即移出字符时，应该更新哪些数据？
4、我们要的结果应该在扩⼤窗⼝时还是缩⼩窗⼝时进⾏更新？

如果⼀个字符进⼊窗⼝，应该增加 window 计数器；如果⼀个字符将移出窗⼝的时候，应该减少 window 计
数器；当 valid 满⾜ need 时应该收缩窗⼝；应该在收缩窗⼝的时候更新最终结果。
*/
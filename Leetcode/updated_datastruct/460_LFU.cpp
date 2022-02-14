#include <iostream>
#include <unordered_map>
#include <list>//双向链表
using namespace std;

//为什么存freq_table[freq].begin()?
//1.freq_table[freq]是一个双链表，begin代表表头的这个迭代器：节点地址。
//2.因为双链表表头代表最新插入的节点，因此插入之后，key_table[key]就是存这个表头节点的地址。

//缓存的节点信息
struct Node{
    int key, val, freq;
    Node(int _key, int _val, int _freq): key(_key), val(_val), freq(_freq){}
};

class LFUCache {
private:
    int minfreq, capacity;
    unordered_map<int, list<Node>::iterator> key_table;//存双向链表某个节点的地址
    unordered_map<int, list<Node>> freq_table;
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minfreq =0;
        key_table.clear();
        freq_table.clear();
    }
    
    int get(int key) {
        if(capacity==0) return -1;
        //有可能这个key不存在
        if(!key_table.count(key)){
            return -1;
        }
        //如果存在
        auto it = key_table.find(key);
        list<Node>::iterator node = it->second;
        
        //找到节点后，频率加1,也就是freq_table要修改，node的freq也要修改
        int freq = node->freq;
        int val = node->val;
        
        freq_table[freq].erase(node);
        // //这里直接用node可能不行。erase（node）不知道会不会delete node。
        // freq_table[freq+1].push_front(*node);
        if(freq_table[freq].size()==0){
            freq_table.erase(freq);
            if(minfreq==freq){
                minfreq++;
            }
        }
        freq_table[freq+1].push_front(Node(key,val,freq+1));
        //key还要存节点的地址
        key_table[key] = freq_table[freq+1].begin();
        return val;

        
    }
    
    void put(int key, int value) {
        if(capacity==0) return ;
        auto it = key_table.find(key);
        //如果当前没有这个key
        if(it == key_table.end()){
            //就插入这个key，又分满和没满两种情况
            //如果缓存已满
            if(key_table.size()== capacity){
                //要先删除频率最小，插入最早的节点
                //通过minFreq 拿到 freq_table[minFreq] 链表末尾的节点
                auto it2 = freq_table[minfreq].back();
                key_table.erase(it2.key);//
                freq_table[minfreq].pop_back();//弹出频率最小，插入最早的节点

                //如果刚好是最后一个节点
                if(freq_table[minfreq].size()==0){
                    freq_table.erase(minfreq);
                }
            }
            //开始插入
            freq_table[1].push_front(Node(key,value,1));
            key_table[key] = freq_table[1].begin();

            minfreq=1;//!!!!!!!!!!!!!!!!!!!!!你漏了这个堆栈错误
            //为什么设置1，因为新插入，最小使用频率当然是一。
        }
        //如果有这个key
        else{
            //与get操作基本一致，除了需要更新缓存的值
            list<Node>::iterator node = it->second;
            int freq = node->freq;
            freq_table[freq].erase(node);//这个不是o(1)吧,可能是，因为它传的是某个节点的地址
            if(freq_table[freq].size()==0){
                freq_table.erase(freq);
                if(minfreq==freq){
                    minfreq++;
                }
            }
            freq_table[freq+1].push_front(Node(key,value,freq+1));
            key_table[key] = freq_table[freq+1].begin();
        }
    }
};

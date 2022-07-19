#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

//节点类。拥有指向前后的指针
class Node{
public:
    int key, val;
public:
    Node *next;
    Node *prev;
public:
    Node(int k, int v){
        key = k;
        val = v;

        //自行添加的代码
        next = nullptr;
        prev = nullptr;
    }

    //自增的函数
    ~Node(){
        next = nullptr;
        prev = nullptr;
    }
};

//用Node类型构造双链表
class DoubleList{

private:
    //头尾虚节点
    Node *head, *tail;
    //链表元素个数
    int nums;//c++中，变量名和函数名不能相同！！！
public: 
    DoubleList(){
        //初始化双向链表的数据
        head = new Node(0,0);
        tail = new Node(0,0);
        head->next = tail;
        tail->prev = head;
        nums = 0;
    }

    //在链表尾部添加节点x,时间O(1)
    void addLast(Node *x){//传指针还是实体还是引用？
        x->prev = tail->prev;
        x->next = tail;
        // tail->prev = x;
        // head->next = x;

        //先修改tail的前一个元素的指针
        tail->prev->next = x;
        tail->prev = x;
        nums++;
    }

    //删除链表中的x节点（x一定存在）
    //由于是双链表且给的是目标Node节点，时间O(1)
    void remove(Node *x){//内存泄漏？？？
        x->prev->next = x->next;
        x->next->prev = x->prev;
        nums--;
        //java只需要写上面这三行

    }

    //删除链表中的第一个节点，并返回该节点，时间O(1)
    Node* removeFirst(){
        if(head->next == tail ){
            return NULL;
        }
        Node *first = head->next;
        remove(first);
        return first;
    }

    //返回链表长度,时间O(1)
    int size(){
        return this->nums;
    }
};

class LRUCache{
//key-> Node(key,val)
private:
    unordered_map<int, Node*> map;
    //Node(k1,v1) <-> Node(k2,v2) ...
    DoubleList cache;
    //最大容量
    int cap;

public:
    LRUCache(int capacity){
        cap = capacity;
    }

private:
    //将某个key提升为最近使用的
    void makeRecently(int key){
        Node* x = map[key];
        //先从链表中删除这个节点
        cache.remove(x);
        //重新插到队尾
        cache.addLast(x);
    }

    //添加最近使用的元素
    void addRecently(int key, int val){
        Node *x = new Node(key,val);
        //链表尾部就是最近使用的元素
        cache.addLast(x);
        //别忘了在map中添加key的映射
        map[key] = x;
    }

    //删除某一个key
    void deleteKey(int key){
        Node *x = map[key];
        //从链表中删除
        cache.remove(x);
        //从map中删除
        map.erase(key);
    }

    //删除最久未使用的元素
    void removeLeastRecently(){
        //链表头部的第一个元素就是最久未使用的
        Node* deletedNode = cache.removeFirst();//最终链表删除的节点会用deletedNode指向
        //同时别忘了从map中删除它的key
        int deletedKey = deletedNode->key;
        map.erase(deletedKey);
        // 所以下面需不需要delete 这个不要的节点呢？
        delete deletedNode;//根据leetcode答案是可以写的。
        // deletedNode = Null;
    }

public: 
    int get(int key){
        if(map.find(key)==map.end()){
            return -1;
        }
        //将该数据提升为最近使用的
        makeRecently(key);
        return map[key]->val;
    }

    void put(int key, int val){
        if(map.find(key)!=map.end()){
            //如果存在这个key,则把它作为最近使用的数据
            deleteKey(key);
            addRecently(key,val);
            return;
        }
        //不然，先判断是否满任务
        if(cache.size() == cap){
            //删除最久没使用的任务
            removeLeastRecently();
        }

        addRecently(key,val);
    }
};






// 作者：LeetCode-Solution
// 链接：https://leetcode-cn.com/problems/lru-cache/solution/lruhuan-cun-ji-zhi-by-leetcode-solution/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};

/*//////////////////////////////////////*/
class LRUCache {
public:
    int capacity;
    list<pair<int,int>> lru;


    unordered_map<int,list<pair<int,int>>::iterator> keytonode;
    //每个key对应一个链表节点迭代器
    LRUCache(int capacity) {
        this->capacity = capacity;

    }
    
    int get(int key) {
        //key被用过，删除重新添加。
        //如果没有这个key，返回-1
        if(!keytonode.count(key)) return -1;
        auto ptr = keytonode[key];
        int val = (*ptr).second;

        lru.erase(ptr);
        lru.push_back({key,val});
        keytonode[key] = prev(lru.end());
        return val;
    }
    
    void put(int key, int value) {
        //如果存在这个key，删除重新添加
        if(keytonode.count(key)){
            lru.erase(keytonode[key]);
            lru.push_back({key,value});
            keytonode[key] = prev(lru.end());
        }
        else{
            if(lru.size()>=capacity) del();
            lru.push_back({key,value});
            keytonode[key] = prev(lru.end());
            // capacity++; //根本就不需要增加容量？？你想什么呢？
        }
    }
    void del(){
        auto node = lru.begin();
        int key = (*node).first;
        keytonode.erase(key);
        lru.pop_front();
    }


};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */



int main(){
    unordered_map<int,int> a;
    a[10] = 20;
    auto p = a[10];
    return 0;
}
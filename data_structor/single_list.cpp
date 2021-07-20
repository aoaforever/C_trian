#include <iostream>
#include <stdlib.h>

typedef struct LNode{
    int value;
    struct LNode *next;
}LNode,*LinkList;

//新建一个节点
LinkList initial(){
    LinkList L = (LNode*) malloc (sizeof(LNode));
    if (L==NULL)
        return NULL;
    L->next=NULL;
    return L;
}

//在某个节点之后插入元素,时间复杂度O(1)
bool InsertafterNode(LNode * p, int value){
    if (p==NULL)
        return false;

    LNode* s =initial();
    s->value=value;
    s->next=p->next;
    p->next=s;
    return true;
    
}

//在某个节点之前插入元素,时间复杂度O(1)
bool InsertbeforeNode(LNode * p, int value){
    if (p==NULL)
        return false;

    LNode* s =initial();
   
    s->next=p->next;
    p->next=s;

    s->value=p->value;
    p->value=value;


    return true;
    
}


//在表最后后插一个值
bool tailInsert(LinkList &L, int value){
  
    //遍历到最后一个节点
    LNode*p=L;
    while(p->next!=NULL)
        p=p->next;

    InsertafterNode(p,value);



    return true;
}

void print_list(LinkList L){
    //带头指针
    LNode* p=L;
    
    p=p->next;
    while(p!= NULL){
        printf("value = %d\t",p->value);
        p=p->next;
    }
    printf("\n");

}

//在第i个节点后插一个节点
bool tailInsert_i(LinkList &L, int i, int value){

    if(i==0){
        //不能插入在表头
        return false;
    }


    //搜索位置i,找到第i节点的前一个节点
    LNode* P= L;
    for (int j =0 ; j<i-1 ; j++){
        P=P->next;
    }

    //在这判断i是否超出表的长度
    if (P==NULL)
        return false;

    InsertafterNode(P,value);
    
    return true;

}

//在第i个节点前插一个节点
bool priorInsert_i(LinkList &L, int i, int value){

    if(i==0){
        //不能插入在表头
        return false;
    }


    //搜索位置i,找到第i节点的前一个节点
    LNode* P= L;
    for (int j =0 ; j<i ; j++){
        P=P->next;
    }

    //在这判断i是否超出表的长度
    if (P==NULL)
        return false;

    InsertbeforeNode(P,value);
    
    return true;

}
//指定p节点删除,时间复杂度O(1)
bool deleteNode(LNode* p, int &e ){
    if(p==NULL)
        return false;

    LNode* q=p->next;
    if (q==NULL)
        return false;//如果p刚好是最后一个节点，不给表头是无法删除的。
    p->next=q->next;
    e=p->value;
    p->value=q->value;

    free(q);
    return true;
}

//按位序删除，删除第i个节点
bool deleteNode_i(LinkList & L, int i , int &e){
    if(i<1)
        return false;    

    LNode* p =L;
    for(int j =0; j<i-1; j++){
        p=p->next;
    }

    if (p==NULL)
        return false;

    if(p->next==NULL)
        return false;//第i-1个节点就是最后一个节点了。

    // LNode* q=p->next;
    // p->next=q->next;
    // e=q->value;

    // free(q);

    deleteNode(p->next,e);//如果i是最后一个节点，这个函数也是不能够删除的


    return true;
}



/*判断三件事：
1.位序不能是头节点 i<1 ，false;
2.该节点是否为空
3.是否超出列表范围
*/

int main(){
    LinkList L = initial();
    //在L后面先插几个节点
    tailInsert(L,1);
    tailInsert(L,2);
    tailInsert(L,3);
    tailInsert(L,4);
    print_list(L);

    //在第i个位置插入元素
    tailInsert_i(L,1,125 );
    print_list(L);

    priorInsert_i(L,2,222);
    print_list(L);

    int e=0;
    deleteNode_i(L,6,e);
    print_list(L);
    printf("e=%d\n",e);

    return 0;
}
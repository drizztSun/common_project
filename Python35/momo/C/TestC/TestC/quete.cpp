#include<stdlib.h>
#include<stdio.h>

#define NULL 0

typedef struct node{
    int data;
    struct node *next;
}node;

typedef struct queue{
    node *front;    
    node *rear;     
}queue;

//初始化结点
node *init_node(){
    node *n=(node*)malloc(sizeof(node));
    if(n==NULL){    //建立失败，退出
        exit(0);
    }
    return n;
}

//初始化队列
queue *init_queue(){
    queue *q=(queue*)malloc(sizeof(queue));
    if(q==NULL){    //建立失败，退出
        exit(0);
    }
    //头尾结点均赋值NULL
    q->front=NULL;  
    q->rear=NULL;
    return q;
}

//队列判空
int empty(queue *q){
    if(q->front==NULL){
        return 1;   //1--表示真，说明队列非空
    }else{
        return 0;   //0--表示假，说明队列为空
    }
}

//入队操作
void push(queue *q,int data){
    node *n =init_node();
    n->data=data;
    n->next=NULL;   //采用尾插入法
    //if(q->rear==NULL){     //使用此方法也可以
    if(empty(q)){
        q->front=n;
        q->rear=n;
    }else{
        q->rear->next=n;    //n成为当前尾结点的下一结点
        q->rear=n;  //让尾指针指向n
    }
}

//出队操作
void pop(queue *q){
    node *n=q->front;
    if(empty(q)){
        return ;    //此时队列为空，直接返回函数结束
    }
    if(q->front==q->rear){
        q->front=NULL;  //只有一个元素时直接将两端指向置为空即可
        q->rear=NULL;
        free(n);        //记得归还内存空间
    }else{
        q->front=q->front->next;
        free(n);
    }
}

void print_queue(queue *q){
    node *n = init_node();
    n=q->front;
    if(empty(q)){
        return ;    //此时队列为空，直接返回函数结束
    }
    while (n!=NULL){
        printf("%d\t",n->data);
        n=n->next;
    }
    printf("\n");   //记得换行
}

void iter_print_queue(queue *q){
    node *n = q->front;
    while (n!=NULL){//or while(n)
        printf("%d\t",n->data);
        n = n->next;
    }
}

int main() {
    printf("Hello world!");
}

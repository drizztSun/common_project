#include<stdlib.h>
#include<stdio.h>
#define maxsize 10

struct cirqueue{
    int data[maxsize];
    int front;
    int rear;
    int length;
}; 

int empty(cirqueue*);

cirqueue *init(){
    cirqueue *q = (cirqueue*)malloc(sizeof(cirqueue));
    q->front=0;
    q->rear=0;
    q->length = 0;
    return q;
}
int empty(const cirqueue *qu){
    return qu->length == 0 ? 1 : 0; 
}

int full(const cirqueue *qu){
    return qu->length == maxsize ? 1 : 0; 
}

int front(const cirqueue *qu){
    return ! empty(qu) ? qu->data[qu->front] : 0;
}

int rear(const cirqueue *qu){
    return ! empty(qu) ? qu->data[qu->rear] : 0; 
}
void push(cirqueue *qu, int x){
    if(full(qu)){
        printf("size exceed \n");
        return;
    }
    if(qu){
        qu ->data[qu->rear] = x;
        qu->length++;
        return;
    }
    qu->rear++;
    qu ->data[qu->rear] = x;
    qu->length++;
    if(qu->rear == maxsize+1){
        qu->rear = 0;
    }
    return;
    
}

void pop(cirqueue *qu){
    if(empty(qu)){
        return;
    }
    qu->front--;
    qu->length--;
    return;   
}

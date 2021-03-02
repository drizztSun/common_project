/*
225. Implement Stack using Queues

Implement a last in first out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal queue (push, top, pop, and empty).

Implement the MyStack class:

void push(int x) Pushes element x to the top of the stack.
int pop() Removes the element on the top of the stack and returns it.
int top() Returns the element on the top of the stack.
boolean empty() Returns true if the stack is empty, false otherwise.
Notes:

You must use only standard operations of a queue, which means only push to back, peek/pop from front, size, and is empty operations are valid.
Depending on your language, the queue may not be supported natively. You may simulate a queue using a list or deque (double-ended queue), as long as you use only a queue's standard operations.
 

Example 1:

Input
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 2, 2, false]

Explanation
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // return 2
myStack.pop(); // return 2
myStack.empty(); // return False
 

Constraints:

1 <= x <= 9
At most 100 calls will be made to push, pop, top, and empty.
All the calls to pop and top are valid.
 

Follow-up: Can you implement the stack such that each operation is amortized O(1) time complexity? In other words, performing n operations will take overall O(n) time even if one of those operations may take longer. You can use more than two queues.

*/
#include <queue>

using std::queue;


/*
225.Implement-Stack-using-Queues
比较直观的解法：使用一个队列，需要读或者退出队列末尾的元素时，可重复将队首元素弹出并加回队列，重复len-1次即可（len是队列的长度）。缺点是，即使是每次读队列末尾元素也要绕一圈。

更好的解法是：在每次往队列push元素的时候，就进行一次大反转，使得队列里的元素其实是以从新到旧的顺序排放的。这样，每次top()和pop()的操作都只要o(1)的时间操作。
*/

class MyStack {
    queue<int>q;
public:
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    // O(n)
    void push(int x) 
    {
        q.push(x);
        for (int i=0; i<q.size()-1; i++)
        {
            q.push(q.front());
            q.pop();
        }        
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() 
    {
        int result=q.front();
        q.pop();
        return result;
    }
    
    /** Get the top element. */
    int top() 
    {
        return q.front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() 
    {
        return q.empty();
    }
};


class MyStack {
    queue<int> buff;
    int _top = INT_MAX;
    
public:
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        buff.push(x);
        _top = x;
    }
    
    /** Removes the element on top of the stack and returns that element. */
    // O(n)
    int pop() {
        queue<int> tmp;
        int size = buff.size() - 1;
        
        while (size--) {
            _top = buff.front();
            tmp.push(_top);
            buff.pop();
        }
        
        int x = buff.front();
        std::swap(buff, tmp);
        return x;
    }
    
    /** Get the top element. */
    int top() {
        return _top;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return buff.size() == 0;
    }
};


// all O(1)
class MyStack {
public:
    queue<void*> *q;

    /** Initialize your data structure here. */
    MyStack() {
        q = new queue<void*>();
    }

    ~MyStack() {
        delete q;
    }

    /** Push element x onto stack. */
    void push(int x) {
        queue<void*> *newQ = new queue<void*>();
        newQ->push((void*) x);
        newQ->push((void*) q);
        q = newQ;
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int res = (char*) q->front() - (char*) 0;
        q->pop();
        queue<void*> *newQ = (queue<void*>*) q->front();
        q->pop();
        delete q;
        q = newQ;
        return res;
    }
    
    /** Get the top element. */
    int top() {
        return (char*) q->front() - (char*) 0;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q->empty();
    }
};
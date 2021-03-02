/*
232. Implement Queue using Stacks

Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.
Notes:

You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.
Follow-up: Can you implement the queue such that each operation is amortized O(1) time complexity? In other words, performing n operations will take overall O(n) time even if one of those operations may take longer.

 

Example 1:

Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]

Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
 

Constraints:

1 <= x <= 9
At most 100 calls will be made to push, pop, peek, and empty.
All the calls to pop and peek are valid.


*/
#include <stack>

using std::stack;

/*
232.Implement-Queue-using-Stacks
此题设置两个stack。

一个简单的想法是：第二个栈仅仅用作临时倾倒stack1元素的备用容器。每次需要remove或get第一个栈的栈底元素时，将Stack1的所有元素（除栈底）倒入Stack2中，然后操作之后再把Stack2的元素都倒回Stack1中。这种方法有点浪费时间。

更好的设计是：因为Stack2已经把元素反向，所以任何类似Queue队首的操作都可以在Stack2里操作，取Stack2的栈顶即可。而对于Queue队尾的push操作，则留在Stack1完成。只有当Stack2已经空了的时候，才需要把Stack1里的元素倒入Stack2.

*/

class MyQueue {
    stack<int>Stack1;
    stack<int>Stack2;
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) 
    {
        Stack1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() 
    {
        if (Stack2.empty())
        {
            while (!Stack1.empty())
            {
                Stack2.push(Stack1.top());
                Stack1.pop();
            }
        }
        int result=Stack2.top();
        Stack2.pop();
        return result;
    }
    
    /** Get the front element. */
    int peek() 
    {
        if (Stack2.empty())
        {
            while (!Stack1.empty())
            {
                Stack2.push(Stack1.top());
                Stack1.pop();
            }
        }
        return Stack2.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() 
    {
        return Stack1.empty()&&Stack2.empty();
    }
};

// all O(1)
class MyQueue {
    stack<int>Stack1;
    stack<int>Stack2;
    int front = 0;

public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) 
    {
        if (Stack1.empty())
            front = x;
        Stack1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() 
    {
        if (Stack2.empty())
        {
            while (!Stack1.empty())
            {
                Stack2.push(Stack1.top());
                Stack1.pop();
            }
        }
        int result=Stack2.top();
        Stack2.pop();
        return result;
    }
    
    /** Get the front element. */
    int peek() 
    {
        if (!Stack2.empty())
        {
            return Stack2.top();  
        }
        return front;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() 
    {
        return Stack1.empty()&&Stack2.empty();
    }
};
/*
155. Min Stack

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
 

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
 

Constraints:

Methods pop, top and getMin operations will always be called on non-empty stacks.


*/
#include <stack>

using std::stack;

/*
    155.Min-Stack
    解法1：
    要做到实时得到getMin()，不妨就对栈内的每一个元素都记录下对应的当前栈内元素最小值。于是我们可以构建另一个栈StackMin，跟随数据本身的Stack同步进退。

        void push(int x) 
        {
            Stack.push(x);
            if (StackMin.empty())
                StackMin.push(x);
            else
                StackMin.push(min(x,StackMin.top()));
        }
    解法2：
    有一种更省空间的解法。就是压入栈内的元素不直接是x，而是delta = x-Min_old。

    入栈的时候，如果delta为正数，那么说明Min变量需要更新为Min_new = Min_old，否则就是Min_new = x

    出栈的时候，我们看到的是栈顶元素delta，以及Min_new。我们需要复原的是x和Min_old：

    如果delta是正号，说明Min_old = Min_new，然后推出x = delta+Min_old.
    如果delta是负号，说明x = Min_new，然后推出Min_old = x-delta.
*/
class MinStack {
    stack<int>Stack;
    stack<int>StackMin;
public:
    /** initialize your data structure here. */
    MinStack() { }
    
    void push(int x) 
    {
        Stack.push(x);
        if (StackMin.empty())
            StackMin.push(x);
        else
            StackMin.push(std::min(x,StackMin.top()));
    }
    
    void pop() 
    {
        Stack.pop();
        StackMin.pop();
    }
    
    int top() 
    {
        return Stack.top();
    }
    
    int getMin() 
    {
        return StackMin.top();
    }
};

class MinStack {
    stack<long long>Stack;
    long long Min;
public:
    /** initialize your data structure here. */
    MinStack() { }
    
    void push(int x) {
        if (Stack.empty())
        {
            Stack.push(0);
            Min = x;
        }
        else
        {
            if (x>=Min)
                Stack.push(x-Min);
            else
            {
                Stack.push(x-Min);
                Min = x;
            }
        }
    }
    
    void pop() 
    {
        if (Stack.top()<0)
            Min = Min + (-Stack.top());   
        Stack.pop();
    }
    
    int top() {
        int ret;
        if (Stack.top()>=0)
            ret = Stack.top()+Min;                    
        else
            ret = Min;
        return ret;
    }
    
    int getMin() {
        return Min;
    }
};




class MinStack {

    stack<std::pair<int, int>> st;

public:
    /** initialize your data structure here. */
    MinStack() {}
    
    void push(int x) {
        if (st.empty())    
            st.push({x, x});
        else
            st.push({x, std::min(x, st.top().second)});
    }
    
    void pop() {
        if (!st.empty()) st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};

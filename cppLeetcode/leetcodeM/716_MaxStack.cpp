/*
716. Max Stack

Design a max stack data structure that supports the stack operations and supports finding the stack's maximum element.

Implement the MaxStack class:

MaxStack() Initializes the stack object.
void push(int x) Pushes element x onto the stack.
int pop() Removes the element on top of the stack and returns it.
int top() Gets the element on the top of the stack without removing it.
int peekMax() Retrieves the maximum element in the stack without removing it.
int popMax() Retrieves the maximum element in the stack and removes it. If there is more than one maximum element, only remove the top-most one.
 

Example 1:

Input
["MaxStack", "push", "push", "push", "top", "popMax", "top", "peekMax", "pop", "top"]
[[], [5], [1], [5], [], [], [], [], [], []]
Output
[null, null, null, null, 5, 5, 1, 5, 1, 5]

Explanation
MaxStack stk = new MaxStack();
stk.push(5);   // [5] the top of the stack and the maximum number is 5.
stk.push(1);   // [5, 1] the top of the stack is 1, but the maximum is 5.
stk.push(5);   // [5, 1, 5] the top of the stack is 5, which is also the maximum, because it is the top most one.
stk.top();     // return 5, [5, 1, 5] the stack did not change.
stk.popMax();  // return 5, [5, 1] the stack is changed now, and the top is different from the max.
stk.top();     // return 1, [5, 1] the stack did not change.
stk.peekMax(); // return 5, [5, 1] the stack did not change.
stk.pop();     // return 1, [5] the top of the stack and the max element is now 5.
stk.top();     // return 5, [5] the stack did not change.
 

Constraints:

-107 <= x <= 107
At most 104 calls will be made to push, pop, top, peekMax, and popMax.
There will be at least one element in the stack when pop, top, peekMax, or popMax is called.
 

Follow up: Could you come up with a solution that supports O(1) for each top call and O(logn) for each other call? 

*/
#include <stack>
#include <list>
#include <map>
#include <vector>


using std::vector;
using std::map;
using std::list;
using std::stack;

/*
    716.Max-Stack
    此题初看很像 155.Min Stack，但本质有很大的不同，问题就在于popMax()这个操作，从一个数据结构的中段弹出元素，完全不是stack的风格。所以需要果断放弃155题的思路。那么哪些数据结构可以方便的删除中段的元素呢？似乎只有list了。

    回顾 460.LFU Cache，我们已经接触过了list。其操作非常类似vector，而且还有一个非常巨大的优势，可以根据iterator来删除任意元素。本题的思路和460也非常相似，就是用到了一个有序的map，其key是list里的元素的数值，而value就是对应key的所有list元素的迭代器（可以理解为地址或指针）。

    设计了以上的数据结构，操作就很容易了。对于popMax()，我们直接在Map的尾元素得到当前链表的最大值 x=(--Map.end())->first。然后auto it = Map[x].back()就是当前链表最顶端的最大值的地址。直接在list中删除即可 List.erase(it)。

    特别注意，popMax(x)和pop(x)操之后，可能Map[x]的元素个数就是0了，此时一定要将Map删除这个key！

*/
class MaxStack {
    list<int>List;
    map<int,vector<list<int>::iterator>>Map;

public:

    /** initialize your data structure here. */
    MaxStack() {}
    
    void push(int x) 
    {
        List.push_back(x);
        Map[x].push_back(--List.end());
    }
    
    int pop() 
    {
        int x=List.back();
        Map[x].pop_back();
        if (Map[x].size()==0)
            Map.erase(x);
        List.pop_back();
        return x;
    }
    
    int top() 
    {
        return List.back();
    }
    
    int peekMax() 
    {
        return (--Map.end())->first;
    }
    
    int popMax() 
    {
        /*
            int maxv = _maxbuf.rbegin()->first;
            auto it = _maxbuf.rbegin()->second.back();
            _maxbuf.rbegin()->second.pop_back();
            if (_maxbuf.rbegin()->second.empty())
                _maxbuf.erase(maxv);
            _buf.erase(it);
            return maxv;
        */
        int x=(--Map.end())->first;
        auto it=Map[x].back();
        Map[x].pop_back();
        if (Map[x].size()==0)
            Map.erase(x);
        List.erase(it);
        return x;
    }
};

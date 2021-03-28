/*
1381. Design a Stack With Increment Operation

Design a stack which supports the following operations.

Implement the CustomStack class:

    .CustomStack(int maxSize) Initializes the object with maxSize which is the maximum number of elements in the stack or do nothing if the stack reached the maxSize.
    .void push(int x) Adds x to the top of the stack if the stack hasn't reached the maxSize.
    .int pop() Pops and returns the top of stack or -1 if the stack is empty.
    .void inc(int k, int val) Increments the bottom k elements of the stack by val. If there are less than k elements in the stack, just increment all the elements in the stack.
 

Example 1:

Input
["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
[[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
Output
[null,null,null,2,null,null,null,null,null,103,202,201,-1]
Explanation
CustomStack customStack = new CustomStack(3); // Stack is Empty []
customStack.push(1);                          // stack becomes [1]
customStack.push(2);                          // stack becomes [1, 2]
customStack.pop();                            // return 2 --> Return top of the stack 2, stack becomes [1]
customStack.push(2);                          // stack becomes [1, 2]
customStack.push(3);                          // stack becomes [1, 2, 3]
customStack.push(4);                          // stack still [1, 2, 3], Don't add another elements as size is 4
customStack.increment(5, 100);                // stack becomes [101, 102, 103]
customStack.increment(2, 100);                // stack becomes [201, 202, 103]
customStack.pop();                            // return 103 --> Return top of the stack 103, stack becomes [201, 202]
customStack.pop();                            // return 202 --> Return top of the stack 102, stack becomes [201]
customStack.pop();                            // return 201 --> Return top of the stack 101, stack becomes []
customStack.pop();                            // return -1 --> Stack is empty return -1.
 

Constraints:

1 <= maxSize <= 1000
1 <= x <= 1000
1 <= k <= 1000
0 <= val <= 100
At most 1000 calls will be made to each method of increment, push and pop each separately.

*/

#include <vector>
using std::vector;



class CustomStack {
    
    vector<int> _nums;
    vector<int> _add;
    
    int _maxsize;
    
public:
    
    CustomStack(int maxSize) {
        _maxsize = maxSize;
    }
    
    void push(int x) {

        if (_nums.size() == _maxsize) return;
        
        _nums.push_back(x);
        
        _add.push_back(0);
    }
    
    int pop() {
        
        if (_nums.empty()) return -1;
        
        int val = _nums.back() + _add.back();
        _nums.pop_back();

        if (_add.size() > 1) _add[_add.size()-2] += _add.back();
        _add.pop_back();
        return val;
    }
    
    void increment(int k, int val) {
        
        if (_add.empty()) return;
        
        int idx = k >= _add.size() ? _add.size() -1 : k-1; 
        _add[idx] += val;
    }
};

/*
Explanation
Use an additional array to record the increment value.
inc[i] means for all elements stack[0] ~ stack[i],
we should plus inc[i] when popped from the stack.
Then inc[i-1]+=inc[i],
so that we can accumulate the increment inc[i]
for the bottom elements and the following pops.


Complexity
C++/Python, initialization is O(1) time & space.
Java, initialization is O(N) time & space.
(We cam use ArrayList, but shrug)
push, pop, increment, all O(1) time and space.


*/
class CustomStack {
    
    vector<int> stack, inc;
    int n;
    
    CustomStack(int maxSize) {
        n = maxSize;
    }

    void push(int x) {
        if (stack.size() == n) return;
        stack.push_back(x);
        inc.push_back(0);
    }

    int pop() {
        int i = stack.size() - 1;
        if (i < 0) return -1;
        if (i > 0) inc[i - 1] += inc[i];
        int res = stack[i] + inc[i];
        stack.pop_back();
        inc.pop_back();
        return res;
    }

    void increment(int k, int val) {
        int i = std::min(k, (int)stack.size()) - 1;
        if (i >= 0) inc[i] += val;
    }
};

/*
    1381.Design-a-Stack-With-Increment-Operation
    本题虽然暴力解可以AC，但是有o(N)的优秀解法。用到的就是差分数组的原理。类似的题有1109.Corporate Flight Bookings

    假设当我们遇到increment(k,val)操作时，我们设置offset[k]=value。这样当我们退栈的过程中遇到第k个元素的时候，就知道从此往下继续退栈的话，所有的元素都要加上一个diff = value。
    如果往下退栈的过程中再遇到另一个offset[k2] = value2，就知道从k2往下继续退栈出的元素都要加上一个diff = value+value2.

    特别注意的是，当如果你需要入栈第k个元素的时候，你需要记录offset[k-1] = diff，同时将手头的diff清空。
*/

class CustomStack {
    vector<int>nums;
    vector<int>offset;
    int maxSize;
    int count = 0;
    int diff = 0;
public:
    CustomStack(int maxSize) 
    {
        this->maxSize =  maxSize;
        nums.resize(maxSize, 0);
        offset.resize(maxSize, 0);
    }
    
    void push(int x) 
    {
        if (count==maxSize) return;
        
        if (count>=1)
            offset[count-1] += diff;
        diff = 0;
        
        nums[count] = x;
        offset[count] = 0;
        count++;        
    }
    
    int pop() 
    {
        if (count==0) return -1;
        
        diff += offset[count-1];
        int ret = nums[count-1] + diff;
        count -= 1;
        return ret;        
    }
    
    void increment(int k, int val) 
    {
        if (count == 0) return;
        offset[min(k-1, count-1)] += val;
    }
};

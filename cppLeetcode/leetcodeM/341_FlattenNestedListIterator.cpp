/*
341. Flatten Nested List Iterator


Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:

Input: [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false, 
             the order of elements returned by next should be: [1,1,2,1,1].
Example 2:

Input: [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false, 
             the order of elements returned by next should be: [1,4,6].


*/


/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
#include <vector>
#include <stack>

using std::stack;
using std::vector;

class NestedIterator {

    /*
        341.Flatten-Nested-List-Iterator
        仔细分析数据结构的定义。vector<NestedInteger>包含的是元素是NestedInteger类型. 当对元素做.getInteger()操作后得到的才是整形；做.getList()操作后得到的是vector<NestedInteger>类型。

        设计一个stack<NestedInteger>Stack的堆栈。

        hasNext()的目的，就是将Stack的栈顶元素不断展开（如果对应的是List数据的话），直至栈顶元素isInteger()为止。则下一步的next()就是读取栈顶元素并抽取整形数据，同时退栈。
    */
    stack<NestedInteger>Stack;
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) 
    {
        for (int i=nestedList.size()-1; i>=0; i--)
            Stack.push(nestedList[i]);
    }

    int next() 
    {
        int result=Stack.top().getInteger();
        Stack.pop();
        return result;
    }

    bool hasNext() 
    {
        while (!Stack.empty() && Stack.top().isInteger() == false)
        {
            vector<NestedInteger>temp = Stack.top().getList();
            Stack.pop();
            for (int i=temp.size()-1; i>=0; i--)
                Stack.push(temp[i]);
        }
        
        return !Stack.empty();
    }
};
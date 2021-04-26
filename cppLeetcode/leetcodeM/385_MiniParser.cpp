/*
385. Mini Parser

Given a nested list of integers represented as a string, implement a parser to deserialize it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Note: You may assume that the string is well-formed:

. String is non-empty.
. String does not contain white spaces.
. String contains only digits 0-9, [, - ,, ].
 

Example 1:

Given s = "324",

You should return a NestedInteger object which contains a single integer 324.
 

Example 2:

Given s = "[123,[456,[789]]]",

Return a NestedInteger object containing a nested list with 2 elements:

1. An integer containing value 123.
2. A nested list containing two elements:
    i.  An integer containing value 456.
    ii. A nested list with one element:
         a. An integer containing value 789.
 

*/
#include <stack>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::stack;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {

    // This is the interface that allows for creating nested lists.
    // You should not implement it, or speculate about its implementation
    class NestedInteger {
        public:
        // Constructor initializes an empty nested list.
        NestedInteger();
    
        // Constructor initializes a single integer.
        NestedInteger(int value);
    
        // Return true if this NestedInteger holds a single integer, rather than a nested list.
        bool isInteger() const;
    
        // Return the single integer that this NestedInteger holds, if it holds a single integer
        // The result is undefined if this NestedInteger holds a nested list
        int getInteger() const;
    
        // Set this NestedInteger to hold a single integer.
        void setInteger(int value);
    
        // Set this NestedInteger to hold a nested list and adds a nested integer to it.
        void add(const NestedInteger &ni);
    
        // Return the nested list that this NestedInteger holds, if it holds a nested list
        // The result is undefined if this NestedInteger holds a single integer
        const vector<NestedInteger> &getList() const;
    };
  
    /*
        385.Mini-Parser
        本题涉及了一种不常见的自定义数据结构NestedInteger，需要好好分析。

        本题一个可以取巧的地方在于：任何一个NestedInteger变量都可以完全看做是一个vector，哪怕这个list里的元素只有1.这样就避免了考虑这个NestedInteger变量可能仅有一个int的麻烦。

        另外，注意到NestedInteger类没有给出清零的操作，所以必须尽量不借助多余的变量来实现栈的操作。

        具体的算法是：

        遇到s[i]=='['时，就要新开了一个NestedInteger的变量。这个变量的本质要是一个List，后续的同级元素都是它的子元素。怎么利用构造函数新开一个类的对象呢？
        Stack.push(NestedInteger());
        这样，这个变量不用命名、不用赋初值就可以直接放入栈里。

        遇到s[i]是数字开头时，把完整的数字段抽取出来后得到val。需要这个val转成NestedInteger并放入当前Stack.top()里成为它的一个元素。
        Stack.top().add(Integer(val));
        遇到s[i]==']'时，说明Stack.top()已经把同一层级的所有元素收罗干净了。它本身整个就要投入自己上一级的NestedInteger中，成为它的一个元素。
        NestedInteger temp=Stack.top();
        Stack.pop();
        Stack.top().add(temp);
        特别注意的是，上述语句的前提条件是 Stack.size()>1
    */
    NestedInteger deserialize(string s) 
    {
        if (s[0]!='[') return NestedInteger(stoi(s));
        
        stack<NestedInteger>Stack;
        
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='[')
                Stack.push(NestedInteger());
            else 
            {
                int i0=i;
                while (i<s.size() && s[i]!=',' && s[i]!=']') i++;

                if (i>i0)
                {
                    int num = stoi(s.substr(i0,i-i0));
                    Stack.top().add(NestedInteger(num));
                }
                
                if (s[i]==']' && Stack.size()>1)
                {
                    NestedInteger temp=Stack.top();
                    Stack.pop();
                    Stack.top().add(temp);
                }
            }
        }
        
        return Stack.top();
    }

public:
    NestedInteger deserialize_stack(string s) {
        
        if (s[0]!='[') return NestedInteger(stoi(s));
        
        vector<NestedInteger> st;
        long long num = 0;
        bool isnum = false;
        int sig = 1;
        
        for (int i = 0; i < s.length(); i++) {
            
            if (isdigit(s[i])) {
                isnum = true;
                num = num * 10 + s[i] - '0';
            } else if (s[i] == '-') {
                sig = -1;
            }
            else if (s[i] == '[') {
                st.push_back(NestedInteger());
            } else if (s[i] == ',') {
                if (!isnum) continue;
                st.back().add(NestedInteger(sig*num));
                sig = 1;
                num = 0;
                isnum = false;
            } else if (s[i] == ']') {
                if (isnum)
                    st.back().add(NestedInteger(sig * num));
                if (st.size() == 1) continue;
                sig = 1;
                num = 0;
                auto c = st.back();
                st.pop_back();
                st.back().add(c);
                isnum = false;
            }
        }
        
        return st.back();
    }

    char* a;
    void pa(char* x) {
        std::cout << (int)(x - a) << std::endl;
    }
private:
    NestedInteger xdeserialize(char* &x) {
        if (*x == '[') {
            ++x;
            auto y = NestedInteger();
            if (*x == ']') {
                ++x;
                return y;
            }
            for (--x; *x != ']';)
                y.add(xdeserialize(++x));
            ++x;
            pa(x);
            return y;
        }
        else {
            bool s = false;
            if (*x == '-') {
                ++x;
                s = true;
            }
            int z = 0;
            for (; isdigit(*x); ++x) 
                z = z * 10 + *x - '0';
            if (s)
                z *= -1;
            return NestedInteger(z);
        }
    }
public:
    NestedInteger deserialize(string s) {
        char* x = (char*)s.c_str();
        a = x;
        return xdeserialize(x);
    }
};
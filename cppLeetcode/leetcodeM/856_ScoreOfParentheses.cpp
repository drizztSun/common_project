/*
856. Score of Parentheses

Given a balanced parentheses string S, compute the score of the string based on the following rule:

() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.
 

Example 1:

Input: "()"
Output: 1
Example 2:

Input: "(())"
Output: 2
Example 3:

Input: "()()"
Output: 2
Example 4:

Input: "(()(()))"
Output: 6
 

Note:

S is a balanced parentheses string, containing only ( and ).
2 <= S.length <= 50


*/
#include <stack>
#include <string>

using std::string;
using std::stack;

class ScoreOFParentheses {

    /*
        856.Score-of-Parentheses
        此题的本质是一道Parentheses Parse。规则如下：同一层级的元素需要相加。更高一层级的元素（括号内）在脱括号的时候乘以2.不过有一个特殊的规则，如果更高一层级的元素是空，那么脱括号的时候赋值为1.
    */
    int doit_stack_parenthesis(string S) {
        stack<int>Stack;
        int cur = 0;
        for (auto ch: S)
        {
            if (ch==')')
            {
                if (cur==0)
                    cur = 1;
                else // "(((())))"
                    cur = cur*2;
                cur = Stack.top()+cur;
                Stack.pop();
            }
            else
            {
                // push it "((()))((..."
                Stack.push(cur);
                cur = 0;
            }
        }
        return cur;
    }

public:
    
    int doit_stack_parenthesis(string S) {
        
        stack<int> st;
        st.push(0);

        for (auto c : S) {

            if (c == '(')
                st.push(0);
            else {
                int v = st.top();
                st.pop();
                st.top() += std::max(2 * v, 1);
            }
        }
        
        return st.top();
    }

    /*
        Approach 0: Stack
        cur record the score at the current layer level.

        If we meet '(',
        we push the current score to stack,
        enter the next inner layer level,
        and reset cur = 0.

        If we meet ')',
        the cur score will be doubled and will be at least 1.
        We exit the current layer level,
        and set cur = stack.pop() + cur

        Complexity: O(N) time and O(N) space
    */
    int doit_stack_1(string S) {
        stack<int> stack;
        int cur = 0;
        for (char i : S)
            if (i == '(') {
                stack.push(cur);
                cur = 0;
            }
            else {
                cur += stack.top() + std::max(cur, 1);
                stack.pop();
            }
        return cur;
    }

    /*
        Approach 1: Array
        Same as stack, I do it with an array.
        We change a pointer instead of pushing/popping repeatedly.

        Complexity: O(N) time and O(N) space
    */
    int doit_array(string S) {
        int res[30] = {0}, i = 0;
        for (char c : S)
            if (c == '(') 
                res[++i] = 0;
            else 
                res[i - 1] += std::max(res[i] * 2, 1), i--;
        return res[0];
    }

    /*
        Follow-Up
        Can you solve it in O(1) space?

        Approach 2: O(1) Space
        We count the number of layers.
        If we meet '(' layers number l++
        else we meet ')' layers number l--

        If we meet "()", we know the number of layer outside,
        so we can calculate the score res += 1 << l.
    */
    int doit_01(string S) {
        
        int res = 0, l = 0;
        
        for (int i = 0; i < S.length(); ++i) {
            if (S[i] == '(') 
                l++; 
            else 
                l--;
            
            if (S[i] == ')' && S[i - 1] == '(') 
                res += 1 << l;
        }
        return res;
    }
};
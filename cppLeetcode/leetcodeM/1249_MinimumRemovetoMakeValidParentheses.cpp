/*
1249. Minimum Remove to Make Valid Parentheses

Given a string s of '(' , ')' and lowercase English characters. 

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 

Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
Example 2:

Input: s = "a)b(c)d"
Output: "ab(c)d"
Example 3:

Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.
Example 4:

Input: s = "(a(b(c)d)"
Output: "a(b(c)d)"
 

Constraints:

1 <= s.length <= 10^5
s[i] is one of  '(' , ')' and lowercase English letters.


*/
#include <string>
#include <stack>

using std::stack;
using std::string;


class MinRemoveToMakeValid {

public:

    /*
        1249.Minimum-Remove-to-Make-Valid-Parentheses
        本题和 921.Minimum-Add-to-Make-Parentheses-Valid 本质相同，都是贪心的思想。只不过921只需要统计删除（或者增加）括号的个数，本题需要具体的把增删的位置指出来。

        具体的说，依然是用一个变量count来表示unmatched left parenthesis。当统计到count<0的时候，意味着必须删除一个右括号，否则无论之后的字符串如何表现，当前的字符串永远不可能合法。那么删除哪个右括号呢？注意，其实可以有多个选择，但是本题只要输出一种，那么最简单的方法就是把当前的那个右括号删了。

        当遍历完所有的字符，如果最后count>0，说明有未被匹配的左括号。此时意味着我们必须删除这些左括号。那么如何知道是哪些左括号未被匹配呢？显然，我们可以一开始使用栈来标记左括号的匹配情况，那么one pass之后栈里剩下的那些左括号就可以放心删除了。
    
    */
    string doit_parenthesis(string s) 
    {
        stack<int>Stack;
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='(')
            {
                Stack.push(i);
            }
            else if (s[i]==')')
            {
                if (Stack.empty())
                    s[i] = ' ';
                else
                    Stack.pop();
            }
        }
        while (!Stack.empty())
        {
            s[Stack.top()] = ' ';
            Stack.pop();
        }
        string t;
        for (auto ch: s)
            if (ch!=' ') t.push_back(ch);
        
        return t;

    }

    string doit_(string s) {

        int opening = 0;
        string ans;
        for (auto c: s) {

            if (c == '(')
                opening++;
            else if (c == ')')
                opening--;

            if (opening == -1) {
                opening++;
                continue;
            }
            
            ans.push_back(c);
        }
        
        if (opening == 0) return ans;
        
        string ans1;
        std::reverse(ans.begin(), ans.end());
        for (auto c: ans) {
            if (c == '(' && opening > 0) {
                opening--;
                continue;
            }
            ans1.push_back(c);
        }
        
        std::reverse(begin(ans1), end(ans1));
        return ans1;
    }
};
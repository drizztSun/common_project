/*
1087. Brace Expansion

You are given a string s representing a list of words. Each letter in the word has one or more options.

. If there is one option, the letter is represented as is.
. If there is more than one option, then curly braces delimit the options. For example, "{a,b,c}" represents options ["a", "b", "c"].
For example, if s = "a{b,c}", the first character is always 'a', but the second character can be 'b' or 'c'. The original list is ["ab", "ac"].

Return all words that can be formed in this manner, sorted in lexicographical order.

 

Example 1:

Input: s = "{a,b}c{d,e}f"
Output: ["acdf","acef","bcdf","bcef"]
Example 2:

Input: s = "abcd"
Output: ["abcd"]
 

Constraints:

1 <= s.length <= 50
s consists of curly brackets '{}', commas ',', and lowercase English letters.
s is guaranteed to be a valid input.
There are no nested curly brackets.
All characters inside a pair of consecutive opening and ending curly brackets are different.

*/
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using std::stack;
using std::vector;
using std::string;


class BraceExpansion {

    /*
        1087.Brace-Expansion
        因为此题明确没有nested的括号，所以简单的字符串处理就能AC。但是为了能扩展解决1096.Brace Expansion II，这里介绍一下更通用的栈的操作。

        首先，为了保证每个字母都能触发入栈操作，我们将所有的字母都用括号包起来，注意到这样做并不改变原义。比如：{a,b}c{d,e}f变成{{a},{b}}{c}{{d},{e}}{f}

        我们什么时候入栈？当遇到左括号和逗号的时候都需要。当然，为了区分这两个操作，我们需要两个栈stackOp和stackStr，分别来存放操作符（标记0或者1）和操作数（字符串数组）。
        当退栈的时候，如果对应的stackOp栈顶是0，说明手头的元素curStr要与stackStr的栈顶元素做叉乘操作；如果stackOp栈顶标记是1，说明手头的元素curStr要与stackStr的栈顶元素做并集操作。

        有一个特别注意的地方：一旦启动退栈进程，如果stackOp栈顶有连续若干个1，那么这些并集操作要连续地进行。原因是：连续被压入栈的这些逗号，本质肯定都是平级的，需要一并处理。如果stackOp栈顶是0，那么只需要再进行一次叉乘操作，这是因为叉乘的优先级较高，相邻之间能合并的早就已经合并完了。
    
    */
    vector<string> expand(string S) 
    {
        string s;
        for (auto ch: S)
        {
            if (isalpha(ch))
            {
                s.push_back('{');
                s.push_back(ch);
                s.push_back('}');
            }
            else
                s.push_back(ch);
        }
        S = s;
        
        stack<int>stackOp;
        stack<vector<string>>stackStr;
        vector<string>cur;
            
        for (int i=0; i<S.size(); i++)
        {
            if (S[i]=='{')
            {
                stackStr.push(cur);
                stackOp.push(0);
                cur.clear();
            }
            else if (S[i]==',')
            {
                stackStr.push(cur);
                stackOp.push(1);
                cur.clear();
            }
            else if (isalpha(S[i]))
            {
                string temp;
                temp.push_back(S[i]);
                cur.push_back(temp);
            }
            else if (S[i]=='}')
            {
                while (stackOp.top()==1)
                {
                    cur = combine(stackStr.top(), cur);
                    stackStr.pop();
                    stackOp.pop();
                }
                if (stackOp.top()==0)
                {
                    cur = crossProduct(stackStr.top(), cur);
                    stackStr.pop();
                    stackOp.pop();
                }
            }
        }
        
        std::sort(cur.begin(), cur.end());
        return cur;        
    }
    
    vector<string>combine(vector<string>&s, vector<string>&t)
    {
        vector<string>ret;
        for (int i=0; i<s.size(); i++)
            ret.push_back(s[i]);
        for (int i=0; i<t.size(); i++)
            ret.push_back(t[i]);
        return ret;
    }
    
    vector<string>crossProduct(vector<string>&s, vector<string>&t)
    {
        if (s.size()==0) s.push_back("");
        if (t.size()==0) t.push_back("");
        vector<string>ret;
        for (int i=0; i<s.size(); i++)
            for (int j=0; j<t.size(); j++)
            {
                ret.push_back(s[i]+t[j]);
            }
        return ret;
    }

public:
    
    vector<string> doit_stack(string s) {

        vector<string> res{ "" };
        string current;

        for (int i = 0; i < s.length(); i++) {

            if (s[i] == '{') {
                i++;
                vector<string> options;
                while (i < s.length() && s[i] != '}') {
                    if (s[i] != ',')
                        options.push_back({s[i]});
                    i++;
                }
                std::sort(begin(options), end(options));
                vector<string> tmp;
                for (auto& c : res) {
                    for (auto opt : options)
                        tmp.push_back(c + opt);
                }
                std::swap(res, tmp);
            }
            else {
                current += s[i];
                if (i == s.length() - 1 || s[i + 1] == '{') {
                    for (int i = 0; i < res.size(); i++) {
                        res[i] += current;
                    }
                    current.clear();
                } 
            }
        }

        return res;
    }
};
/*
921. Minimum Add to Make Parentheses Valid

Given a string S of '(' and ')' parentheses, we add the minimum number of parentheses ( '(' or ')', and in any positions ) so that the resulting parentheses string is valid.

Formally, a parentheses string is valid if and only if:

It is the empty string, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
Given a parentheses string, return the minimum number of parentheses we must add to make the resulting string valid.

 

Example 1:

Input: "())" 
Output: 1
Example 2:

Input: "((("
Output: 3
Example 3:

Input: "()"
Output: 0
Example 4:

Input: "()))(("
Output: 4
 

Note:

S.length <= 1000
S only consists of '(' and ')' characters.


*/
#include <string>
using std::string;

class MinAddToMakeValid {

public:

    /*
        921.Minimum-Add-to-Make-Parentheses-Valid
        此题的贪心法比较容易理解。我们维护一个计数器count，表示是目前为止尚未被匹配的左括号的数目。

        举个例子：s = (()))((

        我们依次查看到((的时候，count=2，此时我们并不着急对s做任何改动，因为s后面还有字符，说不定这些左括号都能被匹配到。

        我们继续查看到(())的时候，count=0，果然这时候的字符就是匹配的，我们依然不需要对s做任何改动。

        我们继续查看到(()))的时候，count=-1，此时我们不得不出手。因为无论s后面的字符如何，都无法挽救当前这个无法被匹配的右括号。此时必须处理，即增加一个左括号与之匹配。至于放在哪里我们并不关心，总之有地方放就是了。注意，既然增加一个左括号，那么此时的count=0.

        我们继续查看到(()))((的时候，count=2，字符串完结。对于这两个未被匹配的左括号，我们也必须处理，不得不增加两个右括号与之匹配。

        回顾上述的过程，我们所有增加括号的操作都是必要操作。最终我们实现了count=0，意味着这个字符串此时已经合法了。所以之前的“必要操作”也是“充分操作”，就是最终解。

        如果题目改成"Minimum delete to Make Parentheses Valid"，答案其实一模一样。我们增加多少括号促成匹配，就等效于减少多少（对称的）括号促成匹配。
    */
    int doit_parenthesis(string S) 
    {        
        int count = 0;
        int ret = 0;
        for (auto ch:S)
        {
            if (ch=='(')
                count++;
            else
                count--;
            if (count < 0)
            {
                ret += 1;
                count = 0;
            }
        }
        ret += count;
        return ret;
    }

    int doit_best(string S) {
        
        int opening = 0;
        int total = 0;
        for (auto c : S) {
            opening += c == '(' ? 1 : -1;
            
            if (opening == -1) {
                total++;
                opening++;
            }
        }
        
        return total + opening;
    }
    
    int doit_(string S) {

        int opening = 0;
        int total = 0;
        for (auto c : S) {
            
            if (c == '(') {
                
                if (opening < 0) {
                    total -= opening;
                    opening = 0;
                }
                opening++;
                continue;
            } else
                opening--;
        }
        
        return total + abs(opening);
    }
};
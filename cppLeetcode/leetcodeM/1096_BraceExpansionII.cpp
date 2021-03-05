/*
1096. Brace Expansion II

Under a grammar given below, strings can represent a set of lowercase words.  Let's use R(expr) to denote the set of words the expression represents.

Grammar can best be understood through simple examples:

.Single letters represent a singleton set containing that word.
    . R("a") = {"a"}
    . R("w") = {"w"}
. When we take a comma delimited list of 2 or more expressions, we take the union of possibilities.
    . R("{a,b,c}") = {"a","b","c"}
    . R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
. When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
    . R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
    . R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}

Formally, the 3 rules for our grammar:

For every lowercase letter x, we have R(x) = {x}
For expressions e_1, e_2, ... , e_k with k >= 2, we have R({e_1,e_2,...}) = R(e_1) ∪ R(e_2) ∪ ...
For expressions e_1 and e_2, we have R(e_1 + e_2) = {a + b for (a, b) in R(e_1) × R(e_2)}, where + denotes concatenation, and × denotes the cartesian product.
Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.

 

Example 1:

Input: "{a,b}{c,{d,e}}"
Output: ["ac","ad","ae","bc","bd","be"]
Example 2:

Input: "{{a,z},a{b,c},{ab,z}}"
Output: ["a","ab","ac","z"]
Explanation: Each distinct word is written only once in the final answer.
 

Constraints:

1 <= expression.length <= 60
expression[i] consists of '{', '}', ','or lowercase English letters.
The given expression represents a set of words based on the grammar given in the description.

*/
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <stack>

using std::stack;
using std::unordered_set;
using std::set;
using std::vector;
using std::string;


class BraceExpansionII {


    
    vector<string> doit_(string S) {

        vector<std::pair<set<string>, bool>> res;
        res.push_back({{""}, true});
        string current;

        int i = 0;
        while (i < S.length()) {

            if (S[i] == '{') {
                res.push_back({{}, true});
            } else if (S[i] == '}') {
                auto c = res.back();
                res.pop_back();

                if (res.back().second) {
                    std::sort(begin(c.first), end(c.first));
                    set<string> tmp;
                    for (auto w: c.first) {
                        for (auto w2: res.back().first)
                            tmp.insert(w2 + w);
                    }
                    vector<string> tmp(begin(tmp), end(tmp));
                    std::swap(res.back().first, tmp);
                } else {
                    for (auto w : c.first) {
                        res.back().first.insert(w);
                    }
                }
            } else if (S[i] == ',') {
                res.back().second = false;
                current.clear();
            } else {
                current = {S[i]};
            }

            i++;
        }

        return res.back().first;
    }


public:


    /*
        1096.Brace-Expansion-II
        解法1：递归
        我们先考虑一个乘法和加法的组合问题。例如计算a+b*c+b*d*e+f+g+h*u。

        这是一个比较典型的用栈可以解决的问题。遇到所有的单项式（也就是发现被加号所分割），就把当前的变量cur推入栈中，并把cur重置为空。如果遇到的是多项式（也就是被乘号所分割），就新得到的这部分乘数next与手头的cur相乘并更新为cur。这样最终遍历完之后，栈里面是有若干个单项式，求它们的和就行了。

        本题类似的思想，只不过把加号变成了逗号（对应的是取并集的运算），把乘号变成了双目的大括号（对应的是点乘的运算）。我们一旦遇到了左括号，就会向右寻找与它对应的右括号，这中间的部分就可以用递归处理（记作next）。默认情况下，我们都会将cur和next做点乘操作。

        解法2：栈
        如果不用递归，也可以强行只用栈处理。规则如下：

        遇到逗号，就将当前的cur推入栈中，同时标记这个入栈的操作为1.然后将cur重置为空。
        遇到左括号，就将当前的cur推入栈中，同时标记这个入栈的操作为2.然后将cur重置为空。
        遇到右括号，就不停地将stack顶端连续标记为1操作的那些元素退栈，不停地与cur做并集操作。然后再将stack顶端标记为2操作的一个元素退栈，再与cur做点乘。得到的就是更新后的cur。（也就是说，遇到一个右括号，预示着要完成这个括号内的所有并集操作，再加上一次与这个括号之前元素的点乘操作）
        遇到任何其他字母，就将cur的值置为这个字符串。
        需要注意的是，我们最好对所有的字母提前包裹上"{}"，这样会带来处理上的便利。比如"{a,b}c{d,e}f"，因为c不包裹大括号的话，就无法判断它与前面是否是点乘的关系进而无法使之前的cur入栈。
    
    */
    vector<string> braceExpansionII(string expression) 
    {
        string S = expression;
                
        auto resultSet =  dfs(S,0,S.size()-1);
        
        vector<string>results;
        for (auto x:resultSet)
            results.push_back(x);
        sort(results.begin(),results.end());
        return results;        
    }
    
    unordered_set<string>dfs(string&S, int a, int b)
    {
        stack<unordered_set<string>>Stack;
        unordered_set<string>cur={};       
                       
        for (int i=a; i<=b; i++)            
        {            
            if (S[i]=='{')
            {
                int level = 1;
                int j = i+1;
                while (j<=b && level>0)
                {
                    level += (S[j]=='{');
                    level -= (S[j]=='}');
                    if (level==0)
                        break;
                    else
                        j++;
                }
                auto next = dfs(S,i+1,j-1);                
                cur = product(cur,next);
                i = j;                
            }
            else if (S[i]==',')
            {
                Stack.push(cur);
                cur = {};
            }
            else
            {                                
                int j = i+1;
                while (j<=b && isalpha(S[j]))
                    j++;
                unordered_set<string>next({S.substr(i,j-i)});
                cur = product(cur, next);                
                i = j-1;
            }
        }
        
        while (!Stack.empty())
        {
            for (auto x: Stack.top())
                cur.insert(x);
            Stack.pop();
        }
        return cur;
    }
    
    unordered_set<string>product(unordered_set<string>&A, unordered_set<string>&B)
    {
        if (A.size()==0)
            A.insert("");
        unordered_set<string>results;
        for (auto x:A)
            for (auto y:B)
                results.insert(x+y);
        return results;
    }

public:

    vector<string> doit_stack(string S) 
    {
        string expression;
        for (int i=0; i<S.size(); i++)
        {
            if (isalpha(S[i]))
            {
                expression.push_back('{');
                expression.push_back(S[i]);
                expression.push_back('}');
            }
            else
                expression.push_back(S[i]);                
        }
        
        stack<unordered_set<string>>stackStr;
        stack<int>stackOp;        
        unordered_set<string>cur;
        
        for (int i=0; i<expression.size(); i++)
        {
            if (expression[i]=='{')
            {
                stackStr.push(cur);                
                stackOp.push(0);
                cur = {};
            }
            else if (expression[i]==',')
            {
                stackStr.push(cur);                
                stackOp.push(1);
                cur = {};
            }
            else if (expression[i]=='}')
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
            else
            {
                int j=i+1;
                while (j<expression.size() && isalpha(expression[j]))
                    j++;
                cur={expression.substr(i,j-i)};
                i = j-1;
            }
        }               
        
        vector<string>rets(cur.begin(), cur.end());
        sort(rets.begin(),rets.end());
        
        return rets;
    }

    unordered_set<string>combine(unordered_set<string>&s, unordered_set<string>&t)
    {
        unordered_set<string>ret;
        for (auto x:s)
            ret.insert(x);
        for (auto y:t)
            ret.insert(y);
        return ret;
    }
    
    unordered_set<string>crossProduct(unordered_set<string>&s, unordered_set<string>&t)
    {
        if (s.size()==0) s.insert("");
        if (t.size()==0) t.insert("");
        unordered_set<string>ret;
        for (auto x:s)
            for (auto y:t)
                ret.insert(x+y);
        return ret;
    }



};
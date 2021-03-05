/*
 1106. Parsing A Boolean Expression
 
 Return the result of evaluating a given boolean expression, represented as a string.

 An expression can either be:

 "t", evaluating to True;
 "f", evaluating to False;
 "!(expr)", evaluating to the logical NOT of the inner expression expr;
 "&(expr1,expr2,...)", evaluating to the logical AND of 2 or more inner expressions expr1, expr2, ...;
 "|(expr1,expr2,...)", evaluating to the logical OR of 2 or more inner expressions expr1, expr2, ...


 Example 1:

 Input: expression = "!(f)"
 Output: true
 Example 2:

 Input: expression = "|(f,t)"
 Output: true
 Example 3:

 Input: expression = "&(t,f)"
 Output: false
 Example 4:

 Input: expression = "|(&(t,f,t),!(t))"
 Output: false


 Constraints:

 1 <= expression.length <= 20000
 expression[i] consists of characters in {'(', ')', '&', '|', '!', 't', 'f', ','}.
 expression is a valid expression representing a boolean, as given in the description.
 
 
 */

#include <functional>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <any>

using std::stack;
using std::vector;
using std::string;
using std::unordered_map;


class ParseBoolExpr {


    bool doit_recursive(string expression) {

        std::function<bool(int&)> parse = [&](int& p) {
            char c = expression[p++];

            if (c == 'f') return false;
            if (c == 't') return true;
            if (c == '!') {
                bool ans = !parse(++p);
                ++p;
                return ans;
            }

            bool is_and = (c == '&');
            bool ans = is_and;
            ++p;

            while (true) {
                
                if (is_and)
                    ans &= parse(p);
                else
                    ans |= parse(p);

                if (expression[p++] == ')')
                    break;
            }

            return ans;
        };

        int p = 0;
        return parse(p);
    }

    /*
        1106.Parsing-A-Boolean-Expression
        本题和上周周赛的最后一题（1096. Brace Expansion II）属于同一类型，相对来说更容易些。

        对于这种带有括号优先级的expression parsing，栈或者递归的写法都是比较常见的。

        解法1：栈
        我们需要设立两个栈，一个存储的是操作符，stack<char>stackOp；另一个存储的是操作数，注意操作数是个数组，stack<vector<int>>stackNums

        进栈的特征是遇到操作符，将这个操作符和手头的操作数组nums都压入栈后清空。退栈的特征是遇到右括号，这个时候调用stackOp的栈顶操作符，来指挥怎么eval手头的nums，并与stackNums的栈顶元素（也是个数组）合并。当然，两个栈都要吐出栈顶元素。其余的时候，只需要不断增加手头的操作数组nums的长度即可。

        解法2：递归
        遇到一个操作符的话，也就意味着马上有一个左括号i。我们找到和它平级的右括号j，这样[i,j]之间的字符串的处理可以写成一个递归函数。递归函数返回的就是一个bool值。递归的边界就是字符串不再包括子括号了，那么这时候需要做的就是根据操作符来eval一堆操作数nums即可。
    */

    bool parseBoolExpr(string expression) 
    {
        bool ret = helper(expression, 0, expression.size()-1);
        return ret;
    }
    
    bool helper(string &s, int a, int b)
    {
        vector<int>vals;
        for (int i=a+2; i<=b-1; i++)
        {
            if (s[i]=='&' || s[i]=='|' || s[i]=='!')
            {                
                int level = 1;
                int j = i+2;
                while (j<=b-1 && level>0)
                {
                    level += (s[j]=='(');
                    level -= (s[j]==')');
                    if (level==0)
                        break;
                    else
                        j++;
                }
                vals.push_back(helper(s, i, j));
                i = j;
            }
            else if (s[i]=='t' || s[i]=='f')
            {
                vals.push_back(s[i]=='t');
            }            
        }
        return eval(s[a], vals);        
    }

    int eval(char oper, vector<int>&nums)
    {        
        int result;
        if (oper=='!')
            result = !nums[0];
        else if (oper=='&')
        {
            result = 1;
            for (int i=0; i<nums.size(); i++)
                result = result&nums[i];
        }
        else if (oper=='|')
        {
            result = 0;
            for (int i=0; i<nums.size(); i++)
                result = result|nums[i];
        }

        return result;
    }

public:
    
    bool doit_stack(string expression) 
    {
        stack<char>stackOp;
        stack<vector<int>>stackVal;
        vector<int>curVals;
        int ret;

        auto eval = [&](char oper, vector<int>&nums)
        {
            int result;
            if (oper=='!')
                result = !nums[0];
            else if (oper=='&')
            {
                result = 1;
                for (int i=0; i<nums.size(); i++)
                    result = result&nums[i];
            }
            else if (oper=='|')
            {
                result = 0;
                for (int i=0; i<nums.size(); i++)
                    result = result|nums[i];
            }

            return result;
        };

        for (int i=0; i<expression.size(); i++)
        {
            if (expression[i]=='!' || expression[i]=='&' || expression[i]=='|')
            {
                stackOp.push(expression[i]);
                stackVal.push(curVals);
                curVals.clear();
                i++;
            }
            else if (expression[i]==')')
            {
                ret = eval(stackOp.top(), curVals);
                stackOp.pop();
                curVals = stackVal.top();
                curVals.push_back(ret);
                stackVal.pop();
            }
            else if (expression[i]=='t' || expression[i]=='f' )
            {
                curVals.push_back(expression[i]=='t');
            }
        }

        return ret;
    }

    bool doit_stack(string S) {

        vector<char> Stack;

        for (auto c : S) {

            if (c == ')') {

                vector<bool> tmp;
                while (!Stack.empty() && Stack.back() != '(') {
                    tmp.push_back(Stack.back() == 't');
                    Stack.pop_back();
                }
                
                Stack.pop_back();
                char ops = Stack.back();
                Stack.pop_back();

                if (ops == '!') {
                    Stack.push_back(tmp.back()? 'f' : 't');
                } else if (ops == '|') {
                    Stack.push_back(std::any_of(tmp.begin(), tmp.end()) ? 't' : 'f');
                } else if (ops == '&') {
                    Stack.push_back(std::all_of(begin(tmp), end(tmp)) ? 't' : 'f');
                }
            } else {
                if (c != ',')
                    Stack.push_back(c);
            }
        }

        return Stack.back() == 't';
    }

public:
    
    bool doit_(string expression) {
        
        vector<char> buff;
        
        auto And = [](vector<bool>& c) {
            return std::all_of(begin(c), end(c), [](bool a){ return a; });
        };
        
        auto Or = [](vector<bool>& c) {
            return std::any_of(begin(c), end(c), [](bool a){return a; });
        };
        
        auto Not = [](vector<bool>& c) {
            return !c[0];
        };
        
        unordered_map<char, std::function<bool(vector<bool>&)>> func;
        func.insert({'&', And});
        func.insert({'|', Or});
        func.insert({'!', Not});
        
        for (auto c : expression) {
            
            if (c == ')') {
                
                vector<bool> tmp;
                while (! buff.empty() && buff.back() != '(') {
                    tmp.push_back(buff.back() == 't' ? true : false);
                    buff.pop_back();
                }
                
                buff.pop_back();
                char c = buff.back();
                buff.pop_back();
                buff.push_back(func[c](tmp) ? 't' : 'f');
                
            } else {
                if (c != ',')
                    buff.push_back(c);
            }
        }
        
        return buff[0] == 't';
    }
    
    bool parseBoolExpr(string expression) {
        if (expression[0] == 't')
            return true;
        if (expression[0] == 'f')
            return false;
    
        char const op = expression[0];
        int const end = expression.length() - 1;  // remove ')'
        int begin = 2;  // remove '#('
        if (op == '!')
            return !parseBoolExpr(expression.substr(begin, end - begin));
        int cnt = 0;  // count of unpaired brakets
        bool ans = (op == '&') ? true : false;\
        for (int pos = begin; pos <= end; ++pos) {
            if (pos == end || (expression[pos] == ',' && cnt == 0)) {
                bool const b = parseBoolExpr(expression.substr(begin, pos - begin));
                if (op == '&') {
                    ans = ans && b;
                    if (!ans) return false;
                } else {
                    ans = ans || b;
                    if (ans) return true;
                }
                begin = pos + 1;
            } else if (expression[pos] == '(') {
                ++cnt;
            } else if (expression[pos] == ')') {
                --cnt;
            }
        }
        return ans;
    }

    

};

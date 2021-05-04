/**
 772. Basic Calculator III

 Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, '+', '-', '*', '/' operators, and open '(' and closing parentheses ')'. The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

 

Example 1:

Input: s = "1+1"
Output: 2
Example 2:

Input: s = "6-4/2"
Output: 4
Example 3:

Input: s = "2*(5+5*2)/3+(6/2+8)"
Output: 21
Example 4:

Input: s = "(2+6*3+5-(3*14/7+2)*5)+3"
Output: -12
Example 5:

Input: s = "0"
Output: 0
 

Constraints:

1 <= s <= 104
s consists of digits, '+', '-', '*', '/', '(', and ')'.
s is a valid expression.
 

Follow up: Could you solve the problem without using built-in library functions?
 
 */

#include <string>
#include <vector>
#include <stack>
#include <functional>

using std::vector;
using std::stack;
using std::string;


class BasicCalculateIII {

    /*
        772.Basic-Calculator-III
        对于括号的处理必然要用到stack。本题的处理思想是，遇到左括号就将字符串入栈并清空curStr，直到遇到了右括号，才开始调用子函数eval(curStr)解析当前的curStr的数值结果.
        于是子任务eval(s)就是解析一个不包含括号的运算字符串，类似于227.Basic Calculator II。解析完的结果再转化为字符串，与栈顶的字符串拼接起来，继续往下处理。

        这里与227.Basic Calculator II不同的一个细节是，我们在eval(s)里面可以处理这样的字符串：++2-+3*-3-+1/-3，也就是说，在每个二元运算符加减乘除之外，每个操作数之前可能还有一个符号位。
        这是为什么呢？举个例子：3+(1-4)，括号内得到的其实是-3，于是到了外层需要解析3+-3。再举个例子：3*(2-4)，括号内得到的其实是-2，于是到了外层需要解析3*-2。这些都是我们需要在eval里考虑到的情况。
    */
    int doit_stack(string s) 
    {
        stack<string>Stack;
        string curStr;

        auto eval = [](string s)
        {
            string S = "+";
            for (auto ch:s)
            {
                if (ch==' ') continue;
                S.push_back(ch);
                if (ch=='(')
                    S+="+";
            }
            s = S;
            
            vector<long>nums;

            for (int i=0; i<s.size(); i++)
            {
                if (s[i]=='+' || s[i]=='-')
                {
                    int j = i+1;
                    if (s[j]=='+' || s[j]=='-') j++;
                    while (j<s.size() && isdigit(s[j]))
                        j++;
                    long num = stol(s.substr(i+1,j-i-1));
                    if (s[i]=='+') nums.push_back(num);
                    else if (s[i]=='-') nums.push_back(-num);
                    i = j-1;
                }
                else if (s[i]=='*' || s[i]=='/')
                {
                    int j = i+1;
                    if (s[j]=='+' || s[j]=='-') j++;
                    while (j<s.size() && isdigit(s[j]))
                        j++;
                    int num = stoi(s.substr(i+1,j-i-1));                
                    if (s[i]=='*') nums.back() *= num;
                    else if (s[i]=='/') nums.back() /= num;
                    i = j-1;
                }
            }

            int ret = 0;
            for (int i=0; i<nums.size(); i++)
                ret+=nums[i];
            return ret;
        };

        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='(')
            {
                Stack.push(curStr);
                curStr = "";
            }
            else if (s[i]==')')
            {                
                int curRes = eval(curStr);
                curStr = Stack.top() + std::to_string(curRes);
                Stack.pop();                
            }
            else
                curStr.push_back(s[i]);
        }
        return eval(curStr);        
    }
    

public:

    int calculate(string s) {
        int i = 0;

        auto parseNum = [](string& s, int& i) -> long{
            long n = 0;
            while(i < s.length() && isdigit(s[i])){
                n = (long) s[i++] - '0' + 10 * n;   
            }
            return n;
        };

        std::function<int(string&, int&)> parseExpr = [&](string& s, int& i) -> int{
            vector<int> nums;
            char op = '+';
            for (; i < s.length() && op != ')'; i++) {
                if (s[i] == ' ') continue;
                long n = s[i] == '(' ? parseExpr(s, ++i) : parseNum(s, i);
                switch(op) {
                    case '+' : nums.push_back(n); break;
                    case '-' : nums.push_back(-n); break;
                    case '*' : nums.back() *= n; break;
                    case '/' : nums.back() /= n; break;
                }            
                op = s[i];
            }
            int res = 0;
            for (int n : nums) res += n;
            return res;
        };

        return parseExpr(s, i);
    }

    int doit_recursive(string s) {
        int i = 0;
        return parseExpr(s, i);
    }
    
    int parseExpr(string& s, int& i) {
        vector<int> nums;
        char op = '+';
        for (; i < s.length() && op != ')'; i++) {
            if (s[i] == ' ') continue;
            long n = s[i] == '(' ? parseExpr(s, ++i) : parseNum(s, i);
            switch(op) {
                case '+' : nums.push_back(n); break;
                case '-' : nums.push_back(-n); break;
                case '*' : nums.back() *= n; break;
                case '/' : nums.back() /= n; break;
            }            
            op = s[i];
        }
        int res = 0;
        for (int n : nums) res += n;
        return res;
    }
    
    long parseNum(string& s, int& i) {
        long n = 0;
        while(i < s.length() && isdigit(s[i])){
             n = (long) s[i++] - '0' + 10 * n;   
        }
        return n;
    }
};
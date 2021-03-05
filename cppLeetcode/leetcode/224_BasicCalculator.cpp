/*
224. Basic Calculator

Given a string s representing an expression, implement a basic calculator to evaluate it.

 

Example 1:

Input: s = "1 + 1"
Output: 2
Example 2:

Input: s = " 2-1 + 2 "
Output: 3
Example 3:

Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
 

Constraints:

1 <= s.length <= 3 * 10^5
s consists of digits, '+', '-', '(', ')', and ' '.
s represents a valid expression.
*/
#include <string>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::string;

class BasicCalculator {

    /*
        224.Basic-Calculator
        典型的栈的应用。需要设置两个栈

        stack<int>nums;
        stack<int>sign;
        nums用来存储数值，sign用来存储符号。这里需要有个小技巧，在字符串最开始添加一个+入栈，遇到'('也添加一个+入栈，这样保证每个数字（和小括号产生的中间结果）都在sign中有一个对应的符号位。

        具体的算法是：遇到'('就将当前结果curResult入栈并清零。遇到')'就将当前结果与sign的栈顶元素结合形成新数（然后sign退栈），并加上nums的栈顶元素结合形成新数（然后nums退栈）。遇到符号就加入sign的栈。遇到纯数字就取出sign的栈顶元素结合
    */
    int calculate(string s) 
    {
        string S = "+";
        for (auto ch:s)
        {
            if (ch==' ') continue;
            S+=ch;
            if (ch=='(')
                S+="+";            
        }
        s = S;

        stack<int>nums;
        stack<int>signs;
        int sum = 0, sign;

        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='+'||s[i]=='-')
            {
                sign = s[i]=='+'?1:-1;
            }
            else if (isdigit(s[i]))
            {
                int j = i;
                while (j<s.size() && isdigit(s[j]))
                    j++;
                int num = stoi(s.substr(i,j-i));
                i = j-1;
                sum += num*sign;
            }
            else if (s[i]=='(')
            {
                nums.push(sum);
                signs.push(sign);
                sum = 0;
            }
            else if (s[i]==')')
            {                
                sum = nums.top() + signs.top() * sum;
                nums.pop();
                signs.pop();
            }
        }
        return sum;
    }

public:
    
    int doit_stack(string s) {
        
        vector<std::pair<long, int>> st{{0, 1}};
        int sig = 1;
        long num = 0;
        int n = s.length();

        for (int i = 0; i <= n; i++) {

            if (i == n) {
                st.back().first += st.back().second * num;
                
            } else if (s[i] == '-' || s[i] == '+') {

                st.back().first += st.back().second * num;
                num = 0;
                st.back().second = s[i] == '-'? -1 : 1;

            } else if (isdigit(s[i])) {
                num = num * 10 + s[i] - '0';

            } else if (s[i] == '(') {
                st.push_back({0, 1});

            } else if (s[i] == ')') {
                int c = st.back().first + st.back().second * num;
                st.pop_back();
                st.back().first += st.back().second * c;
                num = 0;
            }
        }

        return st.back().first;
    }
};
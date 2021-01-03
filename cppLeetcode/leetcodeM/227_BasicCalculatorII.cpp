/*
227. Basic Calculator II

Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5
 

Constraints:

1 <= s.length <= 3 * 105
s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
s represents a valid expression.
All the integers in the expression are non-negative integers in the range [0, 231 - 1].
The answer is guaranteed to fit in a 32-bit integer.
*/
#include <stack>
#include <string>

using std::string;
using std::stack;

class BasicCaculatorII {

public:

    /*
    Approach 1: Using Stack
    Intuition

    We know that there could be 4 types of operations - addition (+), subtraction (-), multiplication (*) and division (/). 
    Without parenthesis, we know that, multiplication (*) and (\) operations would always have higher precedence than addition (+) and subtraction (-) based on operator precedence rules.

    Complexity Analysis

    Time Complexity: O(n), where n is the length of the string s. We iterate over the string s at most twice.

    Space Complexity: O(n), where n is the length of the string s.
    */

    int doit_stack(string s) {

        int len = s.length();
        if (len == 0) return 0;
        
        stack<int> stack;
        int currentNumber = 0;
        char operation = '+';
        
        for (int i = 0; i < len; i++) {
        
            char currentChar = s[i];
            if (isdigit(currentChar)) {
                currentNumber = (currentNumber * 10) + (currentChar - '0');
            }
        
            if (!isdigit(currentChar) && !iswspace(currentChar) || i == len - 1) {

                if (operation == '-') {
                    stack.push(-currentNumber);
                } else if (operation == '+') {
                    stack.push(currentNumber);
                } else if (operation == '*') {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop * currentNumber);
                } else if (operation == '/') {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop / currentNumber);
                }
                operation = currentChar;
                currentNumber = 0;
            }
        }
        int result = 0;
        while (stack.size() != 0) {
            result += stack.top();
            stack.pop();
        }
        return result;
    }

    /*
    Approach 2: Optimised Approach without the stack
    Intuition

    In the previous approach, we used a stack to track the values of the evaluated expressions. In the end, we pop all the values from the stack and add to the result. 
    Instead of that, we could add the values to the result beforehand and keep track of the last calculated number, thus eliminating the need for the stack. Let's understand the algorithm in detail.

    Algorithm

    The approach works similar to Approach 1 with the following differences :

    Instead of using a stack, we use a variable lastNumber to track the value of the last evaluated expression.
    If the operation is Addition (+) or Subtraction (-), add the lastNumber to the result instead of pushing it to the stack. The currentNumber would be updated to lastNumber for the next iteration.
    If the operation is Multiplication (*) or Division (/), we must evaluate the expression lastNumber * currentNumber and update the lastNumber with the result of the expression. This would be added to the result after the entire string is scanned.
    Implementation

    Complexity Analysis

    Time Complexity: O(n), where nn is the length of the string ss.

    Space Complexity: O(1), as we use constant extra space to store lastNumber, result and so on.
    */
    int doit_(string s) {

        if (s.empty()) return 0;
        
        int current_num = 0, last_num = 0, result = 0;
        int length = s.length();
        char sign = '+';

        for (int i = 0; i < length; i++) {
            char currentchar = s[i];

            if (isdigit(currentchar)) {
                current_num = current_num * 10 + (currentchar - '0');
            }

            if (i == s.length()-1 || !isdigit(currentchar) && !isspace(currentchar)) {

                if (sign == '+' || sign == '-') {
                    result += last_num;
                    last_num = (sign == '+') ? current_num : -current_num;
                } else if (sign == '*') {
                    last_num *= current_num;
                } else if (sign == '/') {
                    last_num /= current_num;
                }

                sign = currentchar;
                current_num = 0;
            }
        }

        result += last_num;
        return result;
    }

};
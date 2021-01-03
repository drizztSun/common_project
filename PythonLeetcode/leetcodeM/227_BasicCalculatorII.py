"""
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


"""


class BasicCalculatorII:

    """
    Approach 1: Using Stack
    Intuition

    We know that there could be 4 types of operations - addition (+), subtraction (-), multiplication (*) and division (/).
    Without parenthesis, we know that, multiplication (*) and (\) operations would always have higher precedence than addition (+) and subtraction (-) based on operator precedence rules.

    Algorithm

    Scan the input string s from left to right and evaluate the expressions based on the following rules

    If the current character is a digit 0-9 ( operand ), add it to the number currentNumber.
    Otherwise, the current character must be an operation (+,-,*, /). Evaluate the expression based on the type of operation.
    Addition (+) or Subtraction (-): We must evaluate the expression later based on the next operation. So, we must store the currentNumber to be used later. Let's push the currentNumber in the Stack.
    Stack data structure follows Last In First Out (LIFO) principle. Hence, the last pushed number in the stack would be popped out first for evaluation.
    In addition, when we pop from the stack and evaluate this expression in the future, we need a way to determine if the operation was Addition (+) or Subtraction (-).
    To simplify our evaluation, we can push -currentNumber in a stack if the current operation is subtraction (-) and assume that the operation for all the values in the stack is addition (+).
    This works because (a - currentNumber) is equivalent to (a + (-currentNumber)).

    Multiplication (*) or Division (/): Pop the top values from the stack and evaluate the current expression. Push the evaluated value back to the stack.

    Complexity Analysis

    Time Complexity: O(n), where nn is the length of the string s. We iterate over the string ss at most twice.

    Space Complexity: O(n), where nn is the length of the string s.
    """

    def doit_stack(self, s: str) -> int:
        import math
        i, stack, sign, num = 0, [], '+', 0
        while i < len(s):
            c = s[i]
            if c.isdigit():
                num = num * 10 + int(c)

            if i == len(s) - 1 or c in '+-*/':
                if sign == '+':
                    stack.append(num)
                elif sign == '-':
                    stack.append(-num)
                elif sign == '*':
                    stack.append(stack.pop() * num)
                elif sign == '/':
                    div = stack.pop()
                    if div >= 0:
                        stack.append(int(math.floor(div / num)))
                    else:
                        stack.append(-int(math.floor(-div // num)))

                sign, num = c, 0

            i += 1

        return sum(stack)

    """
    Approach 2: Optimised Approach without the stack
    Intuition
    
    In the previous approach, we used a stack to track the values of the evaluated expressions. In the end, we pop all the values from the stack and add to the result. 
    Instead of that, we could add the values to the result beforehand and keep track of the last calculated number, thus eliminating the need for the stack. Let's understand the algorithm in detail.
    
    Algorithm
    
    The approach works similar to Approach 1 with the following differences :
    
    Instead of using a stack, we use a variable lastNumber to track the value of the last evaluated expression.
    If the operation is Addition (+) or Subtraction (-), add the lastNumber to the result instead of pushing it to the stack. The currentNumber would be updated to lastNumber for the next iteration.
    If the operation is Multiplication (*) or Division (/), we must evaluate the expression lastNumber * currentNumber and update the lastNumber with the result of the expression. 
    This would be added to the result after the entire string is scanned.
    Implementation
    
    Complexity Analysis

    Time Complexity: O(n), where nn is the length of the string ss.
    
    Space Complexity: O(1), as we use constant extra space to store lastNumber, result and so on.
    """
    def doit_(self, s: str) -> int:
        import math

        if not s: return 0

        sign, cur_num, last_num, result = '+', 0, 0, 0

        for i in range(len(s)):

            if s[i].isdigit():
                cur_num = cur_num * 10 + int(s[i])

            if not s[i].isdigit() and not s[i].isspace() or i == len(s) - 1:

                if sign == '+' or sign == '-':
                    result += last_num
                    last_num = (cur_num if sign == '+' else -cur_num)
                elif sign == '*':
                    last_num *= cur_num
                elif sign == '/':
                    if last_num > 0:
                        last_num = int(math.floor(last_num / cur_num))
                    else:
                        last_num = -int(math.floor(-last_num // cur_num))

                sign = s[i]
                cur_num = 0

        result += last_num
        return result


if __name__ == '__main__':

    BasicCalculatorII().doit_("14-3/2")

    BasicCalculatorII().doit_("3 + 2 * 2")




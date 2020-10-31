"""
224 Basic Calculator

Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

Example 1:

Input: "1 + 1"
Output: 2
Example 2:

Input: " 2-1 + 2 "
Output: 3
Example 3:

Input: "(1+(4+5+2)-3)+(6+8)"
Output: 23
Note:
You may assume that the given expression is always valid.
Do not use the eval built-in library function.

"""


class Calculator:




    """
    Approach 1: Stack and String Reversal
    Intuition

    This question qualifies really well for a stack question. Since the expression might have parenthesis, we can use a stack to find the value for each sub-expression within a parenthesis.
    Essentially, we need to delay processing the main expression until we are done evaluating the interim sub-expressions within parenthesis and to introduce this delay, we use a stack.

    We push the elements of the expression one by one onto the stack until we get a closing bracket ). Then we pop the elements from the stack one by one and evaluate the expression on-the-go.
    This is done till we find the corresponding ( opening bracket. This kind of evaluation is very common when using the stack data structure.
    However, if you notice the way we calculate the final answer, you will realize that we actually process the values from right to left whereas it should be the other way around.

    """
    def doit_stack(self, s: str) -> int:

        def evaluate_expr(stack):

            res = stack.pop() if stack else 0

            # Evaluate the expression till we get corresponding ')'
            while stack and stack[-1] != ')':
                sign = stack.pop()
                if sign == '+':
                    res += stack.pop()
                else:
                    res -= stack.pop()
            return res

        stack = []
        n, operand = 0, 0

        for i in range(len(s) - 1, -1, -1):
            ch = s[i]

            if ch.isdigit():

                # Forming the operand - in reverse order.
                operand = (10**n * int(ch)) + operand
                n += 1

            elif ch != " ":
                if n:
                    # Save the operand on the stack
                    # As we encounter some non-digit.
                    stack.append(operand)
                    n, operand = 0, 0

                if ch == '(':
                    res = evaluate_expr(stack)
                    stack.pop()

                    # Append the evaluated result to the stack.
                    # This result could be of a sub-expression within the parenthesis.
                    stack.append(res)

                # For other non-digits just push onto the stack.
                else:
                    stack.append(ch)

        # Push the last operand to stack, if any.
        if n:
            stack.append(operand)

        # Evaluate any left overs in the stack.
        return evaluate_expr(stack)

    def doit_stack_1(self, s):
        """
        :type s: str
        :rtype: int
        """
        if not s:
            return

        res = num = 0
        sign = 1
        stack = []
        for c in s:
            if c.isdigit():
                num = 10 * num + ord(c) - ord('0')
            elif c == "+" or c == "-":
                res += sign * num
                num = 0
                sign = 1 if c == "+" else -1
            elif c == "(":
                stack.append(res)
                stack.append(sign)
                res = 0
                sign = 1
            elif c == ")":
                res += sign * num
                num = 0
                res *= stack.pop()
                res += stack.pop()
        res = res + sign * num
        return res

    """
    Approach 2: Stack and No String Reversal
    """
    def doit_stack_nostr(self, s: str) -> int:

        stack = []
        operand = 0
        res = 0 # For the on-going result
        sign = 1 # 1 means positive, -1 means negative

        for ch in s:
            if ch.isdigit():

                # Forming operand, since it could be more than one digit
                operand = (operand * 10) + int(ch)

            elif ch == '+':

                # Evaluate the expression to the left,
                # with result, sign, operand
                res += sign * operand

                # Save the recently encountered '+' sign
                sign = 1

                # Reset operand
                operand = 0

            elif ch == '-':

                res += sign * operand
                sign = -1
                operand = 0

            elif ch == '(':

                # Push the result and sign on to the stack, for later
                # We push the result first, then sign
                stack.append(res)
                stack.append(sign)

                # Reset operand and result, as if new evaluation begins for the new sub-expression
                sign = 1
                res = 0

            elif ch == ')':

                # Evaluate the expression to the left
                # with result, sign and operand
                res += sign * operand

                # ')' marks end of expression within a set of parenthesis
                # Its result is multiplied with sign on top of stack
                # as stack.pop() is the sign before the parenthesis
                res *= stack.pop() # stack pop 1, sign

                # Then add to the next operand on the top.
                # as stack.pop() is the result calculated before this parenthesis
                # (operand on stack) + (sign on stack * (result from parenthesis))
                res += stack.pop() # stack pop 2, operand

                # Reset the operand
                operand = 0

        return res + sign * operand

    """
    Keep a global running total and a stack of signs (+1 or -1), one for each open scope. The "global" outermost sign is +1.

    Each number consumes a sign.
    Each + and - causes a new sign.
    Each ( duplicates the current sign so it can be used for the first term inside the new scope. 
    That's also why I start with [1, 1] - the global sign 1 and a duplicate to be used for the first term, since expressions start like 3... or (..., not like +3... or +(....
    
    Each ) closes the current scope and thus drops the current sign.
    Also see the example trace below my programs.
    """
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        i, sign, num = 0, [1, 1], 0
        while i < len(s):
            c = s[i]
            if c.isdigit():
                start = i
                while i < len(s) and s[i].isdigit():
                    i+=1
                num += sign.pop()*int(s[start:i])
                continue
            elif c in "+-(":
                sign += sign[-1]*(1, -1)[c=='-'],
            elif c == ')':
                sign.pop()

            i += 1

        return num


if __name__ == '__main__':

    pass
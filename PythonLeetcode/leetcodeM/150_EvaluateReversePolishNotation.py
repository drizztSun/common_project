"""
150. Evaluate Reverse Polish Notation


Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Note:

Division between two integers should truncate toward zero.
The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.
Example 1:

Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation: 
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
"""
#from math import ceil, floor

class EvalRPN:

    """
        Approach 1: Reducing the List In-place
        Intuition

        This approach literally follows the animation above. A pointer is used to step through the list, and each time an operator (`+-*/) is found, that operator is then applied to the 2 values before it (which are always numbers, as long as the original input was valid). The 3 values are then replaced with the result. This process is repeated until the list is of length 1, containing a single number that is the answer to be returned.

        Algorithm

        The code is simpler for Python than Java. For Java (and other languages where the input type is a fixed size array), we have to define our own method to delete values from an array. This is done by shuffling the other elements down into the gap. Of course, you could start by copying the input into an ArrayList (so that you could then use its delete method), but then the algorithm would require O(n)O(n) space instead of O(1)O(1) space.

        Diagram showing the in-place shuffles.

        We have to be a little careful about the types in the Python code, as in the middle of processing the list, some numbers will be represent as strings, and others as ints. Additionally, we also need to be aware that python division does not truncate towards zero. We can instead use int(a / b) to achieve the desired result. Note that this is not the same as int(a // b).

        In the Java code, we have to convert ints back to Strings, because Java doesn't support mixed lists of Strings and ints.

        Finally, If you know how to use lambda functions in your chosen programming language, an ideal solution would use them to elegantly handle the 4 operations (+-*/). The first set of solutions here use lambda functions. If you aren't familiar with lambda functions though (or your chosen programming language doesn't support them), that's fine. You'll get a chance to learn them when you're ready! Scroll down a little more, as we have also provided solutions that don't use them.
    """
    def doit_1(self, tokens: list) -> int:

        operations = {
            "+": lambda a, b: a + b,
            "-": lambda a, b: a - b,
            "/": lambda a, b: int(a / b),
            "*": lambda a, b: a * b
        }
        
        current_position = 0
        
        while len(tokens) > 1:
            
            # Move the current position pointer to the next operator.
            while tokens[current_position] not in "+-*/":
                current_position += 1
        
            # Extract the operator and numbers from the list.
            operator = tokens[current_position]
            number_1 = int(tokens[current_position - 2])
            number_2 = int(tokens[current_position - 1])
            
            # Calculate the result to overwrite the operator with.
            operation = operations[operator]
            tokens[current_position] = operation(number_1, number_2)
            
            # Remove the numbers and move the pointer to the position
            # after the new number we just added.
            tokens.pop(current_position - 2)
            tokens.pop(current_position - 2)
            current_position -= 1
        
        return tokens[0]

    def doit_2(self, tokens: list) -> int:

        current_position = 0

        while len(tokens) > 1:
            
            # Move the current position pointer to the next operator.
            while tokens[current_position] not in "+-*/":
                current_position += 1
        
            # Extract the operator and numbers from the list.
            operator = tokens[current_position]
            number_1 = int(tokens[current_position - 2])
            number_2 = int(tokens[current_position - 1])
            
            # Calculate the result to overwrite the operator with.
            if operator == "+":
                tokens[current_position] = number_1 + number_2
            elif operator == "-":
                tokens[current_position] = number_1 - number_2
            elif operator == "*":
                tokens[current_position] = number_1 * number_2
            else:
                tokens[current_position] = int(number_1 / number_2)
            
            # Remove the numbers and move the pointer to the position
            # after the new number we just added.
            tokens.pop(current_position - 2)
            tokens.pop(current_position - 2)
            current_position -= 1
            
        return tokens[0]

    """
        Approach 2: Evaluate with Stack
        Intuition

        The first approach worked, but O(n^2)O(n 
        2
        ) is too slow for large nn. As hinted at above, a Double-Linked List could be an option. However, it requires a lot of set-up code, and in practice requires more space than the elegant Stack approach we're going to look at now.

        We don't want to repeatedly delete items from the middle of a list, as this inevitably leads to O(n^2)O(n 
        2
        ) time performance. So recall that the above algorithm scanned through the list from left to right, and each time it reached an operator, it'd replace the operator and the 2 numbers immediately before it with the result of applying the operator to the 2 numbers.

        The two key steps of the above algorithm were:

        Visit each operator, in linear order. Finding these can be done with a linear search of the original list.
        Get the 2 most recently seen numbers that haven't yet been replaced. These could be tracked using a Stack.
        The algorithm would be as follows:

        Complexity Analysis

        Let nn be the length of the list.

        Time Complexity : O(n)O(n).

        We do a linear search to put all numbers on the stack, and process all operators. Processing an operator requires removing 2 numbers off the stack and replacing them with a single number, which is an O(1)O(1) operation. Therefore, the total cost is proportional to the length of the input array. Unlike before, we're no longer doing expensive deletes from the middle of an Array or List.

        Space Complexity : O(n)O(n).

        In the worst case, the stack will have all the numbers on it at the same time. This is never more than half the length of the input array.

    """
    def doit_stack(self, tokens: list) -> int:
        
        stack = []
        def formula(a, b, c):
            if c == '-': 
                return a-b
            elif c == '+':
                return a+b
            elif c == '*':
                return a*b
            elif c == '/':
                return int(a/b)

        for c in tokens:
            
            if c.isdigit() or len(c) > 1 and c[0]=='-':
                stack.append(-int(c[1:]) if c[0] == '-' else int(c))
            else:
                op1, op2 = stack[-1], stack[-2]
                stack.pop()
                stack.pop()
                stack.append(formula(op2, op1, c))
            
        return stack[0]

    def doit_st(self, tokens: list) -> int:
        
        operations = {
            "+": lambda a, b: a + b,
            "-": lambda a, b: a - b,
            "/": lambda a, b: int(a / b),
            "*": lambda a, b: a * b
        }
        
        stack = []
        for token in tokens:
            if token in operations:
                number_2 = stack.pop()
                number_1 = stack.pop()
                operation = operations[token]
                stack.append(operation(number_1, number_2))
            else:
                stack.append(int(token))
        return stack.pop()

    def doit_statck(self, tokens):
    
        stack = []
        
        for token in tokens:
            
            if token not in "+-/*":
                stack.append(int(token))
                continue
        
            number_2 = stack.pop()
            number_1 = stack.pop()
            
            result = 0
            if token == "+":
                result = number_1 + number_2
            elif token == "-":
                result = number_1 - number_2
            elif token == "*":
                result = number_1 * number_2
            else:
                result = int(number_1 / number_2)
                
            stack.append(result)

        return stack.pop()

if __name__ == '__main__':

    EvalRPN().doit_stack(["10","6","9","3","+","-11","*","/","*","17","+","5","+"])
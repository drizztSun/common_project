



# 592. Fraction Addition and Subtraction

# Given a string representing an expression of fraction addition and subtraction,
# you need to return the calculation result in string format.
# The final result should be irreducible fraction.
# If your final result is an integer, say 2, you need to change it to the format of fraction that has denominator 1.
# So in this case, 2 should be converted to 2/1.

# Example 1:
# Input:"-1/2+1/2"
# Output: "0/1"

# Example 2:
# Input:"-1/2+1/2+1/3"
# Output: "1/3"

# Example 3:
# Input:"1/3-1/2"
# Output: "-1/6"

# Example 4:
# Input:"5/3+1/3"
# Output: "2/1"

# The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
# Each fraction (input and output) has format �numerator/denominator.
# If the first input fraction or the output is positive, then '+' will be omitted.
# The input only contains valid irreducible fractions, where the numerator and denominator of each fraction will always be in the range [1,10].
# If the denominator is 1, it means this fraction is actually an integer in a fraction format defined above.
# The number of given fractions will be in the range [1,10].
# The numerator and denominator of the final result are guaranteed to be valid and in the range of 32-bit int.

class fractionAddition:
    def doit(self, expression):
        """
        :type expression: str
        :rtype: str
        """
        def GCD(a, b):
            a, b = abs(a), abs(b)
            while b:
                tmp = b
                b = a % b
                a = tmp
            return a

        result = 0
        num = 0
        stack = []
        sign = False if expression[0] == '-' else True


        for i, c in enumerate(expression):

            if c in ('-', '+'):
                sign = c == '+'

            elif c.isdigit():
                num = num*10 + int(c)

            if c in ('-', '+', '/') and i != 0 or i == len(expression) - 1:
                if not sign and c != '-':
                    num = -num
                    sign = True
                stack.append(num)
                num = 0
                if len(stack) == 4:
                    a, b, c, d = stack[:]
                    A = a * d + b * c
                    B = b * d
                    gcd = GCD(A, B)
                    stack[0], stack[1] = int(A / gcd), int(B / gcd)
                    stack.pop()
                    stack.pop()

        
            
        sign = '-' if (stack[0] * stack[1]) < 0 else ''
        stack[0] = abs(stack[0])
        stack[1] = abs(stack[1])

        return sign + str(stack[0]) + '/' + str(stack[1])
                    

if __name__=="__main__":


    res = fractionAddition().doit("-1/2+1/2") # "0/1"

    res = fractionAddition().doit("-1/2+1/2+1/3") # "1/3"
    
    res = fractionAddition().doit("1/3-1/2") # "-1/6"

    res = fractionAddition().doit("5/3+1/3") #"2/1"
    

    pass
        
# 772 Basic Calculator III

# Implement a basic calculator to evaluate a simple expression string.

# The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

# The expression string contains only non-negative integers, +, -, *, / operators , open ( and closing parentheses ) and empty spaces .
# The integer division should truncate toward zero.

# You may assume that the given expression is always valid. All intermediate results will be in the range of [-2147483648, 2147483647]


# Example
# "1 + 1" = 2
# " 6-4 / 2 " = 4
# "2*(5+5*2)/3+(6/2+8)" = 21
# "(2+6* 3+5- (3*14/7+2)*5)+3"=-12

class CalculateIII:
    """
    @param s: the expression string
    @return: the answer
    """
    def doit(self, s):
        """
        :type expression: str
        :rtype: int
        """
        def evalExpress(e):
            st = []
            num, i, neg = 0, 0, 1
            while i < len(e):

                if e[i].isdigit():
                    num *= 10
                    num += int(e[i])

                if i == len(e) - 1 or e[i] in ('*', '/', '+', '-'):
                    num *= neg
                    if st and st[-1][1] in ('*', '/'):
                        p = st.pop()
                        num = p[0] * num if p[1] == '*' else int(p[0] / num)

                    st.append([num, e[i] if i != len(e) - 1 else 'n'])
                    num, neg = 0, 1
                    if i+1 < len(e) and e[i+1] in ('+', '-'):
                        neg = -1 if e[i+1] == '-' else 1
                        i += 1
                i += 1

            op, rvt = '', 0
            for c in st:
                if not op:
                    rvt, op = c
                elif op in ('+', '-'):
                    rvt += c[0] if op == '+' else -c[0]
                    op = c[1]

            return rvt

        stack = ['']
        for i in range(len(s)):

            if s[i] == '(':
                stack.append('')

            elif s[i] == ')':
                ans = evalExpress(stack.pop())
                if stack:
                    stack[-1] += str(ans)

            elif s[i].isdigit() or s[i] in ('+', '-', '*', '/'):
                stack[-1] += s[i]

        return evalExpress(stack[-1])


if __name__ == "__main__":

    res = CalculateIII().doit("1 + 1")

    res = CalculateIII().doit(" 6-4 / 2 ")

    res = CalculateIII().doit("2*(5+5*2)/3+(6/2+8)")
 
    res = CalculateIII().doit("(2+6* 3+5- (3*14/7+2)*5)+3")

    res = CalculateIII().doit("(3-(5-(8)-(2+(9-(0-(8-(2))))-(4))-(4)))") # 23

    pass

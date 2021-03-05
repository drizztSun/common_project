"""
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


"""


class ParsingBooleanExpre:

    def doit_stack(self, expression: str) -> bool:

        stack = []

        func = {
            '|': lambda x: any(x),
            '&': lambda x: all(x),
            '!': lambda x: not x[0]
        }

        for c in expression:

            if c == ')':
                temp = []
                while stack and stack[-1] != '(':
                    temp.append(stack.pop())
                stack.pop()
                op = stack.pop()

                stack.append(func[op](temp))
            else:

                if c == 't':
                    stack.append(True)
                elif c == 'f':
                    stack.append(False)
                elif c == ',':
                    continue
                else:
                    stack.append(c)

        return stack[0]


    def doit_stack_(self, S: str) -> bool:

        stval, stops, cur = [], [], []

        i = 0

        while i < len(S):
            
            if S[i] in '!|&':
                
                stval.append(cur)
                cur = []
                stops.append(S[i])
                i += 1
                
            elif S[i] == ')':
                
                res = None
                if stops[-1] == '!':
                    res = not cur[0]
                elif stops[-1] == '|':
                    res = any(cur)
                elif stops[-1] == '&':
                    res = all(cur)
                    
                cur = stval.pop()
                cur.append(res)
                stops.pop()
                
            elif S[i] in 'tf':
                
                cur.append(S[i] == 't')
                
            i += 1
            
        return cur[0]
    

    def doit_recursive(self, expression: str) -> bool:

        p = 0

        def search():
            nonlocal p
            ch = expression[p]
            p += 1

            if ch == 't':
                return True
            elif ch == 'f':
                return False
            elif ch == '!':
                p += 1
                ans = not search()
                p += 1
                return ans

            is_and = (ch == '&')
            ans = is_and
            p += 1
            while True:

                if is_and:
                    ans &= search()
                else:
                    ans |= search()

                if expression[p] == ')':
                    p += 1
                    break
                p += 1

            return ans

        return search()


if __name__ == '__main__':

    ParsingBooleanExpre().doit_recursive("|(f, t)")

    ParsingBooleanExpre().doit_("|(&(t,f,t),!(t))")
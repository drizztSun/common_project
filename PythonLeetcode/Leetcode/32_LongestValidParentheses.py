import os


# 20. Valid Parentheses
# Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
# The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
class isValidParentheses(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: bool
        """
        stack = []
        for c in s:
            if c in ('(', '{', '['):
                stack.append(c)
            elif c in (')', '}', ']') and not stack:
                return False
            else:
                if c == ')' and stack[-1] == '(' or c == '}' and stack[-1] == '{' or c == ']' and stack[-1] == '[':
                    stack.pop()
                else:
                    return False

        return not stack 
        
# 22. Generate Parentheses
# Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
# For example, given n = 3, a solution set is:
# [
#  "((()))",
#  "(()())",
#  "(())()",
#  "()(())",
#  "()()()"
# ]

class generateParenthesis(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        def generate(left, right, num, res, rv):

            if left == num and right == num:
                rv.append(res)
        
            if left < num:
                generate(left + 1, right, num, res + '(', rv)

            if left > right:
                generate(left, right+1, num, res + ')', rv)

        rv = []
        generate(0, 0, n, "", rv)
        return rv
        
    def doit1(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        def generate(p, left, right, res):

            if right == 0:
                res.append(p)
            
            if left:
                generate(p + '(', left - 1, right, res)

            if left < right:
                generate(p + ')', left, right - 1, res)

        
        res = []
        generate('', n, n, res)
        return res

    def doit2(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        def generate(p, left, right):
            if right >= left >= 0:
                if not right:
                    yield p
                for q in generate(p + '(', left-1, right): yield q
                for q in generate(p + ')', left, right-1): yield q

        return list(generate('', n, n))



# My method is DP. First consider how to get the result f(n) from previous result f(0)…f(n-1).
# Actually, the result f(n) will be put an extra () pair to f(n-1). Let the “(” always at the first position, to produce a valid result, we can only put “)” in a way that there will be i pairs () inside the extra () and n - 1 - i pairs () outside the extra pair.

# Let us consider an example to get clear view:

# f(0): “”
# f(1): “(“f(0)”)”

# f(2): "(“f(0)”)"f(1), “(“f(1)”)”f(0)

# f(3): "(“f(0)”)"f(2), "(“f(1)”)"f(1), “(“f(2)”)”f(0)

# So f(n) = "(“f(0)”)"f(n-1) , "(“f(1)”)"f(n-2) "(“f(2)”)"f(n-3) … "(“f(i)”)“f(n-1-i) … “(f(n-1)”)”f(0)


    def doit3(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        D = [[""]]
        
        i = 1
        while i <= n:

            cur = []
            j = 0
            while j < i:
                
                for first in D[j]:
                    for second in D[i-j-1]:
                        cur.append("(" + first + ")" + second)
                j += 1

            D.append(cur)
            i += 1

        return D[-1]

# 32. Longest Valid Parentheses

# Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
# For "(()", the longest valid parentheses substring is "()", which has length = 2.
# Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.


class longestValidParentheses(object):

    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        stack = []
        for i, c in enumerate(s):
            if c == '(':
                stack.append(i)
            else:
                if stack and s[stack[-1]] == '(':
                    stack.pop()
                else:
                    stack.append(i)

        length = 0
        if not stack:
            length = len(s)
        else:
            a, b, = len(s)-1, -1
            while stack:
                b = stack.pop()
                length = max(length, a-b)
                a = b

            length = max(length, a - 0)

        return length

# My solution uses DP. The main idea is as follows: I construct a array <b>longest[]</b>, for any longest[i], it stores the longest length of valid parentheses which is end at i.
# And the DP idea is :
# If s[i] is ‘(’, set longest[i] to 0,because any string end with ‘(’ cannot be a valid one.
# Else if s[i] is ‘)’
#    If s[i-1] is ‘(’, longest[i] = longest[i-2] + 2
#    Else if s[i-1] is ‘)’ and s[i-longest[i-1]-1] == ‘(’, longest[i] = longest[i-1] + 2 + longest[i-longest[i-1]-2]
# For example, input “()(())”, at i = 5, longest array is [0,2,0,0,2,0], longest[5] = longest[4] + 2 + longest[1] = 6.
# 

    def doit1(self, s):
        """
        :type s: str
        :rtype: int
        """
        D = [0 for _ in range(len(s)+ 1)]

        maxLen = 0
        for i in range(1, len(s)+1):
            
            if s[i-1] == '(':
                D[i] = 0
            else:
                if i-2 >= 0 and s[i-2] == '(':
                    D[i] = D[i-2] + 2

                elif i-D[i-1]-2 >=0 and s[i-D[i-1]-2] == '(':
                    D[i] = D[i-1] + 2 

                    if i-D[i-1]-2 >= 0 and D[i-D[i-1]-2] > 0:
                        D[i] += D[i-D[i-1]-2]
               
                maxLen = max(maxLen, D[i])

        return maxLen    


if __name__ == "__main__":


    res = generateParenthesis().doit1(3)


    res = longestValidParentheses().doit1(')(')

    res = longestValidParentheses().doit1('())')

    pass
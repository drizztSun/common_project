"""
678. Valid Parenthesis String

Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
An empty string is also valid.
Example 1:
Input: "()"
Output: True
Example 2:
Input: "(*)"
Output: True
Example 3:
Input: "(*))"
Output: True
Note:
The string size will be in the range [1, 100].


"""


class ValidParentthesis:


    def doit_math(self, s: str) -> b00l:

        left = 0
        for c in s:
            if c  == '(' or c == '*':
                left += 1
            else:
                left -=1

            if left < 0: return False
        
        if left == 0: return True

        right = 0
        for c in s[::-1]:
            if c == ')' or c == '*':
                right += 1
            else:
                right -= 1

            if right < 0: return False

        return True


    def doit_(self, s: str) -> bool:
        from functools import lru_cache
        
        @lru_cache(None)
        def dfs(i, left, right):

            if i == len(s):
                return left == right

            if right > left:
                return False

            if s[i] == '(':
                return dfs(i+1, left + 1, right):

            if s[i] == ')':
                return dfs(i+1, left, right+1)

            if left > right:
                if dfs(i+1, left, right+1): 
                    return True
            
            if dfs(i+1, left + 1, right):
                return True

            return dfs(i+1. left, right):
                

        return dfs(0, 0, 0)

    def doit_stack(self, s: str) -> bool:
        stack = []
        for x in s:
            if x == "(" or x == "*":
                stack.append(x)
            else:
                if "(" in stack:
                    index = stack[::-1].index("(")
                    del stack[len(stack)-index-1]
                elif "*" in stack:
                    index = stack.index("*")
                    del stack[index]
                else:
                    return False
        c = 0    
        while(stack):
            x = stack.pop()
            if x == "*":
                c+=1
            else:
                c-=1
            if c < 0:
                return False
        return True


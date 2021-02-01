"""
# 921. Minimum Add to Make Parentheses Valid

# Given a string S of '(' and ')' parentheses, we add the minimum number of parentheses ( '(' or ')',
# and in any positions ) so that the resulting parentheses string is valid.

# Formally, a parentheses string is valid if and only if:

# It is the empty string, or
# It can be written as AB (A concatenated with B), where A and B are valid strings, or
# It can be written as (A), where A is a valid string.
# Given a parentheses string, return the minimum number of parentheses we must add to make the resulting string valid.


# Example 1:

# Input: "())"
# Output: 1

# Example 2:

# Input: "((("
# Output: 3
# Example 3:

# Input: "()"
# Output: 0
# Example 4:

# Input: "()))(("
# Output: 4


# Note:

# S.length <= 1000
# S only consists of '(' and ')' characters.
"""

class MinAddToMakeValid:

    """
        Intuition:
        To make a string valid,
        we can add some ( on the left,
        and add some ) on the right.
        We need to find the number of each.


        Explanation:
        left records the number of ( we need to add on the left of S.
        right records the number of ) we need to add on the right of S,
        which equals to the number of current opened parentheses.


        Loop char c in the string S:
        if (c == '('), we increment right,
        if (c == ')'), we decrement right.
        When right is already 0, we increment left
        Return left + right in the end


        Time Complexity:
        Time O(N)
        Space O(1)
    """
    def minAddToMakeValid(self, S):
        left = right = 0
        for i in S:
            if right == 0 and i == ')':
                left += 1
            else:
                right += 1 if i == '(' else -1
        return left + right


    """
    Approach 1: Balance
    Intuition and Algorithm

    Keep track of the balance of the string: the number of '(''s minus the number of ')''s.
    A string is valid if its balance is 0, plus every prefix has non-negative balance.

    The above idea is common with matching brackets problems, but could be difficult to find if you haven't seen it before.

    Now, consider the balance of every prefix of S. If it is ever negative (say, -1),
    we must add a '(' bracket. Also, if the balance of S is positive (say, +B), we must add B ')' brackets at the end.
    """

    def doit(self, S):

        ans = bal = 0
        for c in S:
            
            bal += 1 if c == '(' else -1
            # It is guaranteed bal >= -1
            if bal == -1:
                ans += 1
                bal += 1

        return ans + bal

    def doit(self, S):
        res, cur = [], 0
        for i, c in enumerate(S):

            if i != 0 and S[i-1] == ')' and c == '(':
                res.append(cur)
                cur = 0

            cur += 1 if c == '(' else -1

            if i == len(S) - 1:
                res.append(cur)

        ans = 0
        while res:
            c = res.pop()
            if c > 0:
                ans += c
            else:
                if not res:
                    ans += abs(c)
                else:
                    res[-1] += c

        return ans

    def doit(self, S):
        left = right = 0

        for char in S:
            if char == '(':
                left += 1
            else:
                if left:
                    left -= 1
                else:
                    right += 1
        return left + right


if __name__ == '__main__':

    res = MinAddToMakeValid().doit("())")

    res = MinAddToMakeValid().doit("(((")

    res = MinAddToMakeValid().doit("()")

    res = MinAddToMakeValid().doit("()))((")

    res = MinAddToMakeValid().doit("(()())((")

    res = MinAddToMakeValid().doit("((((()))(()())")  # 2

    res = MinAddToMakeValid().doit("()))((")  # 4

    pass

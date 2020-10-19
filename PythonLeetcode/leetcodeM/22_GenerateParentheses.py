"""
22. Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.



Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
"""


class GenerateParenthesis:

    def doit(self, n: int):

        op = []
        def helper(open, closed, open_so_far, para):
            if open == 0 and closed == 0:
                op.append(para)
                return

            if open > 0:
                helper(open-1, closed, open_so_far + 1, para + '(' )

            if open_so_far> 0:
                helper(open, closed -1, open_so_far -1 , para + ')')

        helper(n-1, n, 1, '(')
        return op

    """
    Approach 2: Backtracking
    Intuition and Algorithm
    
    Instead of adding '(' or ')' every time as in Approach 1, let's only add them when we know it will remain a valid sequence. We can do this by keeping track of the number of opening and closing brackets we have placed so far.
    
    We can start an opening bracket if we still have one (of n) left to place. And we can start a closing bracket if it would not exceed the number of opening brackets
    """
    def doit_backtrack(self, N):
        ans = []
        def backtrack(S = '', left = 0, right = 0):
            if len(S) == 2 * N:
                ans.append(S)
                return
            if left < N:
                backtrack(S+'(', left+1, right)
            if right < left:
                backtrack(S+')', left, right+1)

        backtrack()
        return ans

    """
    Approach 3: Closure Number
    Intuition
    
    To enumerate something, generally we would like to express it as a sum of disjoint subsets that are easier to count.
    
    Consider the closure number of a valid parentheses sequence S: the least index >= 0 so that S[0], S[1], ..., S[2*index+1] is valid. Clearly, every parentheses sequence has a unique closure number. We can try to enumerate them individually.
    
    Algorithm
    
    For each closure number c, we know the starting and ending brackets must be at index 0 and 2*c + 1. Then, the 2*c elements between must be a valid sequence, plus the rest of the elements must be a valid sequence.
    """
    def doit_closue_number(self, N):
        if N == 0: return ['']
        ans = []
        for c in xrange(N):
            for left in self.generateParenthesis(c):
                for right in self.generateParenthesis(N-1-c):
                    ans.append('({}){}'.format(left, right))
        return ans


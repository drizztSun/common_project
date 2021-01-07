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

    def doit_dfs(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        left = right = n

        def search(l, r, memo):

            if l > r or l < 0 or r < 0:
                return []

            if l == r == 0:
                return [""]

            if (l, r) in memo:
                return memo[(l, r)]

            res = []

            for c in search(l - 1, r, memo):
                res.append('(' + c)

            for c in search(l, r - 1, memo):
                res.append(')' + c)

            memo[(l, r)] = res
            return res

        return search(left, right, {})

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


    Complexity Analysis

    Our complexity analysis rests on understanding how many elements there are in generateParenthesis(n). This analysis is outside the scope of this article, but it turns out this is the n-th Catalan number (n+1)^-1 * C(2n, n), 
    which is bounded asymptotically by 4^n(n*n^0.5)^-1

    Time Complexity : 4^n(n*n^0.5)^-1. Each valid sequence has at most n steps during the backtracking procedure.

    Space Complexity : 4^n(n*n^0.5)^-1 , as described above, and using O(n)O(n) space to store the sequence.
    """
    def doit_backtracking(self, N):
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

        def search(N):
            if N == 0:
                return ['']

            ans = []
            for c in range(N):
                for left in search(c):
                    for right in search(N-1-c):
                        ans.append('({}){}'.format(left, right))
        search(N)
        return ans




if __name__ == '__main__':

    GenerateParenthesis().doit_1(3)


"""
# 856. Score of Parentheses


# Given a balanced parentheses string S, compute the score of the string based on the following rule:

# () has score 1
# AB has score A + B, where A and B are balanced parentheses strings.
# (A) has score 2 * A, where A is a balanced parentheses string.


# Example 1:

# Input: "()"
# Output: 1
# Example 2:

# Input: "(())"
# Output: 2
# Example 3:

# Input: "()()"
# Output: 2
# Example 4:

# Input: "(()(()))"
# Output: 6
"""


class ScoreOfParentheses:

    """
    Approach 1: Divide and Conquer
    Intuition

    Split the string into S = A + B where A and B are balanced parentheses strings, and A is the smallest possible non-empty prefix of S.

    Algorithm

    Call a balanced string primitive if it cannot be partitioned into two non-empty balanced strings.

    By keeping track of balance (the number of ( parentheses minus the number of ) parentheses),
    we can partition S into primitive substrings S = P_1 + P_2 + ... + P_n. Then, score(S) = score(P_1) + score(P_2) + ... + score(P_n), by definition.

    For each primitive substring (S[i], S[i+1], ..., S[k]), if the string is length 2, then the score of this string is 1.
    Otherwise, it's twice the score of the substring (S[i+1], S[i+2], ..., S[k-1]).

    Complexity Analysis

    Time Complexity: O(N^2), where NN is the length of S. An example worst case is (((((((....))))))).

    Space Complexity: O(N), the size of the implied call stack.

    Complexity Analysis

    Time Complexity: O(N^2),  where NN is the length of S. An example worst case is (((((((....))))))).

    Space Complexity: O(N), the size of the implied call stack.
    """
    def doit_divide_conquer(self, S):

        def F(i, j):

            ans = base = 0

            for c in range(i, j):

                base += 1 if S[c] == '(' else -1

                if base == 0:
                    if c - i == 1:
                        ans += 1
                    else:
                        ans += 2 * F(i+1, c)

                    i = c + 1

            return ans

        return F(0, len(S))

    """
    Approach 2: Stack
    Intuition and Algorithm
    
    Every position in the string has a depth - some number of matching parentheses surrounding it. 
    For example, the dot in (()(.())) has depth 2, because of these parentheses: (__(.__))
    
    Our goal is to maintain the score at the current depth we are on. When we see an opening bracket, 
    we increase our depth, and our score at the new depth is 0. When we see a closing bracket, 
    we add twice the score of the previous deeper part - except when counting (), which has a score of 1.
    
    For example, when counting (()(())), our stack will look like this:
    
    [0, 0] after parsing (
    [0, 0, 0] after (
    [0, 1] after )
    [0, 1, 0] after (
    [0, 1, 0, 0] after (
    [0, 1, 1] after )
    [0, 3] after )
    [6] after )
    """
    def doit_stack(self, S):
        stack = [0]
        # The score of the current frame

        for x in S:
            if x == '(':
                stack.append(0)
            else:
                v = stack.pop()
                stack[-1] += max(2 * v, 1)

        return stack.pop()

    """
    Approach 3: Count Cores
    Intuition
    
    The final sum will be a sum of powers of 2, as every core (a substring (), with score 1) 
    will have it's score multiplied by 2 for each exterior set of parentheses that contains that core.
    
    Algorithm
    
    Keep track of the balance of the string, as defined in Approach #1. For every ) that immediately follows a (, the answer is 1 << balance, 
    as balance is the number of exterior set of parentheses that contains this core.
    """
    def doit_count(self, S):
        ans = bal = 0
        for i, x in enumerate(S):
            if x == '(':
                bal += 1
            else:
                bal -= 1
                if S[i-1] == '(':
                    ans += 1 << bal
        return ans


if __name__ == '__main__':

    res = ScoreOfParentheses().doit("()")  # 1

    res = ScoreOfParentheses().doit("(())")  # 2

    res = ScoreOfParentheses().doit("()()")  # 2

    res = ScoreOfParentheses().doit("(()()())")  # 6

    res = ScoreOfParentheses().doit("(((()(()())((())))))")
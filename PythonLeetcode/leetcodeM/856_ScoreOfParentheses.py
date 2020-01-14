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

"""


class ScoreOfParentheses:

    def doit(self, S):
        scoreStack = []
        score = 0
        for x in S:
            if x == '(':
                scoreStack.append(score)
                score = 0
            else:
                score = scoreStack.pop() + max(score*2, 1)
        return score

    def doit(self, S):

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


if __name__ == '__main__':

    res = ScoreOfParentheses().doit("()")  # 1

    res = ScoreOfParentheses().doit("(())")  # 2

    res = ScoreOfParentheses().doit("()()")  # 2

    res = ScoreOfParentheses().doit("(()()())")  # 6

    res = ScoreOfParentheses().doit("(((()(()())((())))))")

    pass

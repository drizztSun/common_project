"""
301 Remove Invalid Parentheses

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"
Output: ["()()()", "(())()"]
Example 2:

Input: "(a)())()"
Output: ["(a)()()", "(a())()"]
Example 3:

Input: ")("
Output: [""]
"""


class RemoveInvalidParentheses:

    """
    Approach 1: Backtracking
    Intuition

    For this question, we are given an expression consisting of parentheses and there can be some misplaced or extra brackets in the expression that cause it to be invalid.
    An expression consisting of parentheses is considered valid only when every closing bracket has a corresponding opening bracket and vice versa.

    This means if we start looking at each of the bracket from left to right, as soon as we encounter a closing bracket,
    there should be an unmatched opening bracket available to match it. Otherwise the expression would become invalid.
    The expression can also become invalid if the number of opening parentheses i.e. ( are more than the number of closing parentheses i.e. ).

    Let us look at an invalid expression and all the possible valid expressions that can be formed from it by removing some of the brackets.
    There is no restriction on which parentheses we can remove. We simply have to make the expression valid.

    """
    def doit_backtracking(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        left = 0
        right = 0

        # First, we find out the number of misplaced left and right parentheses.
        for char in s:

            # Simply record the left one.
            if char == '(':
                left += 1
            elif char == ')':
                # If we don't have a matching left, then this is a misplaced right, record it.
                right = right + 1 if left == 0 else right

                # Decrement count of left parentheses because we have found a right
                # which CAN be a matching one for a left.
                left = left - 1 if left > 0 else left

        result = {}

        def recurse(s, index, left_count, right_count, left_rem, right_rem, expr):
            # If we reached the end of the string, just check if the resulting expression is
            # valid or not and also if we have removed the total number of left and right
            # parentheses that we should have removed.
            if index == len(s):
                if left_rem == 0 and right_rem == 0:
                    ans = "".join(expr)
                    result[ans] = 1
                return

            # The discard case. Note that here we have our pruning condition.
            # We don't recurse if the remaining count for that parenthesis is == 0.
            if (s[index] == '(' and left_rem > 0) or (s[index] == ')' and right_rem > 0):
                recurse(s, index + 1,
                        left_count,
                        right_count,
                        left_rem - (s[index] == '('),
                        right_rem - (s[index] == ')'), expr)

            expr.append(s[index])

            # Simply recurse one step further if the current character is not a parenthesis.
            if s[index] != '(' and s[index] != ')':
                recurse(s, index + 1,
                        left_count,
                        right_count,
                        left_rem,
                        right_rem, expr)
            elif s[index] == '(':
                # Consider an opening bracket.
                recurse(s, index + 1,
                        left_count + 1,
                        right_count,
                        left_rem,
                        right_rem, expr)
            elif s[index] == ')' and left_count > right_count:
                # Consider a closing bracket.
                recurse(s, index + 1,
                        left_count,
                        right_count + 1,
                        left_rem,
                        right_rem, expr)

            # Pop for backtracking.
            expr.pop()

        # Now, the left and right variables tell us the number of misplaced left and
        # right parentheses and that greatly helps pruning the recursion.
        recurse(s, 0, 0, 0, left, right, [])
        return list(result.keys())

    def doit_dfs(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        def removeParentheses(s, start, end, result, par):
            i, stack = start, 0
            while i < len(s):
                if s[i] == par[1]:
                    stack -= 1
                elif s[i] == par[0]:
                    stack += 1

                if stack >= 0:
                    i += 1
                    continue

                j = end
                while j <= i:
                    if s[j] == par[1] and (j == end or s[j - 1] != par[1]):
                        removeParentheses(s[:j] + s[j + 1:], i, j, result, par)
                    j += 1
                return

            reversedStr = s[::-1]
            if par[0] == '(':
                removeParentheses(reversedStr, 0, 0, result, [')', '('])
            else:
                result.append(reversedStr)

        result, par = [], ['(', ')']
        removeParentheses(s, 0, 0, result, par)
        if len(result) == 0:
            result.append("")
        return result


if __name__ == "__main__":

    RemoveInvalidParentheses().doit_dfs("()())()")

    RemoveInvalidParentheses().doit_dfs("(a)())()")

    RemoveInvalidParentheses().doit_dfs(")(")
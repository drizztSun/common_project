
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
                for q in generate(p + '(', left-1, right):
                    yield q
                for q in generate(p + ')', left, right-1):
                    yield q

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


"""
# 32. Longest Valid Parentheses

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Example 1:

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"

"""


class LongestValidParentheses(object):

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

    """
    # My solution uses DP.
    # The main idea is as follows: I construct a array <b>longest[]</b>, for any longest[i], it stores the longest length of valid parentheses which is end at i.
    # And the DP idea is :
    # If s[i] is ‘(’, set longest[i] to 0,because any string end with ‘(’ cannot be a valid one.
    # Else if s[i] is ‘)’
    #    If s[i-1] is ‘(’, longest[i] = longest[i-2] + 2
    #    Else if s[i-1] is ‘)’ and s[i-longest[i-1]-1] == ‘(’, longest[i] = longest[i-1] + 2 + longest[i-longest[i-1]-2]
    # For example, input “()(())”, at i = 5, longest array is [0,2,0,0,2,0], longest[5] = longest[4] + 2 + longest[1] = 6.
    #
    """
    # (DP)

    def doit_dp(self, s):
        """
        :type s: str
        :rtype: int
        """
        dp, max_len = [0 for _ in range(len(s))], 0

        for i in range(1, len(s)):
            if s[i] == ')':
                if s[i-1] == '(':
                    dp[i] = 2 + (dp[i-2] if i - 2 >= 0 else 0)

                elif i - dp[i-1] > 0 and s[i-dp[i-1]-1] == '(':
                    dp[i] = dp[i-1] + 2 + (dp[i-dp[i-1]-2] if i-dp[i-1]-2 > 0 else 0)

                max_len = max(max_len, dp[i])
        return max_len

    """
    Approach 3: Using Stack
    Algorithm

    Instead of finding every possible string and checking its validity, we can make use of stack while scanning the given string to check if the string scanned so far is valid,
    and also the length of the longest valid string. In order to do so, we start by pushing -1 onto the stack.

    For every ‘(’ encountered, we push its index onto the stack.

    For every ‘)’ encountered, we pop the topmost element and subtract the current element's index from the top element of the stack, which gives the length of the currently encountered valid string of parentheses.
    If while popping the element, the stack becomes empty, we push the current element's index onto the stack. In this way, we keep on calculating the lengths of the valid substrings, and return the length of the longest valid string at the end.

    See this example for better understanding.
    Complexity Analysis

    Time complexity : O(n). nn is the length of the given string..
    Space complexity : O(n). The size of stack can go up to nn.

    every '(' will be match and removed from stack, by '('. if there is any '(', left in the stack, it means we don't have ')' to match it.
    '-1' is the begining of the list. if there is any ')' can't find '(' in stack, it means from ')', which blocked the longest sequence, we have to find new one.
    """
    def doit_stack(self, s):
        """
        :type s: str
        :rtype: int
        """
        st, max_len = [-1], 0

        for i in range(len(s)):
            if s[i] == '(':
                st.append(i)
            else:
                st.pop()
                if not st:
                    st.append(i)
                else:
                    max_len = max(max_len, i - st[-1])
        return max_len

    """
    Approach 4: Without extra space
    Algorithm

    In this approach, we make use of two counters left and right.
    First, we start traversing the string from the left towards the right and for every ‘(’ encountered, we increment the left counter and for every ‘)’ encountered, we increment the right counter.
    Whenever left becomes equal to right, we calculate the length of the current valid string and keep track of maximum length substring found so far.
    If right becomes greater than left we reset left and right to 0.

    Next, we start traversing the string from right to left and similar procedure is applied.

    Example of this approach:
    """
    def doit1(self, s):
        """
        :type s: str
        :rtype: int
        """
        left, right = 0, 0
        max_len = 0

        for c in s:
            if c == '(':
                left += 1
            else:
                right += 1

            if left == right:
                max_len = max(max_len, 2 * right)
            elif right > left:
                left = right = 0

        left = right = 0
        for c in reversed(s):
            if c == '(':
                left += 1
            else:
                right += 1

            if right == left:
                max_len = max(max_len, 2 * right)
            elif left > right:
                left = right = 0

        return max_len


if __name__ == "__main__":

    res = generateParenthesis().doit1(3)

    res = LongestValidParentheses().doit1(')(')

    res = LongestValidParentheses().doit1('()(()))')

    pass

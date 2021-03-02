"""
1190. Reverse Substrings Between Each Pair of Parentheses

You are given a string s that consists of lower case English letters and brackets. 

Reverse the strings in each pair of matching parentheses, starting from the innermost one.

Your result should not contain any brackets.

 

Example 1:

Input: s = "(abcd)"
Output: "dcba"
Example 2:

Input: s = "(u(love)i)"
Output: "iloveu"
Explanation: The substring "love" is reversed first, then the whole string is reversed.
Example 3:

Input: s = "(ed(et(oc))el)"
Output: "leetcode"
Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.
Example 4:

Input: s = "a(bcdefghijkl(mno)p)q"
Output: "apmnolkjihgfedcbq"
 

Constraints:

0 <= s.length <= 2000
s only contains lower case English characters and parentheses.
It's guaranteed that all parentheses are balanced.
"""


class ReverseParentheses:

    """
        Solution 1: Brute Force
        Here is the brute force solution, which seems really easy to write.
        Nothing more to talk about.

        Time O(N^2), Space O(N)
    """
    def doit_(self, s):
        res = ['']
        for c in s:
            if c == '(':
                res.append('')
            elif c == ')':
                res[len(res) - 2] += res.pop()[::-1]
            else:
                res[-1] += c
        return "".join(res)

    """
        Solution 2: Wormholes
        Intuition
        Nice. I got a green accpeted with solution 1.
        Now before move on, let us check the solutions in the discuss.

        Hey hey hey wait, ALL solutions are BRUTE FORCE ?
        Hmmmm... why not O(N)?

        Fine fine fine, here comes an easy O(N) solution.

        Explanation
        In the first pass,
        use a stack to find all paired parentheses,
        I assume you can do this.

        Now just imgine that all parentheses are wormholes.
        As you can see in the diagram,
        the paired parentheses are connected to each other.

        image

        First it follows the left green arrrow,
        go into the left wormhole and get out from the right wormhole.
        Then it iterates the whole content between parentheses.
        Finally it follows the right arrow,
        go into the left wormhole,
        get out from the right wormhole and finish the whole trip.

        So in the second pass of our solution,
        it traverses through the paired parentheses
        and generate the result string res.

        i is the index of current position.
        d is the direction of traversing.


        Complexity
        Time O(N) for two passes
        Space O(N)

    """
    def doit_stack_parenthesis(self, s: str) -> str:
        opened = []
        pair = {}
        for i, c in enumerate(s):
            if c == '(':
                opened.append(i)
            if c == ')':
                j = opened.pop()
                pair[i], pair[j] = j, i
        res = []
        i, d = 0, 1
        while i < len(s):
            if s[i] in '()':
                i = pair[i]
                d = -d
            else:
                res.append(s[i])
            i += d
        return ''.join(res)
# 761. Special Binary String

# Special binary strings are binary strings with the following two properties:

# The number of 0's is equal to the number of 1's.
# Every prefix of the binary string has at least as many 1's as 0's.
# Given a special string S, a move consists of choosing two consecutive,
# non-empty, special substrings of S, and swapping them.

# (Two strings are consecutive if the last character of the first string
# is exactly one index before the first character of the second string.)

# At the end of any number of moves, what is the lexicographically largest resulting string possible?

# Example 1:
# Input: S = "11011000"
# Output: "11100100"

# Explanation:
# The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
# This is the lexicographically largest string possible after some number of swaps.
# Note:

# S has length at most 50.
# S is guaranteed to be a special binary string as defined above.


class MakeLargestSpecial:

    # Just 4 steps:

    # Split S into several special strings (as many as possible).
    # Special string starts with 1 and ends with 0. Recursion on the middle part.
    # Sort all special strings in lexicographically largest order.
    # Join and output all strings.
    # Updated:

    # The middle part of a special string may not be another special string. But in my recursion it is.
    # For example, 1M0 is a splitted special string. M is its middle part and it must be another special string.

    # Because:

    # The number of 0's is equal to the number of 1's in M
    # If there is a prefix P of Mwhich has one less 1's than 0's,
    # 1P will make up a special string. 1P will be found as special string before 1M0 in my solution.
    # It means that every prefix of M has at least as many 1's as 0's.
    # Based on 2 points above, M is a special string.

    def doit(self, S):
        """
        :type S: str
        :rtype: str
        """
        def largestSpecialString(s):
            count, j = 0, 0
            res = []

            for i in range(len(s)):

                count += 1 if s[i] == '1' else -1
                if count == 0:
                    res.append('1' + largestSpecialString(s[j+1:i]) + '0')
                    j = i + 1

            return ''.join(sorted(res, reverse=1))

        return largestSpecialString(S)


import functools

class Solution:

    def compareTwoNumbers(self, num1, num2):
        if num2 + num1 > num1 + num2:
            return 1

        if num2 + num1 == num1 + num2:
            return 0

        return -1

    def makeLargestSpecial(self, s):
        """
        :type S: str
        :rtype: str
        """

        if len(s) is 2:
            return s

        sum = 0
        start_index = 0
        substrings = []

        for index, c in enumerate(s):

            if c is '1':
                sum += 1
            else:
                sum -= 1

            if sum is 0:
                substrings.append(s[start_index: index + 1])
                start_index = index + 1

        if len(substrings) is 1:
            return "1" + self.makeLargestSpecial(substrings[0][1:-1]) + "0"

        else:
            results = []
            for sub in substrings:
                results.append(self.makeLargestSpecial(sub))

            sorted_nums = sorted(results, key=functools.cmp_to_key(self.compareTwoNumbers))
            result = ''

            for r in sorted_nums:
                result = result + r

            return result


if __name__ == "__main__":

    res = MakeLargestSpecial().doit("11011000")

    pass

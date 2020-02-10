# 984. String Without AAA or BBB

# Given two integers A and B, return any string S such that:

# S has length A + B and contains exactly A 'a' letters, and exactly B 'b' letters;
# The substring 'aaa' does not occur in S;
# The substring 'bbb' does not occur in S.


# Example 1:

# Input: A = 1, B = 2
# Output: "abb"
# Explanation: "abb", "bab" and "bba" are all correct answers.

# Example 2:

# Input: A = 4, B = 1
# Output: "aabaa"

class StrWithout3a3b:

    """
    Approach 1: Greedy
    Intuition

    Intuitively, we should write the most common letter first.
    For example, if we have A = 6, B = 2, we want to write 'aabaabaa'.
    The only time we don't write the most common letter is if the last two letters we have written are also the most common letter

    Algorithm

    Let's maintain A, B: the number of 'a' and 'b''s left to write.
    If we have already written the most common letter twice, we'll write the other letter. Otherwise, we'll write the most common letter.

    Complexity Analysis

    Time Complexity: O(A+B)O(A+B).
    Space Complexity: O(A+B)O(A+B).
    """

    def doit(self, A, B):

        ans = []

        while A or B:

            if len(ans) >= 2 and ans[-1] == ans[-2]:
                writeA = ans[-1] == 'b'
            else:
                writeA = A >= B

            if writeA:
                ans.append('a')
                A -= 1
            else:
                ans.append('b')
                B -= 1

        return ''.join(ans)

    def doit(self, A, B):

        ans = ""

        while A and B:
            if A > B:
                ans += "aab"
                A -= 2
                B -= 1
            elif B > A:
                ans += "bba"
                B -= 2
                A -= 1
            else:
                ans += "ab"*A
                A = 0
                B = 0
        ans += "a"*A
        ans += "b"*B

        return ans

        return ans


if __name__ == '__main__':

    res = StrWithout3a3b().doit(4, 1)

    pass

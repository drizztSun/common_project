
# 541. Reverse String II

# Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting from the start of the string. 
# If there are less than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, 
# then reverse the first k characters and left the other as original.

# Example:
# Input: s = "abcdefg", k = 2
# Output: "bacdfeg"

# Restrictions:
# The string consists of lower English letters only.
# Length of the given string and k will in the range [1, 10000]


class ReverseStr(object):

    def doit(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        res, i = '', 0
        while i < len(s):

            e = i + k if i + k < len(s) else len(s)
            res += s[i: e][::-1]

            i = e
            e = i + k if i + k < len(s) else len(s)
            res += s[i:e]

            i = e

        return res                        

    def doit1(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        i = 0
        ans = list(s)
        while i < len(s):
            start = i
            end = min(start + k - 1, len(s) - 1)
            while start < end:
                tmp = ans[start]
                ans[start] = ans[end]
                ans[end] = tmp
                start += 1
                end -= 1
            i = i + 2 * k
            start = i
        return "".join(ans)


# 557. Reverse Words in a String III

# Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

# Example 1:
# Input: "Let's take LeetCode contest"
# Output: "s'teL ekat edoCteeL tsetnoc"
# Note: In the string, each word is separated by single space and there will not be any extra space in the string.

class ReverseWordsIII(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        A = s.split(' ')
        for i in range(len(A)):
            A[i] = A[i][::-1]
        return ' '.join(A)



if __name__ == "__main__":

    res = ReverseStr().doit("abcdefg", 2)

        
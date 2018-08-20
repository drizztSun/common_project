
# 344. Reverse String


# Write a function that takes a string as input and returns the string reversed.

# Example:
# Given s = "hello", return "olleh".


class Solution(object):
    def reverseString(self, s):
        """
        :type s: str
        :rtype: str
        """
        i, j = 0, len(s) - 1
        A = list(s)
        while i < j:
            A[i], A[j] = A[j], A[i]            
            i += 1
            j -= 1
            
        return ''.join(A)



if __name__ == "__main__":

    res = Solution().doit("abcdefg")
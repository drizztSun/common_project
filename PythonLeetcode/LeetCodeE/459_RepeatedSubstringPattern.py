# 459. Repeated Substring Pattern


# Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. 
# You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

 

# Example 1:

# Input: "abab"
# Output: True
# Explanation: It's the substring "ab" twice.

# Example 2:

# Input: "aba"
# Output: False

# Example 3:

# Input: "abcabcabcabc"
# Output: True
# Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)


class RepeatedSubstringPattern:
    def doit(self, s):
        """
        :type s: str
        :rtype: bool
        """
        for L in range(1, len(s) // 2 + 1):

            if len(s) % L:
            
                continue
 
            sub, j = s[:L], L
            while j < len(s):
                if sub != s[j: j + L]:
                    break
                j += L

            if j == len(s):
                return True

        return False


    def doit1(self, s):
        """
        :type s: str
        :rtype: bool
        """
        return (s + s)[1: -1].find(s) != -1


if __name__ == "__main__":

    res = RepeatedSubstringPattern().doit('abab')

    res = RepeatedSubstringPattern().doit("aba")

    res = RepeatedSubstringPattern().doit("abcabcabcabc")       
        

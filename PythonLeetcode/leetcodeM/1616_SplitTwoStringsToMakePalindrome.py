"""
1616. Split Two Strings to Make Palindrome


You are given two strings a and b of the same length. Choose an index and split both strings at the same index, splitting a into two strings: 
aprefix and asuffix where a = aprefix + asuffix, and splitting b into two strings: bprefix and bsuffix where b = bprefix + bsuffix. Check if aprefix + bsuffix or bprefix + asuffix forms a palindrome.

When you split a string s into sprefix and ssuffix, either ssuffix or sprefix is allowed to be empty. For example, if s = "abc", then "" + "abc", "a" + "bc", "ab" + "c" , and "abc" + "" are valid splits.

Return true if it is possible to form a palindrome string, otherwise return false.

Notice that x + y denotes the concatenation of strings x and y.

 

Example 1:

Input: a = "x", b = "y"
Output: true
Explaination: If either a or b are palindromes the answer is true since you can split in the following way:
aprefix = "", asuffix = "x"
bprefix = "", bsuffix = "y"
Then, aprefix + bsuffix = "" + "y" = "y", which is a palindrome.
Example 2:

Input: a = "abdef", b = "fecab"
Output: true
Example 3:

Input: a = "ulacfd", b = "jizalu"
Output: true
Explaination: Split them at index 3:
aprefix = "ula", asuffix = "cfd"
bprefix = "jiz", bsuffix = "alu"
Then, aprefix + bsuffix = "ula" + "alu" = "ulaalu", which is a palindrome.
Example 4:

Input: a = "xbdef", b = "xecab"
Output: false
 

Constraints:

1 <= a.length, b.length <= 105
a.length == b.length
a and b consist of lowercase English letters
"""


class SplitTwoStringsToPalindrome:

    def doit_(self, a: str, b: str) -> bool:

        def centerpalindrome(target, s):
            s, e = s, len(target) - s - 1
            while s < e and target[s] == target[e]:
                s += 1
                e -= 1

            return s >= e
        
        def prefixpalindrome(s1, s2):
            n, i = len(s2), 0
            while i < n and s1[i] == s2[n-i-1]:
                i += 1
            return i
        
        # get a, b prefix length to match b, a surfix
        aprefix, bprefix = prefixpalindrome(a, b), prefixpalindrome(b, a)
        
        # a suffix + a half / b suffix, a half  / a suffix + b half / b prefix + b half
        return centerpalindrome(a, aprefix) or centerpalindrome(a, bprefix) or centerpalindrome(b, aprefix), centerpalindrome(b, bprefix)

if __name__ == '__main__':

    res = SplitTwoStringsToPalindrome().doit_("xbdef", "xecab")

    SplitTwoStringsToPalindrome().doit_("pvhmupgqeltozftlmfjjde", "yjgpzbezspnnpszebzmhvp")

    SplitTwoStringsToPalindrome().doit_("x", "y")

    SplitTwoStringsToPalindrome().doit_("xbdef", "xecab")

    SplitTwoStringsToPalindrome().doit_("abda", "acmc")
        
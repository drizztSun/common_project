"""
87. Scramble String

We can scramble a string s to get a string t using the following algorithm:

If the length of the string is 1, stop.
If the length of the string is > 1, do the following:

1. Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
2. Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
3. Apply step 1 recursively on each of the two substrings x and y.

Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.



Example 1:

Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at random index.
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at ranom index each of them.
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
The algorithm stops now and the result string is "rgeat" which is s2.
As there is one possible scenario that led s1 to be scrambled to s2, we return true.
Example 2:

Input: s1 = "abcde", s2 = "caebd"
Output: false
Example 3:

Input: s1 = "a", s2 = "a"
Output: true


Constraints:

s1.length == s2.length
1 <= s1.length <= 30
s1 and s2 consist of lower-case English letters.
"""


class isScramble(object):
    def doit(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        if s1 == s2:
            return True

        length = len(s1)
        pattern = [0 for x in range(127)]
        
        for j in range(len(s1)):
            pattern[ord(s1[j])] += 1
            pattern[ord(s2[j])] -= 1

        for c in pattern:
            if c != 0:
                return False 

        for i in range(1, length):
            if self.doit(s1[0:i], s2[0:i]) and self.doit(s1[i:], s2[i:]):
                return True
            
            if self.doit(s1[0:i], s2[length-i:]) and self.doit(s1[i:], s2[0: length-i]):
                return True
    
        return False

    # best one 
    def doit2(self, x, y):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """

        def search(s1, s2):

            if len(s1) != len(s2):
                return False

            if s1 == s2:
                return True

            if len(s1) == 1:
                return s1 == s2

            d, d1, d2 = {}, {}, {}

            for i, s in enumerate(s1[:-1], 1):

                d[s] = d.get(s, 0) + 1

                d1[s2[i - 1]] = d1.get(s2[i - 1], 0) + 1

                d2[s2[-i]] = d2.get(s2[-i], 0) + 1

                # two Counter should be same, before verify next level.
                if d == d1 and search(s1[:i], s2[:i]) and search(s1[i:], s2[i:]):
                    return True

                if d == d2 and search(s1[:i], s2[-i:]) and search(s1[i:], s2[:len(s2) - i]):
                    return True

            return False

        return search(x, y)


if __name__=="__main__":
    
    res = isScramble().doit2("great", "rgeat")

    res = isScramble().doit2("aa", "aa")
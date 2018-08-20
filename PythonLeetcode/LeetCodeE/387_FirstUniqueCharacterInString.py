


# 387. First Unique Character in a String

# Given a string, find the first non-repeating character in it and return it's index.
# If it doesn't exist, return -1.

# Examples:

# s = "leetcode"
# return 0.

# s = "loveleetcode",
# return 2.


class firstUniqChar(object):

    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        ps = {}
        
        for c in s:
            ps[c] = ps.get(c, 0) + 1

        A = set([c for c in ps.keys() if ps[c] == 1])

        for i, c in enumerate(s):
            if c in A:
                return i

        return -1


    def doit1(self, s):
        """
        :type s: str
        :rtype: int
        """
        letters = 'abcdefghijklmnopqrstuvwsyz'
        index = [s.index(c) for c in letters if s.count(c) == 1]
        return min(index) if index else -1

if __name__=="__main__":


    res = firstUniqChar().doit("leetcode")
                
    res = firstUniqChar().doit("loveleetcode")

    pass

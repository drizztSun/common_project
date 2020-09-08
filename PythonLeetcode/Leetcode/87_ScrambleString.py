"""
# 87. Scramble String

    #Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
    #Below is one possible representation of s1 = "great":
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

    pass



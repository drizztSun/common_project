



# 383. Ransom Note

# Given an arbitrary ransom note string and another string containing letters from all the magazines,
# write a function that will return true if the ransom note can be constructed from the magazines ;
# otherwise, it will return false.

# Each letter in the magazine string can only be used once in your ransom note.

# Note:
# You may assume that both strings contain only lowercase letters.

# canConstruct("a", "b") -> false
# canConstruct("aa", "ab") -> false
# canConstruct("aa", "aab") -> true

import collections

class canConstruct(object):
    def doit2(self, ransomNote, magazine):
        """
        :type ransomNote: str
        :type magazine: str
        :rtype: bool
        """
        rd = {}

        for c in ransomNote:
            rd[c] = rd.get(c, 0) + 1

        for c in magazine:
            if c in rd:
                rd[c] -= 1

        for c in rd.keys():
            if rd[c] > 0:
                return False
        
        return True


    def doit1(self, ransomNote, magazine):
        """
        :type ransomNote: str
        :type magazine: str
        :rtype: bool
        """
        letters = set(ransomNote)

        for i in letters:
            if ransomNote.count(i) > magazine.count(i):
                return False

        return True


    def doit(self, ransomNote, magazine):
        """
        :type ransomNote: str
        :type magazine: str
        :rtype: bool
        """
        return not collections.Counter(ransomNote) - collections.Counter(magazine)        
        


if __name__=="__main__":


    res = canConstruct().doit('a', 'b') # false

    res = canConstruct().doit('aa', 'ab')  # false

    res = canConstruct().doit('aa', 'aab') # true

    pass
        
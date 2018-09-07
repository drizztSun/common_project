# 567. Permutation in String


# Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1.
# In other words, one of the first string's permutations is the substring of the second string.
# Example 1:
# Input:s1 = "ab" s2 = "eidbaooo"
# Output:True
# Explanation: s2 contains one permutation of s1 ("ba").

# Example 2:
# Input:s1= "ab" s2 = "eidboaoo"
# Output: False
# Note:
# The input strings only contain lower case letters.
# The length of both given strings is in range [1, 10,000].



class PermutationInString:


    def doit(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        n1, n2 = len(s1), len(s2)
        
        if n1 > n2:
            return False
        
        m1, m2 = {}, {}
        for c in s1:
            m1[c] = m1.get(c, 0) + 1
        
        for c in s2[:n1]:
            m2[c] = m2.get(c, 0) + 1
            

        
        for i in range(n2 - n1):

            if m1 == m2:
                return True

            m2[s2[i]] -= 1
            if m2[s2[i]] == 0:
                del m2[s2[i]]
            
            m2[s2[i + n1]] = m2.get(s2[i + n1], 0) + 1
            
            
        return m1 == m2

        




    def permutaions(iterable):

        pool = tuple(iterable)
        length = len(pool)

        for indices in product(range(length)):
            if len(set(indices)) == length:
                yield tuple(pool[i] for i in indices)


    def doit1(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        from itertools import permutations
        charList = set(s1)
        length = len(s1)
        permutationsList = set(''.join(c) for c in permutations(s1))

        for i in range(len(s2)):

            if s2[i] in charList and i + length <= len(s2) and s2[i : i + length] in permutationsList:
                return True

        return False
        



if __name__ == "__main__":

    res = PermutationInString().doit(s1 = "ab", s2 = "eidbaooo")

    res = PermutationInString().doit("adc", "dcda")

    res = PermutationInString().doit("abcdxabcde", "abcdeabcdx")

    res = False

        


import os
import collections

# leetcode 115. Distinct Subsequences
# Given a string S and a string T, count the number of distinct subsequences of S which equals T.
# A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of 
# the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
# Here is an example:
# S = "rabbbit", T = "rabbit"
# Return 3.


class numDistinct(object):

    def doit2(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """

        if len(s) < len(t):
            return 0
        
        diff, m, n = len(s) - len(t), len(s), len(t)
        D = [1 for _ in range(m+1)]
                
        for i in range(1, n+1):
            D[0], lastD = 0, D[:]
            for j in range(1, m+1):
                 if t[i-1] == s[j-1]:
                    D[j] = D[j-1] + lastD[j-1]
                 else:
                    D[j] = D[j-1]

        return D[m]
    

    def doit1(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """
        A = set()
        for i in t:
            A.add(i)
            
        indexes = collections.defaultdict(list)
        for j in range(len(s)):
            if s[j] in A:
                indexes[s[j]].append(j)
            
        mydict = {}
        
        def search(s1, t1) :
            if t1 == len(t):
                return 1
            
            if s1 == len(s):
                return 0
            
            way, tup = 0, (s1, t1)
            if tup in mydict:
                return mydict[tup]
            
            for index in indexes[t[t1]]:
                if index >= s1:
                    way += search(index+1, t1+1)
                    
            mydict[tup] = way
            return way
        
        return search(0, 0)

    def doit(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """
        if len(s) < len(t):
            return 0

        diff = len(s) - len(t)
        
        def search(src, s, target, t, res, n):

            if t == len(target):
                return 1

            if s == len(src) or n < 0:
                return 0

            if (s, t) in res:
                return res[(s, t)]

            ret = 0
            if src[s] == target[t]:
                ret += search(src, s + 1, target, t + 1 , res, n)
            
            for i in range(1, n+1):
                ret += search(src, s + i, target, t, res, n - i) 
               
            res[(s, t)] = ret
            return ret

        return search(s, 0, t, 0, {}, diff)        
        



if __name__=="__main__":

    res = numDistinct().doit("bbb", "bb") # 3

    res = numDistinct().doit("ccc", "c") # 3
    
    res = numDistinct().doit("rabbbit", "rabbit") # 3


    pass
"""
 115. Distinct Subsequences

Given a string S and a string T, count the number of distinct subsequences of S which equals T.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing 
the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

It's guaranteed the answer fits on a 32-bit signed integer.

Example 1:

Input: S = "rabbbit", T = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
(The caret symbol ^ means the chosen letters)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^

Example 2:

Input: S = "babgbag", T = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
(The caret symbol ^ means the chosen letters)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^
"""
import collections


class NumDistinct:

    def doit_recursive(self, s: str, t: str) -> int:
        """
        :type s: str
        :type t: str
        :rtype: int

        Please look at Longest Common Subsequence for an idea of how to think about these subproblems.

        If you take a look at the given example, "rabbbit" and "rabbit," notice how you can use any ordering of the 'b's in the middle to obtain "rabbit."
        This indicates that even when we find a matching character in our subsequence, we can't just stop there. We have to search the rest of the string,
        excluding the matching character just found.

        So, when we find s[i] == t[j], where i is our current index in s and j the current index in t, the answer is not just distinct(i+1, j+1).
        It is also distinct(i+1, j) -- (this is skipping the current index in i and finding the next character that matches j in t).
        Whenever s[i] != t[j], we just defer the problem to distinct(i+1, j). We memoize each answer as we go along.

        O(mn) time and space.
        """

        def helper(i, j, memo):
            if (i, j) in memo:
                return memo[(i, j)]

            # base case
            if j == len(t):
                return 1
            if i == len(s):
                return 0

            # if the characters match, we call with both the character in the
            # subsequence and without
            if s[i] == t[j]:
                memo[(i, j)] = helper(i + 1, j + 1, memo) + helper(i + 1, j, memo)
                return memo[(i, j)]
            else:
                memo[(i, j)] = helper(i + 1, j, memo)
                return memo[(i, j)]

        memo = {}
        return helper(0, 0, memo)

    def doit_dp(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int

        After getting the recursive solution, if there's enough time in an interview, the optimal solution really is the iterative version to preserve stack space.
        We take the distinct(i+1, j+1) and distinct(i+1, j) calls and put it into table form. We start at the base case: any case where the string t is empty, is 1.
        Build up from there with the recurrence relation we found.
        """
        if len(s) < len(t):
            return 0
        
        m, n = len(s), len(t)
        D = [1 for _ in range(m+1)] # t = '', s = '..' always has 1 common subsequence.
                
        for i in range(1, n+1):
            D[0], lastD = 0, D[:] # if t = '...' s = '', always has 0 common subsequence.

            for j in range(1, m+1):
                # if we remove current one
                D[j] = D[j-1]
                if t[i-1] == s[j-1]:
                    # if current s[j] == t[i], it also need to add s[0..j-1], t[0..j-1]
                    D[j] += lastD[j-1]
        return D[m]

    def doit_dp_1(self, s: str, t: str) -> int:
        count = [0] * len(t)
        tset = set(t)
        tdict = {}
        for idx, letter in enumerate(t):
            if letter in tdict:
                tdict[letter].append(idx)
            else:
                tdict[letter] = [idx]

        for letter in s:
            if letter in tset:
                idxs = tdict[letter]
                for idx in reversed(idxs):
                    if idx == 0:
                        count[0] += 1
                    else:
                        count[idx] += count[idx - 1]
        return count[-1]

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

    res = NumDistinct().doit("bbb", "bb") # 3

    res = NumDistinct().doit("ccc", "c") # 3
    
    res = NumDistinct().doit("rabbbit", "rabbit") # 3



# 730. Count Different Palindromic Subsequences

# Given a string S, find the number of different non-empty palindromic subsequences in S, and return that number modulo 10^9 + 7.

# A subsequence of a string S is obtained by deleting 0 or more characters from S.

# A sequence is palindromic if it is equal to the sequence reversed.

# Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.

# Example 1:
# Input: 
# S = 'bccb'
# Output: 6
# Explanation: 
# The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
# Note that 'bcb' is counted only once, even though it occurs twice.

# Example 2:
# Input: 
# S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
# Output: 104860361
# Explanation: 
# There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.

# Note:

# The length of S will be in the range [1, 1000].
# Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.



class CountPalindromicSubsequences:



# I started out with only the DFS part, got TLE, then designed the DP part cache and passed.

# The computations are done in DFS(start, end) in which I computed the answer for the string S[start, end].
# cache is only to save the results of the computations in order to avoid repetitions.

# In DFS(start, end), for instance, for the letter 'a',
# I compute the number of palindromes that start and end with 'a' in the following way:

# First of all, I compute when 'a' appears first (index i) and last (index j) in the segment I am considering.
# Then it breaks down into two cases:

# If i == j. There is only one 'a' in the segment. So the answer is 1.

# If i != j. The possible palindromes are 'a', 'aa', and 'a*a' where '*' stands for any palindromes contained in S[i+1:j].
# The answer would be DFS(i+1,j) + 2. Since I want to avoid repetitive computation, I write cache(i+1,j) + 2 instead.

# The worst case time complexity is O(n^2). The best case time complexity is O(n).

# Btw, to make this algorithm even faster, one could set check to be a 2D list instead of a dictionary,
# but that would occupy more space.

    def doit(self, S):
        """
        :type S: str
        :rtype: int
        """
        dp = {}

        # return the amount of distinct palindromes of S[start:end]
        def search(start, end):

            if (start, end) in dp:
                return dp[(start, end)]

            # if less then two, 'bb', 'bc' are two elements
            if end <= start + 2:
                return end - start

            count = 0
            for c in ['a', 'b', 'c', 'd']:

                # s, e = S.index(c, start, end), S.rindex(c, start, end)
                s, e = S.find(c, start, end), S.rfind(c, start, end)

                if s == -1 or e == -1:
                    continue

                # could be 'a' 'aa' and searched 'a*a'
                count += search(s+1, e) + 2 if s != e else 1

            dp[(start, end)] = count % 1000000007

            return dp[(start, end)]
            
        return search(0, len(S))      


    def doit1(self, S):
        """
        :type S: str
        :rtype: int
        """
        result = set()
        d = set()
        
        def search(content, prefix, suffix,  result):

            if content in d:
                return 
            if not content:
                return 

            for i in set(content):
                s, e = content.find(i), content.rfind(i)
                result.add( prefix + i + suffix)
                if s != e:
                    result.add( prefix + i + i + suffix)
                    search(content[s+1: e], prefix+i, i+suffix, result)
            d.add(content)
            return 
                    
        search(S, '', '', result)
        return len(result)
        



if __name__ == "__main__":



    res = CountPalindromicSubsequences().doit('bccb')


    res = CountPalindromicSubsequences().doit('abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba')



    pass
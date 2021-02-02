"""
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
"""

class RepeatedSubstringPattern:

    def doit(self, s):
        """
        :type s: str
        :rtype: bool
        """
        for L in range(1, len(s) // 2 + 1):

            if len(s) % L  != 0:
                continue
 
            sub, j = s[:L], L
            while j < len(s):
                if sub != s[j: j + L]:
                    break
                j += L

            if j == len(s):
                return True

        return False

    """
        Approach 4: Knuth-Morris-Pratt Algorithm (KMP)
        Lookup Table

        Rabin-Karp is the best fit for the multiple pattern search, whereas KMP is typically used for the single pattern search.

        The key to KMP is the partial match table, often called lookup table, or failure function table. It stores the length of the longest prefix that is also a suffix.

        Here are two examples

        a b c a b c a
        0 0 0 1 2 3 4

        "ab"   -- No common prefix/surfix
        "abc"   -- No common prefix/surfix
        "abca"  -- Length of common prefix/surfix "a" = 1
        "abcab" -- Length of common prefix/surfix "ab" = 2
        "abcabc" -- Length of common prefix/surfix "abc" = 3
        "abcabca" -- Length of common prefix/surfix "abca" = 4

        a b a b b a
        0 0 1 2 0 1

        "ab" -- No common prefix/surfix
        "aba" -- Length of common prefix/surfix "a" = 1
        "abab" -- Length of common prefix/surfix "ab" = 2
        "ababb" -- No common prefix/surfix
        "ababba" -- Length of common prefix/surfix "a" = 1
        
        How to Get an Answer

        Once we have a lookup table, we know the length l of common prefix/suffix for the input string: l = dp[n - 1].

        That means that n - l should the length of the repeated sequence. To confirm that, one should verify if n - l is a divisor of n.

        (a b c (a b c a b c) a b c) -- Length of common prefix/surfix "ab" = 9

        (n-l) = 3 should be the length of repeated pattern

        (a b c) a b c a b c (a b c)

        How to check: n % (n-l) == 0 --> True --> It's a repeated pattern string


        a b a b b a => The longest common prefix/suffix length l = 1    
        
        n - l = 5 should be the length of repeated pattern

        (a b a b b) a

        How to check: n % (n-l) == 0 --> False --> It is not a reapted pattern string

        Algorithm

        Construct lookup table:

        dp[0] = 0 since one character is not enough to speak about proper prefix / suffix.

        Iterate over i from 1 to n:

        Introduce the second pointer j = dp[i - 1].

        While j > 0 and there is no match s[i] != s[j], do one step back to consider a shorter prefix: j = dp[j - 1].

        If we found a match s[i] == s[j], move forward: j += 1

        Write down the length of common prefix / suffix: dp[i] = j.

        Now we have a length of common prefix / suffix for the entire string: l = dp[n - 1].

        The string is a repeated pattern string if this length is nonzero and n - l is a divisor of n. Return l != 0 and n % (n - l) == 0.

        Implementation


        Complexity Analysis

        Time complexity: O(N). During the execution, j could be decreased at most NN times and then increased at most NN times, that makes overall execution time to be linear O(N).

        Space complexity: O(N) to keep the lookup table.
    """
    def doit_KMP(self, s: str) -> bool:        
        n = len(s)
        dp = [0] * n
        # Construct partial match table (lookup table).
        # It stores the length of the proper prefix that is also a proper suffix.
        # ex. ababa --> [0, 0, 1, 2, 1]
        # ab --> the length of common prefix / suffix = 0
        # aba --> the length of common prefix / suffix = 1
        # abab --> the length of common prefix / suffix = 2
        # ababa --> the length of common prefix / suffix = 1
        for i in range(1, n):
            j = dp[i - 1]
            while j > 0 and s[i] != s[j]:
                j = dp[j - 1]
            if s[i] == s[j]:
                j += 1
            dp[i] = j

        l = dp[n - 1]
        # check if it's repeated pattern string
        return l != 0 and n % (n - l) == 0
    

    """
        Approach 2: Concatenation

        Repeated pattern string looks like PatternPattern, and the others like Pattern1Pattern2.

        Let's double the input string:

        PatternPattern --> PatternPatternPatternPattern

        Pattern1Pattern2 --> Pattern1Pattern2Pattern1Pattern2

        Now let's cut the first and the last characters in the doubled string:

        PatternPattern --> *atternPatternPatternPatter*

        Pattern1Pattern2 --> *attern1Pattern2Pattern1Pattern*

        It's quite evident that if the new string contains the input string, the input string is a repeated pattern string.

        Implementation


        Complexity Analysis

        Time complexity: (N^2) because of the way in and contains are implemented.

        Space complexity: O(N), the space is implicitly used to keep s + s string.
    """
    def doit_(self, s: str) -> bool:
        return s in (s + s)[1: -1]

    def doit1(self, s):
        """
        :type s: str
        :rtype: bool
        """
        return (s + s)[1: -1].find(s) != -1

    """
        Approach 3: Find Divisors + Rabin-Karp
        Rabin-Karp

        Rabin-Karp is a linear-time O(N) string searching algorithm:

        Move a sliding window of length L along the string of length N.

        Check hash of the string in the sliding window.

        rabin_karp

        In some situations, one has to implement a particular hash algorithm to fit in a linear time, for example, we used rolling hash algorithm for the problem Longest Duplicate Substring.

        For the current problem the standard hash / hashCode is enough because the idea is to check only lengths L, which are divisors of N. This way we're not sliding, we're jumping:

        . the first string is 0..L

        . the second string is L..2L

        ...

        . the last string is N - L..N

        To copy characters in sliding window takes time L, to compute hash - time L as well. In total, there are N / L substrings, that makes it all work in a linear time \mathcal{O}(N)O(N).

        Find divisors

        Now the only problem is to find divisors of N. Let's iterate to the square root of N, and for each identified divisor i calculate the paired divisor N / i.

        Algorithm

        Deal with base cases: n <= 2.

        Iterate from \sqrt{n} 
        n
        ​	
        to 1.

        For each divisor n % i == 0:

        Compute paired divisor n / i.

        Use Rabin-Karp to check substrings of the lengths l = i and l = n / i:

        Take as a reference hash first_hash the hash of the first substring of length l.

        Jump along the string with a step of length l while the hash of the current substring is equal to first_hash.

        If the hashes of all substrings along the way are equal, the input string consists of repeated patterns of length l. Return True.

        Side note. The good practice is to verify the equality of two substrings after the hash match. This logic is not hard to add, and it could bring you kudos during the interview.

        Implementation


        Complexity Analysis

        Time complexity: up to \mathcal{O}(N \sqrt{N})O(N 
        N
        ​	
        ). \mathcal{O}(\sqrt{N})O( 
        N
        ​	
        ) to compute all divisors and \mathcal{O}(N)O(N) for each divisor "verification". That's an upper-bound estimation because divisor function grows slower than \sqrt{N} 
        N
        ​	
        .

        Space complexity: up to \mathcal{O}(\sqrt{N})O( 
        N
        ​	
        ) to keep a copy of each substring during the hash computation.
    """
    def doit_rollinghash(self, s: str) -> bool:        
        n = len(s)
        if n < 2:
            return False
        if n == 2:
            return s[0] == s[1]
            
        for i in range(int(n**0.5), 0, -1):
            if n % i == 0:
                divisors = [i]
                if i != 1:
                    divisors.append(n // i)

                for l in divisors:
                    first_hash = curr_hash = hash(s[:l])
                    start = l
                    
                    while start != n and curr_hash == first_hash:
                        curr_hash = hash(s[start:start + l])
                        start += l
                    
                    if start == n and curr_hash == first_hash:
                        return True
                
        return False

if __name__ == "__main__":

    res = RepeatedSubstringPattern().doit('abab')

    res = RepeatedSubstringPattern().doit("aba")

    res = RepeatedSubstringPattern().doit("abcabcabcabc")       
        

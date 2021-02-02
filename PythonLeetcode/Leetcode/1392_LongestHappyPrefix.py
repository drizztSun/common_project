"""
1392. Longest Happy Prefix

A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).

Given a string s. Return the longest happy prefix of s .

Return an empty string if no such prefix exists.

 

Example 1:

Input: s = "level"
Output: "l"
Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
Example 2:

Input: s = "ababab"
Output: "abab"
Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.
Example 3:

Input: s = "leetcodeleet"
Output: "leet"
Example 4:

Input: s = "a"
Output: ""
 

Constraints:

1 <= s.length <= 10^5
s contains only lowercase English letters.


"""


class LongestHappyPrefix:

    def doit_dp_suffix_KMP(self, s: str) -> str:
        
        dp = [0 for _ in range(len(s))]
        
        for i in range(1, len(s)):
            
            j = dp[i-1]
            
            while j > 0 and s[j] != s[i]:
                j = dp[j-1]
            
            dp[i] = j + (s[i] == s[j])
            
        return s[:dp[-1]]


    def doit_rollinghash(self, s: str) -> str:

        """
        :type s: str
        :rtype: str
        """
        # We use a rolling hash here with a prefix sums to check the prefix and suffix when the hashes collide
        # Rabin Karp in Python
        
        if not s: return ""
        
        n, prefix_hash, suffix_hash, prime = len(s), 0, 0, 10 ** 9 + 7
		
		# Need this multipler to not TLE on large strings
        multiplier = 1
        
        check_indices = []
        
        # Step 1. Calculate a rolling hash from front - call it prefix_hash, another hash from back call it suffix_hash
        for index in range(n - 1):
            
            prefix_hash = (26 * prefix_hash + ord(s[index])) % prime
            suffix_hash = (suffix_hash + multiplier * (ord(s[n-index-1]))) % prime
            
            multiplier = (multiplier * 26) % prime
            
            # store indices for which the hashes are the same 
            if prefix_hash == suffix_hash: check_indices.append(index)
        
        
		# Step 2. Check all possible indices and return the substring
        
        ci_len = len(check_indices)
        # Start from reverse so that the largest possible K length substring is returned first
        for index in range(ci_len - 1, -1, -1):
            
            valid_substring = True
            k = check_indices[index] + 1
            
            for i in range(k):
                if s[i] != s[n - k + i]: 
                    valid_substring = False; break
            
            if valid_substring:
                return s[n - k :]
        
        return ""
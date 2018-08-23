# 467. Unique Substrings in Wraparound String

# Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", 
# 
# so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".

# Now we have another string p. Your job is to find out how many unique non-empty substrings of p are present in s. 
# 
# In particular, your input is the string p and you need to output the number of different non-empty substrings of p in the string s.

# Note: p consists of only lowercase English letters and the size of p might be over 10000.

# Example 1:
# Input: "a"
# Output: 1

# Explanation: Only the substring "a" of string "a" is in the string s.

# Example 2:
# Input: "cac"
# Output: 2
# Explanation: There are two substrings "a", "c" of string "cac" in the string s.

# Example 3:
# Input: "zab"
# Output: 6
# Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of string "zab" in the string s.



class FindSubstringInWraproundString(object):


    def doit(self, p):
        """
        :type p: str
        :rtype: int
        """
        c2i = { c:i for i, c in enumerate(string.ascii_lowercase)}
        goes = [0 for _ in range(26)]
        c = 0
        n = len(p)

        while c < n:

            st, end = c2i[p[c]], c + 1

            while end < n and c2i[p[end]] == (c2i[p[end-1]] + 1) % 26:
                end += 1

            org = end
            while 0 <= goes[st] < end - c:
                goes[st], st, end = end - c, (st + 1) % 26, end - 1

            c = org
            
        return sum(goes)        


# DP solution #1: same idea as above using DP to track the ongoing lengths of each substring sequence. 
# Let dp[i] denote the substring sequence length at each ending char s[i]. There are two cases to consider.

# if s[i] is part of a previous sequence ending at s[i-1], then dp[i]=dp[i-1]+1
# s[i] is not part of a previous sequence ending at s[i-1], then dp[i]=1
# Use vector v to store the maximum length dp[i] for each consecutive substring's unique ending value s[i] in buckets from 'a' to 'z' inclusive. 
# Finally add up all the buckets and return that sum.
    def doit1(self, p):
        """
        :type p: str
        :rtype: int
        """
        if not p:
            return 0
        
        c2i = { c:i for i, c in enumerate(string.ascii_lowercase)}
        V = [ 0 for _ in range(26)]
        dp = [1 for _ in range(len(p))]
        V[c2i[p[0]]] = 1

        for i in range(1, len(p)):
            
            if c2i[p[i]] == (c2i[p[i-1]] + 1) % 26:
                dp[i] = dp[i-1] + 1
            else:
                dp[i] = 1
            
            V[c2i[p[i]]] = max(dp[i], V[c2i[p[i]]])

        return sum(V)
    
    

    # TLE
    def doit1(self, p):
        """
        :type p: str
        :rtype: int
        """
        c = set()
        visited = set()
        last = 0

        for i in range(len(p) + 1):

            if i == 0 or (i != len(p) and (ord(p[i-1]) + 1 == ord(p[i]) or p[i-1: i+1] == 'za')):
                continue

            if p[last: i] not in visited:

                for j in range(last, i):
                    for k in range(j+1, i+1):
                        c.add(p[j:k])

                visited.add(p[last:i])

            last = i

        return len(c)
        


if __name__ == "__main__":

    res = FindSubstringInWraproundString().doit("a")

    res = FindSubstringInWraproundString().doit("cac")

    res = FindSubstringInWraproundString().doit("zab")

    res = FindSubstringInWraproundString().doit("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz")

    res = 1
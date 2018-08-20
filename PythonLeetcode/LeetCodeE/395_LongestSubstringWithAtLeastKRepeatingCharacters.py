



# 395. Longest Substring with At Least K Repeating Characters

# Find the length of the longest substring T of a given string (consists of lowercase letters only)
# such that every character in T appears no less than k times.

# Example 1:
# Input:
# s = "aaabb", k = 3
# Output:
# 3

# The longest substring is "aaa", as 'a' is repeated 3 times.

# Example 2:
# Input:
# s = "ababbc", k = 2
# Output:
# 5

# The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.


class longestSubstring(object):
    
    def doit(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        def search(t, k):
            res = 0
            for c in set(t):
                if t.count(c) < k:
                   return max([search(y, k) for y in t.split(c)])

            return len(t)

        return search(s, k)
                


    def doit(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        def search(s, k):
            d = {}
            for c in s:
                d[c] = d.get(c, 0) + 1
        
            for l in d.keys():
                if d[l] < k:
                    return max(map(lambda x: search(x, k), s.split(l)))

            return len(s)

        return search(s, k)                    

        
        
    # For each h, apply two pointer technique to find the longest substring with at least K repeating characters and the number of unique characters in substring is h.
    def doit3(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        code = s.split()
        counts = [ 0 for _ in range(26)]
        h, i, j, idx, maxv = 0, unique, nolessThanK
        
        for h in range(1, 27):

            i, j = 0, 0
            unique = 0
            nolessThanK = 0

            while j < len(s):
                
                if unique <= h:
                    idx = ord(s[j]) - ord('a')
                    if counts[idx] == 0:
                        unique += 1
                    counts[idx] += 1
                    
                    if counts[idx] == k:
                        nolessThanK += 1

                    j += 1

                else : 
                    
                    idx = ord(s[i]) - ord('a')
                    if count[idx] == k:
                        nolessThanK -= 1

                    counts[idx] -= 1

                    if counts[idx] == 0:
                        unique -= 1

                    i += 1

                #
                if unique == h and unique == nolessThanK:
                    maxv = max(j - i, maxv)

        return maxv

                    



        
            
        
        
        


if __name__=="__main__":

    res = longestSubstring().doit("aaabb", 3)
 
    res = longestSubstring().doit("ababbc", 2)

    pass
        



# 424. Longest Repeating Character Replacement

# Given a string that consists of only uppercase English letters, you can replace any letter in the string with another letter at most k times. Find the length of a longest substring containing all repeating letters you can get after performing the above operations.

# Note:
# Both the string's length and k will not exceed 104.

# Example 1:

# Input:
# s = "ABAB", k = 2
# Output:
# 4

# Explanation:
# Replace the two 'A's with two 'B's or vice versa.

# Example 2:

# Input:
# s = "AABABBA", k = 1
# Output:
# 4

# Explanation:
# Replace the one 'A' in the middle with 'B' and form "AABBBBA".
# The substring "BBBB" has the longest repeating letters, which is 4.


import collections

class characterReplacement:

    
   def doit(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
		cnt = defaultdict(int)
		max_freq = 0

		for i in range(len(s)):

			cnt[s[i]] += 1

			if cnt[s[i]] > max_freq:
				max_freq = cnt[s[i]]
			else:
				if i >= max_freq + k:
					cnt[s[i - max_freq - k]] -= 1

		return min(max_freq + k, len(s))


# The problem says that we can make at most k changes to the string (any character can be replaced with any other character). So, let’s say there were no constraints like the k. Given a string convert it to a string with all same characters with minimal changes. The answer to this is
# length of the entire string - number of times of the maximum occurring character in the string
# Given this, we can apply the at most k changes constraint and maintain a sliding window such that
# (length of substring - number of times of the maximum occurring character in the substring) <= k

    def doit(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        begin = 0
        cnt = [ 0 for _ in range(26)]
        maxlen = 0
        for end in range(len(s)):

            n = ord(s[end]) - ord('A')
            cnt[n] += 1

            while end - begin + 1 - max([cnt[i] for i in range(26)]) > k:
                cnt[ord(s[begin]) - ord('A')] -= 1
                begin += 1

            maxlen = max(maxlen, end - start + 1)


        return maxlen       
                    




    def doit(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
		cnt = collections.defaultdict(int)
		max_freq = 0

		for i in range(len(s)):
			cnt[s[i]] += 1

			if cnt[s[i]] > max_freq:

				max_freq = cnt[s[i]]
			else:

				if i >= max_freq + k:
					cnt[s[i - max_freq - k]] -= 1

		return min(max_freq + k, len(s))


    def doit(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        if len(s) <= k:
            return len(s)

        d = collections.defaultdict(list)
        maxLength = 0

        for i, c in enumerate(s):
            d[c].append(i)

            
            rest = d[c][-1] - d[c][0] + 1 - len(d[c]) 
            if rest <= k:
                length = d[c][-1] - d[c][0] + 1 + k - rest
                maxLength = max(maxLength, length)
            else:
                while d[c][-1] - d[c][0] - len(d[c]) + 1 > k:
                    d[c].pop(0)

        return maxLength if maxLength <= len(s) else len(s)


if __name__=="__main__":


    res = characterReplacement().doit("ABAB", 2)

    res = characterReplacement().doit("AABABBA", 1)


    pass
        
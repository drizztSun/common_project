"""
1525. Number of Good Ways to Split a String


You are given a string s, a split is called good if you can split s into 2 non-empty strings p and q where its concatenation is equal to s and the number of distinct letters in p and q are the same.

Return the number of good splits you can make in s.

 

Example 1:

Input: s = "aacaba"
Output: 2
Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.
Example 2:

Input: s = "abcd"
Output: 1
Explanation: Split the string as follows ("ab", "cd").
Example 3:

Input: s = "aaaaa"
Output: 4
Explanation: All possible splits are good.
Example 4:

Input: s = "acbadbaada"
Output: 2
 

Constraints:

s contains only lowercase English letters.
1 <= s.length <= 10^5

"""


class NumberOfGoodWaysToSplit:

    def doit_hashtable(self, s: str) -> int:
        from collections import defaultdict
        
        cnt = defaultdict(int)
        left, right = [], []
        for c in s:
            cnt[c] += 1
            left.append(len(cnt))
            
        cnt = defaultdict(int)
        for c in reversed(s):
            cnt[c] += 1
            right.append(len(cnt))
        
        n, ans = len(s), 0
        for i in range(n-1):
            if left[i] == right[n-i-2]:
                ans += 1
                
        return ans
    
    def doit_hashtable(self, s: str) -> int:

        cnt = set()
        left, right = [], []
        for c in s:
            cnt.add(c)
            left.append(len(cnt))
            
        cnt = set()
        for c in reversed(s):
            cnt.add(c)
            right.append(len(cnt))
        
        n, ans = len(s), 0
        for i in range(n-1):
            if left[i] == right[n-i-2]:
                ans += 1
                
        return ans

    def doit_hashtable(self, s: str) -> int:

        left, total, ans = [0] * 26, [0]*26, 0

        for c in s:
            total[c - ord('a')] += 1

        for c in s:
            left[c - ord('a')] += 1

            L, R = 0, 0

            for i in range(26):
                if left[i]: L += 1
                if total[i] - left[i]: R += 1

            if L == R: ans += 1

            if L > R: break

        return ans
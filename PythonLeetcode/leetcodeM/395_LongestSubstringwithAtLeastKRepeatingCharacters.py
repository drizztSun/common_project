"""
395. Longest Substring with At Least K Repeating Characters


Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.



Example 1:

Input: s = "aaabb", k = 3
Output: 3
Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input: s = "ababbc", k = 2
Output: 5
Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.


Constraints:

1 <= s.length <= 104
s consists of only lowercase English letters.
1 <= k <= 105


"""


class LongestSubstringAtleastKRepeatingChar:

    """
    Approach 3: Sliding Window
    Intuition

    There is another intuitive method to solve the problem by using the Sliding Window Approach. The sliding window slides over the string s and validates each character. Based on certain conditions, the sliding window either expands or shrinks.

    A substring is valid if each character has at least k frequency. The main idea is to find all the valid substrings with a different number of unique characters and track the maximum length. Let's look at the algorithm in detail.

    Algorithm

    Find the number of unique characters in the string s and store the count in variable maxUnique. For s = aabcbacad, the unique characters are a,b,c,d and maxUnique = 4.

    Iterate over the string s with the value of currUnique ranging from 1 to maxUnique. In each iteration, currUnique is the maximum number of unique characters that must be present in the sliding window.

    The sliding window starts at index windowStart and ends at index windowEnd and slides over string s until windowEnd reaches the end of string s. At any given point, we shrink or expand the window to ensure that the number of unique characters is not greater than currUnique.

    If the number of unique character in the sliding window is less than or equal to currUnique, expand the window from the right by adding a character to the end of the window given by windowEnd

    Otherwise, shrink the window from the left by removing a character from the start of the window given by windowStart.

    Keep track of the number of unique characters in the current sliding window having at least k frequency given by countAtLeastK. Update the result if all the characters in the window have at least k frequency.

    """
    def doit_sliding_window(self, s: str, k: int) -> int:
        from collections import defaultdict
        maxCnt = len(set(s))
        res = 0

        for uniqueCnt in range(1, maxCnt + 1):

            cnt = defaultdict(int)
            cntK, unique, i, j = 0, 0, 0, 0

            while j < len(s):

                if unique <= uniqueCnt:
                    cnt[s[j]] += 1
                    if cnt[s[j]] == 1:
                        unique += 1
                    if cnt[s[j]] == k:
                        cntK += 1
                    j += 1
                else:
                    cnt[s[i]] -= 1

                    if cnt[s[i]] == k - 1:
                        cntK -= 1

                    if cnt[s[i]] == 0:
                        unique -= 1
                        del cnt[s[i]]

                    i += 1

                if unique == uniqueCnt and cntK == len(cnt):
                    res = max(res, j - i)

        return res

    def doit_(self, s: str, k: int) -> int:
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

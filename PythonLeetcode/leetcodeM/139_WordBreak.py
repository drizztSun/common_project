"""
139. Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false

"""


class WordBreak:

    def doit_dp(self, s: str, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
        """
        DP = [False] * len(s)

        for i in range(len(s)):
            for w in wordDict:
                if w == s[i - len(w) + 1: i + 1] and (DP[i - len(w)] or i - len(w) == -1):
                    DP[i] = True

        return DP[-1]

    def doit_dp_1(self, s: str, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
        """
        wordset = set(wordDict)
        words = [0]

        for i in range(len(s)):
            for j in reversed(words):
                if s[j:i+1] in wordset:
                    words.append(i+1)
                    if i == len(s) - 1:
                        return True
                    break
        return False

    class Trie(object):

        def __init__(self):
            self.root = {'*': '*'}

            """
            Initialize your data structure here.
            """

        def insert(self, word):
            """
            Inserts a word into the trie.
            :type word: str
            :rtype: None
            """
            current = self.root

            for c in word:

                if c not in current:
                    current[c] = {}

                current = current[c]

            current['*'] = '*'

        def search_word(self, word):

            current = self.root

            for c in word:

                if c not in current:
                    return False

                current = current[c]
            if '*' in current:
                return True

            else:
                return False

    def wordBreak(self, s: str, wordDict) -> bool:
        trie = WordBreak.Trie()

        for w in wordDict:
            trie.insert(w)

        dp = [False for i in range(len(s) + 1)]
        dp[0] = True

        for i in range(1, len(s) + 1):
            for j in range(i):

                if dp[j] and trie.search_word(s[j:i]):
                    dp[i] = True
                    break

        return dp[-1]
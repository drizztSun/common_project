"""
# 472. Concatenated Words

# Given a list of words (without duplicates),
# please write a program that returns all concatenated words in the given list of words.
# A concatenated word is defined as a string that is comprised
# entirely of at least two shorter words in the given array.

# Example:
# Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

# Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

# Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
# "dogcatsdog" can be concatenated by "dog", "cats" and "dog";
# "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
# Note:
# The number of elements of the given array will not exceed 10,000
# The length sum of elements in the given array will not exceed 600,000.
# All the input string will only include lower case letters.
# The returned elements order does not matter.
"""


class FindAllConcatenatedWordsInADict:

    def doit_dp(self, words):
        """
        : type list[str]:
        """
        wordset = set(words)
        res = []

        for w in words:

            dp = [0 for _ in range(len(w)+1)]
            dp[0] = 1

            for i in range(len(w)):
                if dp[i] == 0:
                    continue

                for j in range(i+1, len(w)):

                    if w[i:j] in wordset:
                        dp[j] = 1

                if dp[-1] == 1:
                    res.append(w)
                    break
        return res


    # <dfs>
    def doit_dfs(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        ans = []
        words_map = set(words)

        def help(w, cur, length):
            if cur == len(w):
                return length > 1

            for i in range(cur + 1, len(w)+1):
                if w[cur:i] in words_map and help(w, i, length+1):
                    return True
            return False

        for w in words:
            if help(w, 0, 0):
                ans.append(w)
        return ans

    def doit_dp_dfs_1(self, words):

        if words == [] or words == ['']:
            return []

        wordDict = set(words)
        min_len = min(len(w) for w in words if w != '')

        def helper(s, num):
            if s in wordDict and num > 0:
                return True
            for j in range(min_len, len(s) + 1 - min_len):
                if s[:j] in wordDict and helper(s[j:], num + 1):
                    return True
            return False

        return [w for w in words if len(w) >= 2 * min_len and helper(w, 0)]

    def doit_dp_dfs(self, words):
        """
        : type list[str]:
        """
        def search(w):
            if w in wordsMap:
                return True

            for i in range(len(w), 0, -1):
                if w[:i] in wordsMap and search(w[i:]):
                    return True
            return False

        wordsMap = set(words)
        ans = []

        for w in wordsMap:
            wordsMap.remove(w)
            if search(w):
                ans.append(w)
            wordsMap.add(w)
        return ans
        

if __name__ == "__main__":

    res = FindAllConcatenatedWordsInADict().doit(["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"])
# 1048. Longest String Chain

# Given a list of words, each word consists of English lowercase letters.

# Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.
# For example, "abc" is a predecessor of "abac".

# A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1,
# where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.

# Return the longest possible length of a word chain with words chosen from the given list of words.


# Example 1:

# Input: ["a","b","ba","bca","bda","bdca"]
# Output: 4
# Explanation: one of the longest word chain is "a","ba","bda","bdca".


# Note:

# 1 <= words.length <= 1000
# 1 <= words[i].length <= 16
# words[i] only consists of English lowercase letters.


class LongestStrChain:

    def doit(self, words):
        import collections
        wordslen = collections.defaultdict(set)  # set is faster for a search
        wordsflag = dict()

        for word in words:
            wordslen[len(word)].add(word)  # map length of words to words
            wordsflag[word] = 0  # map each word to a flag

        m = len(wordslen.keys())  # upper limit for max possible chain length
        n = min(wordslen.keys())  # min word length

        # chain = []
        self.maxlen = 0  # current max chain length

        def search(word, l):
            # Depth first search + recursion
            # chain.append(word)
            wordsflag[word] = 1

            if l > self.maxlen:
                self.maxlen = l

            for j in range(len(word)):
                wordNext = word[:j] + word[j+1:]
                if wordNext in wordslen[len(word)-1]:
                    if not wordsflag[wordNext]:
                        search(wordNext, l+1)
            # chain.pop()

        for i in sorted(wordslen.keys(), reverse=True):  # search from the longest to the shortest words
            for word in wordslen[i]:
                if self.maxlen == m:
                    return m
                elif len(word)-n+1 <= self.maxlen or wordsflag[word]:
                    continue
                else:
                    search(word, 1)

        return self.maxlen

    """
    First we want to sort the array in word length, because our dp approach relies on the shorter words come first so that we can determine if current word has a parent or not.
    Since each word is distinct, we can make the array into a set to improve lookup time.
    We run a for loop on the word length to find all possible combinations of the word's parents and check if the parent is in the set.
    If found, we can just take the maximum of all parents' length and then plus 1.
    If not found, we assign 1 to it to indicate it can only be the start of the word chain.
    """

    def doit(self, words):

        words.sort(key=lambda x: len(x))
        wordsSet = set(words)
        dp = {}
        ans = 0
        for w in words:
            dp[w] = 1
            for j in range(len(w)):
                parent = w[:j] + w[j+1:]

                if parent in wordsSet:
                    dp[w] = max(dp[w], dp[parent] + 1)
            ans = max(ans, dp[w])
        return ans

    def doit(self, words):

        from collections import defaultdict
        from functools import lru_cache

        wordslen = defaultdict(set)
        for word in words:
            wordslen[len(word)].add(word)

        @lru_cache
        def get_chain_len(word):

            if len(word) == 1:
                return 1 if word in wordslen[1] else 0

            ans = 1
            for i in range(len(word)):

                parent = word[:i] + word[i+1:]
                if parent in wordslen[len(parent)]:
                    ans = max(ans, get_chain_len(parent) + 1)

            return ans

        return max(get_chain_len(word) for word in words)


if __name__ == '__main__':

    res = LongestStrChain().doit(["a", "b", "ba", "bca", "bda", "bdca"])

    res = LongestStrChain().doit(["ksqvsyq", "ks", "kss", "czvh", "zczpzvdhx", "zczpzvh", "zczpzvhx", "zcpzvh", "zczvh",
                                  "gr", "grukmj", "ksqvsq", "gruj", "kssq", "ksqsq", "grukkmj", "grukj", "zczpzfvdhx", "gru"])

    pass

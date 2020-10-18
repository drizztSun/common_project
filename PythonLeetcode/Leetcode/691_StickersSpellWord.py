"""
# 691. Stickers to Spell Word

# We are given N different types of stickers. Each sticker has a lowercase English word on it.
# You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them.
# You can use each sticker more than once if you want, and you have infinite quantities of each sticker.

# What is the minimum number of stickers that you need to spell out the target? If the task is impossible, return -1.

# Example 1:

# Input:

# ["with", "example", "science"], "thehat"
# Output:

# 3
# Explanation:

# We can use 2 "with" stickers, and 1 "example" sticker.
# After cutting and rearrange the letters of those stickers, we can form the target "thehat".
# Also, this is the minimum number of stickers necessary to form the target string.

# Example 2:

# Input:

# ["notice", "possible"], "basicbasic"
# Output:

# -1

# Explanation:
# We can't form the target "basicbasic" from cutting letters from the given stickers.

# Note:

# stickers has length in the range [1, 50].
# stickers consists of lowercase English words (without apostrophes).
# target has length in the range [1, 15], and consists of lowercase English letters.
# In all test cases, all words were chosen randomly from the 1000 most common US English words,
# and the target was chosen as a concatenation of two random words.
# The time limit may be more challenging than usual.
# It is expected that a 50 sticker test case can be solved within 35ms on average.
"""
import collections


class MinStickers:

    def doit_dfs(self, stickers, target):
        """
        :type stickers: List[str]
        :type target: str
        :rtype: int
        """
        alphaM = collections.Counter(target)
        res = [float('inf')]

        def dfs(_m, c, p):
            if p == len(target):
                res[0] = min(res[0], c)
                return

            if _m[target[p]] >= alphaM[target[p]]:
                dfs(_m, c, p + 1)
                return

            # Here is  {ret[0]-1} not {ret[0]} because of the next loop {c} will add 1
            if c >= res[0] - 1:
                return

            for sticker in stickers:
                if target[p] in sticker:
                    for n in sticker:
                        _m[n] += 1

                    dfs(_m, c + 1, p + 1)

                    for n in sticker:
                        _m[n] -= 1

        dfs(collections.defaultdict(int), 0, 0)

        return -1 if res[0] == float('inf') else res[0]

    def doit_dp(self, stickers, target):

        t_count = collections.Counter(target)
        A = [collections.Counter(sticker) & t_count
             for sticker in stickers]

        for i in range(len(A) - 1, -1, -1):
            if any(A[i] == A[i] & A[j] for j in range(len(A)) if i != j):
                A.pop(i)

        stickers = ["".join(s_count.elements()) for s_count in A]
        dp = [-1] * (1 << len(target))
        dp[0] = 0
        for state in range(1 << len(target)):
            if dp[state] == -1: continue
            for sticker in stickers:
                now = state
                for letter in sticker:
                    for i, c in enumerate(target):
                        if (now >> i) & 1: continue
                        if c == letter:
                            now |= 1 << i
                            break
                if dp[now] == -1 or dp[now] > dp[state] + 1:
                    dp[now] = dp[state] + 1

        return dp[-1]



if __name__ == "__main__":

    res = MinStickers().doit(["with", "example", "science"], "thehat")

    res = MinStickers().doit(["notice", "possible"], "basicbasic")

    pass

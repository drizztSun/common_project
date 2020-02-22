# 1002. Find Common Characters
#
# Given an array A of strings made only from lowercase letters,
# return a list of all characters that show up in all strings within the list (including duplicates).
# For example, if a character occurs 3 times in all strings but not 4 times,
# you need to include that character three times in the final answer.

# You may return the answer in any order.


# Example 1:

# Input: ["bella","label","roller"]
# Output: ["e","l","l"]

# Example 2:

# Input: ["cool","lock","cook"]
# Output: ["c","o"]


# Note:

# 1 <= A.length <= 100
# 1 <= A[i].length <= 100
# A[i][j] is a lowercase letter

from collections import Counter


class CommonChars:
    def doit(self, A):

        ans = Counter(A[0])
        for word in A[1:]:

            cnt = Counter(word)

            keys = set()
            for c in ans.keys():
                if c in cnt:
                    keys.add(c)
            for c in cnt.keys():
                if c in ans:
                    keys.add(c)

            ans = {k: min(ans[k], cnt[k]) for k in keys}

        res = []
        for k, v in ans.items():
            res.extend([k] * v)

        return res

    def doit1(self, A):

        from collections import Counter

        ans = Counter(A[0])

        for w in A[1:]:

            ans = ans & Counter(w)

        return list(ans.elements())


if __name__ == '__main__':

    res = CommonChars().doit(["bella", "label", "roller"])

    res = CommonChars().doit(["acabcddd", "bcbdbcbd", "baddbadb",
                              "cbdddcac", "aacbcccd", "ccccddda", "cababaab", "addcaccd"])

    pass

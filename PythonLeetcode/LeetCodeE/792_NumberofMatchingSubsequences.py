# 792. Number of Matching Subsequences

# Given string S and a dictionary of words words, find the number of words[i] that is a subsequence of S.

# Example :
# Input:
# S = "abcde"
# words = ["a", "bb", "acd", "ace"]
# Output: 3
# Explanation: There are three words in words that are a subsequence of S: "a", "acd", "ace".
# Note:

# All words in words and S will only consists of lowercase letters.
# The length of S will be in the range of [1, 50000].
# The length of words will be in the range of [1, 5000].
# The length of words[i] will be in the range of [1, 50].


class NumMatchingSubseq:

    def doit(self, S, words):

        sequence = {}
        for w in words:
            if w[0] not in sequence:
                sequence[w[0]] = []
            sequence[w[0]].append((0, w))

        res = 0
        for c in S:

            if c in sequence:
                target = sequence[c]
                del sequence[c]
                for i, w in target:
                    if i == len(w) - 1:
                        res += 1
                    else:
                        i += 1
                        if w[i] not in sequence:
                            sequence[w[i]] = []
                        sequence[w[i]].append((i, w))
        return res

    def doit1(self, S, words):
        import bisect

        def is_sequence(w):
            index = -1
            for c in w:
                if c not in sequence:
                    return False
                n = bisect.bisect_right(sequence[c], index)
                if n == len(sequence[c]):
                    return False
                index = sequence[c][n]
            return True

        sequence = {}
        for i in range(len(S)):
            if S[i] not in sequence:
                sequence[S[i]] = []
            sequence[S[i]].append(i)

        res = 0
        seq_words = {}
        for w in words:
            if w in seq_words:
                res += (0, 1)[seq_words[w]]
            else:
                if is_sequence(w):
                    seq_words[w] = True
                    res += 1
                else:
                    seq_words[w] = False
        return res


if __name__ == '__main__':

    res = NumMatchingSubseq().doit1("abcde", ["a", "bb", "acd", "ace"])  # 3

    pass

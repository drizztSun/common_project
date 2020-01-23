# 916. Word Subsets

# We are given two arrays A and B of words.  Each word is a string of lowercase letters.
# Now, say that word b is a subset of word a if every letter in b occurs in a, including multiplicity.
# For example, "wrr" is a subset of "warrior", but is not a subset of "world".

# Now say a word a from A is universal if for every b in B, b is a subset of a.
# Return a list of all universal words in A.  You can return the words in any order.


# Example 1:

# Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","o"]
# Output: ["facebook","google","leetcode"]

# Example 2:

# Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["l","e"]
# Output: ["apple","google","leetcode"]

# Example 3:

# Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","oo"]
# Output: ["facebook","google"]

# Example 4:

# Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["lo","eo"]
# Output: ["google","leetcode"]

# Example 5:

# Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["ec","oc","ceo"]
# Output: ["facebook","leetcode"]


# Note:

# 1 <= A.length, B.length <= 10000
# 1 <= A[i].length, B[i].length <= 10
# A[i] and B[i] consist only of lowercase letters.
# All words in A[i] are unique: there isn't i != j with A[i] == A[j].

class WordSubsets:

    # (TLE)
    def doit(self, A, B):
        from collections import Counter
        b_set = [Counter(b) for b in B]

        def isSubset(word):
            word_cnt = Counter(word)

            for b in b_set:
                for c, v in b.items():
                    if word_cnt[c] < v:
                        return False
            return True

        return list(filter(isSubset, A))

    """
    Approach 1: Reduce to Single Word in B
    Intuition

    If b is a subset of a, then say a is a superset of b. Also, say N_{\text{"a"}}(\text{word})N
    "a"
    ​
    (word) is the count of the number of \text{"a"}"a"'s in the word.

    When we check whether a word wordA in A is a superset of wordB, we are individually checking the counts of letters: that for each \text{letter}letter, we have N_{\text{letter}}(\text{wordA}) \geq N_{\text{letter}}(\text{wordB})N
    letter
    ​
    (wordA)≥N
    letter
    ​
    (wordB).

    Now, if we check whether a word wordA is a superset of all words \text{wordB}_iwordB
    i
    ​
    , we will check for each letter and each ii, that N_{\text{letter}}(\text{wordA}) \geq N_{\text{letter}}(\text{wordB}_i)N
    letter
    ​
    (wordA)≥N
    letter
    ​
    (wordB
    i
    ​
    ). This is the same as checking N_{\text{letter}}(\text{wordA}) \geq \max\limits_i(N_{\text{letter}}(\text{wordB}_i))N
    letter
    ​
    (wordA)≥
    i
    max
    ​
    (N
    letter
    ​
    (wordB
    i
    ​
    )).

    For example, when checking whether "warrior" is a superset of words B = ["wrr", "wa", "or"], we can combine these words in B to form a "maximum" word "arrow", that has the maximum count of every letter in each word in B.

    Algorithm

    Reduce B to a single word bmax as described above, then compare the counts of letters between words a in A, and bmax.
    """

    def doit(self, A, B):
        def count(word):
            ans = [0] * 26
            for letter in word:
                ans[ord(letter) - ord('a')] += 1
            return ans

        bmax = [0] * 26
        for b in B:
            for i, c in enumerate(count(b)):
                bmax[i] = max(bmax[i], c)

        ans = []
        for a in A:
            if all(x >= y for x, y in zip(count(a), bmax)):
                ans.append(a)
        return ans

    def doit(self, A, B):

        def count(word):
            ans = [0] * 26
            for c in word:
                ans[ord(c) - ord('a')] += 1
            return ans

        b_max = [0] * 26
        for b in B:
            for i, c in enumerate(count(b)):
                b_max[i] = max(b_max[i], c)

        return list(filter(lambda w: all(x >= y for x, y in zip(count(w), b_max)), A))

    def doit(self, A, B):

        def wordSubsets(self, A, B):
            ccb = {}

        for b in B:
            cb = {}
            for l in b:
                if l in cb:
                    cb[l] += 1
                else:
                    cb[l] = 1
            for l in b:
                if l not in ccb or ccb[l] < cb[l]:
                    ccb[l] = cb[l]

        ans = []
        for a in A:
            flag = True
            for i in ccb:
                if a.count(i) < ccb[i]:
                    flag = False
                    break
            if flag:
                ans.append(a)
        return ans


if __name__ == '__main__':

    res = WordSubsets().doit(A=["amazon", "apple", "facebook", "google", "leetcode"], B=[
        "e", "o"])  # ["facebook","google","leetcode"]

    res = WordSubsets().doit(A=["amazon", "apple", "facebook", "google", "leetcode"], B=[
        "l", "e"])  # ["apple","google","leetcode"]

    res = WordSubsets().doit(A=["amazon", "apple", "facebook", "google", "leetcode"], B=[
        "e", "oo"])  # ["facebook","google"]

    res = WordSubsets().doit(A=["amazon", "apple", "facebook", "google", "leetcode"], B=[
        "lo", "eo"])  # ["google","leetcode"]

    res = WordSubsets().doit(A=["amazon", "apple", "facebook", "google", "leetcode"], B=[
        "ec", "oc", "ceo"])  # ["facebook","leetcode"]

    pass

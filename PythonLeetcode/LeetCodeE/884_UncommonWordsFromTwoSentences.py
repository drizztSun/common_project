# 884. Uncommon Words from Two Sentences

# We are given two sentences A and B.  (A sentence is a string of space separated words.
# Each word consists only of lowercase letters.)

# A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.

# Return a list of all uncommon words.

# You may return the list in any order.


# Example 1:

# Input: A = "this apple is sweet", B = "this apple is sour"
# Output: ["sweet","sour"]

# Example 2:

# Input: A = "apple apple", B = "banana"
# Output: ["banana"]

class UncommonFromSentences:

    """
    Approach 1: Counting

    Intuition and Algorithm

    Every uncommon word occurs exactly once in total. We can count the number of occurrences of every word,
    then return ones that occur exactly once.


    Complexity Analysis

    Time Complexity: O(M + N)O(M+N), where M, NM,N are the lengths of A and B respectively.

    Space Complexity: O(M + N)O(M+N), the space used by count.

    """

    def doit(self, A, B):

        cnt = {}
        for c in A.split():
            cnt[c] = cnt.get(c, 0) + 1

        for c in B.split():
            cnt[c] = cnt.get(c, 0) + 1

        return [c for c in cnt.keys() if cnt[c] == 1]


if __name__ == '__main__':

    res = UncommonFromSentences().doit(A="this apple is sweet",
                                       B="this apple is sour")  # ["sweet","sour"]

    res = UncommonFromSentences().doit(
        A="apple apple", B="banana")  # ["banana"]

    pass

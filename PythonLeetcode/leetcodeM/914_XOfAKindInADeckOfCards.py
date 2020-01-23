# 914. X of a Kind in a Deck of Cards

# In a deck of cards, each card has an integer written on it.

# Return true if and only if you can choose X >= 2 such that it is possible to split the entire deck into 1 or more groups of cards, where:

# Each group has exactly X cards.
# All the cards in each group have the same integer.


# Example 1:

# Input: [1,2,3,4,4,3,2,1]
# Output: true
# Explanation: Possible partition [1,1],[2,2],[3,3],[4,4]

# Example 2:

# Input: [1,1,1,2,2,2,3,3]
# Output: false
# Explanation: No possible partition.

# Example 3:

# Input: [1]
# Output: false
# Explanation: No possible partition.

# Example 4:

# Input: [1,1]
# Output: true
# Explanation: Possible partition [1,1]

# Example 5:

# Input: [1,1,2,2,2,2]
# Output: true
# Explanation: Possible partition [1,1],[2,2],[2,2]

# Note:

# 1 <= deck.length <= 10000
# 0 <= deck[i] < 10000


from itertools import groupby
import collections


class HasGroupsSizeX:

    """
    Approach 1: Brute Force
    Intuition
    We can try every possible X.

    Algorithm
    Since we divide the deck of N cards into say, K piles of X cards each, we must have N % X == 0.
    Then, say the deck has C_i copies of cards with number i. Each group with number i has X copies,
    so we must have C_i % X == 0. These are necessary and sufficient conditions.

    Complexity Analysis

    Time Complexity: O(N^2 loglogN), where NN is the number of cards.
    It is outside the scope of this article to prove that the number of divisors of NN is bounded by O(NloglogN).
    Space Complexity: O(N).
    """

    def doit(self, deck):
        N = len(deck)
        cnt = collections.Counter(deck)

        for i in range(2, N+1):
            if N % i == 0 and all(c % i == 0 for c in cnt.values()):
                return True

        return False

    """
    Approach 2: Greatest Common Divisor
    Intuition and Algorithm
    Again, say there are C_i cards of number i. These must be broken down into piles of X cards each, ie. C_i % X == 0 for all i.
    Thus, X must divide the greatest common divisor of C_i.
    If this greatest common divisor g is greater than 1, then X = g will satisfy. Otherwise, it won't.

    Complexity Analysis

    Time Complexity: O(N*log(N)^2), where NN is the number of votes. If there are C_i
    cards with number ii, then each gcd operation is naively O(log(C_i)^2 ).
    Better bounds exist, but are outside the scope of this article to develop.

    Space Complexity: O(N).
    """

    def doit(self, deck):
        from fractions import gcd
        from functools import reduce
        cnt = collections.Counter(deck).values()
        return reduce(gcd, cnt) >= 2


class Solution:
    def gcd(self, a, b):
        if a < b:
            a, b = b, a
        while b:
            a, b = b, a % b
        return a

    def hasGroupsSizeX(self, deck):
        if len(deck) <= 1:
            return False
        deck.sort()
        groups = [len(list(v)) for k, v in groupby(deck)]

        if len(groups) == 1:
            return True

        cur_gcd = groups[0]
        for val in groups:
            cur_gcd = self.gcd(cur_gcd, val)
        return cur_gcd > 1


if __name__ == '__main__':

    res = HasGroupsSizeX().doit([1, 2, 3, 4, 4, 3, 2, 1])  # true

    res = HasGroupsSizeX().doit([1, 1, 1, 2, 2, 2, 3, 3])  # false

    res = HasGroupsSizeX().doit([1])  # false

    res = HasGroupsSizeX().doit([1, 1])  # true

    res = HasGroupsSizeX().doit([1, 1, 2, 2, 2, 2])  # true

    pass

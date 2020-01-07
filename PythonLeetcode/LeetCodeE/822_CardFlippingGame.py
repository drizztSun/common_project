# 822. Card Flipping Game

# On a table are N cards, with a positive integer printed on the front and back of each card (possibly different).

# We flip any number of cards, and after we choose one card.

# If the number X on the back of the chosen card is not on the front of any card, then this number X is good.

# What is the smallest number that is good?  If no number is good, output 0.

# Here, fronts[i] and backs[i] represent the number on the front and back of card i.

# A flip swaps the front and back numbers, so the value on the front is now on the back and vice versa.

# Example:

# Input: fronts = [1,2,4,4,7], backs = [1,3,4,1,3]
# Output: 2
# Explanation: If we flip the second card, the fronts are [1,3,4,4,7] and the backs are [1,2,4,1,3].
# We choose the second card, which has number 2 on the back, and it isn't on the front of any card, so 2 is good.


# Note:

# 1 <= fronts.length == backs.length <= 1000.
# 1 <= fronts[i] <= 2000.
# 1 <= backs[i] <= 2000.


"""
Approach #1: Hash Set [Accepted]
Intuition

If a card has the same value x on the front and back, it is impossible to win with x.
Otherwise, it has two different values, and if we win with x, we can put x face down on the rest of the cards.

Algorithm

Remember all values same that occur twice on a single card.
Then for every value x on any card that isn't in same, x is a candidate answer.
If we have no candidate answers, the final answer is zero.

Complexity Analysis

Time Complexity: O(N), where NN is the length of fronts (and backs). We scan through the arrays.

Space Complexity: O(N).
"""

import itertools


class Flipgame:
    def doit(self, fronts, backs):
        same = {x for i, x in enumerate(fronts) if x == backs[i]}
        ans = 9999
        for x in itertools.chain(fronts, backs):
            if x not in same:
                ans = min(ans, x)

        return ans % 9999

    """
    We are using a set called invalid_numbers to store those cards which have the same number on both sides, the front and back.
    Those numbers are invalid candidates since flipping the card will always lead to the number on the back being on the front side of the deck at least once which violates the rule.
    In valid_indices the indices of the cards with potential candidates are stored, i.e. cards with different values on both sides.

    The first for-loop fills invalid_numbers and valid_indices with elements based on the previous paragraph.

    The second for-loop loops through the indices of cards which hold potential candidates.
    If the number on the back side of the currently examined card is smaller than the current result current_smallest_number,
    it needs to be a valid number in order to become the new result. After this, the front number is checked analogously.
    Remember: Since all cards hold different values on the front and back side, a multiple occurence of current_smallest_number on the front side can always be prevented by flipping all cards with current_smallest_number, except for one.
    If current_smallest_number is on the front side of a card though, the card can be flipped and multiple occurences of this number on the front of the deck can be prevented by applying the procedure recently mentioned.
    """
    def doit(self, fronts, backs):

        invalid_numbers = set()
        number = len(fronts)
        current_smallest_number = 5001
        valid_indices = []

        for i in range(number):
            if (fronts[i] == backs[i]):
                invalid_numbers.add(fronts[i])
            else:
                valid_indices.append(i)

        for i in valid_indices:
            if (backs[i] < current_smallest_number and backs[i] not in invalid_numbers):
                current_smallest_number = backs[i]

            if (fronts[i] < current_smallest_number and fronts[i] not in invalid_numbers):
                current_smallest_number = fronts[i]

        if (current_smallest_number == 5001):
            return 0

        return current_smallest_number


if __name__ == '__main__':

    res = Flipgame().doit(fronts=[1, 2, 4, 4, 7], backs=[1, 3, 4, 1, 3])

    pass

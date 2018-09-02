# 464. Can I Win

# In the "100 game," two players take turns adding, to a running total, any integer from 1..10. 
# The player who first causes the running total to reach or exceed 100 wins.

# What if we change the game so that players cannot re-use integers?

# For example, two players might take turns drawing from a common pool of numbers of 1..15 without replacement 
# until they reach a total >= 100.

# Given an integer maxChoosableInteger and another integer desiredTotal, 
# determine if the first player to move can force a win, assuming both players play optimally.

# You can always assume that maxChoosableInteger will not be larger than 20 and desiredTotal will not be larger than 300.

# Example

# Input:
# maxChoosableInteger = 10
# desiredTotal = 11

# Output:
# false

# Explanation:
# No matter which integer the first player choose, the first player will lose.
# The first player can choose an integer from 1 up to 10.
# If the first player choose 1, the second player can only choose integers from 2 up to 10.
# The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
# Same with other integers chosen by the first player, the second player will always win.



class CanIWin:

    def doit(self, maxChoosableInteger, desiredTotal):
        """
        :type maxChoosableInteger: int
        :type desiredTotal: int
        :rtype: bool
        """
        seen = {}

        def can_win(choices, remainder):
            # if the largest choice exceeds the remainder, then we can win!
            if choices[-1] >= remainder:
                return True

            # if we have seen this exact scenario play out, then we know the outcome
            seen_key = tuple(choices)
            if seen_key in seen:
                return seen[seen_key]

            # we haven't won yet.. it's the next player's turn.
            # importantly, if we win just one permutation then
            # we're still on our way to being able to 'force their hand'
            for index in range(len(choices)):
                if not can_win(choices[:index] + choices[index + 1:], remainder - choices[index]):
                    seen[seen_key] = True
                    return True

            # uh-oh if we got here then next player won all permutations, we can't force their hand
            # actually, they were able to force our hand :(
            seen[seen_key] = False
            return False


        # note: usefully, choices is already sorted
        choices = list(range(1, maxChoosableInteger + 1))

        # let's do some quick checks before we journey through the tree of permutations
        summed_choices = sum(choices)

        # if all the choices added up are less then the total, no-one can win
        if summed_choices < desiredTotal:
            return False

        # if the sum matches desiredTotal exactly, then as
        # long as there is an odd number of choices then first player wins
        if summed_choices == desiredTotal and len(choices) % 2:
            return True

        # slow: time to go through the tree of permutations
        return can_win(choices, desiredTotal)


if __name__ == "__main__":

    res = CanIWin().doit(maxChoosableInteger = 10, desiredTotal = 11)        

    res = False
"""
1753. Maximum Score From Removing Stones


You are playing a solitaire game with three piles of stones of sizes a, b and C respectively. Each turn you choose two different non-empty piles,
take one stone from each, and add 1 point to your score. The game stops when there are fewer than two non-empty piles (meaning there are no more available moves).

Given three integers a, b, and c, return the maximum score you can get.



Example 1:

Input: a = 2, b = 4, c = 6
Output: 6
Explanation: The starting state is (2, 4, 6). One optimal set of moves is:
- Take from 1st and 3rd piles, state is now (1, 4, 5)
- Take from 1st and 3rd piles, state is now (0, 4, 4)
- Take from 2nd and 3rd piles, state is now (0, 3, 3)
- Take from 2nd and 3rd piles, state is now (0, 2, 2)
- Take from 2nd and 3rd piles, state is now (0, 1, 1)
- Take from 2nd and 3rd piles, state is now (0, 0, 0)
There are fewer than two non-empty piles, so the game ends. Total: 6 points.
Example 2:

Input: a = 4, b = 4, c = 6
Output: 7
Explanation: The starting state is (4, 4, 6). One optimal set of moves is:
- Take from 1st and 2nd piles, state is now (3, 3, 6)
- Take from 1st and 3rd piles, state is now (2, 3, 5)
- Take from 1st and 3rd piles, state is now (1, 3, 4)
- Take from 1st and 3rd piles, state is now (0, 3, 3)
- Take from 2nd and 3rd piles, state is now (0, 2, 2)
- Take from 2nd and 3rd piles, state is now (0, 1, 1)
- Take from 2nd and 3rd piles, state is now (0, 0, 0)
There are fewer than two non-empty piles, so the game ends. Total: 7 points.
Example 3:

Input: a = 1, b = 8, c = 8
Output: 8
Explanation: One optimal set of moves is to take from the 2nd and 3rd piles for 8 turns until they are empty.
After that, there are fewer than two non-empty piles, so the game ends.


Constraints:

1 <= a, b, c <= 105


"""


class MaximumScore:

    """
        Reverse engineering, either 3 nums all become 0 or there are two 0’s

        If all 3 nums become 0, then result is (a+b+c)/2
        if 2 out of 3 are 0, it has to be sum of the minimum and middle one, so sum - max

        We need minimum of the two situation, image example [6, 2, 1]
    """

    def doit_math(self, a: int, b: int, c: int) -> int:

        return min((a + b + c) // 2, a + b + c - max(a, b, c))

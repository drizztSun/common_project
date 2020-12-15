"""
1140. Stone Game II

Alice and Bob continue their games with piles of stones.
There are a number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].
The objective of the game is to end with the most stones.

Alice and Bob take turns, with Alice starting first.  Initially, M = 1.

On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <= X <= 2M.  Then, we set M = max(M, X).

The game continues until all the stones have been taken.

Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.



Example 1:

Input: piles = [2,7,9,4,4]
Output: 10
Explanation:  If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again. Alice can get 2 + 4 + 4 = 10 piles in total.
If Alice takes two piles at the beginning, then Bob can take all three piles left. In this case, Alice get 2 + 7 = 9 piles in total. So we return 10 since it's larger.

Example 2:

Input: piles = [1,2,3,4,5,100]
Output: 104


Constraints:

1 <= piles.length <= 100
1 <= piles[i] <= 104

"""


class StoneGameII:

    def doit_dp(self, piles: list) -> int:

        dp = {}
        N = len(piles)

        # return the score difference between Alice and Bob, a + b = T, a - b = r
        def build(i, m):

            if i == len(piles):
                return 0

            if (i, m) in dp:
                return dp[(i, m)]

            m = min(m, N)

            if i + 2 * m >= N:
                return sum(piles[i:])

            res, total = float('-inf'), 0
            for j in range(1, 2 * m + 1):
                total += piles[j + i - 1]
                res = max(res, total - build(i + j, max(m, j)))

            dp[(i, m)] = res
            return res

        #  a + b = T, a - b = r, so (T + r) // 2 == a
        return (sum(piles) + build(0, 1)) // 2

    def stoneGameII(self, A):

        N = len(A)
        for i in range(N - 2, -1, -1):
            A[i] += A[i + 1]

        table = {}

        def dp(i, m):
            if i + 2 * m >= N:
                return A[i]

            if (i, m) in table:
                return table[(i, m)]

            table[(i, m)] = A[i] - min(dp(i + x, max(m, x)) for x in range(1, 2 * m + 1))
            return table[(i, m)]

        return dp(0, 1)


if __name__ == '__main__':

    StoneGameII().doit_dp([2,7,9,4,4])

    StoneGameII().doit_dp([1,2,3,4,5,100])

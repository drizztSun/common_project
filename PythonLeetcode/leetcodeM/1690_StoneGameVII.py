"""
1690. Stone Game VII

Alice and Bob take turns playing a game, with Alice starting first.

There are n stones arranged in a row. On each player's turn, they can remove either the leftmost stone or the rightmost stone
from the row and receive points equal to the sum of the remaining stones' values in the row.

The winner is the one with the higher score when there are no stones left to remove.

Bob found that he will always lose this game (poor Bob, he always loses), so he decided to minimize the score's difference.
Alice's goal is to maximize the difference in the score.

Given an array of integers stones where stones[i] represents the value of the ith stone from the left,
return the difference in Alice and Bob's score if they both play optimally.



Example 1:

Input: stones = [5,3,1,4,2]
Output: 6
Explanation:
- Alice removes 2 and gets 5 + 3 + 1 + 4 = 13 points. Alice = 13, Bob = 0, stones = [5,3,1,4].
- Bob removes 5 and gets 3 + 1 + 4 = 8 points. Alice = 13, Bob = 8, stones = [3,1,4].
- Alice removes 3 and gets 1 + 4 = 5 points. Alice = 18, Bob = 8, stones = [1,4].
- Bob removes 1 and gets 4 points. Alice = 18, Bob = 12, stones = [4].
- Alice removes 4 and gets 0 points. Alice = 18, Bob = 12, stones = [].
The score difference is 18 - 12 = 6.
Example 2:

Input: stones = [7,90,5,1,100,10,10,2]
Output: 122


Constraints:

n == stones.length
2 <= n <= 1000
1 <= stones[i] <= 1000


"""


class StoneGameVII:

    """
        Play optimally =》 Game theory Min-Max
    Always maxmize the relative score to matter who's playing the game（MaxMax)

        1) Max( my total score - opponent's total score) =>
        2) Max(my current score - opponent's relative score of the remaining game)

    game(l, r) := max relative score we can achieve given a sub-game of range [l, r]
    Subproblems overlaps => Recursion with memorization or DP, otherwise (2^n)
    Subproblems / Space complexity: O(n^2) / Time complexity: O(n^2)

    """
    def doit_dfs_dp_TopDown(self, stones: list) -> int:

        n = len(stones)
        dp = [[float('inf') for _ in range(n)] for _ in range(n)]

        def search(l, r, s):

            if l >= r:
                return 0

            if dp[l][r] != float('inf'):
                return dp[l][r]

            return max(s - stones[l] - search(l+1, r, s - stones[l]), s - stones[r] - search(l, r-1, s - stones[r]))

        return search(0, len(stones) - 1, sum(stones))

    """
    O(n^2)
    Bottomup: from smaller scope [i, i+1]  => larger one [j : j+1] 
    """
    def doit_dp_Bottomup(self, stones: list) -> int:
        n = len(stones)
        s = [0] * (n + 1)

        for i in range(n):
            s[i + 1] = s[i] + stones[i]

        dp = [[0] * n for _ in range(n)]

        for c in range(2, n + 1):
            for l in range(0, n - c + 1):
                r = l + c - 1
                dp[l][r] = max(s[r + 1] - s[l + 1] - dp[l + 1][r], s[r] - s[l] - dp[l][r - 1])

        return dp[0][n - 1]


if __name__ == '__main__':

    StoneGameVII().doit_dfs_dp_memo([5, 3, 1, 4, 2])

    StoneGameVII().doit_dfs_dp_memo([7,90,5,1,100,10,10,2])


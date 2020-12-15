"""
1563. Stone Game V

There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.

In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right row),
then Bob calculates the value of each row which is the sum of the values of all the stones in this row.
Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row.
If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.

The game ends when there is only one stone remaining. Alice's is initially zero.

Return the maximum score that Alice can obtain.



Example 1:

Input: stoneValue = [6,2,3,4,5,5]
Output: 18
Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14.
Bob throws away the right row and Alice's score is now 11.
In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
The last round Alice has only one choice to divide the row which is [2], [3].
Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.

Example 2:

Input: stoneValue = [7,7,7,7,7,7,7]
Output: 28
Example 3:

Input: stoneValue = [4]
Output: 0


Constraints:

1 <= stoneValue.length <= 500
1 <= stoneValue[i] <= 10^6


"""


class StoneGameV:

    def doit_(self, stoneValue: list) -> int:
        from functools import lru_cache
        n = len(stoneValue)
        sums = [0] *(n+1)
        for i in range(n):
            sums[i+1] = sums[i] + stoneValue[i]

        @lru_cache(None)
        def dfs(l, r):
            if l >= r: return 0

            ans = 0
            for k in range(l, r):

                sum_l, sum_r = sums[k+1] - sums[l], sums[r+1] - sums[k+1]

                if sum_l < sum_r:
                    ans = max(ans, sum_l + dfs(l, k))
                elif sum_l > sum_r:
                    ans = max(ans, sum_r + dfs(k+1, r))
                else:
                    ans = max(ans, sum_l + max(dfs(l, k), dfs(k+1, r)))

            return ans

        return dfs(0, n-1)


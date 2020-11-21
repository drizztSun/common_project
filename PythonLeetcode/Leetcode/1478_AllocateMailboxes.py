"""
1478. Allocate Mailboxes

Given the array houses and an integer k. where houses[i] is the location of the ith house along a street,
your task is to allocate k mailboxes in the street.

Return the minimum total distance between each house and its nearest mailbox.

The answer is guaranteed to fit in a 32-bit signed integer.



Example 1:



Input: houses = [1,4,8,10,20], k = 3
Output: 5
Explanation: Allocate mailboxes in position 3, 9 and 20.
Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5
Example 2:



Input: houses = [2,3,5,12,18], k = 2
Output: 9
Explanation: Allocate mailboxes in position 3 and 14.
Minimum total distance from each houses to nearest mailboxes is |2-3| + |3-3| + |5-3| + |12-14| + |18-14| = 9.
Example 3:

Input: houses = [7,4,6,1], k = 1
Output: 8
Example 4:

Input: houses = [3,6,14,10], k = 4
Output: 0


Constraints:

n == houses.length
1 <= n <= 100
1 <= houses[i] <= 10^4
1 <= k <= n
Array houses contain unique integers.


"""


class AllocateMailboxes:

    def doit_dp(self, houses: list, k: int) -> int:

        n = len(houses)
        houses.sort()
        dp = [[0 for _ in range(k)] for _ in range(n)]
        onlyone = [[0 for _ in range(n)] for _ in range(n)]

        for i in range(n):
            for j in range(i, n):
                median = houses[(i+j)//2]
                for kk in range(i, j+1):
                    onlyone[i][j] += abs(houses[kk] - median)

        for i in range(n):
            dp[i][0] = onlyone[0][i]

        for i in range(n):
            for kk in range(1, k):

                dp[i][kk] = float('inf')

                for j in range(i):
                    dp[i][kk] = min(dp[i][kk], dp[j][kk-1] + onlyone[j+1][i])

        return dp[n-1][k-1]

    def doit_dp_1(self, houses: list, k: int) -> int:
        if k >= len(houses):
            return 0
        N = len(houses)
        houses.sort()
        dp = {}

        def helper(n, k):
            if (n, k) in dp: return dp[(n, k)]
            if n == k: return 0
            if k == 1:
                dp[(n, k)] = sum(houses[(n + 1) // 2:n]) - sum(houses[:n // 2])
                return dp[(n, k)]

            res = helper(n - 1, k - 1)
            f = 0
            for j in range(2, n + 2 - k):
                f += houses[n - (j + 1) // 2] - houses[n - j]
                if f > res: break
                res = min(res, f + helper(n - j, k - 1))
            dp[(n, k)] = res
            return res

        return helper(N, k)


if __name__ == '__main__':

    AllocateMailboxes().doit_dp([1, 8, 12, 10, 3], 3)

    AllocateMailboxes().doit_dp(houses = [1,4,8,10,20], k = 3)

    AllocateMailboxes().doit_dp(houses = [2,3,5,12,18], k = 2)

    AllocateMailboxes().doit_dp(houses = [7,4,6,1], k = 1)

    AllocateMailboxes().doit_dp(houses = [3,6,14,10], k = 4)





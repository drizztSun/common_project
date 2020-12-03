"""
1473. Paint House III

There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n), some houses that has been painted last summer should not be painted again.

A neighborhood is a maximal group of continuous houses that are painted with the same color.
(For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods  [{1}, {2,2}, {3,3}, {2}, {1,1}]).

Given an array houses, an m * n matrix cost and an integer target where:

houses[i]: is the color of the house i, 0 if the house is not painted yet.
cost[i][j]: is the cost of paint the house i with the color j+1.
Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods, if not possible return -1.



Example 1:

Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
Output: 9
Explanation: Paint houses of this way [1,2,2,1,1]
This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
Example 2:

Input: houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
Output: 11
Explanation: Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}].
Cost of paint the first and last house (10 + 1) = 11.
Example 3:

Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[1,10],[10,1],[1,10]], m = 5, n = 2, target = 5
Output: 5
Example 4:

Input: houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3
Output: -1
Explanation: Houses are already painted with a total of 4 neighborhoods [{3},{1},{2},{3}] different of target = 3.


Constraints:

m == houses.length == cost.length
n == cost[i].length
1 <= m <= 100
1 <= n <= 20
1 <= target <= m
0 <= houses[i] <= n
1 <= cost[i][j] <= 10^4



"""


class PaintHouseIII:

    def doit_dp(self, houses: list, cost: list, m: int, n: int, target: int) -> int:

        kinf = 10**9 + 7
        dp = [[[kinf for _ in range(n+1)] for _ in range(m+1)] for _ in range(target+1)]
        dp[0][0] = [0] * (n+1)

        for k in range(1, target+1):
            for i in range(1, m+1):
                hi, hj = houses[i-1], houses[i-2] if i >= 2 else 0
                si, ei = (1, n) if hi == 0 else (hi, hi)
                sj, ej = (1, n) if hj == 0 else (hj, hj)

                for ci in range(si, ei+1):
                    v = 0 if ci == hi else cost[i-1][ci-1]
                    for cj in range(sj, ej+1):
                        dp[k][i][ci] = min(dp[k][i][ci], dp[k- (ci != cj)][i-1][cj] + v)

        return -1 if (c := min(c for c in dp[k][m])) >= kinf else c

    def doit_dp(self, houses: list, cost: list, m: int, n: int, target: int) -> int:
        # 已经有color的将不需要重新开始
        # 一共有exactly target个neighborhoods的情况

        # m个房子和n个color，所以Cost实际是个矩阵

        # 典型的dp，其中target要作为一个维度
        # dp(j,k,p)表示前j个house，分为k个neighboorhood时的情况，其中最后一个Color为p

        # dp(j,k,p)= dp(j-1,k,p) + min(dp(j-1,k-1,q) for q!=p)

        # Rolling array去掉一重，去掉j或者去掉k均可以

        # dp2(k,p)=dp1(k,p)+ min (dp1(k-1,q) for q!=p) + cost[j-1,j,p]

        # cost[j-1,j,p]表示将houses[j-1]粉刷为p的成本，即costs[j-1][p]

        # 而dp1(k-1,k-1,q)表示其中前一个粉刷的结果
        # 对于不能重新刷的情况，则将其值改为0和float(inf)即可

        # 处理costs部分

        # 其中包括了大量不需要的k部分

        # Soluiton 2 top-down

        cacheLeft = {}

        def lefts(j, k, p):  # 表示所有解
            # 表示dp(j,k)中p以前的最小值
            if p == 0:
                return float("inf")
            if (j, k, p) in cacheLeft:
                return cacheLeft[j, k, p]
            ans = min(lefts(j, k, p - 1), dp(j, k, p - 1))
            cacheLeft[j, k, p] = ans
            return ans

        cacheRight = {}

        def rights(j, k, p):
            if p == n - 1:
                return float("inf")
            if (j, k, p) in cacheRight:
                return cacheRight[j, k, p]
            ans = min(rights(j, k, p + 1), dp(j, k, p + 1))
            cacheRight[j, k, p] = ans
            return ans

        cache = {}

        def dp(j, k, p):
            if j < k:
                return float("inf")
            if j == 0:
                if k == 0:
                    return 0
                else:
                    return float("inf")
            if k == 0:
                return float("inf")
            if (j, k, p) in cache:
                return cache[j, k, p]
            color = houses[j - 1]
            # 当其
            # cost表示cost[j-1][p]
            if color > 0:
                if color - 1 == p:
                    localcost = 0
                else:
                    ans = float("inf")
                    cache[j, k, p] = ans
                    return ans
            else:
                localcost = cost[j - 1][p]  # 颜色为p

            ans = min(dp(j - 1, k, p), min(lefts(j - 1, k - 1, p), rights(j - 1, k - 1, p))) + localcost
            cache[j, k, p] = ans
            return ans

        ans = float("inf")
        for p in range(n):
            ans = min(ans, dp(len(houses), target, p))

        return ans if ans < float("inf") else -1


if __name__ == '__main__':

    PaintHouseIII().doit_dp(houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3)

    PaintHouseIII().doit_dp(houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3)

    PaintHouseIII().doit_dp(houses = [0,0,0,0,0], cost = [[1,10],[10,1],[1,10],[10,1],[1,10]], m = 5, n = 2, target = 5)

    PaintHouseIII().doit_dp(houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3)

"""
256. Paint House

There is a row of n houses, where each house can be painted one of three colors: red, blue, or green.
The cost of painting each house with a certain color is different.
You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix.
For example, costs[0][0] is the cost of painting house 0 with the color red;
costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.



Example 1:

Input: costs = [[17,2,17],[16,16,5],[14,3,19]]
Output: 10
Explanation: Paint house 0 into blue, paint house 1 into green, paint house 2 into blue.
Minimum cost: 2 + 5 + 3 = 10.
Example 2:

Input: costs = []
Output: 0
Example 3:

Input: costs = [[7,6,2]]
Output: 2

"""


class MinCost:

    def doit_dp(self, costs):

        for i in range(1, len(costs)):

            costs[i][0] += min(costs[i-1][1], costs[i-1][2])
            costs[i][1] += min(costs[i-1][0], costs[i-1][2])
            costs[i][2] += min(costs[i-1][0], costs[i-1][1])

        return min(costs[-1])

    """
    Complexity Analysis

    Time complexity : O(n).

    Analyzing memoization algorithms can be tricky at first, and requires understanding how recursion impacts the cost differently to loops. 
    The key thing to notice is that the full function runs once for each possible set of parameters. There are 3 * n different possible sets of parameters, because there are n houses and 3 colors. 
    Because the function body is O(1)O(1) (it's simply a conditional), this gives us a total of 3 * n. There can't be more than 3 * 2 * n searches into the memoization dictionary either. 
    The tree showed this clearly—the nodes representing lookups had to be the child of a call where a full calculation was done. 
    Because the constants are all dropped, this leaves O(n).
    """
    def doit_dp_1(self, costs):
        """
        :type costs: List[List[int]]
        :rtype: int
        """
        from functools import lru_cache
        @lru_cache(maxsize=None)
        def paint_cost(n, color):
            total_cost = costs[n][color]
            if n == len(costs) - 1:
                pass
            elif color == 0:
                total_cost += min(paint_cost(n + 1, 1), paint_cost(n + 1, 2))
            elif color == 1:
                total_cost += min(paint_cost(n + 1, 0), paint_cost(n + 1, 2))
            else:
                total_cost += min(paint_cost(n + 1, 0), paint_cost(n + 1, 1))
            return total_cost

        if costs == []:
            return 0

        return min(paint_cost(0, 0), paint_cost(0, 1), paint_cost(0, 2))

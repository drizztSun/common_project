"""
120. Triangle

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:

Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
"""


class MinimumTotal:

    def doit_dp(self, triangle) -> int:
        """
        :type triangle: List[List[int]]
        :rtype: int
        """
        dp = []
        for i in range(len(triangle)):
            cur = []
            for j in range(len(triangle[i])):

                if i == 0:
                    cur.append(triangle[i][j])
                    continue

                c = float("inf")
                if j - 1 >= 0:
                    c = min(c, dp[-1][j-1])

                if j < len(dp[-1]):
                    c = min(c, dp[-1][j])

                cur.append(c + triangle[i][j])
            dp.append(cur)

        return min(dp[-1])

    def doit_dp_1(self, triangle):
        """
        :type triangle: List[List[int]]
        :rtype: int
        """
        dp = triangle[-1]
        layer = len(triangle) - 2
        lenPrevLayer = len(dp) - 1
        for i in range(len(triangle) - 1):
            for j in range(lenPrevLayer):
                dp[j] = triangle[layer][j] + min(dp[j], dp[j+1])
            lenPrevLayer -= 1
            layer -= 1
        return dp[0]


if __name__ == '__main__':

    m = MinimumTotal().doit_dp([[2], [3, 4], [6, 5, 7], [4, 1, 8, 3]])



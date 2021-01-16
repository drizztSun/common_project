"""
221. Maximal Square

Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:

Input:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4
"""


class MaximalSquare:

    """
        Approach #2 (Dynamic Programming) [Accepted]
        Algorithm

        We will explain this approach with the help of an example.

        0 1 1 1 0
        1 1 1 1 1
        0 1 1 1 1
        0 1 1 1 1
        0 0 1 1 1
        We initialize another matrix (dp) with the same dimensions as the original one initialized with all 0’s.

        dp(i,j) represents the side length of the maximum square whose bottom right corner is the cell with index (i,j) in the original matrix.

        Starting from index (0,0), for every 1 found in the original matrix, we update the value of the current element as

        \text{dp}(i, j) = \min \big( \text{dp}(i-1, j), \text{dp}(i-1, j-1), \text{dp}(i, j-1) \big) + 1.dp(i,j)=min(dp(i−1,j),dp(i−1,j−1),dp(i,j−1))+1.

        We also remember the size of the largest square found so far. In this way, we traverse the original matrix once and find out the required maximum size.
        This gives the side length of the square (say maxsqlenmaxsqlen). The required result is the area maxsqlen^2maxsqlen
        2
         .

        To understand how this solution works, see the figure below.

        Max Square

        An entry 2 at (1, 3)(1,3) implies that we have a square of side 2 up to that index in the original matrix.
        Similarly, a 2 at (1, 2)(1,2) and (2, 2)(2,2) implies that a square of side 2 exists up to that index in the original matrix.
        Now to make a square of side 3, only a single entry of 1 is pending at (2, 3)(2,3). So, we enter a 3 corresponding to that position in the dp array.

        Now consider the case for the index (3, 4)(3,4). Here, the entries at index (3, 3)(3,3) and (2, 3)(2,3) imply that a square of side 3 is possible up to their indices.
        But, the entry 1 at index (2, 4)(2,4) indicates that a square of side 1 only can be formed up to its index.
        Therefore, while making an entry at the index (3, 4)(3,4), this element obstructs the formation of a square having a side larger than 2.
        Thus, the maximum sized square that can be formed up to this index is of size 2\times22×2.

        Complexity Analysis

        Time complexity : O(mn). Single pass.

        Space complexity : O(mn)O(mn). Another matrix of same size is used for dp.


    """
    def doit_dp(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if not matrix:
            return 0

        m, n = len(matrix), len(matrix[0])
        D = [[0] * (n + 1) for _ in range(m + 1)]
        ans = 0

        for i in range(1, m + 1):
            for j in range(1, n + 1):

                if matrix[i - 1][j - 1] == '1':
                    D[i][j] = min(D[i - 1][j - 1], D[i][j - 1], D[i - 1][j]) + 1
                    ans = max(D[i][j], ans)

        return ans ** 2

    """
        
        
    """
    def doit(self, matrix: list) -> int:

        M, N = len(matrix), len(matrix[0])
        dp = [[0 for _ in range(N+1)] for _ in range(2)]
        ans = 0

        for i in range(M):
            index = i % 2
            for j in range(1, N+1):

                if matrix[i][j-1] == "1":
                    dp[index][j] = min(dp[1-index][j], dp[index][j-1], dp[1-index][j-1]) + 1
                else:
                    dp[index][j] = 0

                ans = max(ans, dp[index][j])

        return ans ** 2


if __name__ == '__main__':

    MaximalSquare().doit([["0", "1"]])

    MaximalSquare().doit([["1","1","1","1","1"],
                          ["1","1","1","1","1"],
                          ["0","0","0","0","0"],
                          ["1","1","1","1","1"],
                          ["1","1","1","1","1"]])
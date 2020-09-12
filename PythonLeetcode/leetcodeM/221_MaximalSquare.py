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
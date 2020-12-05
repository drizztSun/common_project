"""
52. N-Queens II

The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens puzzle.



Example 1:


Input: n = 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
Example 2:

Input: n = 1
Output: 1


Constraints:

1 <= n <= 9


"""


class TotalNQueens:

    def doit_backtracking(self, n):
        """
        :type n: int
        :rtype: int
        """
        def isValid(D, n):
            j = 0
            while j < n:
                if D[j] == D[n] or abs(D[j]- D[n]) == abs(j - n):
                    return False
                j += 1

            return True

        D = [-1] * n
        i, D[0] = 0, -1
        rtv = 0

        while i >= 0:

            while i < n and D[i] < n-1:
                D[i] += 1

                if isValid(D, i):
                    i += 1
                    continue

            if i >= n:
                rtv += 1
            elif D[i] == n-1:
                D[i] = -1

            i -= 1

        return rtv
# 576. Out of Boundary Paths

# There is an m by n grid with a ball. Given the start coordinate (i,j) of the ball, 
# you can move the ball to adjacent cell or cross the grid boundary in four directions (up, down, left, right). 
# However, you can at most move N times. Find out the number of paths to move the ball out of grid boundary. 
# The answer may be very large, return it after mod 109 + 7.

# Example 1:
# Input:m = 2, n = 2, N = 2, i = 0, j = 0
# Output: 6
# Explanation:

# Example 2:
# Input:m = 1, n = 3, N = 3, i = 0, j = 1
# Output: 12
# Explanation:

# Note:
# Once you move the ball out of boundary, you cannot move it back.
# The length and height of the grid is in range [1,50].
# N is in range [0,50].


class FindPaths:
    def doit(self, m, n, N, i, j):
        """
        :type m: int
        :type n: int
        :type N: int
        :type i: int
        :type j: int
        :rtype: int
        """
        def search(m, n, step, i, j, visited):

            if step == 0:
                return 0

            if (step, i, j) in visited:
                return visited[(step, i, j)]

            visited[(step, i, j)] = 0
            for x, y in [(i-1, j), (i+1, j), (i, j-1), (i, j+1)]:
                if 0 <= x < m and 0 <= y < n:
                    visited[(step, i, j)] += search(m, n, step - 1, x, y, visited)
                else:
                    visited[(step, i, j)] += 1
            
            visited[(step, i, j)] %= (10**9 + 7)
            return visited[(step, i, j)]

        return search(m, n, N, i, j, {})


    def doit1(self, m, n, N, i, j):
        """
        :type m: int
        :type n: int
        :type N: int
        :type i: int
        :type j: int
        :rtype: int
        """
        import numpy as np
        paths = np.zeros((m, n), dtype=np.int64)
        paths[i][j] = 1
        out = 0
        mod = 10**9 + 7
        for _ in range(N):
            prev = paths % mod
            paths = prev - prev
            paths[1:,:] += prev[:-1,:]
            paths[:-1,:] += prev[1:,:]
            paths[:,1:] += prev[:,:-1]
            paths[:,:-1] += prev[:,1:]
            out += 4 * prev.sum() - paths.sum()
        return int(out % mod)


if __name__ == "__main__":

    res = FindPaths().doit(m = 2, n = 2, N = 2, i = 0, j = 0)

    res = FindPaths().doit(m = 1, n = 3, N = 3, i = 0, j = 1)

    res = 0


"""
1536. Minimum Swaps to Arrange a Binary Grid

Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.

A grid is said to be valid if all the cells above the main diagonal are zeros.

Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.

The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).

 

Example 1:


Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
Output: 3
Example 2:


Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
Output: -1
Explanation: All rows are similar, swaps have no effect on the grid.
Example 3:


Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
Output: 0
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 200
grid[i][j] is 0 or 1


"""

class MinimumSwapsToArragge:

    """
        First, count the number of trailing 0s for each row as zeros.
        Second, for i-th row, which needs n - i - 1 trailing 0s, just find the nearest j that j >= i and zeros[j] >= n - i - 1, 
        then the swap operation needed is j - i - 1, so that j-th row move forward to i-th row. If deque is applied to zeros, then zeros denotes the rows not used. 
        for i-th row, find the nearest j that zeros[j] >= n - i - 1, then the swap operation needed is j. Then pop j-th since it is used.
    """

    def doit_(self, grid: list) -> int:
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        zeros = []
        need = n - 1
        ans = 0

        for i in range(n):
            cur_zeros = n
            for j in range(n - 1, -1, -1):
                if grid[i][j] == 1:
                    cur_zeros = n - j - 1
                    break
            zeros.append(cur_zeros)

        while zeros:
            for i in range(len(zeros)):
                if zeros[i] >= need:
                    need -= 1
                    break
            else:
                return -1
            ans += i
            zeros.pop(i)
        return ans

    def doit_xxx(self, grid: list) -> int:
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        zeros = []
        need = n - 1
        ans = 0

        for i in range(n):
            cur_zeros = n
            for j in range(n - 1, -1, -1):
                if grid[i][j] == 1:
                    cur_zeros = n - j - 1
                    break
            zeros.append(cur_zeros)

        pos = [-1 for _ in range(n)]

        for i, c in enumerate(zeros):
            if pos[c] != -1: 
                return -1
            pos[c] = i

        p = 0
        for i in reversed(len(pos)):

            ans += pos[i] - p
            p += 1
        
        return ans
        
"""
1219. Path with Maximum Gold


In a gold mine grid of size m * n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.

Return the maximum amount of gold you can collect under the conditions:

Every time you are located in a cell you will collect all the gold in that cell.
From your position you can walk one step to the left, right, up or down.
You can't visit the same cell more than once.
Never visit a cell with 0 gold.
You can start and stop collecting gold from any position in the grid that has some gold.
 

Example 1:

Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
Output: 24
Explanation:
[[0,6,0],
 [5,8,7],
 [0,9,0]]
Path to get the maximum gold, 9 -> 8 -> 7.
Example 2:

Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
Output: 28
Explanation:
[[1,0,7],
 [2,0,6],
 [3,4,5],
 [0,3,0],
 [9,0,20]]
Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.
 

Constraints:

1 <= grid.length, grid[i].length <= 15
0 <= grid[i][j] <= 100
There are at most 25 cells containing gold.

"""


class PathWithMaximumGold:

    def doit_dfs(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        
        # start from (0, 0), what is the largest path?
        # as in a tree, traverse a tree from root to leaves, keep the largest one
        
        
        res = [0]
        
        def traverse_dfs(g, x, y, acc):
            if g[x][y] == 0:
                res[0] = max(res[0], acc)
                return
            
            acc += g[x][y]
            tmp = g[x][y]
            g[x][y] = 0
            
            for dx, dy in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
                nx = x + dx
                ny = y + dy
                if 0 <= nx < len(g) and 0 <= ny < len(g[0]):
                    traverse_dfs(g, nx, ny, acc)
                    
            g[x][y] = tmp
            
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                traverse_dfs(grid, i, j, 0)
                
        return res[0]


    def doit_dfs_1(self, grid: list) -> int:
        
        m, n = len(grid), len(grid[0])
        direct = (-1, 0, 1, 0, -1)
        
        def dfs(i, j):
            
            accu = 0
            tmp = grid[i][j]
            grid[i][j] = 0
            for k in range(4):
                x, y = i + direct[k], j + direct[k+1]
                if 0 <= x < m and 0 <= y < n and grid[x][y] != 0:
                    accu = max(accu, dfs(x, y))
                    
            grid[i][j] = tmp
            return accu + grid[i][j]
            
        ans = 0
        for i in range(m):
            for j in range(n):
                
                if grid[i][j] != 0:
                    ans = max(ans, dfs(i, j))
                    
        return ans

    
if __name__ == '__main__':

    PathWithMaximumGold().doit_dfs_1([[1,0,7,0,0,0],
                                      [2,0,6,0,1,0],
                                      [3,5,6,7,4,2],
                                      [4,3,1,0,2,0],
                                      [3,0,5,0,20,0]])
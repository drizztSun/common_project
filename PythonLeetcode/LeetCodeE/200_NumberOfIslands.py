

# 200. Number of Islands

# Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
# An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
# You may assume all four edges of the grid are all surrounded by water.

# Example 1:

# 11110
# 11010
# 11000
# 00000
# Answer: 1

# Example 2:

# 11000
# 11000
# 00100
# 00011
# Answer: 3

class NameOfIsland(object):

    # <dfs>
    def doit(self, gird):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        def search(x, y):
            if 0 <= x < len(grid) and 0 <= y < len(grid[0]) and grid[x][y] == '1':
                grid[x][y] == '0'
                for c in zip((x+1, x-1, x, x), (y, y, y+1, y-1)):
                    search(c[0], c[1])

        res = 0
        for i in range(len(grid)):
            for j in range(len(grid[0])):

                if grid[i][j] == '1':
                    res += 1
                    search(i, j)

        return res


    def doit2(self, grid):
        if not grid: return 0
        m = len(grid); n = len(grid[0])
        count = 0
        
        def helper(grid,i,j):
            if i > m-1 or i < 0 or j > n-1 or j < 0 or grid[i][j] != "1": return 
        
            grid[i][j] = "0"
            helper(grid,i+1,j)
            helper(grid,i,j+1)
            helper(grid,i-1,j)
            helper(grid,i,j-1)
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == "1":
                    count += 1
                    helper(grid,i,j)
                    
        return count

    def doit3(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        if len(grid) == 0: return 0
        m = len(grid)
        n = len(grid[0])
        res = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '1':
                    res += 1
                    grid[i][j] = '2'
                    self.island(i, j, grid, m, n)
        return res
        
    def island(self, x, y, grid, m, n):
        if x + 1 < m and grid[x+1][y] == '1':
            grid[x+1][y] = '2'
            self.island(x+1,y,grid, m, n)
        if y + 1 < n and grid[x][y+1] == '1':
            grid[x][y+1] = '2'
            self.island(x,y+1,grid, m, n)
        if x -1 >=0 and grid[x-1][y] == '1':
            grid[x-1][y] = '2'
            self.island(x-1,y,grid, m, n)
        if y - 1 >= 0 and grid[x][y-1] == '1':
            grid[x][y-1] = '2'
            self.island(x,y-1,grid, m, n)

 
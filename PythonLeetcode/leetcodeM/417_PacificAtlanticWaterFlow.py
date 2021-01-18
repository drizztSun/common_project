"""

417. Pacific Atlantic Water Flow


Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

Note:

The order of returned grid coordinates does not matter.
Both m and n are less than 150.
 

Example:

Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).

"""


class PacificAtlanticWaterFlow:

    def doit_dfs(self, matrix: list) -> list:

        if not matrix or not matrix[0]:
            return []

        m, n = len(matrix), len(matrix[0])
        pac_visited = [[False for _ in range(n)] for x in range(m)]
        alt_visited = [[False for _ in range(n)] for x in range(m)]

        def dfs(M, i, j, visited):
            
            visited[i][j] = True
            directions = [(-1, 0), (0, -1), (1, 0), (0, 1)]
            
            for dir in directions:

                x, y = i + dir[0], j + dir[1]

                if x < 0 or x > m-1 or y < 0 or y > n-1 or visited[x][y] or M[x][y] < M[i][j]:
                    continue

                dfs(M, x, y, visited)

        for x in range(n):
            dfs(matrix, 0, x, pac_visited)

            dfs(matrix, m-1, x, alt_visited)

        for y in range(m):
    
            dfs(matrix, y, 0, pac_visited)

            dfs(matrix, y, n-1, alt_visited)


        return [[i, j] for i in range(m) for j in range(n) if pac_visited[i][j] and alt_visited[i][j]]

    
    def doit_dfs(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
        if not matrix: return []
        self.directions = [(1,0),(-1,0),(0,1),(0,-1)]
        m = len(matrix)
        n = len(matrix[0])
        p_visited = [[False for _ in range(n)] for _ in range(m)]
        
        a_visited = [[False for _ in range(n)] for _ in range(m)]
        result = []

        def dfs(matrix, i, j, visited, m, n):
            # when dfs called, meaning its caller already verified this point 
            visited[i][j] = True
            for dir in self.directions:
                x, y = i + dir[0], j + dir[1]
                if x < 0 or x >= m or y < 0 or y >= n or visited[x][y] or matrix[x][y] < matrix[i][j]:
                    continue
                dfs(matrix, x, y, visited, m, n)
        
        for i in range(m):
            # p_visited[i][0] = True
            # a_visited[i][n-1] = True
            dfs(matrix, i, 0, p_visited, m, n)
            dfs(matrix, i, n-1, a_visited, m, n)
        for j in range(n):
            # p_visited[0][j] = True
            # a_visited[m-1][j] = True
            dfs(matrix, 0, j, p_visited, m, n)
            dfs(matrix, m-1, j, a_visited, m, n)
            
        for i in range(m):
            for j in range(n):
                if p_visited[i][j] and a_visited[i][j]:
                    result.append([i,j])
        return result
                
                

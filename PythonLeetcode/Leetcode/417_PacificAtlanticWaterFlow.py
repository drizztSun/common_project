


# 417. Pacific Atlantic Water Flow


# Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

# Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

# Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

# Note:
# The order of returned grid coordinates does not matter.
# Both m and n are less than 150.
# Example:

# Given the following 5x5 matrix:

#  Pacific ~   ~   ~   ~   ~ 
#       ~  1   2   2   3  (5) *
#       ~  3   2   3  (4) (4) *
#       ~  2   4  (5)  3   1  *
#       ~ (6) (7)  1   4   5  *
#       ~ (5)  1   1   2   4  *
#          *   *   *   *   * Atlantic

# Return:

# [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).


class pacificAtlantic:


    def doit(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
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




# The DFS solution is straightforward. Starting from each point, and dfs its neighbor if the neighbor is equal or less than itself.
# And maintain two boolean matrix for two oceans, indicating an ocean can reach to that point or not.
# Finally go through all nodes again and see if it can be both reached by two oceans.
# The trick is if a node is already visited, no need to visited again. Otherwise it will reach the recursion limits.
    def doit1(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
        if not matrix: 
            return []

        directions = [(1,0),(-1,0),(0,1),(0,-1)]
        m = len(matrix)
        n = len(matrix[0])

        def dfs(matrix, i, j, visited, m, n):
            # when dfs called, meaning its caller already verified this point 
            visited[i][j] = True
            for dir in directions:
                x, y = i + dir[0], j + dir[1]
                if x < 0 or x >= m or y < 0 or y >= n or visited[x][y] or matrix[x][y] < matrix[i][j]:
                    continue
                dfs(matrix, x, y, visited, m, n)
  
        p_visited = [[False for _ in range(n)] for _ in range(m)]
        a_visited = [[False for _ in range(n)] for _ in range(m)]
        result = []
        
        for i in range(m):
            self.dfs(matrix, i, 0, p_visited, m, n)
            self.dfs(matrix, i, n-1, a_visited, m, n)

        for j in range(n):
            self.dfs(matrix, 0, j, p_visited, m, n)
            self.dfs(matrix, m-1, j, a_visited, m, n)
            
        for i in range(m):
            for j in range(n):
                if p_visited[i][j] and a_visited[i][j]:
                    result.append([i,j])

        return result
                
                
       

        

    def doit1(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
        if not matrix or not matrix[0]:
            return []

        m, n = len(matrix), len(matrix[0])
        D = [[0 for _ in range(n)] for x in range(m)]
        
        for x in range(n):
            D[0][x], D[m-1][x] = 1, 2 

        for y in range(m):
            D[y][0], D[y][n-1] = 1, 2 

        D[m-1][0], D[0][n-1] = 3, 3,

        # Pac
        for i in range(1, m):
            for j in range(1, n):
                if matrix[i][j] >= min(matrix[i-1][j], matrix[i][j-1]) and max(D[i-1][j], D[i][j-1]) in (1, 3):
                        D[i][j] += 1

        for i in reversed(range(1, m)):
            for j in reversed(range(1, n)):
    
                if (i, j) == (m-1, n-1) or D[i][j] in (1, 3):
                    continue

                if j + 1 == n:
                    if matrix[i][j] >= matrix[i+1][j] and D[i+1][j] in (1, 3):
                        D[i][j] += 1

                elif i + 1 == m:
                    if matrix[i][j] >= matrix[i][j+1] and D[i][j+1] in (1, 3):
                        D[i][j] += 1

                elif matrix[i][j] >= min(matrix[i+1][j], matrix[i][j+1]) and max(D[i+1][j], D[i][j+1]) in (1, 3):
                    D[i][j] += 1

        # Alt
        for i in reversed(range(0, m-1)):
            for j in reversed(range(0, n-1)):
                if D[i][j] != 3 and matrix[i][j] >= min(matrix[i+1][j], matrix[i][j+1]) and max(D[i+1][j], D[i][j+1]) >= 2:
                    D[i][j] += 2


        for i in range(0, m):
            for j in range(0, n):
                if (i, j) == (0, 0) or D[i][j] in (2, 3):
                    continue

                if j - 1 < 0: 
                    if matrix[i][j] >= matrix[i-1][j] and D[i-1][j] == 3:
                        D[i][j] = 3

                elif i - 1 < 0:
                    if matrix[i][j] >= matrix[i][j-1] and D[i][j-1] == 3:
                        D[i][j] = 3

                elif matrix[i][j] >= min(matrix[i-1][j], matrix[i][j-1]) and max(D[i-1][j], D[i][j-1]) == 3:
                    D[i][j] = 3

        

        return [[i, j] for i in range(m) for j in range(n) if D[i][j] == 3]



if __name__=="__main__":


    matrix = [[1,2,2,3,5],
              [3,2,3,4,4],
              [2,4,5,3,1],
              [6,7,1,4,5],
              [5,1,1,2,4]]
    
    res = pacificAtlantic().doit(matrix) # [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]

    matrix = [[1, 2, 3],
              [8, 9, 4],
              [7, 6, 5]]
    
    res = pacificAtlantic().doit(matrix)

    pass
            
         
        
    
        
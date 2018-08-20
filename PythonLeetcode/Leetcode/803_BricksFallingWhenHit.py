# 803. Bricks Falling When Hit

# We have a grid of 1s and 0s; the 1s in a cell represent bricks.  
# A brick will not drop if and only if it is directly connected to the top of the grid,
# or at least one of its (4-way) adjacent bricks will not drop.

# We will do some erasures sequentially. Each time we want to do the erasure at the location (i, j),
# the brick (if it exists) on that location will disappear, and then some other bricks may drop because of that erasure.

# Return an array representing the number of bricks that will drop after each erasure in sequence.

# Example 1:
# Input: 
# grid = [[1,0,0,0],[1,1,1,0]]
# hits = [[1,0]]
# Output: [2]
# Explanation: 
# If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2) will drop. So we should return 2.

# Example 2:
# Input: 
# grid = [[1,0,0,0],[1,1,0,0]]
# hits = [[1,1],[1,0]]
# Output: [0,0]
# Explanation: 
# When we erase the brick at (1, 0), the brick at (1, 1) has already disappeared due to the last move. So each erasure will cause no bricks dropping.
# Note that the erased brick (1, 0) will not be counted as a dropped brick.
 

# Note:

# The number of rows and columns in the grid will be in the range [1, 200].
# The number of erasures will not exceed the area of the grid.
# It is guaranteed that each erasure will be different from any other erasure, and located inside the grid.
# An erasure may refer to a location with no brick - if it does, no bricks drop.



# Union-Find

# I think for this problem, it is not easy to think the hit sequence recursely. 
# However, this is the first essential step to solve this problem.
# In the Union Find, I used a dummy node m*n to denote the roof node. 
# So, the 1 in the first row will be connected to this roof node.

# The method to calculate how many bricks are fall is to calcuate the rank difference of the roof node.
# 
# There are a few cases to handle :
#
# hit to 0. In this case, we simply add 0 to the result, since this will make no difference for the grid.
# hit to 1. But this 1 is not connected to roof. So the falling brick will be curRoofRank - prevRoofRank.
# hit to 1. But this 1 is connected to roof. So the falling brick will be curRoofRank - prevRoofRank - 1.

class UnionFinder:

    def __init__(self, length):
        self.father = [i for i in range(length)]
        self.count =  [1 for _ in range(length)]

    def Find(self, id):
        while self.father[id] != id:
            self.father[id] = self.father[self.father[id]]
            id = self.father[id]
        return id

    def Union(self, a, b):
        fa, fb = self.Find(a), self.Find(b)
        if fa != fb:
            self.father[fa] = fb
            self.count[fb] += self.count[fa]


class HitBricks:
    def doit(self, grid, hits):
        """
        :type grid: List[List[int]]
        :type hits: List[List[int]]
        :rtype: List[int]
        """
        def unionAround(i, j, grid, uf):
            
            for c in [(i+1, j), (i-1, j), (i, j+1), (i, j-1)]:
                if not (0 <= c[0] < M and 0 <= c[1] < N):
                    continue

                if grid[c[0]][c[1]] == 1:           
                    uf.Union(i * N + j + 1, c[0] * N + c[1] + 1)

            if i == 0:
                uf.Union(i * N + j + 1, 0)                        

        M, N = len(grid), len(grid[0])
        uf = UnionFinder(M * N + 1)

        for c in hits:
            if grid[c[0]][c[1]] == 1:
                grid[c[0]][c[1]] = 2
        
        for i in range(M):
            for j in range(N):
                if grid[i][j] == 1:
                    unionAround(i, j, grid, uf)

        count = uf.count[uf.Find(0)]
        res = [0] * len(hits)

        for i in reversed(range(len(hits))):
            x, y = hits[i]
            if grid[x][y] == 2:
                unionAround(x, y, grid, uf)
                grid[x][y] = 1
            
            newCount = uf.count[uf.Find(0)]
            res[i] = newCount - count - 1 if newCount > count else 0
            count = newCount

        return res

    def doit1(self, grid, hits):
        """
        :type grid: List[List[int]]
        :type hits: List[List[int]]
        :rtype: List[int]
        """
        m, n, s = len(grid), len(grid[0]), [0] * len(hits)

        for i,j in hits:
            grid[i][j] -= 1

        for j in range(n):
            if grid[0][j] == 1:
                stack = [ (0, j) ]
                grid[0][j] += 1

                while stack:
                    i, j = stack.pop()
                    for ii,jj in (i,j+1), (i+1,j), (i,j-1), (i-1,j):
                        if ii>=0 and ii<m and jj>=0 and jj<n and grid[ii][jj]==1:
                            stack.append((ii,jj))
                            grid[ii][jj] += 1

        for k in range(len(hits) - 1, -1, -1):
            i, j = hits[k]
            grid[i][j] += 1
            if grid[i][j] == 1 and (i == 0 or (j < n-1 and grid[i][j+1] == 2) or (i < m-1 and grid[i+1][j] == 2) or (j > 0 and grid[i][j-1] == 2) or grid[i-1][j] == 2):
                kk, stack = 0, [(i, j)]
                grid[i][j] += 1
                while stack:
                    i, j = stack.pop()
                    for ii,jj in (i, j+1), (i+1, j), (i, j-1), (i-1, j):
                        if ii>= 0 and ii < m and jj >= 0 and jj < n and grid[ii][jj] == 1:
                            stack.append((ii, jj))
                            grid[ii][jj] += 1
                            kk += 1
                s[k] = kk

        return s

if __name__ == "__main__":

    res = HitBricks().doit([[1,0,0,0],[1,1,0,0]], [[1,1],[1,0]])

    res = HitBricks().doit([[1,0,0,0],[1,1,1,0]], [[1,0]])

    res = HitBricks().doit([[1],[1],[1],[1],[1]], [[3,0],[4,0],[1,0],[2,0],[0,0]])
    
    pass

    
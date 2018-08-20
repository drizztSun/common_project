# 827. Making A Large Island

# In a 2D grid of 0s and 1s, we change at most one 0 to a 1.

# After, what is the size of the largest island? (An island is a 4-directionally connected group of 1s).

# Example 1:

# Input: [[1, 0], [0, 1]]
# Output: 3
# Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.

# Example 2:

# Input: [[1, 1], [1, 0]]
# Output: 4
# Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 1.

# Example 3:

# Input: [[1, 1], [1, 1]]
# Output: 4
# Explanation: Can't change any 0 to 1, only one island with area = 1.
 

# Notes:

# 1 <= grid.length = grid[0].length <= 50.
# 0 <= grid[i][j] <= 1.


class LargestIsland:
    
    # <union-find>
    def doit(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict
        M, N = len(grid), len(grid[0])
        Parent = [-1] * (M * N)

        def find(idx):
            if Parent[idx] != -1:
                Parent[idx] = find(Parent[idx])
                idx = Parent[idx]
            return idx

        for i in range(M):
            for j in range(N):
                if grid[i][j] == 1:
                    Pij = find(i * N + j)

                    for xx, yy in [(i+1, j), (i-1, j), (i, j-1), (i, j+1)]:
                        if 0 <= xx < M and 0 <= yy < N and grid[xx][yy] == 1:
                            Pxy = find(xx * N + yy)

                            if Pxy != Pij:
                                Parent[Pxy] = Pij

        islands = defaultdict(int)
        for i in range(M):
            for j in range(N):
                if grid[i][j] == 1:
                    islands[find(i * N + j)] += 1

        ans = 0 if grid[i][j] == 0 else islands[find(0)]
        for i in range(M):
            for j in range(N):
                if grid[i][j] == 0:
                    
                    local, tmp = set(), 1
                    for xx, yy in [(i+1, j), (i-1, j), (i, j-1), (i, j+1)]:
                        if 0 <= xx < M and 0 <= yy < N and grid[xx][yy] == 1:
                            local.add(find(xx * N + yy))
                    
                    for l in local:
                        tmp += islands[l]

                    ans = max(tmp, ans)
        
        return ans


class Solution:
    def doit1(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        M, N = len(grid), len(grid[0])
        islands = []

        for i in range(M):
            for j in range(N):
                if grid[i][j] == 1:
                    st, zeros, cnt = [(i, j)], set(), 0
                    
                    while st:
                        x, y = st.pop()
                        grid[i][j] = 2
                        cnt += 1

                        for xx, yy in [(x+1, y), (x-1, y), (x, y+1), (x, y-1)]:
                            if 0 <= xx < M and 0 <= yy < N:
                                if grid[xx][yy] == 1:
                                    grid[xx][yy] = 2
                                    st.append((xx, yy))
                                elif grid[xx][yy] == 0:
                                    zeros.add((xx, yy))

                    islands.append((cnt, zeros))

        if not islands:
            return 1

        islands.sort(key=lambda x: (x[0], len(x[1])))
        maxv = islands[-1][0] + (1 if len(islands[-1][1]) > 0 else 0)
        for i in reversed(range(len(islands))):
            for j in reversed(range(0, i)):
                
                if islands[i][0] + islands[j][0] >= maxv and islands[i][1] & islands[j][1]:
                    maxv = islands[i][0] + islands[j][0] + 1

        return maxv


if __name__ == "__main__":

    res = LargestIsland().doit([[1, 0], [0, 1]])

    res = LargestIsland().doit([[1, 1], [1, 0]])

    res = LargestIsland().doit([[1, 1], [1, 1]])

    res = LargestIsland().doit([[0, 0], [0, 0]])

    res = LargestIsland().doit([[0,0,0,0,0,0,0],
                                [0,1,1,1,1,0,0],
                                [0,1,0,0,1,0,0],
                                [1,0,1,0,1,0,0],
                                [0,1,0,0,1,0,0],
                                [0,1,0,0,1,0,0],
                                [0,1,1,1,1,0,0]])

    pass
        
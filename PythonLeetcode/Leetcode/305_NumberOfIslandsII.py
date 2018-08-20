


# 305. Number of Islands II

# A 2d grid map of m rows and n columns is initially filled with water.
# We may perform an addLand operation which turns the water at position (row, col) into a land.
# Given a list of positions to operate, count the number of islands after each addLand operation.
# An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
# You may assume all four edges of the grid are all surrounded by water.

# Example:

# Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
# Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

# 0 0 0
# 0 0 0
# 0 0 0
# Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

# 1 0 0
# 0 0 0   Number of islands = 1
# 0 0 0
# Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

# 1 1 0
# 0 0 0   Number of islands = 1
# 0 0 0
# Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

# 1 1 0
# 0 0 1   Number of islands = 2
# 0 0 0
# Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

# 1 1 0
# 0 0 1   Number of islands = 3
# 0 1 0
# We return the result as an array: [1, 1, 2, 3]


# Challenge:

# Can you do it in time complexity O(k log mn), where k is the length of the positions?

# <hard> <important>
class NumberOfIslandII(object):


    # <union-find>
    def doit(self, m, n, posiitons):
        """
        type: int
        type: int
        type: list[list[int]]
        rtype: list[int]
        """
        parent = [-1] * (m * n)
        lands = 0
        result = []

        def root(id):
            while parent[id] != id:
                parent[id] = parent[parent[id]] # Path Suspress, child points to father's father
                id = parent[id]
            return id

        for x, y in posiitons:            
            id = x * n + y
            parent[id] = id
            lands += 1 
            nears = [(x-1, y), (x+1, y), (x, y-1), (x, y+1)]

            for nx, ny in nears:
                nid = nx * n + ny
                if 0<= nx < n and 0<= ny < m and parent[nid] != -1:
                    rootid = root(nid)
                    if rootid != id:
                        parent[rootid] = id
                        lands -= 1
            
            result.append(lands)
        return result 
                        
                        



if __name__=="__main__":


    res = NumberOfIslandII().doit(3, 3, [[0,0], [0,1], [1,2], [2,1]]) # [1, 1, 2, 3]

        

    pass
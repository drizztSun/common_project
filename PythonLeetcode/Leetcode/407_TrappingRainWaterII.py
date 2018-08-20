


# 407. Trapping Rain Water II


# Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map,
# compute the volume of water it is able to trap after raining.

# Note:
# Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.

# Example:

# Given the following 3x6 height map:
# [
#  [1,4,3,1,3,2],
#  [3,2,1,3,2,4],
#  [2,3,3,2,3,1]
# ]

# Return 4.


# <important>
class trapRainWater(object):


# The idea is that we maintain all the points of the current border in a min heap and always choose the point with the lowest length. 
# This is actually an optimized searching strategy over the trivial brute force method: 
# instead of dfs each point to find the lowest �border� of its connected component, 
# we can always start a search from the lowest border and update the points adjacent to it.

    # <heap>
    def doit(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        if len(heightMap) == 0 or len(heightMap[0]) == 0:
            return 0

        import heapq
        m, n = len(heightMap), len(heightMap[0])
        points, visited = [], [[False for _ in range(n)] for x in range(m)]        

        for i in range(m):
            heapq.heappush(points, (heightMap[i][0], i, 0))
            heapq.heappush(points, (heightMap[i][n-1], i, n-1))
            visited[i][0], visited[i][n-1] = True, True

        for j in range(n):
            heapq.heappush(points, (heightMap[0][j], 0, j))
            heapq.heappush(points, (heightMap[m-1][j], m-1, j))
            visited[0][j], visited[m-1][j] = True, True

        result = 0
        while points:
            height, x1, y1 = heapq.heappop(points)
            for x, y in [(x1+1, y1), (x1-1, y1), (x1, y1+1), (x1, y1-1)]:
                if 0 <= x < m and 0 <= y < n and not visited[x][y]:
                    result += max(0, height - heightMap[x][y])
                    visited[x][y] = True
                    heapq.heappush(points, (max(height, heightMap[x][y]), x, y))

        return result
                    


    # <dfs>
    def doit1(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        if len(heightMap) < 3 or len(heightMap[0]) < 3:
            return 0
        
        m, n, pq = len(heightMap), len(heightMap[0]), []
        
        for i, j in zip([0]*n + range(1, m-1)*2 + [m-1]*n, range(n)+[0]*(m-2)+[n-1]*(m-2)+range(n)):
            heapq.heappush(pq, (heightMap[i][j], i, j))
            heightMap[i][j] = -1
        
        #do dfs
        res = 0
        def dfs(i, j, curr_height, curr_res):

            for next_i, next_j in ((i+1, j), (i-1, j), (i, j+1), (i, j-1)):

                if 0<=next_i<len(heightMap) and 0<=next_j<len(heightMap[0]) and heightMap[next_i][next_j] >= 0:

                    new_height = heightMap[next_i][next_j]
                    heightMap[next_i][next_j] = -1

                    if new_height < curr_height:
                        #we can secure how much water?
                        curr_res += curr_height-new_height
                        #continue to expand
                        curr_res = dfs(next_i, next_j, curr_height, curr_res)   
                        #note the boundary height will not change...
                    else:
                        #the boundary must be changed now
                        heapq.heappush(pq, (new_height, next_i, next_j))
                
            return curr_res
        
        #for all the boundary points...
        while pq:
            curr_height, curr_i, curr_j = heapq.heappop(pq)
            res = dfs(curr_i, curr_j, curr_height, res)
        return res



# This problem can also be solved in a more general approach way using Dijkstra.

# Construct a graph G = (V, E) as follows:
# V = all cells plus a dummy vertex, v, corresponding to the outside region.
# If cell(i, j) is adjacent to cell(i', j'), then add an direct edge from (i, j) to (i', j') with weight height(i', j').
# Add an edge with zero weight from any boundary cell to the dummy vertex v.

# The weight of a path is defined as the weight of the heaviest edge along it. Then, for any cell (i, j), the height of water it can save is equal to the weight, denoted by dist(i, j), of the shortest path from (i, j) to v. (If the weight is less than or equal to height(i, j), no water can be accumulated at that particular position.)

# We want to compute the dist(i, j) for all pairs of (i, j). Here, we have multiple sources and one destination, but this problem essentially can be solved using one pass of Dijkstra algorithm if we reverse the directions of all edges. The graph is sparse, i.e., there are O(rc) edges, resulting an O(rc log(rc)) = O(rc max(log r, log c)) runtime and using O(rc) space.

    def doit3(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        pass





if __name__=="__main__":

    A =  [
            [1,4,3,1,3,2],
            [3,2,1,3,2,4],
            [2,3,3,2,3,1]
          ]

    res = trapRainWater().doit(A)

    pass
        
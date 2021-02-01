""""
1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance


There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.

Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.

Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.



Example 1:



Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
Output: 3
Explanation: The figure above describes the graph.
The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2]
City 1 -> [City 0, City 2, City 3]
City 2 -> [City 0, City 1, City 3]
City 3 -> [City 1, City 2]
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.
Example 2:



Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
Output: 0
Explanation: The figure above describes the graph.
The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1]
City 1 -> [City 0, City 4]
City 2 -> [City 3, City 4]
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3]
The city 0 has 1 neighboring city at a distanceThreshold = 2.


Constraints:

2 <= n <= 100
1 <= edges.length <= n * (n - 1) / 2
edges[i].length == 3
0 <= fromi < toi < n
1 <= weighti, distanceThreshold <= 10^4
All pairs (fromi, toi) are distinct.

"""


class SmallestNumberOFNeighbour:

    """
        Explanation
        Becasue O(N^3) is accepted in this problem, we don't need a very fast solution.
        we can simply use Floyd algorithm to find the minium distance any two cities.

        Reference Floyd–Warshall algorithm

        I first saw @awice using it long time ago.
        It's really easy and makes a lot sense.

        Iterate all point middle point k,
        iterate all pairs (i,j).
        If it go through the middle point k,
        dis[i][j] = dis[i][k] + dis[k][j].


        Complexity
        Time O(N^3)
        Space O(N^2)
    """
    def doit_(self, n, edges, maxd):
        dis = [[float('inf')] * n for _ in range(n)]
        for i, j, w in edges:
            dis[i][j] = dis[j][i] = w

        for i in range(n):
            dis[i][i] = 0

        for k in range(n):
            for i in range(n):
                for j in range(n):
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j])

        res = {sum(d <= maxd for d in dis[i]): i for i in range(n)}
        return res[min(res)]

    """
        I am using the Floyd-Warshall algorithm to calculate the minimum distance between each pair of cities.
        Then all that is left to do is counting the neighbors within the distance threshold and return the city with the minimum count and maximum id.

        Time complexity: O(n³)
        Space complexity: O(n²)
    """
    def doit_floyd_warshall(self, n: int, edges: list, distanceThreshold: int) -> int:
        # Minimum distance graph between all the cities
        from collections import defaultdict
        from math import inf
        minDistance = defaultdict(lambda: defaultdict(lambda: math.inf))

        # set the distance from a city to itself to 0
        for i in range(n):
            minDistance[i][i] = 0

        # set the initial distances between the cities
        for u, v, weight in edges:
            minDistance[u][v] = weight
            minDistance[v][u] = weight

        # Floyd-Warshall calculates the minimum distance between each pair of cities
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    minDistance[i][j] = min(minDistance[i][j], minDistance[i][k] + minDistance[k][j])

        minNeighborCount = inf
        minCity = -1

        for i in range(n):
            # Count how many of city i's neighbors are within the distance threshold.
            neighborCount = sum(minDistance[i][j] <= distanceThreshold for j in range(n) if j != i)

            # Update the result if a city with less neighbors has been found or the id is higher
            if neighborCount <= minNeighborCount:
                minNeighborCount = neighborCount
                minCity = i

        return minCity

    def doit_dijstra(self, n: int, edges: list, distanceThreshold: int) -> int:
        import heapq
        from collections import defaultdict
        c2nei = defaultdict(list)
        for x, y, dist in edges:
            if dist <= distanceThreshold:
                c2nei[x].append((y, dist))
                c2nei[y].append((x, dist))

        def search(start, bound, num):
            que = [(0, start)]
            dist = [bound + 1] * n
            dist[start] = 0
            visited = [0] * n
            cnt = 0
            while que:
                distcity, city = heapq.heappop(que)
                if visited[city]:
                    continue

                visited[city] = 1
                cnt += 1

                if cnt > num + 1:
                    return cnt - 1
                if city not in c2nei:
                    continue

                for nei, distance in c2nei[city]:
                    if distcity + distance < dist[nei]:
                        heapq.heappush(que, (distcity + distance, nei))
                        dist[nei] = distcity + distance
            visited[start] = 0
            return sum(visited)

        rst = -1
        smallest = float('inf')
        for i in range(n):
            tmp = search(i, distanceThreshold, smallest)
            if tmp <= smallest:
                rst = i
                smallest = tmp

        return rst

    def doit_dfs(self, n: int, edges: list, distanceThreshold: int) -> int:

        from collections import defaultdict

        graph = defaultdict(lambda: defaultdict(int))

        for s, e, w in edges:
            graph[s][e] = graph[e][s] = w

        def dfs(node, distance):

            visited[node] = distance

            for child in graph[node]:

                if graph[node][child] > distance:
                    continue

                if child not in visited or distance - graph[node][child] > visited[child]:
                    dfs(child, distance - graph[node][child])

        ans, maxi = float('inf'), 0
        for i in range(n):
            visited = {}
            dfs(i, distanceThreshold)
            if len(visited) <= ans:
                ans = len(visited)
                maxi = i

        return maxi


if __name__ == '__main__':

    SmallestNumberOFNeighbour().doit_dfs(5, [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], 2)


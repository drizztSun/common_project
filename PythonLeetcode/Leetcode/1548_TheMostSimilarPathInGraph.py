"""
1548. The Most Similar Path in a Graph

We have n cities and m bi-directional roads where roads[i] = [ai, bi] connects city ai with city bi.
Each city has a name consisting of exactly 3 upper-case English letters given in the string array names.
Starting at any city x, you can reach any city y where y != x (i.e. the cities and the roads are forming an undirected connected graph).

You will be given a string array targetPath. You should find a path in the graph of the same length and with the minimum edit distance to targetPath.

You need to return the order of the nodes in the path with the minimum edit distance,
The path should be of the same length of targetPath and should be valid (i.e. there should be a direct road between ans[i] and ans[i + 1]).
If there are multiple answers return any one of them.

The edit distance is defined as follows:



Follow-up: If each node can be visited only once in the path, What should you change in your solution?



Example 1:


Input: n = 5, roads = [[0,2],[0,3],[1,2],[1,3],[1,4],[2,4]], names = ["ATL","PEK","LAX","DXB","HND"], targetPath = ["ATL","DXB","HND","LAX"]
Output: [0,2,4,2]
Explanation: [0,2,4,2], [0,3,0,2] and [0,3,1,2] are accepted answers.
[0,2,4,2] is equivalent to ["ATL","LAX","HND","LAX"] which has edit distance = 1 with targetPath.
[0,3,0,2] is equivalent to ["ATL","DXB","ATL","LAX"] which has edit distance = 1 with targetPath.
[0,3,1,2] is equivalent to ["ATL","DXB","PEK","LAX"] which has edit distance = 1 with targetPath.
Example 2:


Input: n = 4, roads = [[1,0],[2,0],[3,0],[2,1],[3,1],[3,2]], names = ["ATL","PEK","LAX","DXB"], targetPath = ["ABC","DEF","GHI","JKL","MNO","PQR","STU","VWX"]
Output: [0,1,0,1,0,1,0,1]
Explanation: Any path in this graph has edit distance = 8 with targetPath.
Example 3:



Input: n = 6, roads = [[0,1],[1,2],[2,3],[3,4],[4,5]], names = ["ATL","PEK","LAX","ATL","DXB","HND"], targetPath = ["ATL","DXB","HND","DXB","ATL","LAX","PEK"]
Output: [3,4,5,4,3,2,1]
Explanation: [3,4,5,4,3,2,1] is the only path with edit distance = 0 with targetPath.
It's equivalent to ["ATL","DXB","HND","DXB","ATL","LAX","PEK"]


Constraints:

2 <= n <= 100
m == roads.length
n - 1 <= m <= (n * (n - 1) / 2)
0 <= ai, bi <= n - 1
ai != bi
The graph is guaranteed to be connected and each pair of nodes may have at most one direct road.
names.length == n
names[i].length == 3
names[i] consists of upper-case English letters.
There can be two cities with the same name.
1 <= targetPath.length <= 100
targetPath[i].length == 3
targetPath[i] consists of upper-case English letters.
"""


class MostSimilar(object):

    """
    This is a bottom up dynamic programing approach. The computation complexity is O(E*L) where N is number of nodes,
    E is the number of edges in the graph, in the worst case E = N^2 where N is the number nodes. L is the length of the target path.

    This algorithm solves the problem in L steps, in each step the best path for each node assuming the target path is only targetPath[0:step]
    based on the preveious step with targetPath[0:step-1], which makes it a dynamic programing approach.
    """
    def doit_dp_1(self, n, roads, names, targetPath):
        """
        :type n: int
        :type roads: List[List[int]]
        :type names: List[str]
        :type targetPath: List[str]
        :rtype: List[int]
        """
        graph = [[] for _ in range(n)]
        for p1, p2 in roads:
            graph[p1].append(p2)
            graph[p2].append(p1)

        dist_dp = [0] * n
        path = [[None] * n for _ in range(len(targetPath))]

        for step in range(len(targetPath)):
            dist_dp_update = [0] * n
            for node in range(n):
                node_dist = float('inf')
                prev_node = None
                for nb in graph[node]:
                    if node_dist > dist_dp[nb]:
                        node_dist = dist_dp[nb]
                        prev_node = nb
                if names[node] != targetPath[step]:
                    node_dist += 1
                dist_dp_update[node] = node_dist
                path[step][node] = prev_node
            dist_dp = dist_dp_update

        min_dist = min(dist_dp)
        min_idx = dist_dp.index(min_dist)
        best_path = [min_idx]
        for step in range(len(targetPath) - 1, 0, -1):
            best_path.append(path[step][best_path[-1]])

        best_path.reverse()
        return best_path

    def doit_dp(self, n, roads, names, targetPath):
        """
        :type n: int
        :type roads: List[List[int]]
        :type names: List[str]
        :type targetPath: List[str]
        :rtype: List[int]
        """
        import collections
        # our path has the same length with the target Path
        path_len = len(targetPath)
        # build graph
        graph = collections.defaultdict(set)
        for road in roads:
            graph[road[0]].add(road[1])
            graph[road[1]].add(road[0])

        # since the first city in the path can be any of the n cities, add a
        # fictitious source city -1 to the graph to start from
        graph[-1] = set(range(n))

        # in a matrix, keep track of paths of length = path_length (columns)
        # that start from each of the n cities (rows)
        # each mat[row][col] contains the next city following city=row at path_index = col
        next_cities = [[-1] * path_len for _ in range(n)]

        # q for BFS
        q = collections.deque()
        # elements in q are tuples (city, path_index)
        # first element is the (fictitious source city, at path index -1)
        q.append((-1, -1))

        while q:
            current_city, current_path_index = q.popleft()
            # if we go to the end of the path, build an answer path
            if current_path_index == path_len - 1:
                ans, prev_index = [], path_len - 1
                while prev_index > -1:
                    ans.append(current_city)
                    # the previous city (at the previous index i) in the path
                    current_city = next_cities[current_city][prev_index]
                    prev_index -= 1
                # path was constructed from the last city on path
                return reversed(ans)
            # if we are not at the end of the path just yet,
            # see what neighbors to visit at next index in the path
            for next_city in graph[current_city]:
                next_tuple = (next_city, current_path_index + 1)
                # don't visit if this city has been considered after the current
                # at this index
                if next_cities[next_tuple[0]][next_tuple[1]] != -1:
                    continue
                # record that we have been here and where we came from
                next_cities[next_tuple[0]][next_tuple[1]] = current_city
                # Now account for edit distance: it can only be 0 or 1
                if names[next_tuple[0]] == targetPath[next_tuple[1]]:
                    # when edit distance is 0, this city has priority for
                    # visiting next
                    q.appendleft(next_tuple)
                else:  # edit distance is 1
                    q.append(next_tuple)

        return []


if __name__ == '__main__':

    MostSimilar().doit_dp(n = 5, roads = [[0,2],[0,3],[1,2],[1,3],[1,4],[2,4]], names = ["ATL","PEK","LAX","DXB","HND"], targetPath = ["ATL","DXB","HND","LAX"])

    MostSimilar().doit_dp(n = 4, roads = [[1,0],[2,0],[3,0],[2,1],[3,1],[3,2]], names = ["ATL","PEK","LAX","DXB"], targetPath = ["ABC","DEF","GHI","JKL","MNO","PQR","STU","VWX"])

    MostSimilar().doit_dp(n = 6, roads = [[0,1],[1,2],[2,3],[3,4],[4,5]], names = ["ATL","PEK","LAX","ATL","DXB","HND"], targetPath = ["ATL","DXB","HND","DXB","ATL","LAX","PEK"])


"""
1059. All Paths from Source Lead to Destination

Given the edges of a directed graph where edges[i] = [ai, bi] indicates there is an edge between nodes ai and bi, and two nodes source and destination of this graph,
determine whether or not all paths starting from source eventually, end at destination, that is:


At least one path exists from the source node to the destination node
If a path exists from the source node to a node with no outgoing edges, then that node is equal to destination.
The number of possible paths from source to destination is a finite number.
Return true if and only if all roads from source lead to destination.



Example 1:


Input: n = 3, edges = [[0,1],[0,2]], source = 0, destination = 2
Output: false
Explanation: It is possible to reach and get stuck on both node 1 and node 2.
Example 2:


Input: n = 4, edges = [[0,1],[0,3],[1,2],[2,1]], source = 0, destination = 3
Output: false
Explanation: We have two possibilities: to end at node 3, or to loop over node 1 and node 2 indefinitely.
Example 3:


Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]], source = 0, destination = 3
Output: true
Example 4:


Input: n = 3, edges = [[0,1],[1,1],[1,2]], source = 0, destination = 2
Output: false
Explanation: All paths from the source node end at the destination node, but there are an infinite number of paths, such as 0-1-2, 0-1-1-2, 0-1-1-1-2, 0-1-1-1-1-2, and so on.
Example 5:


Input: n = 2, edges = [[0,1],[1,1]], source = 0, destination = 1
Output: false
Explanation: There is infinite self-loop at destination node.


Constraints:

1 <= n <= 104
0 <= edges.length <= 104
edges.length == 2
0 <= ai, bi <= n - 1
0 <= source <= n - 1
0 <= destination <= n - 1
The given graph may have self-loops and parallel edges.



"""


class LeadsToDestination:

    def doit_dfs(self, n: int, edges: list, source: int, destination: int) -> bool:

        from collections import defaultdict
        g = defaultdict(set)
        for c1, c2 in edges:
            g[c1].add(c2)

        if len(edges) == 0 and source == destination:
            return True

        if len(g[destination]) != 0 or len(g[source]) == 0:
            return False

        res, infinite, others = False, False, False

        def dfs(node, path):
            nonlocal infinite, others, res
            if others or infinite:
                return

            if len(g[node]) == 0:
                res = (node == destination)
                others = (node != destination)

            for e in g[node]:

                if e in path:
                    infinite = True
                    return

                path.add(e)
                dfs(e, path)
                path.remove(e)

        dfs(source, set([source]))
        return res and not others and not infinite

    def doit_dfs_1(self, n: int, edges: list, source: int, destination: int) -> bool:

        def DFS(node, visited):

            if node == destination:
                if node in graph[node]:
                    return False
                else:
                    return True

            visited.add(node)
            if not graph[node]:
                return False

            isConnected = True
            for nei in graph[node]:
                if nei in visited:
                    return False
                isConnected = isConnected and DFS(nei, visited)

            visited.remove(node)
            return isConnected

        graph = [[] for _ in range(n)]

        for edge in edges:
            graph[edge[0]].append(edge[1])

        if len(graph[destination]) > 0:
            return False

        return DFS(source, set())


if __name__ == '__main__':

    LeadsToDestination().doit_dfs(4, [[0,1],[0,2],[1,3],[2,3]], 0, 3)





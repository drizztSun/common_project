"""
323. Number of Connected Components in an Undirected Graph


Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to find the number of connected components in an undirected graph.

Example 1:

Input: n = 5 and edges = [[0, 1], [1, 2], [3, 4]]

     0          3
     |          |
     1 --- 2    4

Output: 2
Example 2:

Input: n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]]

     0           4
     |           |
     1 --- 2 --- 3

Output:  1
Note:
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
"""
from collections import defaultdict, deque


class CountComponents:

    def doit_dfs(self, n: int, edges) -> int:

        pos = [i for i in range(n)]
        graph = defaultdict(list)

        for c in edges:
            graph[c[0]].append(c[1])
            graph[c[1]].append(c[0])

        for i in range(n):

            if pos[i] != i:
                continue

            queue = deque([i])

            while queue:

                nextstep = queue.popleft()
                pos[nextstep] = i

                for s in graph[nextstep]:
                    if pos[s] != s:
                        continue
                    queue.append(s)

        return sum([1 if pos[c] == c else 0 for c in range(n)])

    def doit(self, n: int, edges):

        graph = defaultdict(list)
        for i in edges:
            graph[i[0]].append(i[1])
            graph[i[1]].append(i[0])

        def dfs(v, visited):
            visited[v] = True
            for i in graph[v]:
                if visited[i] == False:
                    dfs(i, visited)

        cnt = 0
        visited = [False] * n
        for i in range(n):

            if visited[i] == False:
                dfs(i, visited)
                cnt += 1
        return cnt


if __name__ == '__main__':

    res = CountComponents().doit_dfs(n = 5,  edges = [[0, 1], [1, 2], [3, 4]])

    res = CountComponents().doit_dfs(n = 5, edges = [[0, 1], [1, 2], [2, 3], [3, 4]])
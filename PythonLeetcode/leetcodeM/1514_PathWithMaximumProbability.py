"""
1514. Path with Maximum Probability

You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of traversing that edge succProb[i].

Given two nodes start and end, find the path with the maximum probability of success to go from start to end and return its success probability.

If there is no path from start to end, return 0. Your answer will be accepted if it differs from the correct answer by at most 1e-5.



Example 1:



Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.
Example 2:



Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
Output: 0.30000
Example 3:



Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.


Constraints:

2 <= n <= 10^4
0 <= start, end < n
start != end
0 <= a, b < n
a != b
0 <= succProb.length == edges.length <= 2*10^4
0 <= succProb[i] <= 1
There is at most one edge between every two nodes.

"""


class MaxProbabilityPath:

    def doit_heap_dijstra(self, n: int, edges: list, succProb: list, start: int, end: int) -> float:

        from collections import defaultdict
        from heapq import heappush, heappop

        graph = defaultdict(lambda : defaultdict(int))

        for i in range(len(edges)):
            s, e = edges[i][0], edges[i][1]
            graph[s][e] = succProb[i]
            graph[e][s] = succProb[i]

        buff = [(-1, start)]
        visited = {start: 1}

        while buff:

            p, s = heappop(buff)
            p = -p

            if s in visited and visited[s] > p: continue

            if s == end: return p

            visited[s] = p

            for n, p1 in graph[s].items():
                if n not in visited:
                    heappush(buff, (-p * p1, n))

        return 0.0

    def doit_heap_dijstra_1(self, n: int, edges: list, succProb: list, start: int, end: int) -> float:

        from collections import defaultdict
        from heapq import heappush, heappop

        graph = defaultdict(lambda : defaultdict(int))

        for i in range(len(edges)):
            s, e = edges[i][0], edges[i][1]
            graph[s][e] = succProb[i]
            graph[e][s] = succProb[i]

        buff = [(-1, start)]
        visited = set()

        while buff:

            p, s = heappop(buff)
            p = -p
            visited.add(s)

            if s == end: return p

            for n, p1 in graph[s].items():
                if n not in visited:
                    heappush(buff, (-p * p1, n))

        return 0.0


if __name__ == '__main__':

    MaxProbabilityPath().doit_heap_dijstra(3, [[0,1],[1,2],[0,2]], [0.5,0.5,0.2], 0, 2)

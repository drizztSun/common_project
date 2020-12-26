"""
1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree

Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti]
represents a bidirectional and weighted edge between nodes ai and bi.
A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.

Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST).
An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge.
On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.

Note that you can return the indices of the edges in any order.



Example 1:



Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
Output: [[0,1],[2,3,4,5]]
Explanation: The figure above describes the graph.
The following figure shows all the possible MSTs:

Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
Example 2:



Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
Output: [[],[0,1,2,3]]
Explanation: We can observe that since all 4 edges have equal weight, choosing any 3 edges from the given 4 will yield an MST. Therefore all 4 edges are pseudo-critical.


Constraints:

2 <= n <= 100
1 <= edges.length <= min(200, n * (n - 1) / 2)
edges[i].length == 3
0 <= ai < bi < n
1 <= weighti <= 1000
All pairs (ai, bi) are distinct.



"""


class CriticalAndPseudoCriticalEdges:

    class DSU:

        def __init__(self, n):
            self._parent = [i for i in range(n)]
            self._rank = [0] * n

        def find(self, x):
            while x != self._parent[x]:
                self._parent[x] = self._parent[self._parent[x]]
                x = self._parent[x]
            return x

        def union(self, a, b):
            pa, pb = self.find(a), self.find(b)
            if pa == pb:
                return False

            if self._rank[pa] == self._rank[pb]:
                self._parent[pa] = pb
                self._rank[pb] += 1
            elif self._rank[pa] > self._rank[pb]:
                self._parent[pb] = pa
            else:
                self._parent[pa] = pb
            return True

    def doit_mst(self, n: int, edges: list) -> list:

        for i in range(len(edges)):
            edges[i].append(i)

        edges.sort(key=lambda x: (x[2], x[0]))

        def buildMST(exclude=-1, include=-1):
            du = CriticalAndPseudoCriticalEdges.DSU(n)
            cost, lines = 0, 0

            if include != -1:
                du.union(edges[include][0], edges[exclude][1])
                cost += edges[include][2]
                lines += 1

            for i in range(len(edges)):
                if i == exclude:
                    continue

                if du.union(edges[i][0], edges[i][1]):
                    cost += edges[i][2]
                    lines += 1

            return float('inf') if lines != n - 1 else cost

        min_cost = buildMST()
        critical, pesudo_critical = [], []

        for i in range(len(edges)):
            if buildMST(i, -1) > min_cost:
                critical.append(edges[i][3])
            elif buildMST(-1, i) == min_cost:
                pesudo_critical.append(edges[i][3])

        return [critical, pesudo_critical]


if __name__ == '__main__':

    CriticalAndPseudoCriticalEdges().doit_mst(5, [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]])











"""
1579. Remove Max Number of Edges to Keep Graph Fully Traversable

Alice and Bob have an undirected graph of n nodes and 3 types of edges:

Type 1: Can be traversed by Alice only.
Type 2: Can be traversed by Bob only.
Type 3: Can by traversed by both Alice and Bob.
Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi,
find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob.
The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.

Return the maximum number of edges you can remove, or return -1 if it's impossible for the graph to be fully traversed by Alice and Bob.



Example 1:



Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
Output: 2
Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
Example 2:



Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
Output: 0
Explanation: Notice that removing any edge will not make the graph fully traversable by Alice and Bob.
Example 3:



Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
Output: -1
Explanation: In the current graph, Alice cannot reach node 4 from the other nodes. Likewise, Bob cannot reach 1. Therefore it's impossible to make the graph fully traversable.




Constraints:

1 <= n <= 10^5
1 <= edges.length <= min(10^5, 3 * n * (n-1) / 2)
edges[i].length == 3
1 <= edges[i][0] <= 3
1 <= edges[i][1] < edges[i][2] <= n
All tuples (typei, ui, vi) are distinct.


"""


class MaxNumEdgesToRemove:

    class DSU:

        def __init__(self, n):
            self._parent = [i for i in range(n+1)]
            self._e = 0

        def find(self, x):
            while x != self._parent[x]:
                self._parent[x] = self._parent[self._parent[x]]
                x = self._parent[x]
            return x

        def union(self, a, b):
            pa, pb = self.find(a), self.find(b)
            if pa == pb:
                return 1

            self._parent[pa] = pb
            self._e += 1
            return 0

    def doit_mst(self, n: int, edges: list) -> int:

        da, db = MaxNumEdgesToRemove.DSU(n), MaxNumEdgesToRemove.DSU(n)
        ans = 0

        for c in edges:
            if c[0] != 3:
                continue
            ans += da.union(c[1], c[2])
            db.union(c[1], c[2])

        for c in edges:
            if c[0] == 3:
                continue

            if c[0] == 1:
                ans += da.union(c[1], c[2])
            else:
                ans += db.union(c[1], c[2])

        return ans if da._e == n-1 and db._e == n-1 else -1








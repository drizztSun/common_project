"""
# 847. Shortest Path Visiting All Nodes

# An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.

# graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.

# Return the length of the shortest path that visits every node. You may start and stop at any node,
# you may revisit nodes multiple times, and you may reuse edges.



# Example 1:

# Input: [[1,2,3],[0],[0],[0]]
# Output: 4
# Explanation: One possible path is [1,0,2,0,3]

# Example 2:

# Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
# Output: 4
# Explanation: One possible path is [0,1,4,2,3]


# Note:

# 1 <= graph.length <= 12
# 0 <= graph[i].length < graph.length
"""


class ShortestPathLength:

    """
    Approach #1: Breadth First Search [Accepted]
    Intuition

    A path 'state' can be represented as the subset of nodes visited, plus the current 'head' node.
    Then, the problem reduces to a shortest path problem among these states, which can be solved with a breadth-first search.

    Algorithm

    Let's call the set of nodes visited by a path so far the cover, and the current node as the head.
    We'll store the cover states using set bits: k is in the cover if the kth bit of cover is 1.
    For states state = (cover, head), we can perform a breadth-first search on these states.
    The neighbors are (cover | (1 << child), child) for each child in graph[head].
    If at any point we find a state with all set bits in it's cover, because it is a breadth-first search,
    we know this must represent the shortest path length.
    Complexity Analysis

    Time Complexity: O(2^N * N)
    Space Complexity: O(2^N * N)
    """
    def doit_bfs(self, graph):

        from collections import deque, defaultdict
        N = len(graph)
        queue = deque((1 << x, x) for x in range(N))
        dist = defaultdict(lambda: N*N)
        for x in range(N):
            dist[1 << x, x] = 0

        while queue:
            cover, head = queue.popleft()
            d = dist[cover, head]
            if cover == 2**N - 1: return d
            for child in graph[head]:
                cover2 = cover | (1 << child)
                if d + 1 < dist[cover2, child]:
                    dist[cover2, child] = d + 1
                    queue.append((cover2, child))

    """
    Approach #2: Dynamic Programming [Accepted]
    Intuition
    
    A path 'state' can be represented as the subset of nodes visited, plus the current 'head' node. As in Approach #1, we have a recurrence in states: answer(cover, head) is min(1 + answer(cover | (1<<child), child) for child in graph[head]). Because these states form a DAG (a directed graph with no cycles), we can do dynamic programming.
    
    Algorithm
    
    Let's call the set of nodes visited by a path so far the cover, and the current node as the head. We'll store dist[cover][head] 
    as the length of the shortest path with that cover and head. We'll store the cover states using set bits, and maintain the loop invariant (on cover), that dist[k][...] is correct for k < cover.
    
    For every state (cover, head), the possible next (neighbor) nodes in the path are found in graph[head]. The new cover2 is the old cover plus next.
    
    For each of these, we perform a "relaxation step" (for those familiar with the Bellman-Ford algorithm), 
    where if the new candidate distance for dist[cover2][next] is larger than dist[cover][head] + 1, we'll update it to dist[cover][head] + 1.
    
    Care must be taken to perform the relaxation step multiple times on the same cover if cover = cover2. 
    This is because a minimum state for dist[cover][head] might only be achieved through multiple steps through some path.
    
    Finally, it should be noted that we are using implicitly the fact that when iterating cover = 0 .. (1<<N) - 1, that each new cover cover2 = cover | 1 << x is such that cover2 >= cover. This implies a topological ordering, which means that the recurrence on these states form a DAG.
    """
    def doit_dp_1(self, graph):
        N = len(graph)
        dist = [[float('inf')] * N for i in range(1 << N)]
        for x in range(N):
            dist[1<<x][x] = 0

        for cover in range(1 << N):
            repeat = True
            while repeat:
                repeat = False
                for head, d in enumerate(dist[cover]):
                    for nei in graph[head]:
                        cover2 = cover | (1 << nei)
                        if d + 1 < dist[cover2][nei]:
                            dist[cover2][nei] = d + 1
                            if cover == cover2:
                                repeat = True

        return min(dist[2**N - 1])

    def doit(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        N, M = len(graph), 2 << len(graph) >> 1
        status = [(2 << i >> 1, i) for i in range(N)]
        res = [[0 for _ in range(N)] for _ in range(M)]

        while status:
            
            cover, now = status.pop(0)
            if cover == M - 1:
                return res[cover][now] 

            for c in graph[now]:
                nnow, ncover = c, cover
                if (ncover >> nnow) % 2 != 1:
                    ncover += (2 << nnow >> 1)
                
                if res[ncover][nnow] == 0:
                    res[ncover][nnow] = res[cover][now] + 1
                    status.append((ncover, nnow))
        return -1


if __name__ == "__main__":

    res = ShortestPathLength().doit([[1,2,3],[0],[0],[0]])

    res = ShortestPathLength().doit([[2,3,4,8],[8],[0],[0,8],[0,5,6],[4,7],[4],[5],[0,3,1]])

    res = ShortestPathLength().doit([[1],[0,2,4],[1,3,4],[2],[1,2]])

    pass
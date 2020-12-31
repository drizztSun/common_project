"""
785. Is Graph Bipartite?

Given an undirected graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split its set of nodes into two independent subsets A and B, such that every edge in the graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.



Example 1:


Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Output: true
Explanation: We can divide the vertices into two groups: {0, 2} and {1, 3}.

Example 2:


Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
Output: false
Explanation: We cannot find a way to divide the set of nodes into two independent subsets.



Constraints:

1 <= graph.length <= 100
0 <= graph[i].length < 100
0 <= graph[i][j] <= graph.length - 1
graph[i][j] != i
All the values of graph[i] are unique.
The graph is guaranteed to be undirected.

"""


class isBipartite:

    """
    Approach #1: Coloring by Depth-First Search [Accepted]
    Intuition

    Color a node blue if it is part of the first set, else red. We should be able to greedily color the graph if and only if it is bipartite: one node being blue implies all it's neighbors are red, all those neighbors are blue, and so on.


    Diagram of coloring neighbors of nodes

    Algorithm

    We'll keep an array (or hashmap) to lookup the color of each node: color[node]. The colors could be 0, 1, or uncolored (-1 or null).

    We should be careful to consider disconnected components of the graph, by searching each node. For each uncolored node, we'll start the coloring process by doing a depth-first-search on that node. Every neighbor gets colored the opposite color from the current node. If we find a neighbor colored the same color as the current node, then our coloring was impossible.

    To perform the depth-first search, we use a stack. For each uncolored neighbor in graph[node], we'll color it and add it to our stack, which acts as a sort of "todo list" of nodes to visit next. Our larger loop for start... ensures that we color every node. Here is a visual dry-run of the algorithm whose Python code is below.

    Complexity Analysis

    Time Complexity: O(N+E), where NN is the number of nodes in the graph, and EE is the number of edges. We explore each node once when we transform it from uncolored to colored, traversing all its edges in the process.

    Space Complexity: O(N), the space used to store the color.

    """

    def doit_dfs(self, graph: list) -> bool:

        color = {}
        for node in range(len(graph)):
            if node not in color:
                stack = [node]
                color[node] = 0

                while stack:
                    node = stack.pop()
                    for nei in graph[node]:
                        if nei not in color:
                            stack.append(nei)
                            color[nei] = color[node] ^ 1
                        elif color[nei] == color[node]:
                            return False
        return True
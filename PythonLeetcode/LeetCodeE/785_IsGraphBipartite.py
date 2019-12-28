# 785. Is Graph Bipartite

# Given an undirected graph, return true if and only if it is bipartite.

# Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in the graph has one node in A and another node in B.

# The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.
# There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.

# Example 1:
# Input: [[1,3], [0,2], [1,3], [0,2]]
# Output: true
# Explanation:
# The graph looks like this:
# 0----1
# |    |
# |    |
# 3----2
# We can divide the vertices into two groups: {0, 2} and {1, 3}.

# Example 2:
# Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
# Output: false
# Explanation:
# The graph looks like this:
# 0----1
# | \  |
# |  \ |
# 3----2
# We cannot find a way to divide the set of nodes into two independent subsets.


# Note:

# graph will have length in range [1, 100].
# graph[i] will contain integers in range [0, graph.length - 1].
# graph[i] will not contain i or duplicate values.
# The graph is undirected: if any element j is in graph[i], then i will be in graph[j].

from collections import defaultdict


class IsBipartite:

    def doit(self, graph):
        group = [0] * len(graph)
        for i in range(len(graph)):
            if group[i] == 0:
                group[i] = 1
                stack = [i]
                while stack:
                    cur = stack.pop()
                    for c in graph[cur]:
                        if group[c] == 0:
                            group[c] = -group[cur]
                            stack.append(c)
                        elif group[c] == group[cur]:
                            return False
        return True

    def doit1(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: bool
        """
        N = len(graph)

        left, right = set(), set()

        for i in range(N):

            if i not in left and i not in right:
                left.add(i)

            be_left = i in left
            for j in graph[i]:
                if j not in right or j not in left:
                    if be_left:
                        right.add(j)
                    else:
                        left.add(j)
                else:
                    if (j in left and be_left) or (j in right and not be_left):
                        return False

        return len(left) + len(right) == N

    def doit(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: bool
        """
        def dfs(g, color, n, c):
            if color[n] != 0:
                return c == color[n]

            color[n] = c
            for i in g[n]:
                if color[i] == c:
                    return False

                if color[i] == 0 and not dfs(g, color, i, -c):
                    return False

            return True

        g = defaultdict(list)
        for i in range(len(graph)):
            for c in graph[i]:
                g[i].append(c)
                g[c].append(i)

        colors = [0] * len(graph)

        for k in range(len(graph)):
            if colors[k] == 0 and not dfs(g, colors, k, 1):
                return False

        return True


if __name__ == '__main__':

    res = IsBipartite().doit1([[1, 3], [0, 2], [1, 3], [0, 2]])

    res = IsBipartite().doit1([[1, 2, 3], [0, 2], [0, 1, 3], [0, 2]])

    res = IsBipartite().doit1([[1], [0], [4], [4], [2, 3]])

    res = IsBipartite().doit([[1, 2, 3], [0, 2], [0, 1, 3], [0, 2]])

    res = IsBipartite().doit([[4, 1], [0, 2], [1, 3], [2, 4], [3, 0]])

    pass

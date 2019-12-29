# 797. All Paths From Source to Target

# Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0 to node N-1, and return them in any order.

# The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.  graph[i] is a list of all nodes j for which the edge (i, j) exists.

# Example:
# Input: [[1,2], [3], [3], []]
# Output: [[0,1,3],[0,2,3]]
# Explanation: The graph looks like this:
# 0--->1
# |    |
# v    v
# 2--->3
# There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
# Note:

# The number of nodes in the graph will be in the range [2, 15].
# You can print different paths in any order, but you should keep the order of nodes inside one path.


class AllPathsSourceTarget:

    def doit(self, graph):

        def dfs(c, visited):
            if c in buff:
                return buff[c]

            if c == N-1:
                return [[N-1]]

            res = []
            for n in graph[c]:
                if visited[n]:
                    continue
                visited[n] = True
                for path in dfs(n, visited):
                    res.append([c] + path)
                visited[n] = False

            buff[c] = res
            return res

        buff = {}
        N = len(graph)
        visited = [False for _ in range(N)]
        visited[0] = True
        return dfs(0, visited)

    def doit(self, graph):
        allpaths = []
        def recurse(v, edges, currpath, allpaths):

            if edges[v] == []:
                allpaths.append(currpath+[v])
                currpath = []

            for n in edges[v]:
                recurse(n, edges, currpath+[v], allpaths)

        recurse(0, graph, [], allpaths)
        return allpaths


if __name__ == '__main__':

    res = AllPathsSourceTarget().doit(
        [[1, 2], [3], [3], []])  # [[0,1,3],[0,2,3]]

    pass

# 802. Find Eventual Safe States

# In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  
# If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.

# Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  
# More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped at a terminal node in less than K steps.

# Which nodes are eventually safe?  Return them as an array in sorted order.

# The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  
# The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.

# Example:
# Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
# Output: [2,4,5,6]
# Here is a diagram of the above graph.

# Illustration of graph

# Note:

# graph will have length at most 10000.
# The number of edges in the graph will not exceed 32000.
# Each graph[i] will be a sorted list of different integers, chosen within the range [0, graph.length - 1].

class EventualSafeNodes(object):

    def doit(self, graph):
        v = [0]*len(graph)
        def dfs(i):
            v[i] = 1
            for e in graph[i]:
                if v[e] == 0 and not dfs(e) or v[e] == 1:  
                    return False
            v[i] = 2
            return True
        for i in range(len(graph)):
            if v[i] == 0: 
                dfs(i)

        return [ i for i in range(len(graph)) if v[i] == 2]

    def doit1(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: List[int]
        """
        N = len(graph)
        res = [True if len(graph[i]) == 0 else False for i in range(N) ]
        nontermial = [False] * N

        def dfs(n, visited):
            if res[n]:
                return True

            if visited[n] or nontermial[n]:
                nontermial[n] = True
                return False

            visited[n] = True
            for c in graph[n]:
                if not dfs(c, visited):
                    nontermial[c] = True
                    break
            else:
                res[n] = True

            visited[n] = False
            return res[n]

        visited = [False] * N
        for i in range(N):
            dfs(i, visited)

        return [i for i in range(N) if res[i]]


if __name__ == '__main__':

    res = EventualSafeNodes().doit([[1,2],[2,3],[5],[0],[5],[],[]]) # [2,4,5,6]

    pass

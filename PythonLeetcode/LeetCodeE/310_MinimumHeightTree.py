
# 310. Minimum Height Trees
# For a undirected graph with tree characteristics, we can choose any node as the root. 
# The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). 
# Given such a graph, write a function to find all the MHTs and return a list of their root labels.

# Format
# The graph contains n nodes which are labeled from 0 to n - 1. 
# You will be given the number n and a list of undirected edges (each edge is a pair of labels).

# You can assume that no duplicate edges will appear in edges. 
# Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

# Example 1:

# Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]

#        0
#        |
#        1
#       / \
#      2   3
# return [1]

# Example 2:

# Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

#     0  1  2
#      \ | /
#        3
#        |
#        4
#        |
#        5
# return [3, 4]



class Graph:

    def __init__(self, n, edges):

        self.V = n

        self.degree = [0 for _ in range(self.V)]

        self.edges = [[] for _ in range(self.V)]

        for c in edges:

            self.degree[c[0]] += 1
            self.degree[c[1]] += 1

            self.edges[c[0]].append(c[1])
            self.edges[c[1]].append(c[0])

    def minHighTree(self):

        if self.V == 1:
            return [0]

        level = []
        for i in range(len(self.degree)):
            if self.degree[i] == 1:
                level.append(i)

        nums = self.V
        while nums > 2:
            nums -= len(level)
            tmp = []

            for i in level:
                for c in self.edges[i]:
                    self.degree[c] -= 1
                    if self.degree[c] == 1:
                        tmp.append(c)
            level = tmp
             
        return level
                
        
class findMinHeightTreesII:

    def doit(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        g = Graph(n, edges)

        return g.minHighTree()    



class findMinHeightTrees:

    # TLE
    def doitN(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        def iterateGraph(i, edges, nodes, dep = 0):
           if i in nodes:
                return dep

           nodes.add(i)
           
           if not edges[i]:
               return dep 
           
           maxV = 0
           for j in edges[i]:
                if j in nodes:
                    continue
                maxV = max(maxV, iterateGraph(j, edges, nodes, dep+1))
                
           nodes.remove(i)

           return dep if maxV == 0 else maxV



        nodes = [x for x in range(n)]
        result = [[] for _ in range(n+1)]       
        newEdges = [[] for _ in range(n)]

        for x in edges:
            newEdges[x[0]].append(x[1])
            newEdges[x[1]].append(x[0])                    

        for i in nodes:
            result[iterateGraph(i, newEdges, set())].append(i)

        i = 0
        while i < len(result) - 1 and not result[i]:
            i += 1
  
        return result[i]




    def doit1(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        if n == 1:
            return [0]

        import collections
        newEdges = collections.defaultdict(list)
        degrees = collections.defaultdict(int)

        for c in edges:
            degrees[c[1]] += 1
            degrees[c[0]] += 1

            newEdges[c[0]].append(c[1])
            newEdges[c[1]].append(c[0])
        
        #nodes = collections.deque()
        prelevel, unvisited = [], set(range(n))
        for i in range(n):
            if degrees[i] == 1:
                prelevel.append(i)


        while len(unvisited) > 2:
            tmp = []
            for c in prelevel:
                unvisited.remove(c)
                for e in newEdges[c]:
                    if e in unvisited:
                        degrees[e] -= 1
                        if degrees[e] == 1:
                            tmp.append(e)
            prelevel = tmp

        return prelevel
                       

    def doit(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        if n == 1: 
            return [0] 

        adj = [set() for _ in range(n)]
        for i, j in edges:
            adj[i].add(j)
            adj[j].add(i)

        leaves = [i for i in range(n) if len(adj[i]) == 1]

        while n > 2:
            n -= len(leaves)
            newLeaves = []
            for i in leaves:
                j = adj[i].pop()
                adj[j].remove(i)
                if len(adj[j]) == 1: 
                    newLeaves.append(j)
            leaves = newLeaves
        return leaves        


if __name__=="__main__":

    res = findMinHeightTreesII().doit(1, [])

    res = findMinHeightTreesII().doit(4, [[1, 0], [1, 2], [1, 3]])

    res = findMinHeightTreesII().doit(6, [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]])

    res = findMinHeightTreesII().doit(6, [[0,1],[0,2],[0,3],[3,4],[4,5]])

    pass
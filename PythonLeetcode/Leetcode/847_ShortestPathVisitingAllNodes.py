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

class ShortestPathLength:

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

    # BFS <TLE>
    def doit0(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        N = len(graph)
        st = [(i, 0, set([i])) for i in range(len(graph))]
        cache = set()

        while st:
            
            i, s, g = st.pop(0)
            if len(g) == N:
                return s

            for n in graph[i]:
                f = set(g)
                f.add(n)
                if (n, list(f)) not in cache:
                    st.append((n, s + 1, f))

        return -1

    # BFS <TLE>
    def doit10(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: int
        """
        duSeq = [i for i in range(len(graph))]
        duSeq.sort(key=lambda i : len(graph[i]))
        count = float('inf')
        N = len(graph)

        for i in range(len(duSeq)):
            
            st = [(i, 0, set([i]))]

            while st:
                i, s, g = st.pop(0)
                if len(g) == N:
                    count = min(count, s)
                
                if s >= count:
                    continue    

                for n in graph[i]:
                    f = set(g)
                    f.add(n)
                    st.append((n, s + 1, f))
        
        return count


if __name__ == "__main__":

    res = ShortestPathLength().doit([[1,2,3],[0],[0],[0]])

    res = ShortestPathLength().doit([[2,3,4,8],[8],[0],[0,8],[0,5,6],[4,7],[4],[5],[0,3,1]])

    res = ShortestPathLength().doit([[1],[0,2,4],[1,3,4],[2],[1,2]])

    pass
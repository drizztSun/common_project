"""
1443. Minimum Time to Collect All Apples in a Tree


Given an undirected tree consisting of n vertices numbered from 0 to n-1, which has some apples in their vertices. You spend 1 second to walk over one edge of the tree. 
Return the minimum time in seconds you have to spend to collect all apples in the tree, starting at vertex 0 and coming back to this vertex.

The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and bi. Additionally, there is a boolean array hasApple, 
where hasApple[i] = true means that vertex i has an apple; otherwise, it does not have any apple.

 

Example 1:



Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
Output: 8 
Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect all apples is shown by the green arrows.  
Example 2:



Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,false,true,false]
Output: 6
Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect all apples is shown by the green arrows.  
Example 3:

Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,false,false,false,false,false]
Output: 0
 

Constraints:

1 <= n <= 10^5
edges.length == n - 1
edges[i].length == 2
0 <= ai < bi <= n - 1
fromi < toi
hasApple.length == n

"""


class MinimumTimeToCollectApples:

    def minTime(self, n: int, edges: list, hasApple: list) -> int:
        from collections import defaultdict, deque
        graph = defaultdict(list)
        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])
        
        visited = set()
        
        def dfs(node):
            
            if node in visited: return 0
            
            visited.add(node)

            sec = 0
            for c in graph[node]:
                sec += dfs(c)
                
            return (sec + 2) if sec > 0 or hasApple[node] else 0
        
        return max(dfs(0)-2, 0)
        
    def doit_topsort(self, n: int, edges: list, hasApple: list) -> int:
        from collections import defaultdict, deque
        graph = defaultdict(list)
        degrees = [0 for _ in range(n)]
        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])
            
            degrees[edge[0]] += 1
            degrees[edge[1]] += 1
            
        leaves_no_apple = deque([i for i, c in enumerate(degrees) if c == 1 and i != 0 and not hasApple[i]])
        
        while leaves_no_apple:
            
            size = len(leaves_no_apple)
            
            for _ in range(size):
                
                c = leaves_no_apple.popleft()
                degrees[c] -= 1
                if not graph[c]: continue
                p = graph[c].pop()
                degrees[p] -= 1
                graph[p].remove(c)
                if p != 0 and degrees[p] == 1 and not hasApple[p]:
                    leaves_no_apple.append(p)
                    
        return sum(2 for c in range(n) if c != 0 and degrees[c] != 0)


if __name__ == '__main__':

    MinimumTimeToCollectApples().doit_(n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [False,False,True,False,True,True,False])

    MinimumTimeToCollectApples().doit_(n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [False,False,False,False,False,False,False])

    MinimumTimeToCollectApples().doit_(6, [[0,1],[1,2],[2,3],[3,4],[1,5]], [False,False,False,False,False,True])
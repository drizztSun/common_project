"""
1462. Course Schedule IV

There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have direct prerequisites, for example, to take course 0 you have first to take course 1, which is expressed as a pair: [1,0]

Given the total number of courses n, a list of direct prerequisite pairs and a list of queries pairs.

You should answer for each queries[i] whether the course queries[i][0] is a prerequisite of the course queries[i][1] or not.

Return a list of boolean, the answers to the given queries.

Please note that if course a is a prerequisite of course b and course b is a prerequisite of course c, then, course a is a prerequisite of course c.

 

Example 1:


Input: n = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
Output: [false,true]
Explanation: course 0 is not a prerequisite of course 1 but the opposite is true.
Example 2:

Input: n = 2, prerequisites = [], queries = [[1,0],[0,1]]
Output: [false,false]
Explanation: There are no prerequisites and each course is independent.
Example 3:


Input: n = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
Output: [true,true]
Example 4:

Input: n = 3, prerequisites = [[1,0],[2,0]], queries = [[0,1],[2,0]]
Output: [false,true]
Example 5:

Input: n = 5, prerequisites = [[0,1],[1,2],[2,3],[3,4]], queries = [[0,4],[4,0],[1,3],[3,0]]
Output: [true,false,true,false]
 

Constraints:

2 <= n <= 100
0 <= prerequisite.length <= (n * (n - 1) / 2)
0 <= prerequisite[i][0], prerequisite[i][1] < n
prerequisite[i][0] != prerequisite[i][1]
The prerequisites graph has no cycles.
The prerequisites graph has no repeated edges.
1 <= queries.length <= 10^4
queries[i][0] != queries[i][1]



"""



from collections import defaultdict


class CheckIfPrerequisite:
    
    def doit_dfs(self, n: int, prerequisites: list, queries: list) -> list:
        from collections import defaultdict
        from functools import lru_cache

        d = defaultdict(list)
        for x, y in prerequisites:
            d[x] += y,
        
        @lru_cache(None)
        def dfs(x, y):
            if x == y: return True
            return any(dfs(n, y) for n in d[x])
        
        return [dfs(x, y) for x, y in queries]

    """
        // time O(e*v + queries.size()) , e == # of edges , v = #of vertices
        /*  approach :
            --> visit vertices on topological sorting order
            --> create a 2d boolean array of size n*n where array[i][j]==true means i has a pre req of j
            --> find all prereq of a course .
            --> prereq of current course is : all prereq of its parent course + all parent course
        */
    """

    def doit_topsort(self, n:int, prerequisites: list, queries: list) -> int:
        
        from collections import defaultdict, deque
        
        graph = defaultdict(list)
        indegree = [0 for _ in range(n)]
        related = [[False for _ in range(n)] for _ in range(n)]

        for c1, c2 in prerequisites:
            graph[c1].append(c2)
            related[c1][c2] = True
            indegree[c2] += 1

        
        queue = deque([i for i in range(n) if indegree[i] == 0])

        while queue:

            cur = queue.popleft()

            for child in graph[cur]:

                indegree[child] -= 1

                for i in range(n):
                    if i != cur and related[i][cur]:
                        related[i][child] = True

                if indegree[child] == 0:
                    queue.append(child)


        return [related[s][e] for s, e in queries]

    def checkIfPrerequisite(self, n: int, A: List[List[int]], Q: List[List[int]]) -> List[bool]:
        import collections
        class UF:
            def __init__(self, n):
                self.p=collections.defaultdict(set)
                for i in range(n):
                    self.p[i].add(i)
            def union(self,x,y):
                self.p[x]|=self.p[y]
            def q(self,x,y):
                return y in self.p[x]

        uf=UF(n)
        for dep,cur in A:
            uf.union(cur,dep)
        return [uf.q(*reversed(q)) for q in Q]
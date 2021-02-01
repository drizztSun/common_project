"""
1743. Restore the Array From Adjacent Pairs


There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.

You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.

It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.

Return the original array nums. If there are multiple solutions, return any of them.



Example 1:

Input: adjacentPairs = [[2,1],[3,4],[3,2]]
Output: [1,2,3,4]
Explanation: This array has all its adjacent pairs in adjacentPairs.
Notice that adjacentPairs[i] may not be in left-to-right order.
Example 2:

Input: adjacentPairs = [[4,-2],[1,4],[-3,1]]
Output: [-2,4,1,-3]
Explanation: There can be negative numbers.
Another solution is [-3,1,4,-2], which would also be accepted.
Example 3:

Input: adjacentPairs = [[100000,-100000]]
Output: [100000,-100000]


Constraints:

nums.length == n
adjacentPairs.length == n - 1
adjacentPairs[i].length == 2
2 <= n <= 105
-105 <= nums[i], ui, vi <= 105
There exists some nums that has adjacentPairs as its pairs.

"""


class RestoreArray:

    def doit_(self, adjacentPairs: list) -> list:

        from collections import defaultdict
        graph = defaultdict(list)
        ones = set()

        for i, c in enumerate(adjacentPairs):
            graph[c[0]].append(c[1])
            graph[c[1]].append(c[0])

            for d in c:
                if d not in ones:
                    ones.add(d)
                else:
                    ones.remove(d)

        ones = list(ones)
        cur = graph[ones[0]][0]
        ans = [ones[0]]

        while True:
            ans.append(cur)
            if cur == ones[1]:
                break
            c1, c2 = graph[cur]
            cur = c1 if ans[-2] == c2 else c2

        return ans

    def doit_dfs(self, adjacentPairs: list) -> list:
        from collections import defaultdict

        def dfs(u):
            res.append(u)
            visited[u] = True
            for v in adj[u]:
                if not visited[v]:
                    dfs(v)

        adj = defaultdict(list)
        for u, v in adjacentPairs:
            adj[u].append(v)
            adj[v].append(u)

        edges = [x for x in adj if len(adj[x]) == 1]
        visited = {x: False for x in adj}
        res = []
        dfs(edges[0])

        return res
"""
1766. Tree of Coprimes


There is a tree (i.e., a connected, undirected graph that has no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. Each node has a value associated with it, and the root of the tree is node 0.

To represent this tree, you are given an integer array nums and a 2D array edges. Each nums[i] represents the ith node's value, and each edges[j] = [uj, vj] represents an edge between nodes uj and vj in the tree.

Two values x and y are coprime if gcd(x, y) == 1 where gcd(x, y) is the greatest common divisor of x and y.

An ancestor of a node i is any other node on the shortest path from node i to the root. A node is not considered an ancestor of itself.

Return an array ans of size n, where ans[i] is the closest ancestor to node i such that nums[i] and nums[ans[i]] are coprime, or -1 if there is no such ancestor.



Example 1:



Input: nums = [2,3,3,2], edges = [[0,1],[1,2],[1,3]]
Output: [-1,0,0,1]
Explanation: In the above figure, each node's value is in parentheses.
- Node 0 has no coprime ancestors.
- Node 1 has only one ancestor, node 0. Their values are coprime (gcd(2,3) == 1).
- Node 2 has two ancestors, nodes 1 and 0. Node 1's value is not coprime (gcd(3,3) == 3), but node 0's
  value is (gcd(2,3) == 1), so node 0 is the closest valid ancestor.
- Node 3 has two ancestors, nodes 1 and 0. It is coprime with node 1 (gcd(3,2) == 1), so node 1 is its
  closest valid ancestor.
Example 2:



Input: nums = [5,6,10,2,3,6,15], edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
Output: [-1,0,-1,0,0,0,-1]


Constraints:

nums.length == n
1 <= nums[i] <= 50
1 <= n <= 105
edges.length == n - 1
edges[j].length == 2
0 <= uj, vj < n
uj != vj

"""


class Coprimes:

    """
          这道题目考察的范围还是挺广的。基本方法是建图+DFS。但brute force做的话，当tree是一个list的时候，时间复杂度会退化到O(n^2)。本题切入点是nums[i]的取值范围很小，只有1-50。可以预先计算coprimes。
          然后DFS，用stack存储当前路径上每个num出现的深度和结点编号，对于当前结点，枚举它所有的coprimes，看看最后一次出现的祖先节点是哪个。

          Time complexity: O(n*50)
          Space complexity: O(n)
    """
    def doit_dfs(self, nums: List[int], edges: List[List[int]]) -> List[int]:

        from math import gcd
        from collections import defaultdict

        graph = defaultdict(list)

        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])

        kmax = 50
        coprimes = [set() for i in range(kmax + 1)]
        for i in range(1, kmax + 1):
            for j in range(1, kmax + 1):
                if (gcd(i, j) == 1):
                    coprimes[i].add(j)

        buf = [[] for i in range(kmax + 1)]
        ans = [float('inf') for i in range(len(nums))]

        def dfs(cur: int, level: int):

            cloest, val = -1, -1
            for p in coprimes[nums[cur]]:
                if buf[p] and buf[p][-1][0] > cloest:
                    cloest = buf[p][-1][0]
                    val = buf[p][-1][1]

            ans[cur] = val
            buf[nums[cur]].append([level, cur])

            for child in graph[cur]:
                if ans[child] == float('inf'):
                    dfs(child, level + 1)

            buf[nums[cur]].pop()

        dfs(0, 0)
        return ans
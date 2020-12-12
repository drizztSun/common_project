"""
1273. Delete Tree Nodes

A tree rooted at node 0 is given as follows:

The number of nodes is nodes;
The value of the i-th node is value[i];
The parent of the i-th node is parent[i].
Remove every subtree whose sum of values of nodes is zero.

After doing so, return the number of nodes remaining in the tree.



Example 1:


Input: nodes = 7, parent = [-1,0,0,1,2,2,2], value = [1,-2,4,0,-2,-1,-1]
Output: 2
Example 2:

Input: nodes = 7, parent = [-1,0,0,1,2,2,2], value = [1,-2,4,0,-2,-1,-2]
Output: 6
Example 3:

Input: nodes = 5, parent = [-1,0,1,0,0], value = [-672,441,18,728,378]
Output: 5
Example 4:

Input: nodes = 5, parent = [-1,0,0,1,1], value = [-686,-842,616,-739,-746]
Output: 5


Constraints:

1 <= nodes <= 10^4
parent.length == nodes
0 <= parent[i] <= nodes - 1
parent[0] == -1 which indicates that 0 is the root.
value.length == nodes
-10^5 <= value[i] <= 10^5
The given input is guaranteed to represent a valid tree.


"""


class DeleteTreeNodes:

    """
    Divide to sub problems.
    Traverse to sum tree nodes count
    when sub tree total is zero, also reset and return count zero.
    """
    def doit_(self, nodes: int, parent: list, value: list) -> int:

        from collections import defaultdict
        g = defaultdict(list)
        for i, v in enumerate(parent):
            g[v].append(i)

        def dfs(value, root):
            nonlocal ans
            cnt = 1
            tot = value[root]
            for c in g[root]:
                c_tot, c_cnt = dfs(value, c)
                tot += c_tot
                cnt += c_cnt

            if tot == 0:
                ans += cnt
                cnt = 0

            return tot, cnt

        ans = 0
        dfs(value, 0)
        return nodes - ans


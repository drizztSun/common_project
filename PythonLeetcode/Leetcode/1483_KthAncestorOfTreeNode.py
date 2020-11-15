"""
1483. Kth Ancestor of a Tree Node

You are given a tree with n nodes numbered from 0 to n-1 in the form of a parent array where parent[i] is the parent of node i. The root of the tree is node 0.

Implement the function getKthAncestor(int node, int k) to return the k-th ancestor of the given node. If there is no such ancestor, return -1.

The k-th ancestor of a tree node is the k-th node in the path from that node to the root.



Example:



Input:
["TreeAncestor","getKthAncestor","getKthAncestor","getKthAncestor"]
[[7,[-1,0,0,1,1,2,2]],[3,1],[5,2],[6,3]]

Output:
[null,1,0,-1]

Explanation:
TreeAncestor treeAncestor = new TreeAncestor(7, [-1, 0, 0, 1, 1, 2, 2]);

treeAncestor.getKthAncestor(3, 1);  // returns 1 which is the parent of 3
treeAncestor.getKthAncestor(5, 2);  // returns 0 which is the grandparent of 5
treeAncestor.getKthAncestor(6, 3);  // returns -1 because there is no such ancestor


Constraints:

1 <= k <= n <= 5*10^4
parent[0] == -1 indicating that 0 is the root node.
0 <= parent[i] < n for all 0 < i < n
0 <= node < n
There will be at most 5*10^4 queries.

"""


class TreeAncestor_binarylifting:

    def __init__(self, n: int, parent):

        A = {i: c for i, c in enumerate(parent)}
        self._step = 15
        self._jump = [A]

        for i in range(self._step):
            B = {}
            for i in A:
                if A[i] in A:
                    B[i] = A[A[i]]
            self._jump.append(B)
            A = B

    def getKthAncestor(self, n: int, k: int):

        step = self._step
        while k > 0 and n > -1:

            if k >= 1 << step:
                n = self._jump[step].get(n, -1)
                k -= 1 << step
            else:
                step -= 1

        return n


class TreeAncestor_dp_binarylifting:

    def __init__(self, n: int, parent):
        #根据数据范围可知，最大数据为50000,2^16大于50000，因此取0-15
        self.dp = [[-1 for _ in range(16)] for _ in range(n)]
        #开始填写dp数组
        for i in range(n):
            self.dp[i][0] = parent[i]

        for j in range(1,16):
            for i in range(n):
                #如果dp[i][j-1] == -1，那么已经找到祖先了，不需要再管
                if self.dp[i][j-1] != -1:
                    self.dp[i][j] = self.dp[self.dp[i][j-1]][j-1]

    def getKthAncestor(self, node: int, k: int):
        for i in range(16):
            #判断二进制的每一位是否为1，如果为1，则前进对应的步数
            if k & (1<<i):
                if node >= 0:
                    node = self.dp[node][i]
                else:
                    return -1
        return node


if __name__ == '__main__':

    obj = TreeAncestor_binarylifting(7,[-1,0,0,1,1,2,2])

    obj.getKthAncestor(3, 1)

    obj.getKthAncestor(5, 2)

    obj.getKthAncestor(6, 3)
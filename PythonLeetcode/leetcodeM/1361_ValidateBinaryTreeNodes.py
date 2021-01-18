"""
1361. Validate Binary Tree Nodes

You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i], 
return true if and only if all the given nodes form exactly one valid binary tree.

If node i has no left child then leftChild[i] will equal -1, similarly for the right child.

Note that the nodes have no values and that we only use the node numbers in this problem.

 

Example 1:



Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
Output: true
Example 2:



Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
Output: false
Example 3:



Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
Output: false
Example 4:



Input: n = 6, leftChild = [1,-1,-1,4,-1,-1], rightChild = [2,-1,-1,5,-1,-1]
Output: false
 

Constraints:

1 <= n <= 10^4
leftChild.length == rightChild.length == n
-1 <= leftChild[i], rightChild[i] <= n - 1


"""



class ValidateBinaryTreeNodes:

    def doit_disjoint(self, n: int, leftChild: list, rightChild: list) -> bool:

        parent = [i for i in range(n)]

        def find(i):
            while i != parent[i]:
                parent[i] = parent[parent[i]]
                i = parent[i]
            return parent[i]

        def union(a, b):
            pa, pb = find(a), find(b)

            if pa == pb:
                return False

            parent[pb] = pa
            return True

        for i in range(n):

            if leftChild[i] != -1:
                if not union(i, leftChild[i]):
                    return False

            if rightChild[i] != -1:
                if not union(i, rightChild[i]):
                    return False

        for i in range(n):
            find(i)

        return sum(parent[i] == i for i in range(n)) == 1

    def doit_disjoint(self, n: int, leftChild: list, rightChild: list) -> bool:
        # note down which nodes are seen
        seen = [0] * n
        # ranking of nodes, the smallest one is the root
        # the maximum rank can be simply set as n (actually <= n - 1)
        rank = [n] * n
        
        for i in range(n):
            childs = [leftChild[i], rightChild[i]]
            # when the node is a valid starting point, initialze its rank as 0
            if seen[i] == 0 and any([child != -1 for child in childs]):
                rank[i] = 0
            for child in childs:
                if child == -1:
                    continue
                # can't share the same child with other nodes
                if seen[child]:
                    return False
                # if the current node is a child of some node, its child can't have a smaller rank
                if seen[i] and rank[child] < rank[i]:
                    return False
                # update rank based on child's rank
                if rank[child] < n:
                    # if child already has rank
                    rank[i] = rank[child] - 1
                else:
                    rank[child] = rank[i] + 1
                seen[child] = 1
        
        return sum(seen) == n - 1

    # Using indegree to find the root, if the number of != 1, return False.
    # Then DFS from the root and count the node passed. If the count !=n, return False.
    def doit_dfs(self, n, leftChild, rightChild):
        """
        :type n: int
        :type leftChild: List[int]
        :type rightChild: List[int]
        :rtype: bool
        """
        import collections
        adj = collections.defaultdict(list)
        indegree = [0]*n
        visited = [0]*n
        start = []
        
        for i in range(n):
            for child in leftChild[i], rightChild[i]:
                if child != -1:
                    adj[i].append(child)
                    indegree[child] += 1
        
        for i in range(n):
            if indegree[i] >= 2:
                return False
            if indegree[i] == 0:
                start.append(i)
        
        if len(start) != 1:
            return False
        
        cnt = 0
        def dfs(adj, visited, i):
            nonlocal cnt
            if visited[i] == 1:
                return False
            res = False
            cnt += 1
            for neigh in adj[i]:
                res |= dfs(adj, visited, neigh)
            return res
        return not dfs(adj, visited, start[0]) and cnt == n


if __name__ == '__main__':

    ValidateBinaryTreeNodes().doit_disjoint(4, [3,-1,1,-1], [-1,-1,0,-1])



        








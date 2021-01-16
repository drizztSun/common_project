"""
310. Minimum Height Trees


A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree,
you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h.
Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.

The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.



Example 1:


Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]
Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.
Example 2:


Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]
Example 3:

Input: n = 1, edges = []
Output: [0]
Example 4:

Input: n = 2, edges = [[0,1]]
Output: [0,1]


Constraints:

1 <= n <= 2 * 104
edges.length == n - 1
0 <= ai, bi < n
ai != bi
All the pairs (ai, bi) are distinct.
The given input is guaranteed to be a tree and there will be no repeated edges.



Solution
Overview
As the hints suggest, this problem is related to the graph data structure. Moreover, it is closely related to the problems of Course Schedule and Course Schedule II.
This relationship is not evident, yet it is the key to solve the problem, as one will see later.

First of all, as a straight-forward way to solve the problem, we can simply follow the requirements of the problem, as follows:

Starting from each node in the graph, we treat it as a root to build a tree. Furthermore, we would like to know the distance between this root node and the rest of the nodes.
The maximum of the distance would be the height of this tree.

Then according to the definition of Minimum Height Tree (MHT), we simply filter out the roots that have the minimal height among all the trees.

The first step we describe above is actually the problem of Maximum Depth of N-ary Tree, which is to find the maximum distance from the root to the leaf nodes.
For this, we can either apply the Depth-First Search (DFS) or Breadth-First Search (BFS) algorithms.

Without a rigid proof, we can see that the above straight-forward solution is correct, and it would work for most of the test cases.

However, this solution is not efficient, whose time complexity would be (N^2)  where NN is the number of nodes in the tree.
As one can imagine, it will result in Time Limit Exceeded exception in the online judge.

As a spoiler alert, in this article, we will present a topological sorting alike algorithm with time complexity of O(N), which is also the algorithm to solve the well-known course schedule problems.


"""
class MinimumHeightTrees:

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

    def findMinHeightTrees(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        g = MinimumHeightTrees.Graph(n, edges)
        return g.minHighTree()

    """
    
        Approach 1: Topological Sorting
        Intuition
        
        First of all, let us clarify some concepts.
        
        The distance between two nodes is the number of edges that connect the two nodes.
        
        Note, normally there could be multiple paths to connect nodes in a graph. In our case though, since the input graph can form a tree from any node, as specified in the problem, there could only be one path between any two nodes. In addition, there would be no cycle in the graph. As a result, there would be no ambiguity in the above definition of distance.
        
        The height of a tree can be defined as the maximum distance between the root and all its leaf nodes.
        
        With the above definitions, we can rephrase the problem as finding out the nodes that are overall close to all other nodes, especially the leaf nodes.
        
        If we view the graph as an area of circle, and the leaf nodes as the peripheral of the circle, then what we are looking for are actually the centroids of the circle, i.e. nodes that is close to all the peripheral nodes (leaf nodes).
        
        example of graph
        
        For instance, in the above graph, it is clear that the node with the value 1 is the centroid of the graph. If we pick the node 1 as the root to form a tree, we would obtain a tree with the minimum height, compared to other trees that are formed with any other nodes.
        
        Before we proceed, here we make one assertion which is essential to the algorithm.
        
        For the tree-alike graph, the number of centroids is no more than 2.
        
        If the nodes form a chain, it is intuitive to see that the above statement holds, which can be broken into the following two cases:
        
        If the number of nodes is even, then there would be two centroids.
        If the number of nodes is odd, then there would be only one centroid.
        example of centroids
        
        For the rest of cases, we could prove by contradiction. Suppose that we have 3 centroids in the graph, if we remove all the non-centroid nodes in the graph, then the 3 centroids nodes must form a triangle shape, as follows:
        
        triangle
        
        Because these centroids are equally important to each other, and they should equally close to each other as well. If any of the edges that is missing from the triangle, then the 3 centroids would be reduced down to a single centroid.
        
        However, the triangle shape forms a cycle which is contradicted to the condition that there is no cycle in our tree-alike graph. Similarly, for any of the cases that have more than 2 centroids, they must form a cycle among the centroids, which is contradicted to our condition.
        
        Therefore, there cannot be more than 2 centroids in a tree-alike graph.
        
        Algorithm
        
        Given the above intuition, the problem is now reduced down to looking for all the centroid nodes in a tree-alike graph, which in addition are no more than two.
        
        The idea is that we trim out the leaf nodes layer by layer, until we reach the core of the graph, which are the centroids nodes.
        
        trim
        
        Once we trim out the first layer of the leaf nodes (nodes that have only one connection), some of the non-leaf nodes would become leaf nodes.
        
        The trimming process continues until there are only two nodes left in the graph, which are the centroids that we are looking for.
        
        The above algorithm resembles the topological sorting algorithm which generates the order of objects based on their dependencies. For instance, in the scenario of course scheduling, the courses that have the least dependency would appear first in the order.
        
        In our case, we trim out the leaf nodes first, which are the farther away from the centroids. At each step, the nodes we trim out are closer to the centroids than the nodes in the previous step. At the end, the trimming process terminates at the centroids nodes.
        
        Implementation
        
        Given the above algorithm, we could implement it via the Breadth First Search (BFS) strategy, to trim the leaf nodes layer by layer (i.e. level by level).
        
        Initially, we would build a graph with the adjacency list from the input.
        
        We then create a queue which would be used to hold the leaf nodes.
        
        At the beginning, we put all the current leaf nodes into the queue.
        
        We then run a loop until there is only two nodes left in the graph.
        
        At each iteration, we remove the current leaf nodes from the queue. While removing the nodes, we also remove the edges that are linked to the nodes. As a consequence, some of the non-leaf nodes would become leaf nodes. And these are the nodes that would be trimmed out in the next iteration.
        
        The iteration terminates when there are no more than two nodes left in the graph, which are the desired centroids nodes.
        
        Here are some sample implementations that are inspired from the post of dietpepsi in the discussion forum.
    
    """
    def doit_topsort(self, n: int, edges: list) -> list:

        # base cases
        if n <= 2:
            return [i for i in range(n)]

        # Build the graph with the adjacency list
        neighbors = [set() for i in range(n)]
        for start, end in edges:
            neighbors[start].add(end)
            neighbors[end].add(start)

        # Initialize the first layer of leaves
        leaves = []
        for i in range(n):
            if len(neighbors[i]) == 1:
                leaves.append(i)

        # Trim the leaves until reaching the centroids
        remaining_nodes = n
        while remaining_nodes > 2:
            remaining_nodes -= len(leaves)
            new_leaves = []
            # remove the current leaves along with the edges
            while leaves:
                leaf = leaves.pop()
                # the only neighbor left for the leaf node
                neighbor = neighbors[leaf].pop()
                # remove the only edge left
                neighbors[neighbor].remove(leaf)
                if len(neighbors[neighbor]) == 1:
                    new_leaves.append(neighbor)

            # prepare for the next round
            leaves = new_leaves

        # The remaining nodes are the centroids of the graph
        return leaves

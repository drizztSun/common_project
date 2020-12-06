"""
742. Closest Leaf in a Binary Tree


Given a binary tree where every node has a unique value, and a target key k, find the value of the nearest leaf node to target k in the tree.

Here, nearest to a leaf means the least number of edges travelled on the binary tree to reach any leaf of the tree. Also, a node is called a leaf if it has no children.

In the following examples, the input tree is represented in flattened form row by row. The actual root tree given will be a TreeNode object.

Example 1:

Input:
root = [1, 3, 2], k = 1
Diagram of binary tree:
          1
         / \
        3   2

Output: 2 (or 3)

Explanation: Either 2 or 3 is the nearest leaf node to the target of 1.
Example 2:

Input:
root = [1], k = 1
Output: 1

Explanation: The nearest leaf node is the root node itself.
Example 3:

Input:
root = [1,2,3,4,null,null,null,5,null,6], k = 2
Diagram of binary tree:
             1
            / \
           2   3
          /
         4
        /
       5
      /
     6

Output: 3
Explanation: The leaf node with value 3 (and not the leaf node with value 6) is nearest to the node with value 2.
Note:
root represents a binary tree with at least 1 node and at most 1000 nodes.
Every node has a unique node.val in range [1, 1000].
There exists some node in the given binary tree for which node.val == k.

"""


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class CloestLeafInBinaryTree:

    """
    Approach #1: Convert to Graph [Accepted]
    Intuition

    Instead of a binary tree, if we converted the tree to a general graph, we could find the shortest path to a leaf using breadth-first search.

    Algorithm

    We use a depth-first search to record in our graph each edge travelled from parent to node.

    After, we use a breadth-first search on nodes that started with a value of k, so that we are visiting nodes in order of their distance to k.
    When the node is a leaf (it has one outgoing edge, where the root has a "ghost" edge to null), it must be the answer.

    Complexity Analysis

    Time Complexity: O(N) where NN is the number of nodes in the given input tree. We visit every node a constant number of times.

    Space Complexity: O(N), the size of the graph.
    """
    def doit_bfs(self, root, k: int) -> int:
        import collections
        graph = collections.defaultdict(list)

        def dfs(node, par = None):
            if node:
                graph[node].append(par)
                graph[par].append(node)
                dfs(node.left, node)
                dfs(node.right, node)

        dfs(root)
        queue = collections.deque(node for node in graph if node and node.val == k)
        seen = set(queue)

        while queue:
            node = queue.popleft()
            if node:
                if len(graph[node]) <= 1:
                    return node.val
                for nei in graph[node]:
                    if nei not in seen:
                        seen.add(nei)
                        queue.append(nei)

    """
    Approach #2: Annotate Closest Leaf [Accepted]
    Intuition and Algorithm
    
    Say from each node, we already knew where the closest leaf in it's subtree is. Using any kind of traversal plus memoization, we can remember this information.
    
    Then the closest leaf to the target (in general, not just subtree) has to have a lowest common ancestor with the target that is on the path from the root to the target. 
    We can find the path from root to target via any kind of traversal, and look at our annotation for each node on this path to determine all leaf candidates, choosing the best one.
    
    Complexity Analysis

        Time and Space Complexity: O(N). The analysis is the same as in Approach #1.
    """
    def doit_dp_1(self, root, k):
        annotation = {}
        def closest_leaf(root):
            if root not in annotation:
                if not root:
                    ans = float('inf'), None
                elif not root.left and not root.right:
                    ans = 0, root
                else:
                    d1, leaf1 = closest_leaf(root.left)
                    d2, leaf2 = closest_leaf(root.right)
                    ans = min(d1, d2) + 1, leaf1 if d1 < d2 else leaf2
                annotation[root] = ans
            return annotation[root]

        #Search for node.val == k
        path = []
        def dfs(node):
            if not node:
                return
            if node.val == k:
                path.append(node)
                return True
            path.append(node)
            ans1 = dfs(node.left)
            if ans1: return True
            ans2 = dfs(node.right)
            if ans2: return True
            path.pop()

        dfs(root)
        dist, leaf = float('inf'), None
        for i, node in enumerate(path):
            d0, leaf0 = closest_leaf(node)
            d0 += len(path) - 1 - i
            if d0 < dist:
                dist = d0
                leaf = leaf0

        return leaf.val


if __name__ == '__main__':

    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)

    CloestLeafInBinaryTree().doit_(root, 1)
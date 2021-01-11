"""
662. Maximum Width of Binary Tree

Given a binary tree, write a function to get the maximum width of the given tree. The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and right most non-null nodes in the level, where the null nodes between the end-nodes are also counted into the length calculation.

It is guaranteed that the answer will in the range of 32-bit signed integer.

Example 1:

Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:

Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:

Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:

Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).
 

Constraints:

The given binary tree will have between 1 and 3000 nodes.


"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class MaximumWidthOfBinaryTree:

    """
        Approach 1: BFS Traversal
        Intuition

        Naturally, one might resort to the BFS traversal. After all, the width is measured among the nodes on the same level. So let us get down to the BFS traversal first.

        There are several ways to implement the BFS traversal. Almost all of them share a common point, i.e. using the queue data structure to maintain the order of visits.

        In brief, we push the nodes into the queue level by level. As a result, the priorities of visiting would roll out from top to down and from left to right, due to the FIFO (First-In First-Out) principle of the queue data structure, i.e. the element that enters the queue first would exit first as well.

        BFS traversal

        In the above graph, we show an example of BFS traversal on a full binary tree where we indicate the global order of visiting along with each node.

        Algorithm

        Here are a few steps to implement a solution with the BFS traversal.

        First of all, we create a queue data structure, which would be used to hold elements of tuple as (node, col_index), where the node is the tree node and the col_index is the corresponding index that is assigned to the node based on our indexing schema. Also, we define a global variable called max_width which holds the maximal width that we've seen so far.

        Then we append the root node along with its index 0, to kick off the BFS traversal.

        The BFS traversal is basically an iteration over the elements of queue. We visit the nodes level by level until there are no more elements in the queue.

        At the end of each level, we use the indices of the first and the last elements on the same level, in order to obtain the width of the level.
        At the end of BFS traversal, we then return the maximal width that we've seen over all levels.

        Note: in the above implementation, we use the size of the queue as a delimiter to determine the boundary between each levels.

        One could also use a specific dummy element as a marker to separate nodes of different levels in the queue.

        Complexity Analysis

        Let NN be the total number of nodes in the input tree.

        Time Complexity: O(N)

        We visit each node once and only once. And at each visit, it takes a constant time to process.
        Space Complexity: O(N)

        We used a queue to maintain the nodes along with its indices, which is the main memory consumption of the algorithm.

        Due to the nature of BFS, at any given moment, the queue holds no more than two levels of nodes. In the worst case, a level in a full binary tree contains at most half of the total nodes, 
        i.e. this is also the level where the leaf nodes reside.

        Hence, the overall space complexity of the algorithm is \mathcal{O}(N)O(N).
    """
    def doit_bfs(self, root: 'TreeNode') -> int:
        from collections import deque
        if not root: return 0

        max_width = 0
        # queue of elements [(node, col_index)]
        queue = deque()
        queue.append((root, 0))

        while queue:
            level_length = len(queue)
            _, level_head_index = queue[0]
            # iterate through the current level
            for _ in range(level_length):
                node, col_index = queue.popleft()
                # preparing for the next level
                if node.left:
                    queue.append((node.left, 2 * col_index))
                if node.right:
                    queue.append((node.right, 2 * col_index + 1))

            # calculate the length of the current level,
            #   by comparing the first and last col_index.
            max_width = max(max_width, col_index - level_head_index + 1)

        return max_width


    """
        Approach 2: DFS Traversal
        Intuition

        Although it is definitely more intuitive to implement a solution with BFS traversal, it is not impossible to do it with DFS.

        It might sound twisted, but we don't need to visit the nodes strictly in the order of BFS. All we need is to compare the indices between the first and the last elements of the same level.

        We could build a table that records the indices of nodes grouped by level. Then we could scan the indices level by level to obtain the maximal difference among them, which is also the width of the level.

        With the above idea, as we can see, any traversal will do, including the BFS and DFS.

        Better yet, we don't need to keep the indices of the entire level, but the first and the last index.

        We could use the table to keep only the index of the first element for each level, i.e. depth -> first_col_index, which we illustrate in the following graph.

        tree with first_col_index

        Along with the traversal, we could compare the index of every node with the corresponding first index of its level (i.e. first_col_index).

        Rather than keeping all the indices in the table, we save time and space by keeping only the index of the first element per level.

        Algorithm

        The tricky part is how we can obtain the index for the first element of each level.

        As we discussed before, we use a table with depth of the node as the key and the index of the first element for that depth (level) as the value.

        If we can make sure that we visit the first element of a level before the rest of elements on that level, we then can easily populate the table along with the traversal.

        In fact, a DFS traversal can assure the above priority that we desire. Even better, it could be either preorder, inorder or postorder DFS traversal, as long as we prioritize the visit of the left child node over the right child node.

        Although in principle DFS prioritizes depth over breadth, it could also ensure the level-wise priority. By visiting the left node before the right child node in DFS traversal, we can ensure that the nodes that lean more to the left got visited earlier.

        We showcase a preorder DFS traversal, with an example in the following graph:

        DFS traversal

        We label each node with a number that indicates the global order of visit. As one can see, the nodes at the same level do get visited from left to right. For instance, on the second level, the first node would be visited at the step 2, while the next node at the same level would be visited at the step 5.

        We give some sample implementations of DFS in the following.

        Complexity Analysis

        Let NN be the total number of nodes in the input tree.

        Time Complexity: \mathcal{O}(N)O(N).

        Similar to the BFS traversal, we visit each node once and only once in DFS traversal. And each visit takes a constant time to process as well.
        Space Complexity: \mathcal{O}(N)O(N)

        Unlike the BFS traversal, we used an additional table to keep the index for the first element per level. In the worst case where the tree is extremely skewed, there could be as many levels as the number of nodes. As a result, the space complexity of the table would be \mathcal{O}(N)O(N).

        Since we implement DFS traversal with recursion which would incur some additional memory consumption in the function call stack, we need to take this into account for the space complexity.

        The consumption of function stack is proportional to the depth of recursion. Again, in the same worst case above, where the tree is extremely skewed, the depth of the recursion would be equal to the number of nodes in the tree. Therefore, the space complexity of the function stack would be \mathcal{O}(N)O(N).

        To sum up, the overall space complexity of the algorithm is \mathcal{O}(N) + \mathcal{O}(N) = \mathcal{O}(N)O(N)+O(N)=O(N).

    """
    def doit_dfs(self, root: 'TreeNode') -> int:

        # table contains the first col_index for each level
        first_col_index_table = {}
        max_width = 0

        def DFS(node, depth, col_index):
            nonlocal max_width
            if node is None:
                return
            # if the entry is empty, set the value
            if depth not in first_col_index_table:
                first_col_index_table[depth] = col_index

            max_width = max(max_width, col_index - first_col_index_table[depth] + 1)

            # Preorder DFS, with the priority on the left child
            DFS(node.left, depth+1, 2*col_index)
            DFS(node.right, depth+1, 2*col_index + 1)

        DFS(root, 0, 0)

        return max_width
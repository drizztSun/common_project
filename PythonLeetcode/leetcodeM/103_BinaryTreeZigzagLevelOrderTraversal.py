"""
103. Binary Tree Zigzag Level Order Traversal


Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class ZigzagLevelOrder:

    def zigzagLevelOrder(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        if not root: return []

        buff, result, leftToRight = [root], [], False
        while buff:
            result.append([node.val for node in buff if node])

            temp = []

            for node in reversed(buff):
                if leftToRight:
                    temp.extend([node.left, node.right])
                else:
                    temp.extend([node.right, node.left])

            leftToRight = not leftToRight
            buff = [node for node in temp if node]

        return result

    def doit_(self, root: 'TreeNode') -> list:
        from collections import deque
        if not root: return []
        
        res = []
        qu = deque([root])
        reverse = True
        
        while qu:
            tmp = []
            nextqu = deque()
            while qu:
                n = qu.popleft()
                tmp.append(n.val)
                
                if reverse:
                    if n.left: nextqu.appendleft(n.left)
                    if n.right: nextqu.appendleft(n.right)
                else:
                    if n.right: nextqu.appendleft(n.right)
                    if n.left: nextqu.appendleft(n.left)
                    
            qu = nextqu
            reverse = not reverse
            res.append(tmp)
            
        return res

    """
        Approach 1: BFS (Breadth-First Search)
        Intuition

        Following the description of the problem, the most intuitive solution would be the BFS (Breadth-First Search) approach through which we traverse the tree level-by-level.

        The default ordering of BFS within a single level is from left to right. As a result, we should adjust the BFS algorithm a bit to generate the desired zigzag ordering.

        One of the keys here is to store the values that are of the same level with the deque (double-ended queue) data structure, where we could add new values on either end of a queue.

        So if we want to have the ordering of FIFO (first-in-first-out), we simply append the new elements to the tail of the queue, i.e. the late comers stand last in the queue. While if we want to have the ordering of FILO (first-in-last-out), we insert the new elements to the head of the queue, i.e. the late comers jump the queue.

        pic

        Algorithm

        There are several ways to implement the BFS algorithm.

        One way would be that we run a two-level nested loop, with the outer loop iterating each level on the tree, and with the inner loop iterating each node within a single level.
        We could also implement BFS with a single loop though. The trick is that we append the nodes to be visited into a queue and we separate nodes of different levels with a sort of delimiter (e.g. an empty node). The delimiter marks the end of a level, as well as the beginning of a new level.
        Here we adopt the second approach above. One can start with the normal BFS algorithm, upon which we add a touch of zigzag order with the help of deque. For each level, we start from an empty deque container to hold all the values of the same level. Depending on the ordering of each level, i.e. either from-left-to-right or from-right-to-left, we decide at which end of the deque to add the new element:

        pic

        For the ordering of from-left-to-right (FIFO), we append the new element to the tail of the queue, so that the element that comes late would get out late as well. As we can see from the above graph, given an input sequence of [1, 2, 3, 4, 5], with FIFO ordering, we would have an output sequence of [1, 2, 3, 4, 5].

        For the ordering of from-right-to-left (FILO), we insert the new element to the head of the queue, so that the element that comes late would get out first. With the same input sequence of [1, 2, 3, 4, 5], with FILO ordering, we would obtain an output sequence of [5, 4, 3, 2, 1].


    """
    def doit_bfs(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        from collections import deque
        ret = []
        level_list = deque()
        if root is None:
            return []
        # start with the level 0 with a delimiter
        node_queue = deque([root, None])
        is_order_left = True

        while len(node_queue) > 0:
            curr_node = node_queue.popleft()

            if curr_node:
                if is_order_left:
                    level_list.append(curr_node.val)
                else:
                    level_list.appendleft(curr_node.val)

                if curr_node.left:
                    node_queue.append(curr_node.left)
                if curr_node.right:
                    node_queue.append(curr_node.right)
            else:
                # we finish one level
                ret.append(level_list)
                # add a delimiter to mark the level
                if len(node_queue) > 0:
                    node_queue.append(None)

                # prepare for the next level
                level_list = deque()
                is_order_left = not is_order_left

        return ret

    """
        Approach 2: DFS (Depth-First Search)
        Intuition

        Though not intuitive, we could also obtain the BFS traversal ordering via the DFS (Depth-First Search) traversal in the tree.

        The trick is that during the DFS traversal, we maintain the results in a global array that is indexed by the level, i.e. the element array[level] would contain all the nodes that are at the same level. The global array would then be referred and updated at each step of DFS.

        pic

        Similar with the above modified BFS algorithm, we employ the deque data structure to hold the nodes that are of the same level, and we alternate the insertion direction (i.e. either to the head or to the tail) to generate the desired output ordering.

        Algorithm

        Here we implement the DFS algorithm via recursion. We define a recursive function called DFS(node, level) which only takes care of the current node which is located at the specified level. Within the function, here are three steps that we would perform:

        If this is the first time that we visit any node at the level, i.e. the deque for the level does not exist, then we simply create the deque with the current node value as the initial element.

        If the deque for this level exists, then depending on the ordering, we insert the current node value either to the head or to the tail of the queue.

        At the end, we recursively call the function for each of its child nodes.

        It might go without saying that, one can also implement the DFS traversal via iteration rather than recursion, which could be one of the followup questions by an interviewer.

        Complexity Analysis

        Time Complexity: \mathcal{O}(N)O(N), where NN is the number of nodes in the tree.

        Same as the previous BFS approach, we visit each node once and only once.
        Space Complexity: \mathcal{O}(H)O(H), where HH is the height of the tree, i.e. the number of levels in the tree, which would be roughly \log_2{N}log 
        2
        ​	
        N.

        Unlike the BFS approach, in the DFS approach, we do not need to maintain the node_queue data structure for the traversal.

        However, the function recursion would incur additional memory consumption on the function call stack. As we can see, the size of the call stack for any invocation of DFS(node, level) would be exactly the number of level that the current node resides on. Therefore, the space complexity of our DFS algorithm is \mathcal{O}(\log_2{N})O(log 
        2
        ​	
        N) which is much better than the BFS approach.
    """
    def doit_dfs(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        from collections import deque
        if root is None:
            return []

        results = []
        def dfs(node, level):
            if level >= len(results):
                results.append(deque([node.val]))
            else:
                if level % 2 == 0:
                    results[level].append(node.val)
                else:
                    results[level].appendleft(node.val)

            for next_node in [node.left, node.right]:
                if next_node is not None:
                    dfs(next_node, level+1)

        # normal level order traversal with DFS
        dfs(root, 0)

        return results
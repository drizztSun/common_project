# 1038. Binary Search Tree to Greater Sum Tree


# Given the root of a binary search tree with distinct values, modify it so that every node
# has a new value equal to the sum of the values of the original tree that are greater than or equal to node.val.

# As a reminder, a binary search tree is a tree that satisfies these constraints:

# The left subtree of a node contains only nodes with keys less than the node's key.
# The right subtree of a node contains only nodes with keys greater than the node's key.
# Both the left and right subtrees must also be binary search trees.


# Example 1:

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class BstToGst:

    """
        Approach #1 Recursion [Accepted]
        Intuition

        One way to perform a reverse in-order traversal is via recursion. By using the call stack to return to previous nodes, 
        we can easily visit the nodes in reverse order.

        Algorithm

        For the recursive approach, we maintain some minor "global" state so each recursive call can access and modify the current total sum. 
        Essentially, we ensure that the current node exists, recurse on the right subtree, visit the current node by updating its value and the total sum, and finally recurse on the left subtree. 
        If we know that recursing on root.right properly updates the right subtree and that recursing on root.left properly updates the left subtree, then we are guaranteed to update all nodes with larger values before the current node and all nodes with smaller values after.


        Complexity Analysis

        Time complexity : O(n)

        A binary tree has no cycles by definition, so convertBST gets called on each node no more than once. Other than the recursive calls, 
        convertBST does a constant amount of work, so a linear number of calls to convertBST will run in linear time.

        Space complexity : O(n)

        Using the prior assertion that convertBST is called a linear number of times, 
        we can also show that the entire algorithm has linear space complexity. Consider the worst case, a tree with only right (or only left) subtrees. The call stack will grow until the end of the longest path is reached, which in this case includes all nn nodes.
    """

    def doit_recursive(self, root: TreeNode) -> TreeNode:

        if not root: return root

        val = 0
        def build(node):
            nonlocal val
            if node.right:
                build(node.right)
            
            node.val += val
            val = node.val

            if node.left:
                build(node.left)

        build(root)
        return root

    """
        Approach #2 Iteration with a Stack [Accepted]
        Intuition

        If we don't want to use recursion, we can also perform a reverse in-order traversal via iteration and a literal stack to emulate the call stack.

        Algorithm

        One way to describe the iterative stack method is in terms of the intuitive recursive solution. First, we initialize an empty stack and set the current node to the root. 
        Then, so long as there are unvisited nodes in the stack or node does not point to null, we push all of the nodes along the path to the rightmost leaf onto the stack. This is equivalent to always processing the right subtree first in the recursive solution, and is crucial for the guarantee of visiting nodes in order of decreasing value. Next, we visit the node on the top of our stack, and consider its left subtree. This is just like visiting the current node before recursing on the left subtree in the recursive solution. Eventually, our stack is empty and node points to the left null child of the tree's minimum value node, so the loop terminates.
        Complexity Analysis

        Time complexity : \mathcal{O}(n)O(n)

        The key observation is that each node is pushed onto the stack exactly once. I will take for granted the assumption that a node will always be pushed at least once, as the alternative would imply that at least one node is disconnected from the root. Notice that nodes are only pushed onto the stack when they are pointed to by node at the beginning of the outer while loop, or when there is a path to them from such a node by using only right pointers. Then notice that at the end of each iteration of the loop, node points to the left child of a node that has been pushed onto (and subsequently popped from) the stack. Therefore, because the outer while loop always begins with node pointing to None, the root (which is not pointed to by any other node), or a left child of a visited node, we cannot revisit nodes.

        Space complexity : \mathcal{O}(n)O(n)

        If we assume that the above logic is sound, the assertion that each node is pushed onto the stack exactly once implies that the stack can contain (at most) nn nodes. All other parts of the algorithm use constant space, so there is overall a linear memory footprint.
    """
    def doit_bst(self, root):
        total = 0
        
        node = root
        stack = []
        while stack or node is not None:
            # push all nodes up to (and including) this subtree's maximum on
            # the stack.
            while node is not None:
                stack.append(node)
                node = node.right

            node = stack.pop()
            total += node.val
            node.val = total

            # all nodes with values between the current and its parent lie in
            # the left subtree.
            node = node.left

        return root

    def doit_iterative(self, root):
        
        total = 0
        cur = root
        st = []

        while st or cur:

            if cur:
                st.append(cur)
                cur = cur.right
            else:
                while st and not cur:
                    st[-1].val += total
                    total = st[-1].val
                    cur = st.pop()

                cur = cur.left

        return root

    """
        Approach #3 Reverse Morris In-order Traversal [Accepted]
        Intuition

        There is a clever way to perform an in-order traversal using only linear time and constant space, first described by J. H. Morris in his 1979 paper 
        "Traversing Binary Trees Simply and Cheaply". In general, the recursive and iterative stack methods sacrifice linear space for the ability to return to a node after visiting its left subtree. The Morris traversal instead exploits the unused null pointer(s) of the tree's leaves to create a temporary link out of the left subtree, allowing the traversal to be performed using only constant additional memory. To apply it to this problem, we can simply swap all "left" and "right" references, which will reverse the traversal.

        Algorithm

        First, we initialize node, which points to the root. Then, until node points to null (specifically, the left null of the tree's minimum-value node), 
        we repeat the following. First, consider whether the current node has a right subtree. If it does not have a right subtree, then there is no unvisited node with a greater value, so we can visit this node and move into the left subtree. If it does have a right subtree, then there is at least one unvisited node with a greater value, and thus we must visit first go to the right subtree. To do so, we obtain a reference to the in-order successor (the smallest-value node larger than the current) via our helper function getSuccessor. This successor node is the node that must be visited immediately before the current node, so it by definition has a null left pointer (otherwise it would not be the successor). Therefore, when we first find a node's successor, we temporarily link it (via its left pointer) to the node and proceed to the node's right subtree. Then, when we finish visiting the right subtree, the leftmost left pointer in it will be our temporary link that we can use to escape the subtree. After following this link, we have returned to the original node that we previously passed through, but did not visit. This time, when we find that the successor's left pointer loops back to the current node, we know that we have visited the entire right subtree, so we can now erase the temporary link and move into the left subtree.
    """
    def doit_(self, root):
        # Get the node with the smallest value greater than this one.
        def get_successor(node):
            succ = node.right
            while succ.left is not None and succ.left is not node:
                succ = succ.left
            return succ
                
        total = 0
        node = root
        while node is not None:
            # If there is no right subtree, then we can visit this node and
            # continue traversing left.
            if node.right is None:
                total += node.val
                node.val = total
                node = node.left
            # If there is a right subtree, then there is a node that has a
            # greater value than the current one. therefore, we must traverse
            # that node first.
            else:
                succ = get_successor(node)
                # If there is no left subtree (or right subtree, because we are
                # in this branch of control flow), make a temporary connection
                # back to the current node.
                if succ.left is None:
                    succ.left = node
                    node = node.right
                # If there is a left subtree, it is a link that we created on
                # a previous pass, so we should unlink it and visit this node.
                else:
                    succ.left = None
                    total += node.val
                    node.val = total
                    node = node.left
        
        return root

    def doit_heap(self, root):
        import heapq
        hpq, buff = [], [root]
        
        while buff:
            
            c = buff.pop()
            heapq.heappush(hpq, (-c.val, c))
            
            if c.left:
                buff.append(c.left)
            
            if c.right:
                buff.append(c.right)
                
        ans = 0
        while hpq:
            
            c = heapq.heappop(hpq)
            
            ans += -c[0]
            c[1].val = ans
            
        return root
# 1008. Construct Binary Search Tree from Preorder Traversal

# Return the root node of a binary search tree that matches the given preorder traversal.

# (Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val,
# and any descendant of node.right has a value > node.val.
# Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)


# Example 1:

# Input: [8,5,1,7,10,12]
# Output: [8,5,10,1,7,null,12]


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class BstFromPreorder:


    def doit_dfs_preorder(self, preorder: list) -> TreeNode:
        
        buf = []
        i = 0
        root = None
        
        while i < len(preorder):
            
            c = preorder[i]
            cur = TreeNode(c)
            
            if not buf:
                buf.append(cur)
                if not root:
                    root = cur
            elif buf[-1].val > c:
                buf[-1].left = cur
                buf.append(cur)
            else:
                last = None
                while buf and buf[-1].val < c:
                    last = buf.pop()
                
                last.right = cur
                buf.append(cur)
            
            i += 1
            
        return root

    """
        Approach 1: Construct binary tree from preorder and inorder traversal
        Intuition

        This approach is not the optimal one because of O(NlogN) time complexity, but very straightforward.

        Let's use here two facts:

        Binary tree could be constructed from preorder and inorder traversal.

        Inorder traversal of BST is an array sorted in the ascending order.

        Algorithm

        Construct inorder traversal by sorting the preorder array.

        Construct binary tree from preorder and inorder traversal: the idea is to peek the elements one by one from the preorder array and try to put them as a left or as a right child if it's possible. 
        If it's impossible - just put null as a child and proceed further. 
        The possibility to use an element as a child is checked by an inorder array: if it contains no elements for this subtree, then the element couldn't be used here, and one should use null as a child instead.

        Implementation

        bla


        Complexity Analysis

        Time complexity : O(NlogN). O(NlogN) to sort preorder array and O(N) to construct the binary tree.
        Space complexity : O(N) the inorder traversal and the tree.

    """
    def bstFromPreorder(self, preorder: list) -> TreeNode:
        def helper(in_left = 0, in_right = len(preorder)):
            nonlocal pre_idx
            # if there is no elements to construct subtrees
            if in_left == in_right:
                return None
            
            # pick up pre_idx element as a root
            root_val = preorder[pre_idx]
            root = TreeNode(root_val)

            # root splits inorder list
            # into left and right subtrees
            index = idx_map[root_val]

            # recursion 
            pre_idx += 1
            # build left subtree
            root.left = helper(in_left, index)
            # build right subtree
            root.right = helper(index + 1, in_right)
            return root
        
        inorder = sorted(preorder)
        # start from first preorder element
        pre_idx = 0
        # build a hashmap value -> its index
        idx_map = {val:idx for idx, val in enumerate(inorder)} 
        return helper()

    """
        Approach 2: Recursion
        Intuition

        It's quite obvious that the best possible time complexity for this problem is \mathcal{O}(N)O(N) and hence the approach 1 is not the best one.

        Basically, the inorder traversal above was used only to check if the element could be placed in this subtree. Since one deals with a BST here, this could be verified with the help of lower and upper limits for each element as for the validate BST problem. This way there is no need in inorder traversal and the time complexity is \mathcal{O}(N)O(N).

        Algorithm

        Initiate the lower and upper limits as negative and positive infinity because one could always place the root.

        Start from the first element in the preorder array idx = 0.

        Return helper(lower, upper):

        If the preorder array is used up idx = n then the tree is constructed, return null.

        If current value val = preorder[idx] is smaller then lower limit, or larger than upper limit, return null.

        If the current value is in the limits, place it here root = TreeNode(val) and proceed to construct recursively left and right subtrees: root.left = helper(lower, val) and root.right = helper(val, upper).

        Return root.

        Implementation

        bla


        Complexity Analysis

        Time complexity : O(N) since we visit each node exactly once.
        Space complexity : O(N) to keep the entire tree.
    """
    def bstFromPreorder(self, preorder: list) -> TreeNode:
        def helper(lower = float('-inf'), upper = float('inf')):
            nonlocal idx
            # if all elements from preorder are used
            # then the tree is constructed
            if idx == n:
                return None
            
            val = preorder[idx]
            # if the current element 
            # couldn't be placed here to meet BST requirements
            if val < lower or val > upper:
                return None
            
            # place the current element
            # and recursively construct subtrees
            idx += 1
            root = TreeNode(val)
            root.left = helper(lower, val)
            root.right = helper(val, upper)
            return root
        
        idx = 0
        n = len(preorder)
        return helper()

    """
        Approach 3: Iteration
        Algorithm

        The recursion above could be converted into the iteration with the help of stack.

        Pick the first preorder element as a root root = new TreeNode(preorder[0]) and push it into stack.

        Use for loop to iterate along the elements of preorder array :

        Pick the last element of the stack as a parent node, and the the current element of preorder as a child node.

        Adjust the parent node : pop out of stack all elements with the value smaller than the child value. Change the parent node at each pop node = stack.pop().

        If node.val < child.val - put the child as a right child of the node : node.right = child.

        Else - as a left child : node.left = child.

        Push child node into the stack.

        Return root.

        Implementation
        Complexity Analysis

        Time complexity : \mathcal{O}(N)O(N) since we visit each node exactly once.

        Space complexity : \mathcal{O}(N)O(N) to keep the stack and the tree.
    """
    def bstFromPreorder(self, preorder: 'list') -> TreeNode:
        n = len(preorder)
        if not n:
            return None
        
        root = TreeNode(preorder[0])         
        stack = [root, ] 
        
        for i in range(1, n):
            # take the last element of the stack as a parent
            # and create a child from the next preorder element
            node, child = stack[-1], TreeNode(preorder[i])
            # adjust the parent 
            while stack and stack[-1].val < child.val: 
                node = stack.pop()
            
            # follow BST logic to create a parent-child link
            if node.val < child.val:
                node.right = child 
            else:
                node.left = child 
            # add the child into stack
            stack.append(child)

        return root

    def bstFromPreorder(self, preorder: list) -> TreeNode:
        if not preorder:
            return preorder
        
        # Get frist num of the list and create a TreeNode. The very first number will be the root of the tree
        root = TreeNode(preorder[0])
        # Create a stack and add the root to it. We will have a stack of TreeNodes and pointers that will have
        # a reference to their left and right children
        stack = [root]
        
        for i in range(1, len(preorder)):
            # Add elements to the left of the tree
            if preorder[i] < stack[-1].val:
                # Create a new TreeNode. Set the left of the last element of the stack to the new node.
                # Append the new TreeNode to the stack. So the stack will not only have the previous element with 
                # its left pointing to the new node, but also the new node will be added to the stack 
                # with lt and rt = None
                stack[-1].left = TreeNode(preorder[i])
                stack.append(stack[-1].left)
            # Add elements to the right of the tree
            else:
                while stack and preorder[i] > stack[-1].val:
                    # Keep popping TreeNodes to get the correct node to which we will set its right to the current node
                    last_node = stack.pop()
                last_node.right = TreeNode(preorder[i])
                stack.append(last_node.right)
                
        return root

    def doit(self, preorder):
        """
        :type preorder: List[int]
        :rtype: TreeNode
        """
        root = TreeNode(preorder[0])
        st = [root]

        for i in range(1, len(preorder)):

            if not st:
                st.append(TreeNode(preorder[i]))

            elif st[-1].val > preorder[i]:
                st[-1].left = TreeNode(preorder[i])
                st.append(st[-1].left)

            elif st[-1].val < preorder[i]:

                while st and st[-1].val < preorder[i]:
                    last = st.pop()

                last.right = TreeNode(preorder[i])
                st.append(last.right)

        return root

    def doit(self, preorder):

        def dfs(i, j):
            if j < i:
                return None

            if i == j:
                return TreeNode(preorder[i])

            root = TreeNode(preorder[i])
            l = i+1

            while l <= j and preorder[l] < preorder[i]:
                l += 1

            root.left = dfs(i+1, l-1)
            root.right = dfs(l, j)

            return root

        return dfs(0, len(preorder)-1)


if __name__ == '__main__':

    res = BstFromPreorder().doit([8, 5, 1, 7, 10, 12])

    pass

"""
1485. Clone Binary Tree With Random Pointer


A binary tree is given such that each node contains an additional random pointer which could point to any node in the tree or null.

Return a deep copy of the tree.

The tree is represented in the same input/output way as normal binary trees where each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (in the input) where the random pointer points to, or null if it does not point to any node.
You will be given the tree in class Node and you should return the cloned tree in class NodeCopy. NodeCopy class is just a clone of Node class with the same attributes and constructors.

 

Example 1:


Input: root = [[1,null],null,[4,3],[7,0]]
Output: [[1,null],null,[4,3],[7,0]]
Explanation: The original binary tree is [1,null,4,7].
The random pointer of node one is null, so it is represented as [1, null].
The random pointer of node 4 is node 7, so it is represented as [4, 3] where 3 is the index of node 7 in the array representing the tree.
The random pointer of node 7 is node 1, so it is represented as [7, 0] where 0 is the index of node 1 in the array representing the tree.
Example 2:


Input: root = [[1,4],null,[1,0],null,[1,5],[1,5]]
Output: [[1,4],null,[1,0],null,[1,5],[1,5]]
Explanation: The random pointer of a node can be the node itself.
Example 3:


Input: root = [[1,6],[2,5],[3,4],[4,3],[5,2],[6,1],[7,0]]
Output: [[1,6],[2,5],[3,4],[4,3],[5,2],[6,1],[7,0]]
Example 4:

Input: root = []
Output: []
Example 5:

Input: root = [[1,null],null,[2,null],null,[1,null]]
Output: [[1,null],null,[2,null],null,[1,null]]
 

Constraints:

The number of nodes in the tree is in the range [0, 1000].
Each node's value is between [1, 10^6].

"""


class CopyRandomBinaryTree:

    def doit_recursive(self, root: 'Node') -> 'NodeCopy':
        
        buff = {}
        def copy(node):
            nonlocal buff
            if not node: return None
            
            if node in buff:
                return buff[node]
            
            cur = NodeCopy(node.val)
            buff[node] = cur
            
            cur.left = copy(node.left)
            cur.right = copy(node.right)
            cur.random = copy(node.random)
            
            return cur
        
        return copy(root)

    """
        Approach 1: Iterative Tree Traversal + Hashmap
Intuition

Anytime we encounter a tree problem, we automatically know that we have to traverse the tree. Why? Well, we have to look at the tree to get an answer, right? So we will be (1) traversing the tree and (2) processing each node we look at.

There are 2 types of traversals: Depth-First-Search (DFS) and Breadth-First-Search (BFS). The simplest type of traversal is a preorder Depth-First Search. See below for a template we'll use later on.

# DFS Template

stack = [root]

while stack:
    node = stack.pop()
    if node.left:
        stack.append(node.left)
    if node.right:
        stack.append(node.right)
Algorithm

Okay. So we know we will be doing a DFS tree traversal. But what next? We mentioned earlier that we will be processing the nodes as we traverse the tree. Let's break that down into easy, actionable steps.

As we traverse the tree, we need to...

Create a copy of each node
Connect the copied nodes together
Bingo, that's it. You're done.

Kidding, let's figure out what this will look like a little more concretely. We're going to do two traversals; one to copy each node, and another to connect the copied nodes together.

Step 1: Create a copy of each node

We just established that our first processing step is creating a copy of each node in the original tree. Good, but we also need a place to store the copied nodes with easy lookup access for step 2.

What type of data structure fits this profile? Hashmap!

Why? Hashmaps let us map a key to value AND access that value in O(1) time.

Let's grab our DFS Template from earlier and add Step 1 to it.

# Step 1. Create a copy of each node

copy = {}   # Store our copied nodes here
stack = [root]

while stack:
    node = stack.pop()
    copy[node] = NodeCopy(node.val)  # Map the original node to its NodeCopy
    if node.left:
        stack.append(node.left)
    if node.right:
        stack.append(node.right)
This is how it looks visually:

Current
1 / 5
Interview Tip: You might be tempted to store the value of the node as the key (e.g.: copy[node.val]). This would be fine if all node values in the tree were unique, but the sample inputs show that this is not the case. We can guarantee uniqueness by storing the actual node as the key instead. This is an excellent assumption/topic to discuss with your interviewer.

Step 2: Connect the copied nodes together

At this point, we have a copy of each node in our tree stored in a hashmap. Our next step is to connect the left, right, and random pointers of the copied nodes together to form our original tree's structure. We will do this step in a second DFS traversal.

Interview Tip: Don't worry about prematurely optimizing your solution. Do this connecting step in a second DFS traversal because the Big O complexity of a two pass DFS is the same as a one pass DFS. Mention this thought process to your interviewer.

The code snippet is below. copy[node] looks up and retrieves the current node's copy. We do copy[node].left to set the current node's copy left pointer equal to the copy of the current node's left node. Same idea for right and random pointers.

# Step 2. Connect the copied nodes together

stack = [root]

while stack:
    node = stack.pop()
    if node.left:
        copy[node].left = copy[node.left]      # connect left pointer
        stack.append(node.left)
    if node.right:
        copy[node].right = copy[node.right]    # connect right pointer
        stack.append(node.right)
    if node.random:
        copy[node].random = copy[node.random]  # connect random pointer
This is how it looks visually:

Current
1 / 5
Code

Congrats, you've solved the problem! Put the steps together and we get the following solution:


Pop Quiz: What would happen if we added node.random to the stack in Step 1?

Answer: We would enter an infinite recursive loop and receive a TLE error because we would be creating a cycle within our tree traversal.

Complexity Analysis

Let nn be the number of nodes in the tree.

Time complexity: O(n + n) = O(2n) = O(n)O(n+n)=O(2n)=O(n).

Each traversal costs O(n)O(n) because we check every node once. We traverse the tree twice, which gives us O(n + n)= O(2n)O(n+n)=O(2n). In Big O, we drop any constants to get O(n)O(n) as our final time complexity.
Space complexity: O(n)O(n) linear space to store a copy of each node in our hashmap. Also worth mentioning that the stack space for our DFS can grow to worst-case O(n) for a skewed binary tree.


    """

    def doit_(self, root: 'Node') -> 'NodeCopy':
        if not root:   # Protection against a null root input  
            return None

        # Step 1. Create a copy of each node
        copy = {}
        stack = [root]

        while stack:
            node = stack.pop()
            copy[node] = NodeCopy(node.val)
            if node.left:
                stack.append(node.left)
            if node.right:
                stack.append(node.right)

        # Step 2. Connect the copied nodes together
        stack = [root]

        while stack:
            node = stack.pop()
            if node.left:
                copy[node].left = copy[node.left]
                stack.append(node.left)
            if node.right:
                copy[node].right = copy[node.right]
                stack.append(node.right)
            if node.random:
                copy[node].random = copy[node.random]

        return copy[root]

    def doit_(self, root: 'Node') -> 'NodeCopy':
        if not root:
            return None

        def dfs_copy(node):
            if not node:
                return

            copy[node] = NodeCopy(node.val)

            dfs_copy(node.left)
            dfs_copy(node.right)

            return node

        def dfs_connect(node):
            if not node:
                return

            if node.left:
                copy[node].left = copy[node.left]
            if node.right:
                copy[node].right = copy[node.right]
            if node.random:
                copy[node].random = copy[node.random]

            dfs_connect(node.left)
            dfs_connect(node.right)

            return node     

        copy = {}
        dfs_copy(root)
        dfs_connect(root)
        return copy[root]
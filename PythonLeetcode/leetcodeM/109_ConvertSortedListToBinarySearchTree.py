"""
109. Convert Sorted List to Binary Search Tree


Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

 

Example 1:


Input: head = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.
Example 2:

Input: head = []
Output: []
Example 3:

Input: head = [0]
Output: [0]
Example 4:

Input: head = [1,3]
Output: [3,1]
 

Constraints:

The number of nodes in head is in the range [0, 2 * 104].
-10^5 <= Node.val <= 10^5


"""


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class SortedListToBST:
    
    def doit_search(self, head: 'ListNode') -> 'TreeNode':

        if not head: return None
        
        buff = []
        node = head
        while node:
            buff.append(node.val)
            node = node.next
            
        def build(arr):

            if not arr: return None
            if len(arr) == 1: return TreeNode(arr[0])
            
            mid = len(arr) // 2
            
            node = TreeNode(arr[mid])
            node.left = build(arr[:mid])
            node.right = build(arr[mid+1:])
            
            return node
        
        return build(buff)


    """

    Approach 1: Recursion
    Intuition

    The important condition that we have to adhere to in this problem is that we have to create a height balanced binary search tree using the set of nodes given to us in the form of a linked list. The good thing is that the nodes in the linked list are sorted in ascending order.

    As we know, a binary search tree is essentially a rooted binary tree with a very special property or relationship amongst its nodes. For a given node of the binary search tree, it's value must be \ge≥ the value of all the nodes in the left subtree and \le≤ the value of all the nodes in the right subtree. Since a binary tree has a recursive substructure, so does a BST i.e. all the subtrees are binary search trees in themselves.

    The main idea in this approach and the next is that:

    the middle element of the given list would form the root of the binary search tree. All the elements to the left of the middle element would form the left subtree recursively. Similarly, all the elements to the right of the middle element will form the right subtree of the binary search tree. This would ensure the height balance required in the resulting binary search tree.

    Algorithm

    Since we are given a linked list and not an array, we don't really have access to the elements of the list using indexes. We want to know the middle element of the linked list.
    We can use the two pointer approach for finding out the middle element of a linked list. Essentially, we have two pointers called slow_ptr and fast_ptr. The slow_ptr moves one node at a time whereas the fast_ptr moves two nodes at a time. By the time the fast_ptr reaches the end of the linked list, the slow_ptr would have reached the middle element of the linked list. For an even sized list, any of the two middle elements can act as the root of the BST.
    Once we have the middle element of the linked list, we disconnect the portion of the list to the left of the middle element. The way we do this is by keeping a prev_ptr as well which points to one node before the slow_ptr i.e. prev_ptr.next = slow_ptr. For disconnecting the left portion we simply do prev_ptr.next = None
    We only need to pass the head of the linked list to the function that converts it to a height balances BST. So, we recurse on the left half of the linked list by passing the original head of the list and on the right half by passing slow_ptr.next as the head.

    Time Complexity: O(NlogN). Suppose our linked list consists of NN elements. For every list we pass to our recursive function, we have to calculate the middle element for that list. For a list of size NN, it takes N / 2N/2 steps to find the middle element i.e. O(N)O(N) to find the mid. We do this for every half of the original linked list. From the looks of it, this seems to be an O(N^2)O(N 
    2
    ) algorithm. However, on closer analysis, it turns out to be a bit more efficient than O(N^2)O(N 
    2
    ).

    """
    def sortedListToBST(self, head):
        """
        :type head: ListNode
        :rtype: TreeNode
        """

        # If the head doesn't exist, then the linked list is empty
        if not head:
            return None

        def findMiddle(self, head):

            # The pointer used to disconnect the left half from the mid node.
            prevPtr = None
            slowPtr = head
            fastPtr = head

            # Iterate until fastPr doesn't reach the end of the linked list.
            while fastPtr and fastPtr.next:
                prevPtr = slowPtr
                slowPtr = slowPtr.next
                fastPtr = fastPtr.next.next

            # Handling the case when slowPtr was equal to head.
            if prevPtr:
                prevPtr.next = None

            return slowPtr

        # Find the middle element for the list.
        mid = findMiddle(head)

        # The mid becomes the root of the BST.
        node = TreeNode(mid.val)

        # Base case when there is just one element in the linked list
        if head == mid:
            return node

        # Recursively form balanced BSTs using the left and right halves of the original list.
        node.left = self.sortedListToBST(head)
        node.right = self.sortedListToBST(mid.next)
        return node

    """
        Approach 2: Recursion + Conversion to Array
        This approach is a classic example of the time-space tradeoff.

        You can get the time complexity down by using more space.

        That's exactly what we're going to do in this approach. Essentially, we will convert the given linked list into an array and then use that array to form our binary search tree. In an array fetching the middle element is a O(1)O(1) operation and this will bring down the overall time complexity.

        Algorithm

        1. Convert the given linked list into an array. Let's call the beginning and the end of the array as left and right
        2. Find the middle element as (left + right) / 2. Let's call this element as mid. This is a O(1)O(1) time operation and is the only major improvement over the previous algorithm.
        3. The middle element forms the root of the BST.
        4. Recursively form binary search trees on the two halves of the array represented by (left, mid - 1) and (mid + 1, right) respectively.
        Let's look at the implementation for this algorithm and then we will get to the complexity analysis.


        Complexity Analysis

        Time Complexity: The time complexity comes down to just O(N)O(N) now since we convert the linked list to an array initially and then we convert the array into a BST. Accessing the middle element now takes O(1)O(1) time and hence the time complexity comes down.
        Space Complexity: Since we used extra space to bring down the time complexity, the space complexity now goes up to O(N)O(N) as opposed to just O(\log N)O(logN) in the previous solution. This is due to the array we construct initially.
    """
    def sortedListToBST(self, head):
        """
        :type head: ListNode
        :rtype: TreeNode
        """

        # Form an array out of the given linked list and then
        # use the array to form the BST.
        vals = []
        while head:
            vals.append(head.val)
            head = head.next
        return vals   

        # l and r represent the start and end of the given array
        def convertListToBST(l, r):

            # Invalid case
            if l > r:
                return None

            # Middle element forms the root.
            mid = (l + r) // 2
            node = TreeNode(values[mid])

            # Base case for when there is only one element left in the array
            if l == r:
                return node

            # Recursively form BST on the two halves
            node.left = convertListToBST(l, mid - 1)
            node.right = convertListToBST(mid + 1, r)
            return node

        return convertListToBST(0, len(values) - 1)

    """
    Approach 3: Inorder Simulation
    Intuition

    As we know, there are three different types of traversals for a binary tree:

    Inorder
    Preorder and
    Postorder traversals.
    The inorder traversal on a binary search tree leads to a very interesting outcome.

    Elements processed in the inorder fashion on a binary search tree turn out to be sorted in ascending order.

    The approach listed here make use of this idea to formulate the construction of a binary search tree. The reason we are able to use this idea in this problem is because we are given a sorted linked list initially.

    Before looking at the algorithm, let us look at how the inorder traversal actually leads to a sorted order of nodes' values.

    Complexity Analysis

    Time Complexity: The time complexity is still O(N)O(N) since we still have to process each of the nodes in the linked list once and form corresponding BST nodes.
    Space Complexity: O(\log N)O(logN) since now the only extra space is used by the recursion stack and since we are building a height balanced BST, the height is bounded by \log NlogN.

    """
    def sortedListToBST(self, head):
        """
        :type head: ListNode
        :rtype: TreeNode
        """
        def findSize(head):
            ptr = head
            c = 0
            while ptr:
                ptr = ptr.next
                c += 1
            return c

        # Get the size of the linked list first
        size = findSize(head)

        # Recursively form a BST out of linked list from l --> r
        def convert(l, r):
            nonlocal head

            # Invalid case
            if l > r:
                return None

            mid = (l + r) // 2

            # First step of simulated inorder traversal. Recursively form
            # the left half
            left = convert(l, mid - 1)

            # Once left half is traversed, process the current node
            node = TreeNode(head.val)   
            node.left = left

            # Maintain the invariance mentioned in the algorithm
            head = head.next

            # Recurse on the right hand side and form BST out of them
            node.right = convert(mid + 1, r)
            return node

        return convert(0, size - 1)
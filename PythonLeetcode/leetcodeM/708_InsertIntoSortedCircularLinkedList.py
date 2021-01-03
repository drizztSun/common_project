"""
708. Insert into a Sorted Circular Linked List


Given a node from a Circular Linked List which is sorted in ascending order, write a function to insert a value insertVal into the list such that it remains a sorted circular list. 
The given node can be a reference to any single node in the list, and may not be necessarily the smallest value in the circular list.

If there are multiple suitable places for insertion, you may choose any place to insert the new value. After the insertion, the circular list should remain sorted.

If the list is empty (i.e., given node is null), you should create a new single circular list and return the reference to that single node. Otherwise, you should return the original given node.

 

Example 1:


 
Input: head = [3,4,1], insertVal = 2
Output: [3,4,1,2]
Explanation: In the figure above, there is a sorted circular list of three elements. You are given a reference to the node with value 3, and we need to insert 2 into the list. 
The new node should be inserted between node 1 and node 3. After the insertion, the list should look like this, and we should still return node 3.



Example 2:

Input: head = [], insertVal = 1
Output: [1]
Explanation: The list is empty (given head is null). We create a new single circular list and return the reference to that single node.
Example 3:

Input: head = [1], insertVal = 0
Output: [1,0]
 

Constraints:

0 <= Number of Nodes <= 5 * 10^4
-10^6 <= Node.val <= 10^6
-10^6 <= insertVal <= 10^6

"""


"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next
"""

class InsertIntoSortedCircular:


    def doit_search(self, head: 'Node', insertVal: int) -> 'Node':
        
        td = Node(val=insertVal)
        
        if not head:
            td.next = td
            return td
        
        if head == head.next:
            head.next, td.next = td, head
            return head
        
        node = head
        while True:
            if node.val <= insertVal <= node.next.val or (node.next.val < node.val and (node.val <= insertVal or node.next.val >= insertVal)):
                node.next, td.next = td, node.next
                return head
            node = node.next
            if node == head:
                break
                
        head.next, td.next = td, head.next
        return head

    """
        Approach 1: Two-Pointers Iteration
        Intuition

        As simple as the problem might seem to be, it is actually not trivial to write a solution that covers all cases.

        Often the case for the problems with linked list, one could apply the approach of Two-Pointers Iteration, where one uses two pointers as surrogate to traverse the linked list.

        One of reasons of having two pointers rather than one is that in singly-linked list one does not have a reference to the precedent node, therefore we keep an additional pointer which points to the precedent node.

        For this problem, we iterate through the cyclic list using two pointers, namely prev and curr. When we find a suitable place to insert the new value, we insert it between the prev and curr nodes.


        Algorithm

        First of all, let us define the skeleton of two-pointers iteration algorithm as follows:

        As we mentioned in the intuition, we loop over the linked list with two pointers (i.e. prev and curr) step by step. The termination condition of the loop is that we get back to the starting point of the two pointers (i.e. prev == head)

        During the loop, at each step, we check if the current place bounded by the two pointers is the right place to insert the new value.

        If not, we move both pointers one step forwards.

        Now, the tricky part of this problem is to sort out different cases that our algorithm should deal with within the loop, and then design a concise logic to handle them sound and properly. Here we break it down into three general cases.

        Case 1). The value of new node sits between the minimal and maximal values of the current list. As a result, it should be inserted within the list.

        Case 2). The value of new node goes beyond the minimal and maximal values of the current list, either less than the minimal value or greater than the maximal value. 
            In either case, the new node should be added right after the tail node (i.e. the node with the maximal value of the list).

        Case 3). Finally, there is one case that does not fall into any of the above two cases. This is the case where the list contains uniform values.
        
    """

    def doit_(self, head: 'Node', insertVal: int) -> 'Node':

        if head == None:
            newNode = Node(insertVal, None)             
            newNode.next = newNode
            return newNode
 
        prev, curr = head, head.next
        toInsert = False

        while True:
            
            if prev.val <= insertVal <= curr.val:
                # Case #1.
                toInsert = True
            elif prev.val > curr.val:
                # Case #2. where we locate the tail element
                # 'prev' points to the tail, i.e. the largest element!
                if insertVal >= prev.val or insertVal <= curr.val:
                    toInsert = True

            if toInsert:
                prev.next = Node(insertVal, curr)
                # mission accomplished
                return head

            prev, curr = curr, curr.next
            # loop condition
            if prev == head:
                break
        # Case #3.
        # did not insert the node in the loop
        prev.next = Node(insertVal, curr)
        return head
        
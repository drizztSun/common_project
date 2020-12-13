"""
141. Linked List Cycle

Given head, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer.
Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.



Example 1:


Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
Example 2:


Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
Example 3:


Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.


Constraints:

The number of the nodes in the list is in the range [0, 104].
-105 <= Node.val <= 105
pos is -1 or a valid index in the linked-list.

"""


class LinkedListCycleI:

    """
    Approach 1: Hash Table
    Intuition

    To detect if a list is cyclic, we can check whether a node had been visited before. A natural way is to use a hash table.

    Algorithm

    We go through each node one by one and record each node's reference (or memory address) in a hash table.
    If the current node is null, we have reached the end of the list and it must not be cyclic.
    If current node’s reference is in the hash table, then return true.
    Complexity analysis

    Time complexity : O(n). We visit each of the nn elements in the list at most once. Adding a node to the hash table costs only O(1) time.
    Space complexity: O(n). The space depends on the number of elements added to the hash table, which contains at most nn elements.
    """
    def doit_hashtable(self, head: 'ListNode') -> bool:
        buff = set()
        while head:
            if head in buff:
                return True
            buff.add(head)
            head = head.next
        return False

    """
    Approach 2: Two Pointers
    Intuition
    
    Imagine two runners running on a track at different speed. What happens when the track is actually a circle?
    
    Algorithm
    
    The space complexity can be reduced to O(1)O(1) by considering two pointers at different speed - a slow pointer and a fast pointer. 
    The slow pointer moves one step at a time while the fast pointer moves two steps at a time.
    
    If there is no cycle in the list, the fast pointer will eventually reach the end and we can return false in this case.
    
    Now consider a cyclic list and imagine the slow and fast pointers are two runners racing around a circle track. 
    The fast runner will eventually meet the slow runner. Why? Consider this case (we name it case A) - The fast runner is just one step behind the slow runner. 
    In the next iteration, they both increment one and two steps respectively and meet each other.
    
    How about other cases? For example, we have not considered cases where the fast runner is two or three steps behind the slow runner yet. 
    This is simple, because in the next or next's next iteration, this case will be reduced to case A mentioned above.
    
    Complexity analysis

    Time complexity : O(n). Let us denote nn as the total number of nodes in the linked list. To analyze its time complexity, we consider the following two cases separately.
    Space complexity : O(1). We only use two nodes (slow and fast) so the space complexity is O(1)O(1).
    """

    def doit_twopointers(self, head: 'ListNode') -> bool:

        slow = fast = head

        while slow and fast:

            slow = slow.next
            fast = fast.next
            if not fast:
                return False
            fast = fast.next

            if slow == fast:
                return True

        return False


"""
142. Linked List Cycle II


Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer.
Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Notice that you should not modify the linked list.



Example 1:


Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.
Example 2:


Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.
Example 3:


Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.


Constraints:

The number of the nodes in the list is in the range [0, 104].
-105 <= Node.val <= 105
pos is -1 or a valid index in the linked-list.


Follow up: Can you solve it using O(1) (i.e. constant) memory?
"""


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class LinkedListCycleII:

    def doit_hashset(self, head: 'ListNode') -> 'ListNode':
        visited = set()

        node = head
        while node is not None:
            if node in visited:
                return node
            else:
                visited.add(node)
                node = node.next

        return None

    def doit_twopointers(self, head) -> 'ListNode':

        def getIntersect(head):
            tortoise = head
            hare = head

            # A fast pointer will either loop around a cycle and meet the slow
            # pointer or reach the `null` at the end of a non-cyclic list.
            while hare is not None and hare.next is not None:
                tortoise = tortoise.next
                hare = hare.next.next
                if tortoise == hare:
                    return tortoise

            return None

        if head is None:
            return None

        # If there is a cycle, the fast/slow pointers will intersect at some
        # node. Otherwise, there is no cycle, so we cannot find an entrance to
        # a cycle.
        intersect = getIntersect(head)
        if intersect is None:
            return None

        # To find the entrance to the cycle, we have two pointers traverse at
        # the same speed -- one from the front of the list, and the other from
        # the point of intersection.
        ptr1 = head
        ptr2 = intersect
        while ptr1 != ptr2:
            ptr1 = ptr1.next
            ptr2 = ptr2.next

        return ptr1




# 382. Linked List Random Node

# Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.

# Follow up:
# What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?

# Example:

# // Init a singly linked list [1,2,3].
# ListNode head = new ListNode(1);
# head.next = new ListNode(2);
# head.next.next = new ListNode(3);
# Solution solution = new Solution(head);

# // getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
# solution.getRandom();


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

import random

class LinkedListRandomNote(object):

    def __init__(self, head):
        """
        @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node.
        :type head: ListNode
        """
        self.head_ = head
        self.buff_ = []
        
        while head:
            self.buff_.append(head)
            head = head.next

        self.length_ = len(self.buff_)

    def getRandom(self):
        """
        Returns a random node's value.
        :rtype: int
        """
        return self.buff_[random.randint(0, self.length_-1)].val


# Your Solution object will be instantiated and called as such:
# obj = Solution(head)
# param_1 = obj.getRandom()



class LinkedListRandomNote(object):

    def __init__(self, head):

        self.head_ = head

    def getRandom(self):

        note = head
        before = 0
        buff = [None] * 100

        while note:
            now = 0
            while node and now < 100:
                buff[now] = note
                note = note.next
                now += 1

            r = random.randrange(now + before)
            if r < now:
                pick = buff[r]

            before += now
    
        return pick.val
            
    

if __name__=="__main__":


    head = ListNode(1);
    head.next = ListNode(2);
    head.next.next = ListNode(3);

    obj = LinkedListRandomNote(head)

    res = obj.getRandom()
    
    


    pass
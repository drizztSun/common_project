# 707. Design Linked List

# Design your implementation of the linked list. You can choose to use the singly linked list or the doubly linked list. 
# A node in a singly linked list should have two attributes: val and next. val is the value of the current node, 
# and next is a pointer/reference to the next node. If you want to use the doubly linked list, 
# you will need one more attribute prev to indicate the previous node in the linked list. 
# 
# Assume all nodes in the linked list are 0-indexed.

# Implement these functions in your linked list class:

# get(index) : Get the value of the index-th node in the linked list. If the index is invalid, return -1.

# addAtHead(val) : Add a node of value val before the first element of the linked list. 
# After the insertion, the new node will be the first node of the linked list.

# addAtTail(val) : Append a node of value val to the last element of the linked list.

# addAtIndex(index, val) : Add a node of value val before the index-th node in the linked list.
# If index equals to the length of linked list, the node will be appended to the end of linked list. 
# If index is greater than the length, the node will not be inserted.

# deleteAtIndex(index) : Delete the index-th node in the linked list, if the index is valid.

# Example:

# MyLinkedList linkedList = new MyLinkedList();
# linkedList.addAtHead(1);
# linkedList.addAtTail(3);
# linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
# linkedList.get(1);            // returns 2
# linkedList.deleteAtIndex(1);  // now the linked list is 1->3
# linkedList.get(1);            // returns 3

# the best solution is python list
# How Python implement list
class MyLinkedList1:
    
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.linkedlist = list()
        

    def get(self, index):
        """
        Get the value of the index-th node in the linked list. If the index is invalid, return -1.
        :type index: int
        :rtype: int
        """
        if index < 0 or index >= len(self.linkedlist):
            return -1
        else:
            return self.linkedlist[index]
        

    def addAtHead(self, val):
        """
        Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
        :type val: int
        :rtype: void
        """
        self.linkedlist.insert(0, val)
        

    def addAtTail(self, val):
        """
        Append a node of value val to the last element of the linked list.
        :type val: int
        :rtype: void
        """
        self.linkedlist.append(val)
        

    def addAtIndex(self, index, val):
        """
        Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
        :type index: int
        :type val: int
        :rtype: void
        """
        if 0 <= index and index <= len(self.linkedlist):
            self.linkedlist.insert(index, val)

    def deleteAtIndex(self, index):
        """
        Delete the index-th node in the linked list, if the index is valid.
        :type index: int
        :rtype: void
        """
        if 0 <= index and index < len(self.linkedlist):
            self.linkedlist.pop(index)
   

# ring, but get is still O(n)
class MyLinkedList2:

    class __Node:
        def __init__(self, val=0, prev=None, next=None):
            self.val, self.prev, self.next = val, prev, next

        def insertBefore(self, n):
            n.prev, n.next, self.prev.next, self.prev = self.prev, self, n, n

        def insertAfter(self, n):
            n.prev, n.next, self.next.prev, self.next = self, self.next, n, n

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.__size, self.__dummy = 0, MyLinkedList.__Node()
        self.__dummy.next = self.__dummy.prev = self.__dummy
        
    def size(self):
        return self.__size
        
    def __get(self, index):
        if index < 0 or self.__size <= index:
            return None
        i = self.__dummy
        if index <= self.__size // 2:
            for j in range(index + 1):
                i = i.next
        else:
            for j in range(self.__size - index):
                i = i.prev
        return i

    def get(self, index):
        """
        Get the value of the index-th node in the linked list. If the index is invalid, return -1.
        :type index: int
        :rtype: int
        """
        ans = self.__get(index)
        return ans.val if ans else -1

    def addAtHead(self, val):
        """
        Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
        :type val: int
        :rtype: void
        """
        self.__dummy.insertAfter(MyLinkedList.__Node(val))
        self.__size += 1

    def addAtTail(self, val):
        """
        Append a node of value val to the last element of the linked list.
        :type val: int
        :rtype: void
        """
        self.__dummy.insertBefore(MyLinkedList.__Node(val))
        self.__size += 1

    def addAtIndex(self, index, val):
        """
        Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
        :type index: int
        :type val: int
        :rtype: void
        """
        if index == self.__size:
            self.addAtTail(val)
        else:
            i = self.__get(index)
            if i:
                i.insertBefore(MyLinkedList.__Node(val))
                self.__size += 1

    def deleteAtIndex(self, index):
        """
        Delete the index-th node in the linked list, if the index is valid.
        :type index: int
        :rtype: void
        """
        i = self.__get(index)
        if i:
            i.prev.next, i.next.prev = i.next, i.prev
            self.__size -= 1


class MyLinkedList:

    class __node:

        def __init__(self, val):
            self.val = val
            self.pre, self.next = None, None
            

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.head, self.tail = MyLinkedList.__node("head"), MyLinkedList.__node("tail")
        self.head.next, self.tail.pre = self.tail, self.head
        self.buff = []


    def get(self, index):
        """
        Get the value of the index-th node in the linked list. If the index is invalid, return -1.
        :type index: int
        :rtype: int
        """
        if index >= len(self.buff):
            return -1

        return self.buff[index].val
            

    def addAtHead(self, val):
        """
        Add a node of value val before the first element of the linked list. 
        After the insertion, the new node will be the first node of the linked list.
        :type val: int
        :rtype: void
        """
        n = MyLinkedList.__node(val)
        self.buff.insert(0, n)

        n.next, n.pre, self.head.next.pre, self.head.next = self.head.next, self.head, n, n
        # next = self.head.next
        # self.head.next, n.next, next.pre, n.pre = n, next, n, self.head
            

    def addAtTail(self, val):
        """
        Append a node of value val to the last element of the linked list.
        :type val: int
        :rtype: void
        """
        n = MyLinkedList.__node(val)
        self.buff.append(n)
        
        #self.tail.pre, n.pre, n.next, self.tail.pre.next = n, self.tail.pre, self.tail, n 
        n.next, n.pre, self.tail.pre.next, self.tail.pre = self.tail, self.tail.pre, n, n

    def addAtIndex(self, index, val):
        """
        Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, 
        the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted.
        :type index: int
        :type val: int
        :rtype: void
        """
        if index > len(self.buff):
            return

        if index == len(self.buff):
            self.addAtTail(val)
        else:
            n = MyLinkedList.__node(val)
            self.buff.insert(index, n)

            oldn = self.buff[index + 1]
            oldn.pre, n.pre, oldn.pre.next, n.next = n, oldn.pre, n, oldn.next        
        

    def deleteAtIndex(self, index):
        """
        Delete the index-th node in the linked list, if the index is valid.
        :type index: int
        :rtype: void
        """
        if index >= len(self.buff):
            return

        n = self.buff.pop(index)
        n.pre.next, n.next.pre = n.next, n.pre


if __name__ == "__main__":        

    # Your MyLinkedList object will be instantiated and called as such:

    linkedList = MyLinkedList()
    linkedList.addAtHead(1)
    linkedList.addAtTail(3)
    linkedList.addAtIndex(1, 2)
    res = linkedList.get(1)           
    linkedList.deleteAtIndex(1)
    res = linkedList.get(1)

    #["MyLinkedList","addAtHead","addAtIndex","get","get","get"]
    #[[],[1],[1,2],[1],[0],[2]]
    
    obj = MyLinkedList()
    obj.addAtHead(1)
    obj.addAtIndex(1,2)
    obj.get(1)
    obj.get(0)
    obj.get(2)

    res = 0
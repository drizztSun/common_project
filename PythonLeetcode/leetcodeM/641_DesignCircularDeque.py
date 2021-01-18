"""
641. Design Circular Deque

Design your implementation of the circular double-ended queue (deque).

Your implementation should support following operations:

MyCircularDeque(k): Constructor, set the size of the deque to be k.
insertFront(): Adds an item at the front of Deque. Return true if the operation is successful.
insertLast(): Adds an item at the rear of Deque. Return true if the operation is successful.
deleteFront(): Deletes an item from the front of Deque. Return true if the operation is successful.
deleteLast(): Deletes an item from the rear of Deque. Return true if the operation is successful.
getFront(): Gets the front item from the Deque. If the deque is empty, return -1.
getRear(): Gets the last item from Deque. If the deque is empty, return -1.
isEmpty(): Checks whether Deque is empty or not. 
isFull(): Checks whether Deque is full or not.
 

Example:

MyCircularDeque circularDeque = new MycircularDeque(3); // set the size to be 3
circularDeque.insertLast(1);			// return true
circularDeque.insertLast(2);			// return true
circularDeque.insertFront(3);			// return true
circularDeque.insertFront(4);			// return false, the queue is full
circularDeque.getRear();  			// return 2
circularDeque.isFull();				// return true
circularDeque.deleteLast();			// return true
circularDeque.insertFront(4);			// return true
circularDeque.getFront();			// return 4
 

Note:

All values will be in the range of [0, 1000].
The number of operations will be in the range of [1, 1000].
Please do not use the built-in Deque library.


"""


class MyCircularDeque:

    def __init__(self, k: int):
        """
        Initialize your data structure here. Set the size of the deque to be k.
        """
        self.size = k
        self.items = k*[None]
        self.front = -1
        self.rear = -1

    def insertFront(self, value: int) -> bool:
        """
        Adds an item at the front of Deque. Return true if the operation is successful.
        """
        if self.front == -1:
            self.front = self.rear = self.size - 1
            self.items[self.front] = value
            return True
        elif (self.rear+1)%self.size == self.front:
            return False
        elif self.front<1:
            self.front = self.size - 1
            self.items[self.front] = value
            return True
        else:
            self.front = self.front - 1
            self.items[self.front] = value
            return True

    def insertLast(self, value: int) -> bool:
        """
        Adds an item at the rear of Deque. Return true if the operation is successful.
        """
        if (self.rear+1)%self.size == self.front:
            return False
        elif self.front == -1:
            self.front = 0
            self.rear = 0
            self.items[self.rear] = value
            return True
        else:
            self.rear = (self.rear+1)%self.size
            self.items[self.rear] = value
            return True

        

    def deleteFront(self) -> bool:
        """
        Deletes an item from the front of Deque. Return true if the operation is successful.
        """
        if self.front == -1:
            return False
        elif self.front == self.rear:
            self.front = -1
            self.rear = -1
            return True
        else:
            self.front = (self.front+1)%self.size
            return True
        

    def deleteLast(self) -> bool:
        """
        Deletes an item from the rear of Deque. Return true if the operation is successful.
        """
        if self.front == -1:
            return False
        elif self.front == self.rear:
            self.front = -1
            self.rear = -1
            return True
        else:
            if self.rear>0:
                self.rear-=1
                return True
            else:
                self.rear = self.size - 1
                return True
    def getFront(self) -> int:
        """
        Get the front item from the deque.
        """
        if self.front == -1:
            return -1
        else:
            return self.items[self.front]

    def getRear(self) -> int:
        """
        Get the last item from the deque.
        """
        if self.front == -1:
            return -1
        else:
            return self.items[self.rear]
        

    def isEmpty(self) -> bool:
        """
        Checks whether the circular deque is empty or not.
        """
        return self.front == -1

    def isFull(self) -> bool:
        """
        Checks whether the circular deque is full or not.
        """
        return (self.rear+1)%self.size == self.front

    
class MyCircularDeque:

    def __init__(self, k):
        """
        Initialize your data structure here. Set the size of the deque to be k.
        :type k: int
        """
        self.buff = [-1] * k
        self.max_length = k
        self.size = 0
        self.start = 0
        

    def insertFront(self, value):
        """
        Adds an item at the front of Deque. Return true if the operation is successful.
        :type value: int
        :rtype: bool
        """
        if self.isFull():
            return False

        self.start = (self.start + self.max_length - 1) % self.max_length
        self.buff[self.start] = value
        self.size += 1
        return True
        

    def insertLast(self, value):
        """
        Adds an item at the rear of Deque. Return true if the operation is successful.
        :type value: int
        :rtype: bool
        """
        if self.isFull():
            return False

        self.buff[(self.start + self.size) % self.max_length] = value
        self.size += 1
        return True
        

    def deleteFront(self):
        """
        Deletes an item from the front of Deque. Return true if the operation is successful.
        :rtype: bool
        """
        if self.isEmpty():
            return False
        
        self.start = (self.start + 1) % self.max_length
        self.size -= 1

        return True
        

    def deleteLast(self):
        """
        Deletes an item from the rear of Deque. Return true if the operation is successful.
        :rtype: bool
        """
        if self.isEmpty():
            return False

        self.size -= 1

        return True

    def getFront(self):
        """
        Get the front item from the deque.
        :rtype: int 
        """
        return self.buff[self.start] if not self.isEmpty() else -1

    def getRear(self):
        """
        Get the last item from the deque.
        :rtype: int
        """
        return self.buff[(self.start + self.size - 1) % self.max_length] if not self.isEmpty() else -1

    def isEmpty(self):
        """
        Checks whether the circular deque is empty or not.
        :rtype: bool
        """
        return self.size == 0
        
    def isFull(self):
        """
        Checks whether the circular deque is full or not.
        :rtype: bool
        """
        return self.size == self.max_length
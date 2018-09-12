# 641. Design Circular Deque


# Design your implementation of the circular double-ended queue (deque).

# Your implementation should support following operations:

# MyCircularDeque(k): Constructor, set the size of the deque to be k.
# insertFront(): Adds an item at the front of Deque. Return true if the operation is successful.
# insertLast(): Adds an item at the rear of Deque. Return true if the operation is successful.
# deleteFront(): Deletes an item from the front of Deque. Return true if the operation is successful.
# deleteLast(): Deletes an item from the rear of Deque. Return true if the operation is successful.
# getFront(): Gets the front item from the Deque. If the deque is empty, return -1.
# getRear(): Gets the last item from Deque. If the deque is empty, return -1.
# isEmpty(): Checks whether Deque is empty or not. 
# isFull(): Checks whether Deque is full or not.
 

# Example:

# MyCircularDeque circularDeque = new MycircularDeque(3); // set the size to be 3
# circularDeque.insertLast(1);			// return true
# circularDeque.insertLast(2);			// return true
# circularDeque.insertFront(3);			// return true
# circularDeque.insertFront(4);			// return false, the queue is full
# circularDeque.getRear();  			// return 3
# circularDeque.isFull();				// return true
# circularDeque.deleteLast();			// return true
# circularDeque.insertFront(4);			// return true
# circularDeque.getFront();			// return 4


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




class MyCircularDeque1:

    def __init__(self, k):
        """
        Initialize your data structure here. Set the size of the deque to be k.
        :type k: int
        """
        self.size = k
        self.queue = [0]*k
        self.rear = -1
        self.front = -1
        self.len = 0

    def insertFront(self, value):
        """
        Adds an item at the front of Deque. Return true if the operation is successful.
        :type value: int
        :rtype: bool
        """
        if self.len == self.size:
            return False
        elif self.len == 0:
            self.front = 0
            self.rear = 0
            self.queue[self.front] = value
            self.len +=1
            return True
        if self.front-1 <0:
            self.front = self.size -1
            self.queue[self.front] = value
            self.len +=1
            return True
        self.front -= 1
        self.queue[self.front] = value
        self.len += 1
        return True      

    def insertLast(self, value):
        """
        Adds an item at the rear of Deque. Return true if the operation is successful.
        :type value: int
        :rtype: bool
        """
        if self.len == self.size:
            return False
        elif self.len == 0:
            self.front = 0
        self.rear = (self.rear + 1) % self.size
        self.queue[self.rear] = value
        self.len += 1
        return True

    def deleteFront(self):
        """
        Deletes an item from the front of Deque. Return true if the operation is successful.
        :rtype: bool
        """
        if self.len == 0:
            return False
        elif self.front == self.rear:
            self.front = -1
            self.rear = -1
            self.len -= 1
            return True
        self.front = (self.front + 1) % self.size
        self.len -= 1
        return True

    def deleteLast(self):
        """
        Deletes an item from the rear of Deque. Return true if the operation is successful.
        :rtype: bool
        """
        if self.len == 0:
            return False
        elif self.front == self.rear:
            self.front = -1
            self.rear = -1
            self.len -= 1
            return True
        if self.rear-1 <0:
            self.rear = self.size -1
            self.len -=1
            return True
        self.rear -= 1
        self.len -= 1
        return True

    def getFront(self):
        """
        Get the front item from the deque.
        :rtype: int
        """
        if self.len == 0:
            return -1
        return self.queue[self.front]        

    def getRear(self):
        """
        Get the last item from the deque.
        :rtype: int
        """
        if self.len == 0:
            return -1
        return self.queue[self.rear]

    def isEmpty(self):
        """
        Checks whether the circular deque is empty or not.
        :rtype: bool
        """
        if self.len == 0:
            return True
        return False
        

    def isFull(self):
        """
        Checks whether the circular deque is full or not.
        :rtype: bool
        """
        if self.len == self.size:
            return True
        return False



if __name__ == "__main__":

    obj = MyCircularDeque(3)

    res = obj.insertLast(1)
    res = obj.insertLast(2)
    res = obj.insertFront(3)
    res = obj.insertFront(4)

    res = obj.getRear()
    res = obj.isFull()
    res = obj.deleteLast()
    res = obj.insertFront(4)
    res = obj.getFront()

    res = 1
       
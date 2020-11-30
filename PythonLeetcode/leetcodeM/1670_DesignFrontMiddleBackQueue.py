"""
1670. Design Front Middle Back Queue

Design a queue that supports push and pop operations in the front, middle, and back.

Implement the FrontMiddleBack class:

FrontMiddleBack() Initializes the queue.
void pushFront(int val) Adds val to the front of the queue.
void pushMiddle(int val) Adds val to the middle of the queue.
void pushBack(int val) Adds val to the back of the queue.
int popFront() Removes the front element of the queue and returns it. If the queue is empty, return -1.
int popMiddle() Removes the middle element of the queue and returns it. If the queue is empty, return -1.
int popBack() Removes the back element of the queue and returns it. If the queue is empty, return -1.
Notice that when there are two middle position choices, the operation is performed on the frontmost middle position choice. For example:

Pushing 6 into the middle of [1, 2, 3, 4, 5] results in [1, 2, 6, 3, 4, 5].
Popping the middle from [1, 2, 3, 4, 5, 6] returns 3 and results in [1, 2, 4, 5, 6].


Example 1:

Input:
["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
[[], [1], [2], [3], [4], [], [], [], [], []]
Output:
[null, null, null, null, null, 1, 3, 4, 2, -1]

Explanation:
FrontMiddleBackQueue q = new FrontMiddleBackQueue();
q.pushFront(1);   // [1]
q.pushBack(2);    // [1, 2]
q.pushMiddle(3);  // [1, 3, 2]
q.pushMiddle(4);  // [1, 4, 3, 2]
q.popFront();     // return 1 -> [4, 3, 2]
q.popMiddle();    // return 3 -> [4, 2]
q.popMiddle();    // return 4 -> [2]
q.popBack();      // return 2 -> []
q.popFront();     // return -1 -> [] (The queue is empty)


Constraints:

1 <= val <= 109
At most 1000 calls will be made to pushFront, pushMiddle, pushBack, popFront, popMiddle, and popBack.


"""


class FrontMiddleBackQueue:

    class node:
        def __init__(self, val):
            self._val = val
            self._prev = self._next = None

        def connect(self, node):
            self._next = node
            node._prev = self

    def __init__(self):
        self._head, self._tail = FloatingPointError.node(float('inf')), FloatingPointError.node(float('-inf'))
        self._head.connect(self._tail)
        self._length = 0
        self._mid = None

    def pushFront(self, val: int) -> None:

        s = FrontMiddleBackQueue.node(val)
        s.connect(self._head._next)
        self._head.connect(s)

        if self._length == 0:
            self._mid = self._head._next
        elif self._length % 2 == 1:
            self._mid = self._mid._prev
        self._length += 1


    def pushMiddle(self, val: int) -> None:

        s = FrontMiddleBackQueue.node(val)

        if self._length == 0:
            s.connect(self._head._next)
            self._head.connect(s)
            self._mid = s
        elif self._length % 2 == 0:
            s.connect(self._mid._next)
            self._mid.connect(s)
            self._mid = self._mid._next
        else:
            self._mid._prev.connect(s)
            s.connect(self._mid)
            self._mid = self._mid._prev

        self._length += 1

    def pushBack(self, val: int) -> None:

        s = FrontMiddleBackQueue.node(val)
        self._tail._prev.connect(s)
        s.connect(self._tail)

        if self._length == 0:
            self._mid = self._head._next
        elif self._length % 2 == 0:
            self._mid = self._mid._next

        self._length += 1

    def popFront(self) -> int:
        if self._length == 0:
            return -1

        ret = self._head._next._val
        if self._length % 2 == 0:
            self._mid = self._mid._next
        self._head.connect(self._head._next._next)
        self._length -= 1
        return ret

    def popMiddle(self) -> int:

        if self._length == 0:
            return -1

        ret = self._mid._val

        tmp = self._mid
        if self._length % 2 == 1:
            self._mid = self._mid._prev
        else:
            self._mid = self._mid._next

        tmp._prev.connect(tmp._next)
        self._length -= 1
        return ret

    def popBack(self) -> int:
        if self._length == 0:
            return -1
        ret = self._tail._prev._val

        if self._length % 2 == 1:
            self._mid = self._mid._prev

        self._tail._prev._prev.connect(self._tail)
        self._length -= 1
        return ret
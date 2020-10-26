"""
716. Max Stack

Design a max stack that supports push, pop, top, peekMax and popMax.

push(x) -- Push element x onto stack.
pop() -- Remove the element on top of the stack and return it.
top() -- Get the element on the top.
peekMax() -- Retrieve the maximum element in the stack.
popMax() -- Retrieve the maximum element in the stack, and remove it. If you find more than one maximum elements, only remove the top-most one.
Example 1:
MaxStack stack = new MaxStack();
stack.push(5);
stack.push(1);
stack.push(5);
stack.top(); -> 5
stack.popMax(); -> 5
stack.top(); -> 1
stack.peekMax(); -> 5
stack.pop(); -> 1
stack.top(); -> 5
Note:
-1e7 <= x <= 1e7
Number of operations won't exceed 10000.
The last four operations won't be called when stack is empty.


"""


class MaxStack:
    """
    Approach #1: Two Stacks [Accepted]
    Intuition and Algorithm

    A regular stack already supports the first 3 operations, so we focus on the last two.

    For peekMax, we remember the largest value we've seen on the side. For example if we add [2, 1, 5, 3, 9], we'll remember [2, 2, 5, 5, 9]. This works seamlessly with pop operations, and also it's easy to compute: it's just the maximum of the element we are adding and the previous maximum.

    For popMax, we know what the current maximum (peekMax) is. We can pop until we find that maximum, then push the popped elements back on the stack.

    Our implementation in Python will showcase extending the list class.

    Complexity Analysis

    Time Complexity: O(N) for the popMax operation, and O(1) for the other operations, where NN is the number of operations performed.

    Space Complexity: O(N), the maximum size of the stack.
    """
    def __init__(self):
        self._elements = []

    def push(self, x):
        m = max(x, self._elements[-1][1] if self._elements else x)
        self._elements.append((x, m))

    def pop(self):
        return self._elements.pop()[0]

    def top(self):
        return self._elements[-1][0]

    def peekMax(self):
        return self._elements[-1][1]

    def popMax(self):
        m = self.peekMax()
        b = []
        while self._elements[-1][0] != m:
            b.append(self.pop())

        self._elements.pop()
        for i in reversed(range(len(b))):
            self.push(b[i])
        return m


import heapq


class MaxStackII:

    """
    A regular stack already supports the first 3 operations and max heap can take care of the last two.
    But the main issue is when popping an element form the top of one data structure how can we efficiently remove that element from the other.
    We can use lazy removal (similar to Approach #2 from 480. Sliding Window Median) to achieve this is in average O(log N) time.
    """

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.stack = []
        self.maxHeap = []
        self.toPop_heap = {}  # to keep track of things to remove from the heap
        self.toPop_stack = set()  # to keep track of things to remove from the stack

    def push(self, x):
        """
        :type x: int
        :rtype: void
        """
        heapq.heappush(self.maxHeap, (-x, -len(self.stack)))
        self.stack.append(x)

    def pop(self):
        """
        :rtype: int
        """
        self.top()
        x = self.stack.pop()
        key = (-x, -len(self.stack))
        self.toPop_heap[key] = self.toPop_heap.get(key, 0) + 1
        return x

    def top(self):
        """
        :rtype: int
        """
        while self.stack and len(self.stack) - 1 in self.toPop_stack:
            x = self.stack.pop()
            self.toPop_stack.remove(len(self.stack))
        return self.stack[-1]

    def peekMax(self):
        """
        :rtype: int
        """
        while self.maxHeap and self.toPop_heap.get(self.maxHeap[0], 0):
            x = heapq.heappop(self.maxHeap)
            self.toPop_heap[x] -= 1
        return -self.maxHeap[0][0]

    def popMax(self):
        """
        :rtype: int
        """
        self.peekMax()
        x, idx = heapq.heappop(self.maxHeap)
        x, idx = -x, -idx
        self.toPop_stack.add(idx)
        return x


import bisect



class MaxStackIII:

    class node:
        def __init__(self, val):
            self._val = val
            self._next = None
            self._pre = None

    def __init__(self):
        """
        initialize your data structure here.
        """
        self._elements = MaxStackIII.node(float('inf'))
        self._max_v = []
        self._max_refer = []

    def push(self, x: int):
        n = MaxStackIII.node(x)

        if self._elements._next == None:
            self._elements._next, n._pre = n, self._elements
        else:
            n._next, n._pre = self._elements._next, self._elements
            self._elements._next, self._elements._next._pre = n, n
            #self._elements._next, n._next, self._elements._next._pre, n._pre = n, self._elements._next, n, self._elements

        i = bisect.bisect_right(self._max_v, x)
        self._max_v.insert(i, x)
        self._max_refer.insert(i, n)

    def pop(self) -> int:
        n = self._elements._next._val
        self._elements._next, self._elements._next._next._pre = self._elements._next._next, self._elements
        i = bisect.bisect_right(self._max_v, n)
        self._max_v.pop(i-1)
        self._max_refer.pop(i-1)
        return n

    def top(self) -> int:
        return self._elements._next._val

    def peekMax(self) -> int:
        return self._max_v[-1]

    def popMax(self) -> int:
        c = self._max_v.pop()
        n = self._max_refer.pop()
        n._next._pre, n._pre._next = n._pre, n._next
        return c


if __name__ == '__main__':

    obj = MaxStackIII()

    obj.push(5)
    obj.push(1)
    obj.push(5)

    r = obj.top()
    r = obj.popMax()
    r = obj.top()

    r = obj.peekMax()
    r = obj.pop()
    r = obj.top()


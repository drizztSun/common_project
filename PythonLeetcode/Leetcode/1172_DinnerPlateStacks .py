"""
1172. Dinner Plate Stacks

You have an infinite number of stacks arranged in a row and numbered (left to right) from 0, each of the stacks has the same maximum capacity.

Implement the DinnerPlates class:

DinnerPlates(int capacity) Initializes the object with the maximum capacity of the stacks.
void push(int val) Pushes the given positive integer val into the leftmost stack with size less than capacity.
int pop() Returns the value at the top of the rightmost non-empty stack and removes it from that stack, and returns -1 if all stacks are empty.
int popAtStack(int index) Returns the value at the top of the stack with the given index and removes it from that stack, and returns -1 if the stack with that given index is empty.
Example:

Input:
["DinnerPlates","push","push","push","push","push","popAtStack","push","push","popAtStack","popAtStack","pop","pop","pop","pop","pop"]
[[2],[1],[2],[3],[4],[5],[0],[20],[21],[0],[2],[],[],[],[],[]]
Output:
[null,null,null,null,null,null,2,null,null,20,21,5,4,3,1,-1]

Explanation:
DinnerPlates D = DinnerPlates(2);  // Initialize with capacity = 2
D.push(1);
D.push(2);
D.push(3);
D.push(4);
D.push(5);         // The stacks are now:  2  4
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.popAtStack(0);   // Returns 2.  The stacks are now:     4
                                                       1  3  5
                                                       ﹈ ﹈ ﹈
D.push(20);        // The stacks are now: 20  4
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.push(21);        // The stacks are now: 20  4 21
                                           1  3  5
                                           ﹈ ﹈ ﹈
D.popAtStack(0);   // Returns 20.  The stacks are now:     4 21
                                                        1  3  5
                                                        ﹈ ﹈ ﹈
D.popAtStack(2);   // Returns 21.  The stacks are now:     4
                                                        1  3  5
                                                        ﹈ ﹈ ﹈
D.pop()            // Returns 5.  The stacks are now:      4
                                                        1  3
                                                        ﹈ ﹈
D.pop()            // Returns 4.  The stacks are now:   1  3
                                                        ﹈ ﹈
D.pop()            // Returns 3.  The stacks are now:   1
                                                        ﹈
D.pop()            // Returns 1.  There are no stacks.
D.pop()            // Returns -1.  There are still no stacks.


Constraints:

1 <= capacity <= 20000
1 <= val <= 20000
0 <= index <= 100000
At most 200000 calls will be made to push, pop, and popAtStack.

"""
from heapq import heappush, heappop


class DinnerPlates:

    def __init__(self, capacity: int):

        self._cap = capacity
        self.st = [[]]
        self.l, self.r = 0, 0

    def push(self, val: int) -> None:
        self.st[self.l].append(val)
        if self.r < self.l:
            self.r = self.l

        self.st[self.l].append(val)

        if len(self.st[self.l]) < self._cap:
            return
        i = self.l+1
        while i < len(self.st):
            if len(self.st[i]) == self._cap:
                self.l = i
                break
            i += 1

        if i == len(self.st):
            self._st.append([])
            self.l = i
        return

    def pop(self) -> int:
        if self.r < 0 or len(self.st[self.r]) == 0:
            return -1

        rvt = self.st[self.r][-1]
        self.st[self.r].pop()

        while self.r >= 0 and len(self.st[self.r]) == 0:
            self.r -= 1

        if self.r == -1:
            self.l = 0

        return rvt

    def popAtStack(self, index: int) -> int:

        if index >= len(self.st) or not self.st[index]:
            return -1

        rvt = self.st[self.r][-1]
        self.st[self.r].pop()

        if self.r == index:
            while self.r >= 0 and not self.st[self.r]:
                self.r -= 1

        if index == self.l:
            self.l = index

        if self.r == -1:
            self.l = 0

        return rvt


class DinnerPlates:

    def __init__(self, capacity: int):
        from collections import deque
        self._cap = capacity
        self._deq = deque()
        self._less_slot = set()
        self._idx = []

    def push(self, val: int) -> None:

        if not self._idx:
            self._deq.append([])
            heappush(self._idx, len(self._deq)-1)
            self._less_slot.add(len(self._deq)-1)

        idx = heappop(self._idx)
        self._less_slot.remove(idx)
        self._deq[idx].append(val)

        if len(self._deq[idx]) != self._cap:
            heappush(self._idx, idx)
            self._less_slot.add(idx)

    def pop(self) -> int:

        while self._deq and len(self._deq[-1]) == 0:
            self._deq.pop()

        if not self._deq:
            return -1

        return self._deq[-1].pop()

    def popAtStack(self, index: int) -> int:

        if index >= len(self._deq) or not self._deq[index]:
            return -1

        rvt = self._deq[index].pop()
        if index not in self._less_slot:
            self._less_slot.add(index)
            heappush(self._idx, index)
        return rvt


if __name__ == '__main__':

    obj = DinnerPlates(2)

    obj.push(1)
    obj.push(2)
    obj.push(3)
    obj.push(4)
    obj.push(5)

    obj.popAtStack(0)

    obj.push(20)
    obj.push(21)
    obj.popAtStack(0)
    obj.popAtStack(2)

    obj.pop()
    obj.pop()
    obj.pop()
    obj.pop()
    obj.pop()
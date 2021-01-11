"""
1381. Design a Stack With Increment Operation

Design a stack which supports the following operations.

Implement the CustomStack class:

CustomStack(int maxSize) Initializes the object with maxSize which is the maximum number of elements in the stack or do nothing if the stack reached the maxSize.
void push(int x) Adds x to the top of the stack if the stack hasn't reached the maxSize.
int pop() Pops and returns the top of stack or -1 if the stack is empty.
void inc(int k, int val) Increments the bottom k elements of the stack by val. If there are less than k elements in the stack, just increment all the elements in the stack.
 

Example 1:

Input
["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
[[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
Output
[null,null,null,2,null,null,null,null,null,103,202,201,-1]
Explanation
CustomStack customStack = new CustomStack(3); // Stack is Empty []
customStack.push(1);                          // stack becomes [1]
customStack.push(2);                          // stack becomes [1, 2]
customStack.pop();                            // return 2 --> Return top of the stack 2, stack becomes [1]
customStack.push(2);                          // stack becomes [1, 2]
customStack.push(3);                          // stack becomes [1, 2, 3]
customStack.push(4);                          // stack still [1, 2, 3], Don't add another elements as size is 4
customStack.increment(5, 100);                // stack becomes [101, 102, 103]
customStack.increment(2, 100);                // stack becomes [201, 202, 103]
customStack.pop();                            // return 103 --> Return top of the stack 103, stack becomes [201, 202]
customStack.pop();                            // return 202 --> Return top of the stack 102, stack becomes [201]
customStack.pop();                            // return 201 --> Return top of the stack 101, stack becomes []
customStack.pop();                            // return -1 --> Stack is empty return -1.
 

Constraints:

1 <= maxSize <= 1000
1 <= x <= 1000
1 <= k <= 1000
0 <= val <= 100
At most 1000 calls will be made to each method of increment, push and pop each separately.


"""


from bisect import insort, bisect_right
class CustomStack:

    def __init__(self, maxSize: int):
        self._buff = []
        self._maxsize = maxSize
        self._ops = []

    def push(self, x: int) -> None:
        if len(self._buff) < self._maxsize:
            self._buff.append(x)
            self._ops.append(0)

    def pop(self) -> int:
        if not self._buff: 
            return -1

        if len(self._ops) > 1:
            self._ops[-2] += self._ops[-1]
        return self._buff.pop() + self._ops.pop()

    def increment(self, k: int, val: int) -> None:
        i = min(k-1, len(self._buff)-1)
        if i >= 0:
            self._ops[i] += val

class CustomStack:
    def __init__(self, maxSize: int):
        self.stack = []
        self.increments = []
        self.maxSize = maxSize
    '''
    注意
    void push(int x) Adds x to the top of the stack if the stack hasn't reached the maxSize.
    '''
    def push(self, x: int) -> None:
        # self.stack.push(x)
        if len(self.stack) < self.maxSize:
            self.stack.append(x)
            self.increments.append(0)

    def pop(self) -> int:
        if not self.stack:
            return -1

        topI = len(self.stack) - 1
        if topI - 1 >= 0:
            # 因为Increments the bottom k elements of the stack, 因此如果stack[topI]递增, stack[topI-1]也要递增
            # self.increments[topI - 1] += self.increments[topI]
            self.increments[-2] += self.increments[-1]  # 或者
        # return self.stack.pop()
        return self.stack.pop() + self.increments.pop()

    def increment(self, k: int, val: int) -> None:
        i = min(len(self.stack), k) - 1
        if i >= 0:
            self.increments[i] += val

class CustomStack:

    def __init__(self, maxSize: int):
        self.stack=[]
        self.maxSize=maxSize
        

    def push(self, x: int) -> None:
        if len(self.stack)<self.maxSize:
            self.stack.append(x)

    def pop(self) -> int:
        if self.stack:
            return self.stack.pop()
        else:
            return -1
        
    def increment(self, k: int, val: int) -> None:
        n=min(k,len(self.stack))
        for i in range(0,n):
            self.stack[i]+=val


if __name__ == '__main__':

    obj = CustomStack(3)

    obj.push(1)
    obj.push(2)

    obj.pop()
    obj.push(2)
    obj.push(3)
    obj.push(4)

    obj.increment(5, 100)
    obj.increment(2, 100)

    obj.pop()
    obj.pop()
    obj.pop()
    obj.pop()
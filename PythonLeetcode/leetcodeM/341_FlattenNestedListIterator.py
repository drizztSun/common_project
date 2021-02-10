"""
341. Flatten Nested List Iterator

Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:

Input: [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,1,2,1,1].
Example 2:

Input: [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,4,6].

"""


# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
#class NestedInteger:
#    def isInteger(self) -> bool:
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        """
#
#    def getInteger(self) -> int:
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        """
#
#    def getList(self) -> [NestedInteger]:
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        """
class NestedIterator:

    def __init__(self, nestedList):
        self._buf = []
        for i in reversed(range(len(nestedList))):
            self._buf.append(nestedList[i])

    def next(self):
        return self._buf.pop().getInteger()

    def hasNext(self):

        while self._buf:
            if self._buf[-1].isInteger():
                return True

            newlist = self._buf.pop().getList()
            for i in reversed(range(len(newlist))):
                self._buf.append(newlist[i])

        return False


"""
Approach 1: Make a Flat List with Recursion
Intuition

The simplest way of solving this problem is to flatten the entire input list, in the constructor. Then the actual iterator methods can simply work with this flattened list instead of needing to worry about the input structure.

This approach splits the coding into two parts:

A function that the constructor can call to make a flattened list.
next() and hasNext() methods that iterate over a plain list, by keeping track of the current position within it.
The first part is best done with recursion (iteration is more complicated, and if you were going to use it, then you may as well look at approaches 2, 3, and 4 instead). This approach is the only recursive one that works in any programming language (as of the time of writing this article, things are changing!).

To flatten the list recursively, notice that we can look at the input as a tree. The integers are the leaf nodes, and the order they should be returned is from left to right.

Current
1 / 5
Therefore, we can use a recursive depth-first search to flatten it.

integers = []

define function flattenList(nestedList):
    for nestedInteger in nestedList:
        if nestedInteger.isInteger():
            append nestedInteger.getInteger() to integers
        else:
            recursively call flattenList on nestedInteger.getList()
Here is an animation showing the flattening algorithm.

Current
1 / 47
Algorithm


Complexity Analysis

Let NN be the total number of integers within the nested list, LL be the total number of lists within the nested list, and DD be the maximum nesting depth (maximum number of lists inside each other).

Time complexity:

We'll analyze each of the methods separately.

Constructor: O(N + L)O(N+L).

The constructor is where all the time-consuming work is done.

For each list within the nested list, there will be one call to flattenList(...). The loop within flattenList(...) will then iterate nn times, where nn is the number of integers within that list. Across all calls to flattenList(...), there will be a total of NN loop iterations. Therefore, the time complexity is the number of lists plus the number of integers, giving us O(N + L)O(N+L).

Notice that the maximum depth of the nesting does not impact the time complexity.

next(): O(1)O(1).

Getting the next element requires incrementing position by 1 and accessing an element at a particular index of the integers list. Both of these are O(1)O(1) operations.

hasNext(): O(1)O(1).

Checking whether or not there is a next element requires comparing the length of the integers list to the position variable. This is an O(1)O(1) operation.

Space complexity : O(N + D)O(N+D).

The most obvious auxiliary space is the integers list. The length of this is O(N)O(N).

The less obvious auxiliary space is the space used by the flattenList(...) function. Recall that recursive functions need to keep track of where they're up to by putting stack frames on the runtime stack. Therefore, we need to determine what the maximum number of stack frames there could be at a time is. Each time we encounter a nested list, we call flattenList(...) and a stack frame is added. Each time we finish processing a nested list, flattenList(...) returns and a stack frame is removed. Therefore, the maximum number of stack frames on the runtime stack is the maximum nesting depth, DD.

Because these two operations happen one-after-the-other, and either could be the largest, we add their time complexities together giving a final result of O(N + D)O(N+D).

"""
class NestedIterator:
    
    def __init__(self, nestedList: [NestedInteger]):
        def flatten_list(nested_list):
            for nested_integer in nested_list:
                if nested_integer.isInteger():
                    self._integers.append(nested_integer.getInteger())
                else:
                    flatten_list(nested_integer.getList()) 
        self._integers = []
        self._position = -1 # Pointer to previous returned.
        flatten_list(nestedList)
    
    def next(self) -> int:
        self._position += 1
        return self._integers[self._position]
        
    def hasNext(self) -> bool:
        return self._position + 1 < len(self._integers)


"""
Approach 2: Stack
Intuition

The downside of Approach 1 is that it creates a new data structure instead of simply iterating over the given one. Instead, we should find a way to step through the integers, one at a time, keeping track of where we're currently up to in nestedList.

Algorithm

Let's define a private method called makeStackTopAnInteger() that contains the algorithm to make the stack top an integer (as described above). The makeStackTopAnInteger() method never removes integers.

The next() and hasNext() methods should call makeStackTopAnInteger() before doing anything else. This means that they can then assume that either the stack top is an integer, or the stack is empty. Then, their definitions are as follows:

hasNext(): Returns true if the stack still contains items, false if not.
next(): If the stack still contains items, then it is guaranteed the top is an integer. This integer is popped and returned. If the stack is empty, then the behavior is language-dependent. For example, in Java, a NoSuchElementException should be throw.

Complexity Analysis

Let NN be the total number of integers within the nested list, LL be the total number of lists within the nested list, and DD be the maximum nesting depth (maximum number of lists inside each other).

Time complexity.

Constructor: O(N + L)O(N+L).

The worst-case occurs when the initial input nestedList consists entirely of integers and empty lists (everything is in the top-level). In this case, every item is reversed and stored, giving a total time complexity of O(N + L)O(N+L).

makeStackTopAnInteger(): O( 
N
L
​	
 ) or O(1).

If the top of the stack is an integer, then this function does nothing; taking O(1)O(1) time.

Otherwise, it needs to process the stack until an integer is on top. The best way of analyzing the time complexity is to look at the total cost across all calls to makeStackTopAnInteger() and then divide by the number of calls made. Once the iterator is exhausted makeStackTopAnInteger() must have seen every integer at least once, costing O(N)O(N) time. Additionally, it has seen every list (except the first) on the stack at least once also, so this costs O(L)O(L) time. Adding these together, we get O(N + L)O(N+L) time.

The amortized time of a single makeStackTopAnInteger is the total cost, O(N + L)O(N+L), divided by the number of times it's called. In order to get all integers, we need to have called it NN times. This gives us an amortized time complexity of \dfrac{O(N + L)}{N} = O(\dfrac{N}{N} + \dfrac{L}{N}) = O(\dfrac{L}{N}) 
N
O(N+L)
​	
 =O( 
N
N
​	
 + 
N
L
​	
 )=O( 
N
L
​	
 ).

next(): O(\dfrac{L}{N})O( 
N
L
​	
 ) or O(1)O(1).

All of this method is O(1)O(1), except for possibly the call to makeStackTopAnInteger(), giving us a time complexity the same as makeStackTopAnInteger().

hasNext(): O(\dfrac{L}{N})O( 
N
L
​	
 ) or O(1)O(1).

All of this method is O(1)O(1), except for possibly the call to makeStackTopAnInteger(), giving us a time complexity the same as makeStackTopAnInteger().

Space complexity : O(N + L)O(N+L).

In the worst case, where the top list contains NN integers, or LL empty lists, it will cost O(N + L)O(N+L) space. Other expensive cases occur when the nesting is very deep. However, it's useful to remember that D ≤ LD≤L (because each layer of nesting requires another list), and so we don't need to take this into account.
"""
class NestedIterator:
    
    def __init__(self, nestedList: [NestedInteger]):
        self.stack = list(reversed(nestedList))
        
        
    def next(self) -> int:
        self.make_stack_top_an_integer()
        return self.stack.pop().getInteger()
    
        
    def hasNext(self) -> bool:
        self.make_stack_top_an_integer()
        return len(self.stack) > 0
        
        
    def make_stack_top_an_integer(self):
        # While the stack contains a nested list at the top...
        while self.stack and not self.stack[-1].isInteger():
            # Unpack the list at the top by putting its items onto
            # the stack in reverse order.
            self.stack.extend(reversed(self.stack.pop().getList()))

"""
Approach 3: Two Stacks
Intuition

Reversing the lists to put them onto the stack can be an expensive operation, and it turns out it isn't necessary.

Instead of pushing every item of a sub-list onto the stack, we can instead associate an index pointer with each sub-list, that keeps track of how far along that sub-list we are. Adding a new sub-list to the stack now becomes an O(1)O(1) operation instead of a O(length of sublist)O(lengthofsublist) one.

Here is an animation showing this approach.


"""
class NestedIterator:
    
    def __init__(self, nestedList: [NestedInteger]):
        self.stack = [[nestedList, 0]]
        
    def make_stack_top_an_integer(self):
        
        while self.stack:
            
            # Essential for readability :)
            current_list = self.stack[-1][0]
            current_index = self.stack[-1][1]
            
            # If the top list is used up, pop it and its index.
            if len(current_list) == current_index:
                self.stack.pop()
                continue
            
            # Otherwise, if it's already an integer, we don't need 
            # to do anything.
            if current_list[current_index].isInteger():
                break
            
            # Otherwise, it must be a list. We need to increment the index
            # on the previous list, and add the new list.
            new_list = current_list[current_index].getList()
            self.stack[-1][1] += 1 # Increment old.
            self.stack.append([new_list, 0])
            
    
    def next(self) -> int:
        self.make_stack_top_an_integer()
        current_list = self.stack[-1][0]
        current_index = self.stack[-1][1]
        self.stack[-1][1] += 1
        return current_list[current_index].getInteger()
        
    
    def hasNext(self) -> bool:
        self.make_stack_top_an_integer()
        return len(self.stack) > 0

"""
Approach 5: Using a Generator
Intuition

This approach will only work in programming languages that support generator functions, for example, Python, JavaScript and C#. At the time of writing this article, C++ doesn't support it, but it is expected to support them soon.

In a nutshell, generator functions are a special type of function that can "return" multiple values. When you call a generator function, you get back a special object called a generator. This generator can then be used to get each value from the function, one at a time.

To "return" multiple values from these generator functions, a special keyword, yield, is used. yield behaves similarly to a return statement, except that it does not terminate the function. Instead, it pauses the function, and "returns" the yielded value. Then, when we need another value, the function resumes from where it left off. It continues until it gets to another yield, just like before. When the function gets to the end (no more code left to run), it stops.

For example in Python, if we have a generator gen, we can tell it to resume the function and get the next value by calling next(gen).

As an example, the generators created by this Python generator function can be used to get all numbers from a to b:

"""
class NestedIterator:

    def __init__(self, nestedList: [NestedInteger]):
        # Get a generator object from the generator function, passing in
        # nestedList as the parameter.
        self._generator = self._int_generator(nestedList)
        # All values are placed here before being returned.
        self._peeked = None

    # This is the generator function. It can be used to create generator
    # objects.
    def _int_generator(self, nested_list) -> "Generator[int]":
        # This code is the same as Approach 1. It's a recursive DFS.
        for nested in nested_list:
            if nested.isInteger():
                yield nested.getInteger()
            else:
                # We always use "yield from" on recursive generator calls.
                yield from self._int_generator(nested.getList())
        # Will automatically raise a StopIteration.
    
    def next(self) -> int:
        # Check there are integers left, and if so, then this will
        # also put one into self._peeked.
        if not self.hasNext(): return None
        # Return the value of self._peeked, also clearing it.
        next_integer, self._peeked = self._peeked, None
        return next_integer
        
    def hasNext(self) -> bool:
        if self._peeked is not None: return True
        try: # Get another integer out of the generator.
            self._peeked = next(self._generator)
            return True
        except: # The generator is finished so raised StopIteration.
            return False


class NestedIterator:

    def __init__(self, nestedList):
        """
        Initialize your data structure here.
        :type nestedList: List[NestedInteger]
        """
        self.root_ = nestedList
        self.stk_ = [iter(self.root_)]
        self.current_ = None
        self.curInteger_ = self.getNextOne_()

    def getNextOne_(self):

        while self.stk_ or self.current_:

            if not self.current_:
                # self.current_ = self.stk_[-1]
                self.current_ = self.stk_.pop()

            try:
                node = next(self.current_)
            except StopIteration:
                self.current_ = None
                continue

            if node.isInteger():
                return node
            else:
                self.stk_.append(self.current_)
                self.current_ = iter(node.getList())

        return None

    def next(self):
        """
        :rtype: int
        """
        val = self.curInteger_.getInteger()
        self.curInteger_ = self.getNextOne_()

        return val

    def hasNext(self):
        """
        :rtype: bool
        """
        return self.curInteger_


class NestedIterator:

    def __init__(self, nestedList):
        self._buf = []
        for i in reversed(range(len(nestedList))):
            self._buf.append(nestedList[i])

    def next(self):
        return self._buf[-1].pop().getInteger()

    def hasNext(self):

        while self._buf:
            index = self._buf[-1][1]
            if index == len(self._buf[-1]):
                self._buf.pop()

            if self._buf[-1][index].isInteger():
                return True
            else:
                self._buf[-1][1] += 1
                self._buf.append((self._buf[-1][0][index], 0))

        return False

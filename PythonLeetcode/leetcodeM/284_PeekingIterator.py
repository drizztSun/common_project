"""
284. Peeking Iterator

Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() 
operation -- it essentially peek() at the element that will be returned by the next call to next().

Example:

Assume that the iterator is initialized to the beginning of the list: [1,2,3].

Call next() gets you 1, the first element in the list.
Now you call peek() and it returns 2, the next element. Calling next() after that still return 2. 
You call next() the final time and it returns 3, the last element. 
Calling hasNext() after that should return false.
Follow up: How would you extend your design to be generic and work with all types, not just integer?

"""

# Below is the interface for Iterator, which is already defined for you.
#
# class Iterator:
#     def __init__(self, nums):
#         """
#         Initializes an iterator object to the beginning of a list.
#         :type nums: List[int]
#         """
#
#     def hasNext(self):
#         """
#         Returns true if the iteration has more elements.
#         :rtype: bool
#         """
#
#     def next(self):
#         """
#         Returns the next element in the iteration.
#         :rtype: int
#         """

class PeekingIterator:

    def __init__(self, iterator):
        """
        Initialize your data structure here.
        :type iterator: Iterator
        """
        self._iter = iterator
        self._next = self._iter.next()
        
    def nextV(self, remove=False):
        a = self._next
        
        if remove:
            self._next = self._iter.next() if self._iter.hasNext() else None
            
        return int(a)
        
    def peek(self):
        """
        Returns the next element in the iteration without advancing the iterator.
        :rtype: int
        """
        return self.nextV()
        
    def next(self):
        """
        :rtype: int
        """
        return self.nextV(True)

    def hasNext(self):
        """
        :rtype: bool
        """
        return self._next != None or self._iter.hasNext()


"""
Approach 1: Saving Peeked Value
Intuition

Each time we call .next(...), a value is returned from the Iterator. If we call .next(...) again, a new value will be returned. This means that if we want to use a particular value multiple times, we had better save it.

Our .peek(...) method needs to call .next(...) on the Iterator. But because .next(...) will return a different value next time, we need to store the value we peeked so when .next(...) is called we return the correct value.

Algorithm

Complexity Analysis

Time Complexity : All methods: O(1).

The operation performed to update our peeked value are all O(1).

The actual operations from .next() are impossible for us to analyse, as they depend on the given Iterator. By design, they are none of our concern. Our addition to the time is only O(1) though.

Space Complexity : All methods: O(1).

Like with time complexity, the Iterator itself is probably using memory in its own implementation. But again, this is not our concern. Our implementation only uses a few variables, so is O(1).
"""
class PeekingIterator:
    def __init__(self, iterator):
        self._iterator = iterator
        self._peeked_value = None

    def peek(self):
        # If there's not already a peeked value, get one out and store
        # it in the _peeked_value variable. We aren't told what to do if
        # the iterator is actually empty -- here I have thrown an exception
        # but in an interview you should definitely ask! This is the kind of
        # thing they expect you to ask about.
        if self._peeked_value is None:
            if not self._iterator.hasNext():
                raise StopIteration()
            self._peeked_value = self._iterator.next()
        
        return self._peeked_value

    def next(self):
        # Firstly, we need to check if we have a value already
        # stored in the _peeked_value variable. If we do, we need to
        # return it and also set _peeked_value to null so that the value
        # isn't returned again.
        if self._peeked_value is not None: 
            to_return = self._peeked_value
            self._peeked_value = None
            return to_return
        
        if not self._iterator.hasNext():
            raise StopIteration()
        
        # Otherwise, we need to return a new value.
        return self._iterator.next()

    def hasNext(self):
        # If there's a value waiting in _peeked_value, or if there are values
        # remaining in the iterator, we should return true.
        return self._peeked_value is not None or self._iterator.hasNext()


"""
Approach 2: Saving the Next Value
Intuition

Instead of only storing the next value after we've peeked at it, we can store it immediately in the constructor and then again in the next(...) method. 
This greatly simplifies the code, because we no longer need conditionals to check whether or not we are currently storing a peeked at value.

Algorithm

Note that in the Java code, we need to be careful not to cause an exception to be thrown from the constructor, in the case that the Iterator was empty at the start. 
We can do this by checking it has a next, and if it doesn't, then we set the next variable to null.


Complexity Analysis

Time Complexity : All methods: O(1)O(1).

Same as Approach 1.

Space Complexity : All methods: O(1)O(1).

Same as Approach 1.
"""
class PeekingIterator:
    def __init__(self, iterator):
        self._next = iterator.next()
        self._iterator = iterator

    def peek(self):
        return self._next

    def next(self):
        if self._next is None:
            raise StopIteration()
        to_return = self._next
        self._next = None
        if self._iterator.hasNext():
            self._next = self._iterator.next()
        return to_return

    def hasNext(self):
        return self._next is not None
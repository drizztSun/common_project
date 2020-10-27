"""
251. Flatten 2D Vector

Design and implement an iterator to flatten a 2d vector. It should support the following operations: next and hasNext.



Example:

Vector2D iterator = new Vector2D([[1,2],[3],[4]]);

iterator.next(); // return 1
iterator.next(); // return 2
iterator.next(); // return 3
iterator.hasNext(); // return true
iterator.hasNext(); // return true
iterator.next(); // return 4
iterator.hasNext(); // return false


Notes:

Please remember to RESET your class variables declared in Vector2D, as static/class variables are persisted across multiple test cases. Please see here for more details.
You may assume that next() call will always be valid, that is, there will be at least a next element in the 2d vector when next() is called.

"""

"""
Approach 2: Two Pointers
Intuition

Like we said above, Approach 1 is bad because it creates a new data structure instead of simply iterating over the given one. 
Instead, we should find a way to step through the integers one-by-one, keeping track of where we currently are in the 2D vector. 
The location of each number is represented with 2 indexes; the index of the inner vector, and the index of the integer within its inner vector. Here's an example 2D vector, with the indexes marked on it.

Note that when outer becomes equal to the length of the 2D vector, this means there are no more inner vectors and so there are no more numbers left.

Algorithm

In Approach 1, we used O(N)O(N) auxiliary space and O(N + V)O(N+V) time in the constructor. In this approach though, we perform the necessary work incrementally during calls to hasNext() and next(). 
This means that if the caller stops using the iterator before it's exhausted, we won't have done any unnecessary work.

We'll define an advanceToNext() helper method that checks if the current inner and outer values point to an integer, and 
if they don't, then it moves them forward until they point to an integer (in the way described above). If outer == vector.length becomes true, then the method terminates (because there's no integers left).

In order to ensure no unnecessary work is done, the constructor doesn't check whether or not vector[0][0] points to an integer. 
This is because there might be an arbitrary number of empty inner vectors at the start of the input vector; potentially costing up to O(V)O(V) operations to skip past.

Both hasNext() and next() start by calling advanceToNext() to ensure that inner and outer point to an integer, or that outer is at its "stop" value of outer = vector.length.

next() returns the integer at vector[inner][outer], and then increments inner by 1, so that the next call to advanceToNext() will start searching from after the integer we've just returned.

It is important to note that calling the hasNext() method will only cause the pointers to move if they don't point to an integer. Once they point to an integer, repeated calls to hasNext() will not move them further. 
Only next() is able to move them off a valid integer. This design ensures that the client code calling hasNext() multiple times will not have unusual side effects.
"""


class Vector2DII:

    def __init__(self, v):
        self.vector = v
        self.inner = 0
        self.outer = 0

    # If the current outer and inner point to an integer, this method does nothing.
    # Otherwise, inner and outer are advanced until they point to an integer.
    # If there are no more integers, then outer will be equal to vector.length
    # when this method terminates.
    def advance_to_next(self):
        # While outer is still within the vector, but inner is over the
        # end of the inner list pointed to by outer, we want to move
        # forward to the start of the next inner vector.
        while self.outer < len(self.vector) and self.inner == len(self.vector[self.outer]):
            self.outer += 1
            self.inner = 0

    def next(self) -> int:
        # Ensure the position pointers are moved such they point to an integer,
        # or put outer = vector.length.
        self.advance_to_next()
        # Return current element and move inner so that is after the current
        # element.
        result = self.vector[self.outer][self.inner]
        self.inner += 1
        return result

    def hasNext(self) -> bool:
        # Ensure the position pointers are moved such they point to an integer,
        # or put outer = vector.length.
        self.advance_to_next()
        # If outer = vector.length then there are no integers left, otherwise
        # we've stopped at an integer and so there's an integer left.
        return self.outer < len(self.vector)


class Vector2D:

    def __init__(self, v):
        self._v = v
        self._c, self._index = 0, 0

    def _gonext(self):

        self._index += 1
        while self._c < len(self._v) and self._index == len(self._v[self._c]):
            self._c += 1
            self._index = 0

    def next(self):

        if not self.hasNext():
            return None

        c = self._v[self._c][self._index]
        self._gonext()
        return c

    def hasNext(self):

        if self._c < len(self._v) and self._index < len(self._v[self._c]):
            return True

        while self._c < len(self._v) and self._index == len(self._v[self._c]):
            self._c += 1
            self._index = 0

        if self._c == len(self._v):
            return False

        return True


if __name__ == '__main__':

    v = Vector2D([[-1], [], []])
    v.hasNext()
    v.next()
    v.hasNext()
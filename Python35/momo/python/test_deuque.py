'''
functions
    deque(	[iterable])
Returns a new deque object initialized left-to-right (using append()) with data from iterable. If iterable is not specified, the new deque is empty.
Deques are a generalization of stacks and queues (the name is pronounced ``deck'' and is short for ``double-ended queue''). Deques support thread-safe, memory efficient appends and pops from either side of the deque with approximately the same O(1) performance in either direction.

Though list objects support similar operations, they are optimized for fast fixed-length operations and incur O(n) memory movement costs for "pop(0)" and "insert(0, v)" operations which change both the size and position of the underlying data representation. New in version 2.4.

Deque objects support the following methods:

    append(	x)
Add x to the right side of the deque.
    appendleft(	x)
Add x to the left side of the deque.
    clear(	)
Remove all elements from the deque leaving it with length 0.
extend(	iterable)
Extend the right side of the deque by appending elements from the iterable argument.
    extendleft(	iterable)
Extend the left side of the deque by appending elements from iterable. Note, the series of left appends results in
 reversing the order of elements in the iterable argument.
    pop(	)
Remove and return an element from the right side of the deque. If no elements are present, raises an IndexError.
    popleft(	)
Remove and return an element from the left side of the deque. If no elements are present, raises an IndexError.
    remove(	value)
Removed the first occurrence of value. If not found, raises a ValueError. New in version 2.5.
    rotate(	n)
Rotate the deque n steps to the right. If n is negative, rotate to the left. Rotating one step to the right is equivalent to: "d.appendleft(d.pop())".
In addition to the above, deques support iteration, pickling, "len(d)", "reversed(d)", "copy.copy(d)", "copy.deepcopy(d)", membership testing with the in operator, and subscript references such as "d[-1]".
examples
'''

from collections import deque


def test_deque():
    deque1 = deque([1, 2, 3, 4, 5])
    deque1.appendleft(0)
    deque1.append(6)
    print(deque1)

    # clear
    deque2 = deque([1, 2, 3, 4, 5, 6, 7, 8, 9, 0])
    deque2.clear()
    print(deque2)

    # extend
    deque2.extend([4, 5, 6])
    deque2.extendleft([3, 2, 1])
    print(deque2)

    # pop
    deque3 = deque(["a", 1, 2, 3, "b"])
    deque3.pop()
    deque3.popleft()
    print(deque3)

    # remove
    deque4 = deque([1, 3, 2, 4, 2, 5, 1, 6, 3, 7, 5])
    deque4.remove(2)
    print(deque4)

    # rotate
    deque5 = deque([4, 5, 1, 2, 3])
    deque5.rotate(3)
    print(deque5)


if __name__ == "__main__":
    test_deque()

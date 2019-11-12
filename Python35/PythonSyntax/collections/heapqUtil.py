import heapq


def heapsort(iterable):
    h = []
    for val in iterable:
        heapq.heappush(h, val)
    return [heapq.heappop(h) for i in range(len(h))]


def heapsort1(h):
    # h = [1, 6, 2, 5, 4, 3]
    heapq.heapify(h)
    print(h)

    print("sort results")
    print([heapq.heappop(h) for _ in range(len(h))])


def heap_nlarget_nsmallest():

    h = [1, 6, 2, 5, 4, 3, 7]
    heapq.heapify(h)

    # Return a list with the n largest elements from the dataset defined by iterable.
    # key, if provided, specifies a function of one argument that is used to extract a comparison key from each element in the iterable:
    # key=str.lower Equivalent to: sorted(iterable, key=key, reverse=True)[:n]
    print(heapq.nlargest(3, [1, 6, 2, 5, 4, 3, 7]))

    # Return a list with the n smallest elements from the dataset defined by iterable.
    # key, if provided, specifies a function of one argument that is used to extract a comparison key from each element in the iterable:
    # key=str.lower Equivalent to: sorted(iterable, key=key)[:n]
    print(heapq.nsmallest(3, [1, 6, 2, 5, 4, 3, 7]))


def heap_merge(*iterable):
    # Merge multiple sorted inputs into a single sorted output (for example, merge timestamped entries from multiple log files).
    # Returns an iterator over the sorted values.

    # Similar to sorted(itertools.chain(*iterables)) but returns an iterable, does not pull the data into memory all at once,
    # and assumes that each of the input streams is already sorted (smallest to largest).
    print(list(heapq.merge(iterable)))


def main():

    print(" --- Test heapq --- ")

    A = [1, 6, 2, 5, 4, 3]

    print(heapsort(A))

    c = [1, 6, 2, 5, 4, 3, 7]

    print(heapsort1(c))

    h = []

    # Push the value item onto the heap, maintaining the heap invariant.
    heapq.heappush(h, (5, "write code"))
    heapq.heappush(h, (7, "release product"))
    heapq.heappush(h, (1, "write spec"))
    heapq.heappush(h, (3, "create tests"))

    print(h)

    # Pop and return the smallest item from the heap, maintaining the heap invariant.
    # If the heap is empty, IndexError is raised. To access the smallest item without popping it, use heap[0].
    print(heapq.heappop(h))

    print(h)

    try:
        for _ in range(len(h) + 1):
            print(heapq.heappop(h))
    except IndexError as e:
        print(e)

    # Push item on the heap, then pop and return the smallest item from the heap.
    # The combined action runs more efficiently than heappush() followed by a separate call to heappop().
    print(heapq.heappushpop(h, (1, "write spec")))

    # Pop and return the smallest item from the heap, and also push the new item. The heap size doesn’t change. If the heap is empty, IndexError is raised.

    # This one step operation is more efficient than a heappop() followed by heappush() and can be more appropriate when using a fixed-size heap. The pop/push combination always returns an element from the heap and replaces it with item.

    # The value returned may be larger than the item added. If that isn’t desired, consider using heappushpop() instead. Its push/pop combination returns the smaller of the two values, leaving the larger value on the heap.
    h = [1, 6, 2, 5, 4, 3, 7]
    heapq.heapify(h)
    print(heapq.heapreplace(h, 8))

    try:
        for i in range(1, len(h) + 1):
            heapq.heapreplace(h, i + 8)
    except IndexError as e:
        print(e)

    heap_nlarget_nsmallest()

    heap_merge([1, 2, 3], [6, 5, 4], [10, 9, 7, 8])

    print(" --- Test heapq --- ")


if __name__ == "__main__":

    main()

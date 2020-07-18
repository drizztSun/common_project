import bisect


def test_bisect():
    a = [1, 2, 3, 4, 5]
    print(bisect.bisect_left(a, 3))
    # The returned insertion point i partitions the array a into two halves
    # so that all(val < x for val in a[lo:i]) for the left side and 
    # all(val >= x for val in a[i:hi]) for the right side.

    print(bisect.bisect_right(a, 3))
    print(bisect.bisect(a, 3))
    # The returned insertion point i partitions the array a into two halves
    # so that all(val <= x for val in a[lo:i]) for
    # the left side and all(val > x for val in a[i:hi]) for the right side.

    # all(val == x for val in a[left_i: right_i])

    a = [1, 1, 1, 2, 2, 2, 2, 3, 4, 5, 7, 8]
    print(a[bisect.bisect_left(a, 2):bisect.bisect(a, 2)])

    bisect.insort_left(a, 6)
    print(a)
    # Insert x in a in sorted order. This is equivalent to a.insert(bisect.bisect_left(a, x, lo, hi), x)
    # assuming that a is already sorted. Keep in mind that the O(log n) search is dominated
    # by the slow O(n) insertion step.

    bisect.insort_right(a, 2)
    print(a)
    bisect.insort(a, 2)
    print(a)
    # Similar to insort_left(), but inserting x in a after any existing entries of x.


if __name__ == "__main__":
    test_bisect()

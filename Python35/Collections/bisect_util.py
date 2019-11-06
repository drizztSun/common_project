import bisect


class Array(object):

    def __init__(self, A):
        self.__A = sorted(A)

    def index(self, x):

        i = bisect.bisect_left(self.__A, x)
        if i != len(self.__A) and x == self.__A[i]:
            return i
        raise ValueError

    def find_lt(self, x):
        'Find rightmost value less than x'
        i = bisect.bisect_left(self.__A, x)
        if i > 0:
            return self.__A[i-1]
        # raise ValueError
        return None

    def find_le(self, x):
        'Find the rightmost value less than or equal to x'
        i = bisect.bisect_right(self.__A, x)
        if i:
            return self.__A[i-1]
        # raise ValueError
        return None

    def find_gt(self, x):
        'Find leftmost value greater than x'
        i = bisect.bisect(self.__A, x)
        if i != len(self.__A):
            return self.__A[i]
        # raise ValueError
        return None

    def find_ge(self, x):
        'Find leftmost item greater than or equal to x'
        i = bisect.bisect(self.__A, x)
        if i != len(self.__A):
            return self.__A[i]
        # raise ValueError
        return None

def main():

    a = [1, 2, 3, 4, 4, 4, 4, 4, 5, 6, 7, 8]

    # The returned insertion point i partitions the array a into two halves so that all(val < x for val in a[lo:i])
    # for the left side and all(val >= x for val in a[i:hi]) for the right side.
    left = bisect.bisect_left(a, 4)
    print(bisect.bisect_left(a, 4)) # 3
    print(all(x < 4 for x in a[:left]))

    # The returned insertion point i partitions the array a into two halves so that all(val <= x for val in a[lo:i])
    # for the left side and all(val > x for val in a[i:hi]) for the right side.
    right = bisect.bisect(a, 4)
    print(bisect.bisect_right(a, 4)) # 8
    print(all(x > 4 for x in a[right+1:]))

    assert( all(x == 4 for x in a[left: right]))

    # Insert x in a in sorted order. This is equivalent to a.insert(bisect.bisect_left(a, x, lo, hi), x)
    # assuming that a is already sorted. Keep in mind that the O(log n) search is dominated by the slow O(n) insertion step.
    bisect.insort_left(a, 3)
    print(a)

    bisect.insort_right(a, 5)
    print(a)

    bisect.insort(a, 4)
    print(a)

    # Array
    a = Array([2, 4, 5, 6, 3, 7, 1, 9])

    print( a.find_lt(1))
    print( a.find_lt(100))

    print( a.find_le(4))

    print( a.find_gt(4))

    print( a.find_gt(9))
    print( a.find_gt(-1))


if __name__ == "__main__":

    main()

"""
715. Range Module


A Range Module is a module that tracks ranges of numbers. Your task is to design and implement the following interfaces in an efficient manner.

. addRange(int left, int right) Adds the half-open interval [left, right), tracking every real number in that interval. 
    Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval [left, right) that are not already tracked.

. queryRange(int left, int right) Returns true if and only if every real number in the interval [left, right) is currently being tracked.

. removeRange(int left, int right) Stops tracking every real number currently being tracked in the interval [left, right).


Example 1:

addRange(10, 20): null
removeRange(14, 16): null
queryRange(10, 14): true (Every number in [10, 14) is being tracked)
queryRange(13, 15): false (Numbers like 14, 14.03, 14.17 in [13, 15) are not being tracked)
queryRange(16, 17): true (The number 16 in [16, 17) is still being tracked, despite the remove operation)

Note:

A half open interval [left, right) denotes all real numbers left <= x < right.
0 < left < right < 10^9 in all calls to addRange, queryRange, removeRange.
The total number of calls to addRange in a single test case is at most 1000.
The total number of calls to queryRange in a single test case is at most 5000.
The total number of calls to removeRange in a single test case is at most 1000.

"""


"""
    Approach #1: Maintain Sorted Disjoint Intervals [Accepted]
    Intuition

    Because left, right < 10^9, we need to deal with the coordinates abstractly. Let's maintain some sorted structure of disjoint intervals. These intervals will be closed (eg. we don't store [[1, 2], [2, 3]]; we would store [[1, 3]] instead.)

    In this article, we will go over Python and Java versions separately, as the data structures available to us that are relevant to the problem are substantially different.

    Algorithm (Python)

    We will maintain the structure as a list self.ranges = [].

    Adding a Range

    When we want to add a range, we first find the indices i, j = self._bounds(left, right) for which self.ranges[i: j+1] touches (in a closed sense - not halfopen) the given interval [left, right]. 
    We can find this in log time by making steps of size 100, 10, then 1 in our linear search from both sides.

    Every interval touched by [left, right] will be replaced by the single interval [min(left, self.ranges[i][0]), max(right, self.ranges[j][1])].

    Removing a Range

    Again, we use i, j = self._bounds(...) to only work in the relevant subset of self.ranges that is in the neighborhood of our given range [left, right). 
    For each interval [x, y) from self.ranges[i:j+1], we may have some subset of that interval to the left and/or right of [left, right). We replace our current interval [x, y) with those (up to 2) new intervals.

    Querying a Range

    As the intervals are sorted, we use binary search to find the single interval that could intersect [left, right), then verify that it does.
"""
import bisect

class RangeModule(object):

    def __init__(self):
        self.ranges = []

    def _bounds(self, left, right):
        i, j = 0, len(self.ranges) - 1
        for d in (100, 10, 1):
            while i + d - 1 < len(self.ranges) and self.ranges[i+d-1][1] < left:
                i += d
            while j >= d - 1 and self.ranges[j-d+1][0] > right:
                j -= d
        return i, j

    def addRange(self, left, right):
        i, j = self._bounds(left, right)
        if i <= j:
            left = min(left, self.ranges[i][0])
            right = max(right, self.ranges[j][1])
        self.ranges[i:j+1] = [(left, right)]

    def queryRange(self, left, right):
        i = bisect.bisect_left(self.ranges, (left, float('inf')))
        if i: i -= 1
        return (bool(self.ranges) and
                self.ranges[i][0] <= left and
                right <= self.ranges[i][1])

    def removeRange(self, left, right):
        i, j = self._bounds(left, right)
        merge = []
        for k in range(i, j+1):
            if self.ranges[k][0] < left:
                merge.append((self.ranges[k][0], left))
            if right < self.ranges[k][1]:
                merge.append((right, self.ranges[k][1]))
        self.ranges[i:j+1] = merge
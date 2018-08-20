


# 435. Non-overlapping Intervals


# Given a collection of intervals, find the minimum number of intervals you need to
# remove to make the rest of the intervals non-overlapping.

# Note:
# You may assume the interval's end point is always bigger than its start point.
# Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.

# Example 1:
# Input: [ [1,2], [2,3], [3,4], [1,3] ]
# Output: 1
# Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.

# Example 2:
# Input: [ [1,2], [1,2], [1,2] ]
# Output: 2
# Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.

# Example 3:
# Input: [ [1,2], [2,3] ]
# Output: 0
# Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

def constructIntervals(D):
    return [Intervals(A[0], A[1]) for A in D]

# Definition for an interval.
class Interval(object):
    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e

class eraseOverlapIntervals(object):
    def doit(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: int
        """
        end = float('-inf')
        erased = 0

        for c in sorted(intervals, key = lambda x : x.end):
            if c.start >= end:
                end = c.end
            else:
                erased += 1

        return erased

    def doit1(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: int
        """
        start = float('inf')
        erased = 0

        for c in sorted(intervals, key = lambda x : x[0], reverse=1):

            if c.end <= start:
                start = c.start
            else:
                erased += 1

        return erased


    def doit1(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: int
        """
        intervals.sort(key=lambda x: (x.end, x.start))
        end = float('-inf')
        ans = 0

        for interval in intervals:
            if interval.start < end:
                ans += 1
                end = min(end, interval.end)
            else:
                end = interval.end

        return ans

if __name__=="__main__":



    res = eraseOverlapIntervals().doit(constructIntervals( [ [1,2], [2,3], [3,4], [1,3] ] ))

    res = eraseOverlapIntervals().doit(constructIntervals( [ [1,2], [1,2], [1,2] ] ))

    res = eraseOverlapIntervals().doit(constructIntervals( [ [1,2], [2,3] ] ))


    pass
        
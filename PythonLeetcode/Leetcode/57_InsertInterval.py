"""
# 57. Insert Interval

# Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
# You may assume that the intervals were initially sorted according to their start times.

# Example 1:
# Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

# Example 2:
# Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

# This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
"""


# Definition for an interval.
class Interval:
    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e


class InsertInterval:

    def doit(self, intervals, newInterval):
        """
        :type intervals: List[Interval]
        :type newInterval: Interval
        :rtype: List[Interval]
        """
        res, iend = [], False

        for x in intervals:
            if x.end < newInterval.start:
                res.append(x)
            elif x.start > newInterval.end:
                if not iend:
                    res.append(newInterval)
                    iend = True
                res.append(x)
            else:
                newInterval.start = min(newInterval.start, x.start)
                newInterval.end = max(newInterval.end, x.end)

        if not iend:
            res.append(newInterval)

        return res

    def doit1(self, intervals, newInterval):
        """
        :type intervals: List[Interval]
        :type newInterval: Interval
        :rtype: List[Interval]
        """
        s, e = newInterval.start, newInterval.end

        left = [i for i in intervals if i.end < s]
        right = [i for i in intervals if i.start > e]

        if len(left) + len(right) != len(intervals) :
            s = min(s, intervals[len(left)].start)
            e = max(e, intervals[-1 - len(right)].end)

        return left + [Interval(s, e)] + right

    def doit2(self, intervals, newInterval):
        """
        :type intervals: List[Interval]
        :type newInterval: Interval
        :rtype: List[Interval]
        """
        left_intervals, right_intervals = [], []
        start = newInterval.start
        end = newInterval.end

        for interval in intervals:
            if interval.end < start:
                left_intervals.append(interval)

            elif interval.start > end:
                right_intervals.append(interval)

            else:
                start = min(interval.start, start)
                end = max(interval.end, end)

        return left_intervals + [Interval(start, end)] + right_intervals


if __name__ == "__main__":

    res = InsertInterval().doit([Interval(1,3), Interval(6,9)], Interval(2,5))

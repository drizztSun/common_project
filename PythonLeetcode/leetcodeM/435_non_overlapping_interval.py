"""
435. Non-overlapping Intervals

Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.



Example 1:

Input: [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
Example 2:

Input: [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
Example 3:

Input: [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.


Note:

You may assume the interval's end point is always bigger than its start point.
Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.

"""


class EraseOverlapIntervals:

    """"
    Interval questions
    Greedy

    1. Sweeping line / diff
    2. Sort

        sort by start points => the minimum number of intervals to cover the whole range.
        sort by ending points => the maximum number of intervals that are non-overlapping.



        Approach #5 Using Greedy Approach based on end points [Accepted]
        Algorithm

        The Greedy approach just discussed was based on choosing intervals greedily based on the starting points.
        But in this approach, we go for choosing points greedily based on the end points.
        For this, firstly we sort the given intervals based on the end points. Then, we traverse over the sorted intervals.
        While traversing, if there is no overlapping between the previous interval and the current interval, we need not remove any interval.
        But, if an overlap exists between the previous interval and the current interval, we always drop the current interval.

        To explain how it works, again we consider every possible arrangement of the intervals.

        Non_overlapping

        Case 1:

        The two intervals currently considered are non-overlapping:

        In this case, we need not remove any interval and for the next iteration the current interval becomes the previous interval.

        Case 2:

        The two intervals currently considered are overlapping and the starting point of the later interval falls before the starting point of the previous interval:

        In this case, as shown in the figure below, it is obvious that the later interval completely subsumes the previous interval.
        Hence, it is advantageous to remove the later interval so that we can get more range available to accommodate future intervals. Thus, previous interval remains unchanged and the current interval is updated.

        Case 3:

        The two intervals currently considered are overlapping and the starting point of the later interval falls before the starting point of the previous interval:

        In this case, the only opposition to remove the current interval arises because it seems that more intervals could be accommodated by removing the previous interval in the range marked by A.
        But that won't be possible as can be visualized with a case similar to Case 3a and 3b shown above. But, if we remove the current interval, we can save the range BB to accommodate further intervals.
        Thus, previous interval remains unchanged and the current interval is updated.

        Complexity Analysis

        Time complexity : O(nlog(n)). Sorting takes O(nlog(n)) time.

        Space complexity : O(1). No extra space is used.
    """
    def doit_greedy(self, intervals: list) -> int:
        # Sort by end time can helps us to review the end-time early one first. Then it will make less intervene with other rest intervals.
        intervals.sort(key=lambda x: x[1])
        erased, end = 0, 0

        for c in intervals:
            if c[0] >= end:
                end = c[1]
            else:
                erased += 1

        return erased





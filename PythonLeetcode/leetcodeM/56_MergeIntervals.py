"""
56. Merge Intervals

Given a collection of intervals, merge all overlapping intervals.

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

"""
class Interval:
    def __init__(self):

        self.start, self.end = 0, 0

class MergeIntervals:

    """
    Approach 2: Sorting
    Intuition

    If we sort the intervals by their start value, then each set of intervals that can be merged will appear as a contiguous "run" in the sorted list.

    Algorithm

    First, we sort the list as described. Then, we insert the first interval into our merged list and continue considering each interval in turn as follows: If the current interval begins after the previous interval ends, then they do not overlap and we can append the current interval to merged. Otherwise, they do overlap, and we merge them by updating the end of the previous interval if it is less than the end of the current interval.

    A simple proof by contradiction shows that this algorithm always produces the correct answer. First, suppose that the algorithm at some point fails to merge two intervals that should be merged. This would imply that there exists some triple of indices ii, jj, and kk in a list of intervals \text{ints}ints such that i < j < ki<j<k and (\text{ints[i]}ints[i], \text{ints[k]}ints[k]) can be merged, but neither (\text{ints[i]}ints[i], \text{ints[j]}ints[j]) nor (\text{ints[j]}ints[j], \text{ints[k]}ints[k]) can be merged. From this scenario follow several inequalities:

    \begin{aligned} \text{ints[i].end} < \text{ints[j].start} \\ \text{ints[j].end} < \text{ints[k].start} \\ \text{ints[i].end} \geq \text{ints[k].start} \\ \end{aligned}
    ints[i].end<ints[j].start
    ints[j].end<ints[k].start
    ints[i].end≥ints[k].start
    ​


    We can chain these inequalities (along with the following inequality, implied by the well-formedness of the intervals: \text{ints[j].start} \leq \text{ints[j].end}ints[j].start≤ints[j].end) to demonstrate a contradiction:

    \begin{aligned} \text{ints[i].end} < \text{ints[j].start} \leq \text{ints[j].end} < \text{ints[k].start} \\ \text{ints[i].end} \geq \text{ints[k].start} \end{aligned}
    ints[i].end<ints[j].start≤ints[j].end<ints[k].start
    ints[i].end≥ints[k].start
    ​


    Therefore, all mergeable intervals must occur in a contiguous run of the sorted list.


    """

    def doit(self, intervals: List[List[int]]) -> List[List[int]]:

        intervals.sort(key=lambda x: x[0])

        merged = []
        for interval in intervals:
            # if the list of merged intervals is empty or if the current
            # interval does not overlap with the previous, simply append it.
            if not merged or merged[-1][1] < interval[0]:
                merged.append(interval)
            else:
            # otherwise, there is overlap, so we merge the current and previous
            # intervals.
                merged[-1][1] = max(merged[-1][1], interval[1])

        return merged

    def doit(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[Interval]
        """
        if len(intervals) == 0:
            return []

        sortedIntervals = sorted(intervals, key=lambda Interval: Interval.start)
        result, i, cur = [], 0, Interval(sortedIntervals[0].start, sortedIntervals[0].end)

        while i < len(sortedIntervals):
            if cur.end < sortedIntervals[i].start:
                result.append(cur)
                cur = Interval(sortedIntervals[i].start, sortedIntervals[i].end)
            else:
                if cur.end < sortedIntervals[i].end:
                    cur.end = sortedIntervals[i].end
            i += 1

        result.append(cur)
        return result

    def doit_1(self, intervals):

        if not intervals:
            return []

        intervals = sorted(intervals, key=lambda x: (x[0], -x[1]))
        res = []

        for w in intervals:

            if not res or res[-1][1] < w[0]:
                res.append(w)
            else:
                res[-1][1] = max(w[1], res[-1][1])

        return res


if __name__ == '__main__':

    MergeIntervals().doit([[1,3],[2,6],[8,10],[15,18]])

    MergeIntervals().doit([[1,4],[4,5]])

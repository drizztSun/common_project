# 757. Set Intersection Size At Least Two

# An integer interval [a, b] (for integers a < b) is a set of all consecutive integers from a to b, including a and b.

# Find the minimum size of a set S such that for every integer interval A in intervals, 
# the intersection of S with A has size at least 2.

# Example 1:
# Input: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
# Output: 3
# Explanation:
# Consider the set S = {2, 3, 4}.  For each interval, there are at least 2 elements from S in the interval.
# Also, there isn't a smaller size set that fulfills the above condition.
# Thus, we output the size of this set, which is 3.

# Example 2:
# Input: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
# Output: 5
# Explanation:
# An example of a minimum sized set is {1, 2, 3, 4, 5}.

# Note:
# intervals will have length in range [1, 3000].
# intervals[i] will have length 2, representing some integer interval.
# intervals[i][j] will be an integer in [0, 10^8].


class IntersectionSizeTwo:
    def doit(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        intervals.sort(key=lambda x: (x[1], -x[0]))
        res = [-1, -1]

        for c in intervals:
            sz = len(res)

            if c[0] <= res[sz - 2]:
                continue

            if c[0] > res[sz - 1]:
                res.append(c[1] - 1)

            res.append(c[1])

        return len(res) - 2

    def doit2(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: int
        """
        intervals.sort(key=lambda x: x[1])
        if len(intervals) <= 1:
            return len(intervals[0])
        s = set()
        prev_e = None
        intersect = False
        for e in intervals:
            if not s:
                a = e[1] - 1
                b = e[1]
                s.add(a)
                s.add(b)
                continue
            if e[0] <= a:
                intersect = True
                continue

            if e[0] > a and e[1] > b >= e[0]:
                intersect = True
                a = b
                b = e[-1]
                s.add(b)
                continue
            a = e[1] - 1
            b = e[1]
            s.add(a)
            s.add(b)

        if not intersect:
            return 0
        return len(s)


if __name__ == "__main__":

    intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]    

    res = IntersectionSizeTwo().doit(intervals)

    intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]

    res = IntersectionSizeTwo().doit(intervals)

    res = IntersectionSizeTwo().doit([[2,10],[3,7],[3,15],[4,11],[6,12],[6,16],[7,8],[7,11],[7,15],[11,12]])

    pass
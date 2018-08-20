


# 436. Find Right Interval

# Given a set of intervals, for each of the interval i, 
# check if there exists an interval j whose start point is bigger than or equal to the end point of the interval i,
# which can be called that j is on the "right" of i.

# For any interval i, you need to store the minimum interval j's index,
# which means that the interval j has the minimum start point to build the "right" relationship for interval i.
# If the interval j doesn't exist, store -1 for the interval i. Finally, you need output the stored value of each interval as an array.

# Note:
# You may assume the interval's end point is always bigger than its start point.
# You may assume none of these intervals have the same start point.

# Example 1:
# Input: [ [1,2] ]
# Output: [-1]

# Explanation: There is only one interval in the collection, so it outputs -1.

# Example 2:
# Input: [ [3,4], [2,3], [1,2] ]
# Output: [-1, 0, 1]

# Explanation: There is no satisfied "right" interval for [3,4].
# For [2,3], the interval [3,4] has minimum-"right" start point;
# For [1,2], the interval [2,3] has minimum-"right" start point.

# Example 3:
# Input: [ [1,4], [2,3], [3,4] ]
# Output: [-1, 2, -1]

# Explanation: There is no satisfied "right" interval for [1,4] and [3,4].
# For [2,3], the interval [3,4] has minimum-"right" start point.


class Interval(object):
    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e

import bisect
class findRightInterval(object):


    def doit(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[int]
        """
        res = [-1] * len(intervals)
        A = [[l.start, l.end, i] for i, l in enumerate(intervals)]
        A.sort(key=lambda x : x[0])
    
        # O(nlogn)
        for i , c in enumerate(intervals):
            index = bisect.bisect(A, [c.end])
            if index < len(A):
                res[i] = A[index][2]
            
        return res
                    

    def doit2(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[int]
        """
        x = sorted((interval.start, i) for i, interval in enumerate(intervals)) + [(float('inf'), -1)]
        starts, indices = zip(*x)  # zip
        return [indices[bisect.bisect_left(starts, i.end)] for i in intervals]
        


    # <TLE>
    def doit1(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[int]
        """
        res = [-1] * len(intervals)
        A = [(l.start, l.end, i) for i, l in enumerate(intervals)]
        A.sort(key=lambda x : x[0])
    
        # O(n**2)
        for i , c in enumerate(A):
            s, end = i+1, c[1]
            while s < len(A) and A[s][0] < end:  
                s += 1
            res[c[2]] = A[s][2] if s != len(A) else -1

        return res

    

        



if __name__=="__main__":


    res = findRightInterval().doit([ Interval(1,2) ]) # [-1]

    res = findRightInterval().doit([ Interval(3,4), Interval(2,3), Interval(1,2) ]) # [-1, 0, 1]

    res = findRightInterval().doit([ Interval(1,4), Interval(2,3), Interval(3,4) ]) # [-1, 2, -1]


    res = findRightInterval().doit([ Interval(4,5), Interval(2,3), Interval(1,2) ]) # [-1, 0, 1]

    pass





# 452. Minimum Number of Arrows to Burst Balloons

# There are a number of spherical balloons spread in two-dimensional space.
# For each balloon, provided input is the start and end coordinates of the horizontal diameter.
# Since it's horizontal, y-coordinates don't matter and hence the x-coordinates of start and end of the diameter suffice.
# Start is always smaller than end. There will be at most 104 balloons.

# An arrow can be shot up exactly vertically from different points along the x-axis.
# A balloon with xstart and xend bursts by an arrow shot at x if xstart ? x ? xend.
# There is no limit to the number of arrows that can be shot.
# An arrow once shot keeps travelling up infinitely.
# The problem is to find the minimum number of arrows that must be shot to burst all balloons.

# Example:

# Input:
# [[10,16], [2,8], [1,6], [7,12]]

# Output:
# 2

# Explanation:
# One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).


class findMinArrowShots(object):

    def doit(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        points.sort(key= lambda x: x[1])
        res, end = 0, float('-inf')
    
        for interval in points:
            if interval[0] > end:
                res += 1
                end = interval[1]

        return res
        
    def doit2(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        
        if not points:
            return 0
        
        points = sorted(points, key = lambda x : x[1])
        
        ans = 0
        end = float("-inf")
        for i in xrange(len(points)):
            if points[i][0] > end:
                ans += 1
                end = points[i][1]
        return ans         

    # <TLE>        
    def doit1(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        data = []
        points.sort()
        for c in points:
            for s in data:
                if s[0] <= c[0] <= s[1] or s[0] <= c[1] <= s[1]:
                    s[0], s[1] = max(c[0], s[0]), min(c[1], s[1])
                    s[2] += 1
                    c = None
                    break
            if c:
                data.append([c[0], c[1], 1])

        return len(data)
                            

                    
        



if __name__=="__main__":


    res = findMinArrowShots().doit([[10,16], [2,8], [1,6], [7,12]])

    res = findMinArrowShots().doit([[3,9],[7,12],[3,8],[6,8],[9,10],[2,9],[0,9],[3,9],[0,6],[2,8]])

    pass
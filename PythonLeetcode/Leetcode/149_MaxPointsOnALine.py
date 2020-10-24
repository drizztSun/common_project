"""
149. Max Points on a Line

Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

Example 1:

Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o
+------------->
0  1  2  3  4
Example 2:

Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
"""
import numbers
import math


class Point(object):
    def __init__(self, a=0, b=0):
        self.x = a
        self.y = b


class MaxPoints(object):

    """
    Approach 1: Enumeration
    Intuition

    Let's simplify the problem and search the maximum number of points on a line passing through the point i.

    One could immediately notice that it's interesting to consider only the next points i + 1 .. N - 1 because the maximum number of points containing,
    for example, the point i - 2 was already found during the search of the maximum number of points on a line passing through the point i - 2.


    """
    def doit_enum(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """

        def max_points_on_a_line_containing_point_i(i):
            """
            Compute the max number of points
            for a line containing point i.
            """
            def slope_coprime(x1, y1, x2, y2):
                """ to avoid the precision issue with the float/double number,
                    using a pair of co-prime numbers to represent the slope.
                """
                import sys
                delta_x, delta_y = x1 - x2, y1 - y2
                if delta_x == 0:  # vertical line
                    return (0, 0)
                elif delta_y == 0:  # horizontal line
                    return (sys.maxsize, sys.maxsize)
                elif delta_x < 0:
                    # to have a consistent representation,
                    #   keep the delta_x always positive.
                    delta_x, delta_y = - delta_x, - delta_y
                gcd = math.gcd(delta_x, delta_y)
                slope = (delta_x / gcd, delta_y / gcd)
                return slope

            def add_line(i, j, count, duplicates):
                """
                Add a line passing through i and j points.
                Update max number of points on a line containing point i.
                Update a number of duplicates of i point.
                """
                # rewrite points as coordinates
                x1 = points[i][0]
                y1 = points[i][1]
                x2 = points[j][0]
                y2 = points[j][1]
                # add a duplicate point
                if x1 == x2 and y1 == y2:
                    duplicates += 1
                # add a horisontal line : y = const
                elif y1 == y2:
                    nonlocal horizontal_lines
                    horizontal_lines += 1
                    count = max(horizontal_lines, count)
                # add a line : x = slope * y + c
                # only slope is needed for a hash-map
                # since we always start from the same point
                else:
                    slope = slope_coprime(x1, y1, x2, y2)
                    lines[slope] = lines.get(slope, 1) + 1
                    count = max(lines[slope], count)
                return count, duplicates

            # init lines passing through point i
            lines, horizontal_lines = {}, 1
            # One starts with just one point on a line : point i.
            count = 1
            # There is no duplicates of a point i so far.
            duplicates = 0
            # Compute lines passing through point i (fixed)
            # and point j (interation).
            # Update in a loop the number of points on a line
            # and the number of duplicates of point i.
            for j in range(i + 1, n):
                count, duplicates = add_line(i, j, count, duplicates)
            return count + duplicates

        # If the number of points is less than 3
        # they are all on the same line.
        n = len(points)
        if n < 3:
            return n

        max_count = 1
        # Compute in a loop a max number of points
        # on a line containing point i.
        for i in range(n - 1):
            max_count = max(max_points_on_a_line_containing_point_i(i), max_count)
        return max_count

    def doit1(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        def GCD(a, b):
            return a if b == 0 else GCD(b, a%b)

        lines = {}
        result = 0

        for i in range(len(points)):

            overlap, vertical, localMax = 0, 0, 0
            lines = {}
            j = i + 1
            while j < len(points):
                if points[i].x == points[j].x and points[i].y == points[j].y:
                    overlap += 1
                    j += 1
                    continue

                if points[i].x == points[j].x:
                    vertical += 1
                else:
                    b, a = points[i].y-points[j].y, points[i].x-points[j].x
                    gcd = GCD(a, b)
                    a /= gcd
                    b /= gcd

                    lines[(a, b)] = lines.get((a, b), 0) + 1
                    localMax = max(localMax, lines[(a, b)])
                
                localMax = max(localMax, vertical)
                j += 1

            result = max(localMax + overlap + 1, result)

        return result 


    def doit4(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        def GCD(a, b):
            if b == 0:
                return a
            else:
                return GCD(b, a%b)

        lines = {}
        result = 0

        for i in range(len(points)):

            overlap, vertical, localMax = 0, 0, 0
            lines = {}
            j = i + 1
            while j < len(points):

                if points[i].x == points[j].x and points[i].y == points[j].y:
                    overlap += 1
                    j += 1
                    continue

                b, a = points[i].y-points[j].y, points[i].x-points[j].x
                gcd = GCD(a, b)
                a /= gcd
                b /= gcd

                lines[(a, b)] = lines.get((a, b), 0) + 1
                
                localMax = max(localMax, lines[(a, b)])

                j += 1

            result = max(localMax + overlap + 1, result)


        return result 


    def doit(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        if not points:
            return 0

        if len(points) == 1:
            return 1

        #dedups
        pointCounts = {}
        for p in points:
            if (p.x, p.y) not in pointCounts:
                pointCounts[(p.x, p.y)] = 1
            else:
                pointCounts[(p.x, p.y)] += 1

        uniqPoints = pointCounts.keys()
        if len(uniqPoints) == 1:
            return pointCounts[uniqPoints[0]]

        #print pointCounts
        maxCount = 0
        for i in range(len(uniqPoints) - 1):

            #lines with point i
            x1, y1 = uniqPoints[i]
            countSlope = {}
            countVertical = 0
            slopeMax = 0

            for j in range(i + 1, len(uniqPoints)):
                x2, y2 = uniqPoints[j]
                if x1 == x2:
                    if countVertical == 0:
                        countVertical = pointCounts[(x1, y1)] + pointCounts[(x2, y2)]
                    else:
                        countVertical += pointCounts[(x2, y2)]
                else:
                    d1 = float((y1 - y2))
                    d2 = float((x1 - x2))
                    slope = d1 / d2
                    if slope not in countSlope:
                        countSlope[slope] = pointCounts[(x1, y1)] + pointCounts[(x2, y2)]
                    else:
                        countSlope[slope] += pointCounts[(x2, y2)]
                    #print countTable
                    slopeMax = max(slopeMax, countSlope[slope])

            maxCount = max(maxCount, slopeMax)
            maxCount = max(maxCount, countVertical)

        return maxCount

    # not working on Python 3
    def doit3(self, pointes):
        """
        :type points: List[Point]
        :rtype: int
        """
        if len(pointes) <= 1:
            return len(pointes)

        uniquePoint = {}
        for pt in pointes:
            uniquePoint[(pt.x, pt.y)] = uniquePoint.get((pt.x, pt.y), 0) + 1

        uniqueKeys = list(uniquePoint.keys())
        if len(uniqueKeys) == 1:
            return uniquePoint[uniqueKeys[0]]

        maxCount = 0
        for i in range(len(uniqueKeys)-1):
            x1, y1 = uniqueKeys[i]
            vertical, slopeMax = 0, 0
            slopeCount = {}
            
            for j in range(i+1, len(uniqueKeys)):
                
                x2, y2 = uniqueKeys[j]
    
                if x1 == x2:
                    if vertical == 0:
                        vertical = uniquePoint[(x1, y1)] + uniquePoint[(x2, y2)]
                    else:
                        vertical += uniquePoint[(x2, y2)]

                else:
                    a = float(y1 - y2)
                    b = float(x1 - x2)
                    slope = a / b
                    slopeCount[slope] = slopeCount.get(slope, uniquePoint[(x1, y1)]) + uniquePoint[(x2, y2)]

                    slopeMax = max(slopeMax, slopeCount[slope])

            maxCount = max(maxCount, slopeMax)
            maxCount = max(maxCount, vertical)

        return maxCount


if __name__ =="__main__":

    res = MaxPoints().doit([Point(0, 0), Point(1, 0)])

    res = MaxPoints().doit([Point(1,1), Point(2,2), Point(3,3)])

    res = MaxPoints().doit([Point(1,1), Point(3,2), Point(5,3), Point(4,1), Point(2,3), Point(1,4)])

    pass
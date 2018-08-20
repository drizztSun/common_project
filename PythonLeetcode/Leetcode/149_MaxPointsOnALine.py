import os
import numbers
import math

# Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

# Definition for a point.
class Point(object):
    def __init__(self, a=0, b=0):
        self.x = a
        self.y = b

class maxPoints(object):
    def doit1(self, points):
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

    res = maxPoints().doit([Point(0, 0), Point(1, 0)])

    res = maxPoints().doit([Point(1,1), Point(2,2), Point(3,3)])

    res = maxPoints().doit([Point(1,1), Point(3,2), Point(5,3), Point(4,1), Point(2,3), Point(1,4)])

    pass
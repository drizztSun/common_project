"""
1453. Maximum Number of Darts Inside of a Circular Dartboard


You have a very large square wall and a circular dartboard placed on the wall. You have been challenged to throw darts into the board blindfolded.
Darts thrown at the wall are represented as an array of points on a 2D plane.

Return the maximum number of points that are within or lie on any circular dartboard of radius r.



Example 1:



Input: points = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
Output: 4
Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
Example 2:



Input: points = [[-3,0],[3,0],[2,6],[5,4],[0,9],[7,8]], r = 5
Output: 5
Explanation: Circle dartboard with center in (0,4) and radius = 5 contain all points except the point (7,8).
Example 3:

Input: points = [[-2,0],[2,0],[0,2],[0,-2]], r = 1
Output: 1
Example 4:

Input: points = [[1,2],[3,5],[1,-1],[2,3],[4,1],[1,3]], r = 2
Output: 4


Constraints:

1 <= points.length <= 100
points[i].length == 2
-10^4 <= points[i][0], points[i][1] <= 10^4
1 <= r <= 5000


"""


class MaximumNumberOfDartsInsideOfACircularDartBoard:

    """
    解题思路
    第一种四次方的做法：枚举三个点，求出用这三个点确定的圆心，判断所有的点距离这个点是否小于r，求出可以覆盖点的个数

    第二种三次方的做饭：枚举两个点，用两个点和半径，确定圆心，之后做与第一种方法相同的操作，求出可以覆盖的点的个数
    O(n^3)
    """

    def doit_math(self, points: list, r: int) -> int:
        from itertools import combinations
        res = 1
        for (x1, y1), (x2, y2) in combinations(points, 2):
            d = (x2 - x1) ** 2 + (y2 - y1) ** 2
            if d > 4 * r ** 2 or d == 0:
                continue

            x0 = (x1 + x2) / 2.0 + (y2 - y1) * (r * r - d / 4) ** 0.5 / d ** 0.5
            y0 = (y1 + y2) / 2.0 - (x2 - x1) * (r * r - d / 4) ** 0.5 / d ** 0.5
            res = max(res, sum((x - x0) ** 2 + (y - y0) ** 2 <= r * r + 0.00001 for x, y in points))

            x0 = (x1 + x2) / 2.0 - (y2 - y1) * (r * r - d / 4) ** 0.5
            y0 = (y1 + y2) / 2.0 + (x2 - x1) * (r * r - d / 4) ** 0.5
            res = max(res, sum((x - x0) ** 2 + (y - y0) ** 2 <= r * r + 0.00001 for x, y in points))
        return res

    def doit_math(self, points: list, r: int) -> int:
        # Angular Sweep (N^2 x logN)
        from math import sqrt, atan2, acos
        ans = 1
        for x, y in points:
            angles = []
            for x1, y1 in points:
                if (x1 != x or y1 != y) and (d := sqrt((x1 - x)**2 + (y1 - y)**2)) <= 2 * r:
                    angle = atan2(y1 - y, x1 - x)
                    delta = acos(d / (2 * r))
                    angles.append((angle - delta, 1))
                    angles.append((angle + delta, -1))

            angles.sort(key=lambda x: (x[0], -x[1]))
            val = 1
            for _, entry in angles:
                ans = max(ans, val := val + entry)

        return ans
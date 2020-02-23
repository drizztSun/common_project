# 1037. Valid Boomerang

# A boomerang is a set of 3 points that are all distinct and not in a straight line.

# Given a list of three points in the plane, return whether these points are a boomerang.


# Example 1:

# Input: [[1,1],[2,3],[3,2]]
# Output: true

# Example 2:

# Input: [[1,1],[2,2],[3,3]]
# Output: false


# Note:

# points.length == 3
# points[i].length == 2
# 0 <= points[i][j] <= 100


class IsBoomerang:

    def doit(self, points):

        if points[0] == points[1] or points[1] == points[2] or points[0] == points[2]:
            return False

        f1 = float('inf') if points[0][0] == points[1][0] else (
            points[0][1] - points[1][1]) / (points[0][0] - points[1][0])

        f2 = float('inf') if points[1][0] == points[2][0] else (
            points[2][1] - points[1][1]) / (points[2][0] - points[1][0])

        return f1 != f2

    def doit(self, points):

        p1, p2, p3 = points

        def slope(p1, p2):
            return [p2[1]-p1[1], p2[0]-p1[0]]

        slope1 = slope(p1, p2)
        slope2 = slope(p2, p3)

        return slope1[0]*slope2[1] != slope1[1]*slope2[0]


if __name__ == '__main__':

    res = IsBoomerang().doit([[1, 1], [2, 3], [3, 2]])

    res = IsBoomerang().doit([[1, 1], [2, 2], [3, 3]])

    pass

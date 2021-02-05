# 939. Minimum Area Rectangle

# Given a set of points in the xy-plane, determine the minimum area of a rectangle formed from these points, "with sides parallel to the x and y axes".

# If there isn't any rectangle, return 0.


# Example 1:

# Input: [[1,1],[1,3],[3,1],[3,3],[2,2]]
# Output: 4

# Example 2:

# Input: [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
# Output: 2


# Note:

# 1 <= points.length <= 500
# 0 <= points[i][0] <= 40000
# 0 <= points[i][1] <= 40000
# All points are distinct.

from collections import defaultdict


class MinAreaRect:

    def doit(self, A):
        n = len(points)
        nx = len(set(p[0] for p in points))
        ny = len(set(p[1] for p in points))
        if nx == n or ny == n:
            return 0

        point_dict = {}
        for x, y in points:
            if nx < ny:
                if y not in point_dict:
                    point_dict[y] = []
                point_dict[y].append(x)
            else:
                if x not in point_dict:
                    point_dict[x] = []
                point_dict[x].append(y)

        min_area = float("inf")

        last_x = {}
        for x in sorted(point_dict):
            point_dict[x].sort()
            for j in range(len(point_dict[x])):
                for i in range(j):
                    y1, y2 = point_dict[x][i], point_dict[x][j]
                    if (y1, y2) in last_x:
                        area = (x - last_x[(y1, y2)]) * (y2 - y1)
                        min_area = min(min_area, area)
                    last_x[(y1, y2)] = x

        return min_area if min_area != float("inf") else 0

    """
    Approach 1: Sort by Column
    Intuition

    Count each rectangle by right-most edge.

    Algorithm

    Group the points by x coordinates, so that we have columns of points. Then, for every pair of points in a column (with coordinates (x,y1) and (x,y2)),
    check for the smallest rectangle with this pair of points as the rightmost edge. We can do this by keeping memory of what pairs of points we've seen before.

    Complexity Analysis

    Time Complexity: O(N^2) where NN is the length of points.
    Space Complexity: O(N).
    """

    def doit(self, points):
        import collections
        columns = collections.defaultdict(list)
        for x, y in points:
            columns[x].append(y)

        lastx = {}
        ans = float("inf")

        for x in sorted(columns):
            column = columns[x]
            column.sort()
            for j, y2 in enumerate(column):
                for i in range(j):
                    y1 = column[i]
                    if (y1, y2) in lastx:
                        ans = min(ans, (x - lastx[y1, y2]) * (y2 - y1))
                    lastx[y1, y2] = x
        return ans if ans < float("inf") else 0

    """
    Approach 2: Count by Diagonal
    Intuition

    For each pair of points in the array, consider them to be the long diagonal of a potential rectangle.
    We can check if all 4 points are there using a Set.

    For example, if the points are (1, 1) and (5, 5), we check if we also have (1, 5) and (5, 1).
    If we do, we have a candidate rectangle.

    Algorithm

    Put all the points in a set. For each pair of points, if the associated rectangle are 4 distinct points all in the set,
    then take the area of this rectangle as a candidate answer.

    Complexity Analysis

    Time Complexity: O(N^2), where N is the length of points.
    Space Complexity: O(N), where H is the height of the tree.
    """
    def doit(self, points):
        S = set(map(tuple, points))
        ans = float("inf")
        
        for j, p2 in enumerate(points):
            for i in range(j):
                p1 = points[i]
                if p1[0] != p2[0] and p1[1] != p2[1] and (p1[0], p2[1]) in S and (p2[0], p1[1]) in S:
                    ans = min(ans, abs(p2[0] - p1[0]) * abs(p2[1] - p1[1]))

        return ans if ans < float("inf") else 0


if __name__ == "__main__":

    res = MinAreaRect().doit([[1, 1], [1, 3], [3, 1], [3, 3], [2, 2]])  # 4

    res = MinAreaRect().doit([[1, 1], [1, 3], [3, 1], [3, 3], [4, 1], [4, 3]])  # 2

    pass

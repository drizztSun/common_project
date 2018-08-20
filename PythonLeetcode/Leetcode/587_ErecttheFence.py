


# 587. Erect the Fence

# There are some trees, where each tree is represented by (x,y) coordinate in a two-dimensional garden.
# Your job is to fence the entire garden using the minimum length of rope as it is expensive.
# The garden is well fenced only if all the trees are enclosed.
# Your task is to help find the coordinates of trees which are exactly located on the fence perimeter.

# Example 1:
# Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
# Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
# Explanation:

# Example 2:
# Input: [[1,2],[2,2],[4,2]]
# Output: [[1,2],[2,2],[4,2]]
# Explanation:


# Note:

# All trees should be enclosed together. You cannot cut the rope to enclose trees that will separate them
# in more than one group.
# All input integers will range from 0 to 100.
# The garden has at least one tree.
# All coordinates are distinct.
# Input points have NO order. No order required for output.


# Definition for a point.
class Point(object):
    def __init__(self, a=0, b=0):
        self.x = a
        self.y = b



class OuterTrees(object):

    # Monotone Chain Convex Hull
    # http://www.algorithmist.com/index.php/Monotone_Chain_Convex_Hull
    #
    # Andrew's monotone chain convex hull algorithm constructs the convex hull of a set of 2-dimensional
    #  points in O(nlogn) time.

    # It does so by first sorting the points lexicographically (first by x-coordinate, and in case of a tie,
    #  by y-coordinate), and then constructing upper and lower hulls of the points in O(n) time.

    # An upper hull is the part of the convex hull, which is visible from the above.
    # It runs from its rightmost point to the leftmost point in counterclockwise order.
    # Lower hull is the remaining part of the convex hull.

    # the points in O(n) time.

    # An upper hull is the part of the convex hull, which is visible from the above.
    # It runs from its rightmost point to the leftmost point in counterclockwise order.
    # Lower hull is the remaining part of the convex hull.

    # Pseudo-code
    # Input: a list P of points in the plane.

    # Sort the points of P by x-coordinate (in case of a tie, sort by y-coordinate).

    # Initialize U and L as empty lists.
    # The lists will hold the vertices of upper and lower hulls respectively.

    # for i = 1, 2, ..., n:
    #    while L contains at least two points and the sequence of last two points
    #            of L and the point P[i] does not make a counter-clockwise turn:
    #        remove the last point from L
    #    append P[i] to L

    # for i = n, n-1, ..., 1:
    #    while U contains at least two points and the sequence of last two points
    #            of U and the point P[i] does not make a counter-clockwise turn:
    #        remove the last point from U
    #    append P[i] to U

    # Remove the last point of each list (it's the same as the first point of the other list).
    # Concatenate L and U to obtain the convex hull of P.
    # Points in the result will be listed in counter-clockwise order.
    def doit(self, points):
        """
        :type points: List[Point]
        :rtype: List[Point]
        """
        if len(points) < 2:
            return points

        # 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
        # Returns a positive value, if OAB makes a counter-clockwise turn,
        # negative for clockwise turn, and zero if the points are collinear.
        def cross(o, a, b):
            return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x)

        lowerHull, upperHull = [], []
        points = sorted(set(points), key=lambda p: (p.x, p.y))

        for i in reversed(range(len(points))):
            while len(upperHull) > 1 and cross(upperHull[-2], upperHull[-1], points[i]) < 0:
                upperHull.pop()
            upperHull.append(points[i])

        for i in range(len(points)):
            while len(lowerHull) > 1 and cross(lowerHull[-2], lowerHull[-1], points[i]) < 0:
                lowerHull.pop()
            lowerHull.append(points[i])

        return list(set(lowerHull[:-1] + upperHull[:-1]))

    def doit2(self, points):
        # Sort the points lexicographically (tuples are compared lexicographically).
        # Remove duplicates to detect the case we have just one unique point.
        # points = sorted(set(points))
        points = sorted(points, key=lambda p: (p.x, p.y))

        # Boring case: no points or a single point, possibly repeated multiple times.
        if len(points) <= 1:
            return points

        # 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
        # Returns a positive value, if OAB makes a counter-clockwise turn,
        # negative for clockwise turn, and zero if the points are collinear.
        def cross(o, a, b):
            # return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])
            return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x)

        # Build lower hull
        lower = []
        for p in points:
            while len(lower) >= 2 and cross(lower[-2], lower[-1], p) < 0:
                lower.pop()
            lower.append(p)

        # Build upper hull
        upper = []
        for p in reversed(points):
            while len(upper) >= 2 and cross(upper[-2], upper[-1], p) < 0:
                upper.pop()
            upper.append(p)

        # Concatenation of the lower and upper hulls gives the convex hull.
        # Last point of each list is omitted because it is repeated at the
        # beginning of the other list.
        # return lower[:-1] + upper[:-1]
        return list(set(lower[:-1] + upper[:-1]))

def convex_hull(points):
    """Computes the convex hull of a set of 2D points.

    Input: an iterable sequence of (x, y) pairs representing the points.
    Output: a list of vertices of the convex hull in counter-clockwise order,
      starting from the vertex with the lexicographically smallest coordinates.
    Implements Andrew's monotone chain algorithm. O(n log n) complexity.
    """

    # Sort the points lexicographically (tuples are compared lexicographically).
    # Remove duplicates to detect the case we have just one unique point.
    points = sorted(set(points))

    # Boring case: no points or a single point, possibly repeated multiple times.
    if len(points) <= 1:
        return points

    # 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
    # Returns a positive value, if OAB makes a counter-clockwise turn,
    # negative for clockwise turn, and zero if the points are collinear.
    def cross(o, a, b):
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

    # Build lower hull
    lower = []
    for p in points:
        while len(lower) >= 2 and cross(lower[-2], lower[-1], p) <= 0:
            lower.pop()
        lower.append(p)

    # Build upper hull
    upper = []
    for p in reversed(points):
        while len(upper) >= 2 and cross(upper[-2], upper[-1], p) <= 0:
            upper.pop()
        upper.append(p)

    # Concatenation of the lower and upper hulls gives the convex hull.
    # Last point of each list is omitted because it is repeated at the beginning of the other list.
    return lower[:-1] + upper[:-1]


# Example: convex hull of a 10-by-10 grid.
# assert convex_hull([(i / 10, i % 10) for i in range(100)]) == [(0, 0), (9, 0), (9, 9), (0, 9)]


if __name__ == "__main__":

    L = []
    for c in [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]:
        L.append(Point(c[0], c[1]))

    res = OuterTrees().doit(L) # [[1,1],[2,0],[4,2],[3,3],[2,4]]

    pass
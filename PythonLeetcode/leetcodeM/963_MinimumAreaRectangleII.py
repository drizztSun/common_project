# 963. Minimum Area Rectangle II

# Given a set of points in the xy-plane, determine the minimum area of any rectangle formed from these points,
# with sides not necessarily parallel to the x and y axes.

# If there isn't any rectangle, return 0.

# Example 1:

# Input: [[1,2],[2,1],[1,0],[0,1]]
# Output: 2.00000
# Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.

# Example 2:

# Input: [[0,1],[2,1],[1,1],[1,0],[2,0]]
# Output: 1.00000
# Explanation: The minimum area rectangle occurs at [1,0],[1,1],[2,1],[2,0], with an area of 1.

# Example 3:

# Input: [[0,3],[1,2],[3,1],[1,3],[2,1]]
# Output: 0
# Explanation: There is no possible rectangle to form from these points.

# Example 4:

# Input: [[3,1],[1,1],[0,1],[2,1],[3,3],[3,2],[0,2],[2,3]]
# Output: 2.00000
# Explanation: The minimum area rectangle occurs at [2,1],[2,3],[3,3],[3,1], with an area of 2.


class MinAreaFreeRect:

    """
    Approach 1: Iterate Triangles
    Intuition
    For each triangle, let's try to find the 4th point and whether it is a rectangle.

    Algorithm
    Say the first 3 points are p1, p2, p3, and that p2 and p3 are opposite corners of the final rectangle.
    The 4th point must be p4 = p2 + p3 - p1 (using vector notation) because p1, p2, p4, p3 must form a parallelogram,
    and p1 + (p2 - p1) + (p3 - p1) = p4.

    If this point exists in our collection (we can use a HashSet to check),
    then we should check that the angles of this parallelogram are 90 degrees.
    The easiest way is to check the dot product of the two vectors (p2 - p1) and (p3 - p1).
    (Another way is we could normalize the vectors to length 1, and check that one equals the other rotated by 90 degrees.)

    Complexity Analysis
    Time Complexity: O(N^3), where NN is the length of points.
    Space Complexity: O(N).
    """

    import itertools

    def doit(self, points):
        EPS = 1e-7
        points = set(map(tuple, points))

        for p1, p2, p3 in itertools.pemutation(ponts, 3):

            p4 = p2[0] + p3[0] - p1[0], p2[1] + p3[1] - p1[1]
            if p4 in points:
                v21 = complex(p2[0] - p1[0], p2[1] - p1[1])
                v31 = complex(p3[0] - p1[0], p3[1] - p1[1])

                if abs(v21.real * v31.real + v21.imag * v31.imag) < EPS:
                    ans = min(ans, abs(v21) * abs(v31))

        return ans

    """
    Approach 2: Iterate Centers
    Intuition
    Consider opposite points AC and BD of a rectangle ABCD. They both have the same center O, which is the midpoint of AC and the midpoint of AB;
    and they both have the same radius dist(O, A) == dist(O, B) == dist(O, C) == dist(O, D).
    Notice that a necessary and sufficient condition to form a rectangle with two opposite pairs of points is that the points must have the same center and radius.
    Motivated by that result, let's classify each pair of points PQ by their center C = the midpoint of PQ, and the radius r = dist(P, C).
    Our strategy is to brute force on pairs of points with the same classification.

    Algorithm
    For each pair of points, classify them by center and radius.
    We only need to record one of the points P, since the other point is P' = 2 * center - P (using vector notation).
    For each center and radius, look at every possible rectangle (two pairs of points P, P', Q, Q').
    The area of this rectangle dist(P, Q) * dist(P, Q') is a candidate answer.

    Complexity Analysis

    Time Complexity: O(N^2 * log N), where N is the length of points.
    It can be shown that the number of pairs of points with the same classification is bounded by \log NlogN - see this link for more.

    Space Complexity: O(N).
    """

    def minAreaFreeRect(self, points):

        import itertools
        import collections

        points = [complex(*z) for z in points]
        seen = collections.defaultdict(list)

        for P, Q in itertools.combinations(points, 2):
            center = (P + Q) / 2
            radius = abs(center - P)
            seen[(center, radius)].append(P)

        ans = float("inf")
        for (center, radius), candidates in seen.items():

            for P, Q in itertools.combinations(candidates, 2):

                ans = min(ans, abs(P - Q) * abs(P - (2 * center - Q)))

        return ans if ans < float("inf") else 0


if __name__ == "__main__":

    res = MinAreaFreeRect().doit([[1, 2], [2, 1], [1, 0], [0, 1]])

    res = MinAreaFreeRect().doit([[0, 1], [2, 1], [1, 1], [1, 0], [2, 0]])

    res = MinAreaFreeRect().doit([[0, 3], [1, 2], [3, 1], [1, 3], [2, 1]])

    res = MinAreaFreeRect().doit(
        [[3, 1], [1, 1], [0, 1], [2, 1], [3, 3], [3, 2], [0, 2], [2, 3]]
    )

    pass

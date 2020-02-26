# 1039. Minimum Score Triangulation of Polygon

# Given N, consider a convex N-sided polygon with vertices labelled A[0], A[i], ..., A[N-1] in clockwise order.

# Suppose you triangulate the polygon into N-2 triangles.  For each triangle, the value of that triangle is the product of the labels of the vertices, and the total score of the triangulation is the sum of these values over all N-2 triangles in the triangulation.

# Return the smallest possible total score that you can achieve with some triangulation of the polygon.


# Example 1:

# Input: [1,2,3]
# Output: 6
# Explanation: The polygon is already triangulated, and the score of the only triangle is 6.

# Example 2:


# Input: [3,7,4,5]
# Output: 144
# Explanation: There are two triangulations, with possible scores: 3*7*5 + 4*5*7 = 245, or 3*4*5 + 3*4*7 = 144.  The minimum score is 144.

# Example 3:

# Input: [1,3,1,4,1,5]
# Output: 13
# Explanation: The minimum score triangulation has score 1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13.

class MinScoreTriangulation:

    def doit(self, A):

        memo = [[0 for _ in range(len(A))] for _ in range(len(A))]

        # steps - vertices distance
        for j in range(2, len(A)):

            # try start with each vertex from baseline - vertex with index 0
            for i in range(len(A) - j):

                memo[i][i+j] = float('inf') if memo[i][i + j] == 0 else memo[i][j]

                # choose third vertex within range to make a triangle
                for k in range(i+1, i+j):
                    memo[i][i+j] = min(memo[i][i+j], memo[i][k] + memo[k][i+j] + A[i] * A[k] * A[i+j])

        return memo[0][len(A)-1]


if __name__ == '__main__':

    res = MinScoreTriangulation().doit([1, 2, 3])

    res = MinScoreTriangulation().doit([3, 7, 4, 5])

    res = MinScoreTriangulation().doit([1, 3, 1, 4, 1, 5])

    pass

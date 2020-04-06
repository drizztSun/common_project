package leetcodem

/*

1039. Minimum Score Triangulation of Polygon

Given N, consider a convex N-sided polygon with vertices labelled A[0], A[i], ..., A[N-1] in clockwise order.

Suppose you triangulate the polygon into N-2 triangles.
For each triangle, the value of that triangle is the product of the labels of the vertices,
and the total score of the triangulation is the sum of these values over all N-2 triangles in the triangulation.

Return the smallest possible total score that you can achieve with some triangulation of the polygon.



Example 1:

Input: [1,2,3]
Output: 6
Explanation: The polygon is already triangulated, and the score of the only triangle is 6.

Example 2:

Input: [3,7,4,5]
Output: 144
Explanation: There are two triangulations, with possible scores: 3*7*5 + 4*5*7 = 245, or 3*4*5 + 3*4*7 = 144.  The minimum score is 144.
Example 3:

Input: [1,3,1,4,1,5]
Output: 13
Explanation: The minimum score triangulation has score 1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13.
*/

func minScoreTriangulation(A []int) int {

	if len(A) == 0 {
		return 0
	}

	N := len(A)
	dp := make([][]int, N)
	for i := 0; i < N; i++ {
		dp[i] = make([]int, N)
	}

	for i := 2; i < N; i++ {

		for j := i - 2; j >= 0; j-- {

			for k := j + 1; k < i; k++ {

				cur_area := dp[j][k] + A[i]*A[k]*A[j] + dp[k][i]
				if dp[j][i] == 0 || dp[j][i] > cur_area {
					dp[j][i] = cur_area
				}
			}
		}
	}
	return dp[0][N-1]
}

func Test_1039_MinimumScoreTriangulationOfPolygon() {

	minScoreTriangulation([]int{1, 2, 3})

	minScoreTriangulation([]int{3, 7, 4, 5})

	minScoreTriangulation([]int{1, 3, 1, 4, 1, 5})
}

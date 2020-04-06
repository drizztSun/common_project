package leetcodem

/*
1035. Uncrossed Lines

We write the integers of A and B (in the order they are given) on two separate horizontal lines.

Now, we may draw connecting lines: a straight line connecting two numbers A[i] and B[j] such that:

A[i] == B[j];
The line we draw does not intersect any other connecting (non-horizontal) line.
Note that a connecting lines cannot intersect even at the endpoints: each number can only belong to one connecting line.

Return the maximum number of connecting lines we can draw in this way.



Example 1:


Input: A = [1,4,2], B = [1,2,4]
Output: 2
Explanation: We can draw 2 uncrossed lines as in the diagram.
We cannot draw 3 uncrossed lines, because the line from A[1]=4 to B[2]=4 will intersect the line from A[2]=2 to B[1]=2.
Example 2:

Input: A = [2,5,1,2,5], B = [10,5,2,1,5,2]
Output: 3
Example 3:

Input: A = [1,3,7,1,7,5], B = [1,9,2,5,1]
Output: 2

*/

func maxUncrossedLines(A []int, B []int) int {

	N, M := len(A), len(B)
	dp := make([][]int, N+1)

	maxv := func(a, b int) int {
		if a > b {
			return a
		}
		return b
	}

	dp[0] = make([]int, M+1)
	for i := 1; i < N+1; i++ {
		dp[i] = make([]int, M+1)

		for j := 1; j < M+1; j++ {

			dp[i][j] = dp[i-1][j-1]
			if A[i-1] == B[j-1] {
				dp[i][j]++
			}

			dp[i][j] = maxv(dp[i][j], maxv(dp[i-1][j], dp[i][j-1]))
		}
	}

	return dp[N][M]
}

func Test_1035_UncrossedLines() {

	maxUncrossedLines([]int{1, 4, 2}, []int{1, 2, 4})

	maxUncrossedLines([]int{2, 5, 1, 2, 5}, []int{10, 5, 2, 1, 5, 2})

	maxUncrossedLines([]int{1, 3, 7, 1, 7, 5}, []int{1, 9, 2, 5, 1})
}
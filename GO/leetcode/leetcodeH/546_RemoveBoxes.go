package leetcodeH

/*
Given several boxes with different colors represented by different positive numbers.
You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
Find the maximum points you can get.



Example 1:

Input: boxes = [1,3,2,2,2,3,4,3,1]
Output: 23
Explanation:
[1, 3, 2, 2, 2, 3, 4, 3, 1]
----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
----> [1, 3, 3, 3, 1] (1*1=1 points)
----> [1, 1] (3*3=9 points)
----> [] (2*2=4 points)


Constraints:

1 <= boxes.length <= 100
1 <= boxes[i] <= 100

*/

/*
		Let A be the array of boxes.

	One natural approach is to consider dp(i, j) = the answer for A[i: j+1]. But this isn’t flexible enough for divide and conquer style strategies.
	For example, with [1,2,2,2,1], we don’t have enough information when investigating things like [1,2,2,2] and [1] separately.

	Let dp(i, j, k) = the maximum value of removing boxes if we have k extra boxes of color A[i] to the left of A[i: j+1].
	(We would have at most k < len(A) extra boxes.)
	Let m <= j be the largest value so that A[i], A[i+1], … A[m] are all the same color.
	Because *** a^2 + b^2 < (a+b)^2 ***, any block of contiguous boxes of the same color must be removed at the same time,

	so in fact dp(i, j, k) = dp(m, j, k+(m-i))   ------------- (1).

	Now, we could remove the k boxes we were carrying plus box A[i] (value: (k+1)**2), then remove the rest (value: dp(i+1, j, 0)).

	Or, for any point m in [i+1, j] with A[i] == A[m], we could remove dp(i+1, m-1) first,
	then [m, j] would have k+1 extra boxes of color A[m] behind, which has value dp(m, j, k+1).

	The “i, k = m, k + m - i” part skips order (m-i)*(j-i) calls to dp, and is necessary to get this kind of solution to pass in Python.
*/
func removeBoxexSeach(boxes []int, dp [][][]int, i, j, k int) int {

	if i > j {
		return 0
	}

	if dp[i][j][k] != 0 {
		return dp[i][j][k]
	}

	m := i
	for m+1 <= j && boxes[m+1] == boxes[i] {
		m++
	}

	i, k = m, k+m-i
	res := removeBoxexSeach(boxes, dp, i+1, j, 0) + (k+1)*(k+1)

	for m = i + 1; m <= j; m++ {
		if boxes[i] == boxes[m] {
			ans := removeBoxexSeach(boxes, dp, i+1, m-1, 0) + removeBoxexSeach(boxes, dp, m, j, k+1)
			if ans > res {
				res = ans
			}
		}
	}
	dp[i][j][k] = res
	return res
}

func removeBoxes_dp(boxes []int) int {

	N := len(boxes)
	dp := make([][][]int, N)
	for i := range dp {
		dp[i] = make([][]int, N)
		for j := range dp[i] {
			dp[i][j] = make([]int, N)
		}
	}
	return removeBoxexSeach(boxes, dp, 0, len(boxes)-1, 0)
}

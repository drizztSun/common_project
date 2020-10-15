package leetcodeH

/*

446. Arithmetic Slices II - Subsequence

A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequences:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. A subsequence slice of that array is any sequence of integers (P0, P1, ..., Pk) such that 0 ≤ P0 < P1 < ... < Pk < N.

A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic. In particular, this means that k ≥ 2.

The function should return the number of arithmetic subsequence slices in the array A.

The input contains N integers. Every integer is in the range of -231 and 231-1 and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 231-1.


Example:

Input: [2, 4, 6, 8, 10]

Output: 7

Explanation:
All arithmetic subsequence slices are:
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]

*/

func numberOfArithmeticSlices_dp(A []int) int {

	dp := make([]map[int]int, len(A))
	for i := 0; i < len(A); i++ {
		dp[i] = make(map[int]int, 0)
	}
	result := 0

	for i := range A {

		for j := 0; j < i; j++ {

			diff := A[i] - A[j]

			dp[i][diff]++
			if _, ok := dp[j][diff]; ok {
				dp[i][diff] += dp[j][diff]
				result += dp[j][diff]
			}
		}

	}

	return result
}

func numberOfArithmeticSlices_dp_1(A []int) int {

	pre := make(map[int]int, 0)
	post := make(map[int]int, 0)
	pos := make(map[int][]int, 0)
	seq := make([]map[int]int, len(A))

	for i, c := range A {
		post[c]++
		if _, ok := pos[c]; !ok {
			pos[c] = make([]int, 0)
		}
		pos[c] = append(pos[c], i)
		seq[i] = make(map[int]int, 0)
	}

	for i, b := range A {

		post[b]--

		for c, v := range pre {

			a := b*2 - c

			if cnt, ok := post[a]; ok && cnt > 0 {

				if bcnt, ok := seq[i][c]; ok {
					v += bcnt
				}

				if postKv, ok := pos[a]; ok {
					for _, j := range postKv {
						if j > i {
							seq[j][b] += v
						}
					}
				}
			}

		}
		pre[b]++
	}

	res := 0
	for _, v := range seq {
		for _, c := range v {
			res += c
		}
	}
	return res
}

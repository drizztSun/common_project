package leetcodem

/*
1031. Maximum Sum of Two Non-Overlapping Subarrays

Given an array A of non-negative integers, return the maximum sum of elements in two non-overlapping (contiguous) subarrays, which have lengths L and M.  (For clarification, the L-length subarray could occur before or after the M-length subarray.)

Formally, return the largest V for which V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ... + A[j+M-1]) and either:

0 <= i < i + L - 1 < j < j + M - 1 < A.length, or
0 <= j < j + M - 1 < i < i + L - 1 < A.length.


Example 1:

Input: A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
Output: 20
Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
Example 2:

Input: A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
Output: 29
Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.
Example 3:

Input: A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
Output: 31
Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [3,8] with length 3.
*/

func maxSumTwoNoOverlap(A []int, L int, M int) int {

	Llwnd, Mlwnd := make([]int, len(A)), make([]int, len(A))
	Lrwnd, Mrwnd := make([]int, len(A)), make([]int, len(A))

	ltotal, mtotal := 0, 0
	for i := range A {

		ltotal += A[i]
		if i >= L {
			ltotal -= A[i-L]
			Lrwnd[i-L] = ltotal
		}
		Llwnd[i] = ltotal

		mtotal += A[i]
		if i >= M {
			mtotal -= A[i-M]
			Mrwnd[i-M] = mtotal
		}
		Mlwnd[i] = mtotal
	}

	maxv := func(a, b int) int {
		if a > b {
			return a
		}
		return b
	}

	for i := 1; i < len(A); i++ {
		Llwnd[i] = maxv(Llwnd[i-1], Llwnd[i])
		Mlwnd[i] = maxv(Mlwnd[i-1], Mlwnd[i])
	}

	for i := len(A) - 2; i > -1; i-- {
		Lrwnd[i] = maxv(Lrwnd[i+1], Lrwnd[i])
		Mrwnd[i] = maxv(Mrwnd[i+1], Mrwnd[i])
	}

	ans := 0
	for i := 0; i < len(A); i++ {
		ans = maxv(ans, maxv(Llwnd[i]+Mrwnd[i], Mlwnd[i]+Lrwnd[i]))
	}

	return ans
}

func Test_1031_MaximumSumOfTwoNonOverlappingSubarray() {

	maxSumTwoNoOverlap([]int{0, 6, 5, 2, 2, 5, 1, 9, 4}, 1, 2)

	maxSumTwoNoOverlap([]int{3, 8, 1, 3, 2, 1, 8, 9, 0}, 3, 2)

	maxSumTwoNoOverlap([]int{2, 1, 5, 6, 0, 9, 5, 0, 3, 8}, 4, 3)
}

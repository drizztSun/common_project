package leetcodem

/*
1043. Partition Array for Maximum Sum

Given an integer array A, you partition the array into (contiguous) subarrays of length at most K.
After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning.



Example 1:

Input: A = [1,15,7,9,2,5,10], K = 3
Output: 84
Explanation: A becomes [15,15,15,9,10,10,10]
*/

func maxSumAfterPartitioning(A []int, K int) int {

	dp := make([]int, len(A)+1)

	for i := 0; i < len(A); i++ {

		maxv := 0
		for j := 0; j < K; j++ {

			if i-j >= 0 {
				if A[i-j] > maxv {
					maxv = A[i-j]
				}

				if dp[i+1] < dp[i-j]+(j+1)*maxv {
					dp[i+1] = dp[i-j] + (j+1)*maxv
				}
			}
		}
	}

	return dp[len(A)]
}

func Test_1043_PartitionArrayForMaximumSum() {

	maxSumAfterPartitioning([]int{1, 15, 7, 9, 2, 5, 10}, 3)
}

package leetcodeH

/*

 992. Subarrays with K Different Integers


 Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.

 (For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)

 Return the number of good subarrays of A.



 Example 1:

 Input: A = [1,2,1,2,3], K = 2
 Output: 7
 Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
 Example 2:

 Input: A = [1,2,1,3,4], K = 3
 Output: 3
 Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].


*/

func SubarraysWithKDistinct(A []int, K int) int {

	left_long := make(map[int]int)
	left_short := make(map[int]int)
	cnt_long, cnt_short := 0, 0
	ll, ls := 0, 0
	ans := 0

	for _, v := range A {

		left_long[v] += 1
		left_short[v] += 1

		if left_long[v] == 1 {
			cnt_long += 1
		}

		if left_short[v] == 1 {
			cnt_short += 1
		}

		for cnt_long > K {
			left_long[A[ll]] -= 1
			if left_long[A[ll]] == 0 {
				cnt_long -= 1
			}
			ll += 1
		}

		for cnt_short >= K {
			left_short[A[ls]] -= 1
			if left_short[A[ls]] == 0 {
				cnt_short -= 1
			}
			ls += 1
		}

		ans += ls - ll
	}

	return ans
}

func Test_992_SubarrayWithKDistinct() {

	SubarraysWithKDistinct([]int{1, 2, 1, 2, 3}, 2)

	SubarraysWithKDistinct([]int{1, 2, 1, 3, 4}, 3)

	return
}

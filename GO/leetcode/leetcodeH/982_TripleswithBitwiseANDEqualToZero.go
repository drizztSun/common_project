package leetcodeH

/*

982. Triples with Bitwise AND Equal To Zero

Share
Given an array of integers A, find the number of triples of indices (i, j, k) such that:

0 <= i < A.length
0 <= j < A.length
0 <= k < A.length
A[i] & A[j] & A[k] == 0, where & represents the bitwise-AND operator.


Example 1:

Input: [2,1,3]
Output: 12
Explanation: We could choose the following i, j, k triples:
(i=0, j=0, k=1) : 2 & 2 & 1
(i=0, j=1, k=0) : 2 & 1 & 2
(i=0, j=1, k=1) : 2 & 1 & 1
(i=0, j=1, k=2) : 2 & 1 & 3
(i=0, j=2, k=1) : 2 & 3 & 1
(i=1, j=0, k=0) : 1 & 2 & 2
(i=1, j=0, k=1) : 1 & 2 & 1
(i=1, j=0, k=2) : 1 & 2 & 3
(i=1, j=1, k=0) : 1 & 1 & 2
(i=1, j=2, k=0) : 1 & 3 & 2
(i=2, j=0, k=1) : 3 & 2 & 1
(i=2, j=1, k=0) : 3 & 1 & 2

*/

import "math/bits"

func countTriplets(A []int) int {

	cache := make(map[uint32]int)

	for _, x := range A {
		for _, y := range A {
			cache[uint32(x&y)]++
		}
	}

	ans := 0
	for _, k := range A {

		k := uint32(k)
		bits := bits.Reverse32(uint32(k)) & 0xFFFFFFFF

		for k := bits; k != 0; k = (k - 1) & bits {
			ans += cache[k]
		}
	}
	return ans
}

func countTriplets1(A []int) int {

	cache := make(map[int]int)

	for _, x := range A {
		for _, y := range A {
			cache[x&y]++
		}
	}

	ans := 0
	for _, k := range A {

		for xy, v := range cache {

			if xy&k == 0 {
				ans += v
			}
		}
	}
	return ans
}

func Test_982_TripleWithBitwiseAndEqualToZero() {

	countTriplets1([]int{2, 1, 3})
}

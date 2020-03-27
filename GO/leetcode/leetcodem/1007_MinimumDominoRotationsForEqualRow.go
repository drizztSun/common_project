package leetcodem

/*

In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.  (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the i-th domino, so that A[i] and B[i] swap values.

Return the minimum number of rotations so that all the values in A are the same, or all the values in B are the same.

If it cannot be done, return -1.

Example 1:


Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
Output: 2
Explanation:
The first figure represents the dominoes as given by A and B: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.


Example 2:

Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
Output: -1
Explanation:
In this case, it is not possible to rotate the dominoes to make one row of values equal.


*/

func minDominoRotations(A []int, B []int) int {

	cnt := make([]int, 7)
	max_index := 0

	for _, v := range A {
		cnt[v]++
		if cnt[v] > cnt[max_index] {
			max_index = v
		}
	}

	for _, v := range B {
		cnt[v]++
		if cnt[v] > cnt[max_index] {
			max_index = v
		}
	}

	if cnt[max_index] < (len(A)) {
		return -1
	}

	cnt_a, cnt_b := 0, 0

	for i := 0; i < len(A); i++ {

		if A[i] != max_index && B[i] != max_index {
			return -1
		}

		if A[i] == max_index && B[i] == max_index {
			continue
		}

		if A[i] == max_index {
			cnt_a++
		}

		if B[i] == max_index {
			cnt_b++
		}
	}

	if cnt_a < cnt_b {
		return cnt_a
	} else {
		return cnt_b
	}
}

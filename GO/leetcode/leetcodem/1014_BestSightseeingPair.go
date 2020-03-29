package leetcodem

/*


1014. Best Sightseeing Pair

Given an array A of positive integers, A[i] represents the value of the i-th sightseeing spot, and two sightseeing spots i and j have distance j - i between them.

The score of a pair (i < j) of sightseeing spots is (A[i] + A[j] + i - j) : the sum of the values of the sightseeing spots, minus the distance between them.

Return the maximum score of a pair of sightseeing spots.



Example 1:

Input: [8,1,5,2,6]
Output: 11
Explanation: i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11

*/

func maxScoreSightseeingPair(A []int) int {

	score, maxv := 0, 0

	for i, v := range A {

		if maxv != 0 && maxv+v-i > score {
			score = maxv + v - i
		}

		if maxv < i+v {
			maxv = v + i
		}

	}

	return score
}

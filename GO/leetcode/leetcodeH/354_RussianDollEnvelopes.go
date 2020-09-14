package leetcodeH

/*
354. Russian Doll Envelopes

You have a number of envelopes with widths and heights given as a pair of integers (w, h).
One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Note:
Rotation is not allowed.

Example:

Input: [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
*/
import (
	"sort"
)

func maxEnvelopes_dp(envelopes [][]int) int {

	binarySearch := func(evenenvelopes [][]int, tail []int, c []int) int {

		s, e := 0, len(tail)-1

		for s <= e {
			m := (s + e) / 2
			if envelopes[tail[m]][1] >= c[1] {
				e = m - 1
			} else {
				s = m + 1
			}
		}
		return s
	}

	sort.SliceStable(envelopes, func(i, j int) bool {
		return envelopes[i][0] < envelopes[j][0] || (envelopes[i][0] == envelopes[j][0] && envelopes[i][1] > envelopes[j][1])
	})

	tail := make([]int, 0)

	for i, c := range envelopes {

		index := binarySearch(envelopes, tail, c)

		if index >= len(tail) {
			tail = append(tail, i)
		} else {
			tail[index] = i
		}
	}

	return len(tail)
}

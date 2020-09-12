package leetcodem

/*
279. Perfect Squares

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
*/

import (
	"math"
)

func numSquares(n int) int {

	powers, cnt := make([]int, 0), 0

	for i := 1; i <= int(math.Sqrt(float64(n))); i++ {
		powers = append(powers, i*i)
	}

	check := map[int]bool{n: true}

	for len(check) > 0 {

		tmp := make(map[int]bool, 0)
		cnt++

		for k, _ := range check {

			for _, c := range powers {

				if c == k {
					return cnt
				}

				if c > k {
					break
				}

				tmp[k-c] = true
			}
		}

		check = tmp
	}

	return cnt
}

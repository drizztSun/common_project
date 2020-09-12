package leetcodem

/*
264. Ugly Number II

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note:

1 is typically treated as an ugly number.
n does not exceed 1690.
*/

func nthUglyNumber_dp(n int) int {

	minInt := func(a, b int) int {
		if a > b {
			return b
		}
		return a
	}

	buf := []int{1}
	i2, i3, i5 := 0, 0, 0

	for ; n > 1; n-- {

		n2, n3, n5 := 2*buf[i2], 3*buf[i3], 5*buf[i5]

		s := minInt(minInt(n2, n3), n5)

		if s == n2 {
			i2++
		}

		if s == n3 {
			i3++
		}

		if s == n5 {
			i5++
		}

		buf = append(buf, s)
	}

	return buf[len(buf)-1]
}

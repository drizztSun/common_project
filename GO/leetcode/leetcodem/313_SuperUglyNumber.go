package leetcodem

/*

313. Super Ugly Number

Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

Example:

Input: n = 12, primes = [2,7,13,19]
Output: 32
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
             super ugly numbers given primes = [2,7,13,19] of size 4.
Note:

1 is a super ugly number for any given primes.
The given numbers in primes are in ascending order.
0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

*/
import "math"

func nthSuperUglyNumber_array(n int, primes []int) int {

	k := len(primes)
	uglyNums := make([]int, n)
	index := make([]int, k)
	accum := make([]int, k)

	for i := 0; i < k; i++ {
		index[i] = 0
		accum[i] = primes[i]
	}

	t := 1

	for j := 0; j < n; j++ {

		uglyNums[j] = t
		t = math.MaxInt32
		for i := 0; i < k; i++ {

			if accum[i] == uglyNums[j] {
				index[i]++
				accum[i] = uglyNums[index[i]] * primes[i]
			}

			if accum[i] < t {
				t = accum[i]
			}
		}
	}

	return uglyNums[n-1]
}

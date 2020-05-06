package leetcodeH

import (
	"strconv"
	"math"
)

/*


902. Numbers At Most N Given Digit Set


We have a sorted set of digits D, a non-empty subset of {'1','2','3','4','5','6','7','8','9'}.  (Note that '0' is not included.)

Now, we write numbers using these digits, using each digit as many times as we want.  For example, if D = {'1','3','5'}, we may write numbers such as '13', '551', '1351315'.

Return the number of positive integers that can be written (using the digits of D) that are less than or equal to N.



Example 1:

Input: D = ["1","3","5","7"], N = 100
Output: 20
Explanation:
The 20 numbers that can be written are:
1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
Example 2:

Input: D = ["1","4","9"], N = 1000000000
Output: 29523
Explanation:
We can write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers,
81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers.
In total, this is 29523 integers that can be written using the digits of D.

*/



func atMostNGivenDigitSet1(D []string, N int) int {

	nums := make([]int, 0)

	for _, c := range D {
		n, _ := strconv.ParseInt(c, 10, 32)
		nums = append(nums, int(n))
	}

	bits := make([]int, 0)
	for N > 0 {
		bits = append(bits, N % 10)
		N /= 10
	}

	totals := len(nums)
	length := len(bits)

	res := 0
	for i := 1; i < length; i++ {
		res += int(math.Pow(float64(totals), float64(i)))
	}


	dp := make([]int, length + 1)
	dp[0] = 1

	for i := 0; i < length; i++ {

		for _, c := range nums {

			if c < bits[i] {
				dp[i+1] += int(math.Pow(float64(totals), float64(i)))
			} else if c == bits[i] {
				dp[i+1] += dp[i]
			}
		}

	}

	return res + dp[length]
}

func atMostNGivenDigitSet(D []string, N int) int {

	nums := make([]int, 0)

	for _, c := range D {
		n, _ := strconv.ParseInt(c, 10, 32)
		nums = append(nums, int(n))
	}

	bits := make([]int, 0)
	for N > 0 {
		bits = append(bits, N % 10)
		N /= 10
	}

	totals := len(nums)
	length := len(bits)

	res := 0
	for i := 1; i < length; i++ {
		res += int(math.Pow(float64(totals), float64(i)))
	}

	for i := 0; i < length; i++ {

		eq := false

		for _, c := range nums {
			if c < bits[i]{
				res += int(math.Pow(float64(totals), float64(i)))
			}
			if c == bits[i] {
				eq = true
			}
		}

		if eq == false {
			break
		}

		if i == length - 1 {
			res++
		}
	}

	return res
}


func Test_902_NumbersAtMostNGivenDigits() {

	atMostNGivenDigitSet([]string{"1","3","5","7"}, 100)

	atMostNGivenDigitSet([]string{"1","4","9"}, 1000000000)
}
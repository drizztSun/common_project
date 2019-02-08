package leetcodeE

/*
# 738. Monotone Increasing Digits

#Given a non-negative integer N, find the largest number that is less than or equal to N with monotone increasing digits.

#(Recall that an integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.)

#Example 1:
#Input: N = 10
#Output: 9
#Example 2:
#Input: N = 1234
#Output: 1234
#Example 3:
#Input: N = 332
#Output: 299
*/
import (
	"fmt"
)

func monotoneIncreasingDigits(N int) int {

	var s []int
	n := N
	for n > 0 {
		s = append(s, n%10)
		n /= 10
	}

	for i, prev := len(s)-1, len(s)-1; i > 0; i-- {

		if s[i] != s[prev] {
			prev = i
		}

		if s[i] > s[i-1] {
			s[prev]--
			for prev = prev - 1; prev >= 0; prev-- {
				s[prev] = 9
			}

			N = 0
			for j := len(s) - 1; j >= 0; j-- {
				N = s[j] + 10*N
			}
			break
		}
	}

	return N
}

func Test_738_Mono() {

	res := monotoneIncreasingDigits(999998)

	res = monotoneIncreasingDigits(1234)

	fmt.Println(res)
}

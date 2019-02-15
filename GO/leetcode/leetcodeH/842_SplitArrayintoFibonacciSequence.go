package leetcodeH

/*
Given a string S of digits, such as S = "123456579", we can split it into a Fibonacci-like sequence [123, 456, 579].

Formally, a Fibonacci-like sequence is a list F of non-negative integers such that:

0 <= F[i] <= 2^31 - 1, (that is, each integer fits a 32-bit signed integer type);
F.length >= 3;
and F[i] + F[i+1] = F[i+2] for all 0 <= i < F.length - 2.
Also, note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.

Return any Fibonacci-like sequence split from S, or return [] if it cannot be done.

Example 1:

Input: "123456579"
Output: [123,456,579]
Example 2:

Input: "11235813"
Output: [1,1,2,3,5,8,13]
Example 3:

Input: "112358130"
Output: []
Explanation: The task is impossible.
Example 4:

Input: "0123"
Output: []
Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
Example 5:

Input: "1101111"
Output: [110, 1, 111]
Explanation: The output [11, 0, 11, 11] would also be accepted.
Note:

1 <= S.length <= 200
S contains only digits.
*/

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

func splitIntoFibonacci(S string) []int {

	for i := 0; i < 10 && i < len(S); i++ {

		if S[0] == '0' && i > 0 {
			break
		}

		first, _ := strconv.Atoi(S[:i+1])

		for j := i + 1; j < i+10 && j < len(S); j++ {

			if S[i] == '0' && j > i+1 {
				break
			}

			second, _ := strconv.Atoi(S[i+1 : j+1])
			Fib := []int{first, second}

			k := j + 1
			for k < len(S) {
				c := Fib[len(Fib)-1] + Fib[len(Fib)-2]
				next := strconv.Itoa(c)

				if c < math.MaxInt32 && strings.HasPrefix(S[k:], next) {
					k += len(next)
					Fib = append(Fib, c)
				} else {
					break
				}
			}

			if k == len(S) && len(Fib) > 2 {
				return Fib
			}
		}

	}

	return make([]int, 0)
}

func Test_842_splitIntoFibonacci() {

	var res []int

	res = splitIntoFibonacci("123456579")

	res = splitIntoFibonacci("0123")

	res = splitIntoFibonacci("112358130")

	res = splitIntoFibonacci("0000")

	res = splitIntoFibonacci("539834657215398346785398346991079669377161950407626991734534318677529701785098211336528511")

	res = splitIntoFibonacci("539834657215398346785398346991079669377161950407626991734534318677529701785098211336528511")

	fmt.Println(res)

}

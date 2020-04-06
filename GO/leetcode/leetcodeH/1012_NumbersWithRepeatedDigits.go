package leetcodeH

/*
1012. Numbers With Repeated Digits

Given a positive integer N, return the number of positive integers less than or equal to N that have at least 1 repeated digit.



Example 1:

Input: 20
Output: 1
Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
Example 2:

Input: 100
Output: 10
Explanation: The positive numbers (<= 100) with atleast 1 repeated digit are 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.
Example 3:

Input: 1000
Output: 262


"""
Intuition
Count res the Number Without Repeated Digit
Then the number with repeated digits = N - res

Similar as
788. Rotated Digits
902. Numbers At Most N Given Digit Set

Explanation:
Transform N + 1 to arrayList
Count the number with digits < n
Count the number with same prefix
For example,
if N = 8765, L = [8,7,6,6],
the number without repeated digit can the the following format:
XXX
XX
X
1XXX ~ 7XXX
80XX ~ 86XX
870X ~ 875X
8760 ~ 8765

Time Complexity:
the number of permutations A(m,n) is O(1)
We count digit by digit, so it's O(logN)
"""

*/

func count(m, n int) int {
	if n == 0 {
		return 1
	}

	return count(m, n-1) * (m - n + 1)
}

func numDupDigitsAtMostN(N int) int {

	digits := make([]int, 0)
	for base := N + 1; base > 0; {
		digits = append([]int{base % 10}, digits...)
		base /= 10
	}
	n := len(digits)

	res := 0
	for i := 1; i < n; i++ {
		res += 9 * count(9, i-1)
	}

	s := make(map[int]bool)
	for i, v := range digits {
		base := 0
		if i == 0 {
			base = 1
		}

		for j := base; j < v; j++ {
			if _, ok := s[j]; !ok {
				res += count(9-i, n-i-1)
			}
		}

		if _, ok := s[v]; ok {
			break
		}

		s[v] = true
	}

	return N - res
}

func Test_1012_NumbersWithRepeatDigits() {

	numDupDigitsAtMostN(8765)

	numDupDigitsAtMostN(20)

	numDupDigitsAtMostN(100)

	numDupDigitsAtMostN(1000)
}

package leetcodem

/*
5. Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"

*/

func longestPalindrome(s string) string {

	N := len(s)
	dp := make([][]bool, N)
	res := ""

	for i := 0; i < N; i++ {
		dp[i] = make([]bool, N)
		for j := 0; j < N; j++ {
			dp[i][j] = false
			if i == j || j == i+1 && s[i] == s[j] {
				dp[i][j] = true
				if len(res) < j-i+1 {
					res = s[i : j+1]
				}
			}
		}
	}

	for step := 2; step < N; step++ {
		for i := 0; i+step < N; i++ {
			dp[i][step+i] = false
			if dp[i+1][step+i-1] && s[i] == s[step+i] {
				dp[i][step+i] = true
				if len(res) < step+1 {
					res = s[i : step+i+1]
				}
			}
		}
	}

	return res
}

func longestPalindrome_2(s string) string {
	if len(s) <= 1 {
		return s
	}
	stringLength := len(s)

	left, right := 0, 1

	longestPalindromeString := s[:1]

	for right != stringLength {
		right++
		if isPalinedrome(s[left:right]) {
			longestPalindromeString = s[left:right]

			shouldStop := false
			for !shouldStop {
				if left-1 < 0 || right+1 > stringLength {
					break
				}
				if s[left-1] == s[right] {
					left--
					right++
					longestPalindromeString = s[left:right]
				} else {
					shouldStop = true
				}
			}
			continue
		}

		left++
		if isPalinedrome(s[left:right]) {
			longestPalindromeString = s[left:right]

			shouldStop := false
			for !shouldStop {
				if left-1 < 0 || right+1 > stringLength {
					break
				}
				if s[left-1] == s[right] {
					left--
					right++
					longestPalindromeString = s[left:right]
				} else {
					shouldStop = true
				}
			}
		}
	}

	return longestPalindromeString
}

func isPalinedrome(s string) bool {
	r := []rune(s)
	stringLength := len(r)
	for i := 0; i < stringLength/2; i++ {
		if r[i] != r[stringLength-i-1] {
			return false
		}
	}
	return true
}

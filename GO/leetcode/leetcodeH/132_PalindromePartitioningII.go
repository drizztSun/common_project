package leetcodeH

/*
132. Palindrome Partitioning II

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.



Example 1:

Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
Example 2:

Input: s = "a"
Output: 0
Example 3:

Input: s = "ab"
Output: 1


Constraints:

1 <= s.length <= 2000
s consists of lower-case English letters only.
*/

func minCut_dp(s string) int {

	if len(s) == 0 {
		return 0
	}

	dp := make([]int, len(s)+1)
	for i := range dp {
		dp[i] = len(s) - i
	}

	partition := make([][]bool, len(s))
	for j := range partition {
		partition[j] = make([]bool, len(s))
	}

	for i := len(s) - 1; i >= 0; i-- {

		for j := i; j < len(s); j++ {

			if s[i] == s[j] && (j-i < 2 || partition[i+1][j-1]) {

				partition[i][j] = true

				if dp[i] > 1+dp[j+1] {
					dp[i] = 1 + dp[j+1]
				}
			}
		}
	}

	return dp[0] - 1
}

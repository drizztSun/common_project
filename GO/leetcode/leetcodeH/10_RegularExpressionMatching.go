package leetcodeH

/*

10. Regular Expression Matching


# Implement regular expression matching with support for '.' and '*'.
# '.' Matches any single character.
# '*' Matches zero or more of the preceding element.

# The matching should cover the entire input string (not partial).

# The function prototype should be:
# bool isMatch(const char *s, const char *p)

# Some examples:
# isMatch("aa","a") ? false
# isMatch("aa","aa") ? true
# isMatch("aaa","aa") ? false
# isMatch("aa", "a*") ? true
# isMatch("aa", ".*") ? true
# isMatch("ab", ".*") ? true
# isMatch("aab", "c*a*b") ? true

*/

func searchString(s, p string, i, j int, dict map[[2]int]bool) bool {

	if i == len(s) {
		for j < len(p) && p[j] == '*' {
			j++
		}
		return j == len(p)
	}

	if j == len(p) {
		return i == len(s)
	}

	key := [2]int{i, j}
	if v, ok := dict[key]; ok {
		return v
	}

	if i+1 < len(s) && p[i+1] == '*' {
		c := j
		for j < len(p) && p[j+1] != '*' {
			j++
		}

		// match 0 s
		if searchString(s, p, i, j+1, dict) {
			return true
		}

		// match multiple s
		for s[i] == p[c] || p[c] == '.' {
			if searchString(s, p, i+1, j+1, dict) {
				return true
			}
			i++
		}
	} else if s[i] == p[j] || p[j] == '.' {
		return searchString(s, p, i+1, j+1, dict)
	}

	dict[key] = false

	return false
}

func isMatch(s, p string) bool {

	dict := make(map[[2]int]bool)

	return searchString(s, p, 0, 0, dict)
}

func isMatchDP(s, p string) bool {

	M, N := len(s)+1, len(p)+1

	dp := make([][]bool, M)
	for i := 0; i < M; i++ {
		dp[i] = make([]bool, N)
	}

	dp[0][0] = true
	for j := 1; j < N; j++ {
		dp[0][j] = p[j-1] == '*' && dp[0][j-2]
	}

	for i := 1; i < M; i++ {

		for j := 1; j < N; j++ {

			if p[j-1] != '*' {
				dp[i][j] = (s[i-1] == p[j-1] || p[j-1] == '.') && dp[i-1][j-1]
			} else {
				// s[0..i-1] p[0..j] is matched, so '*' match one more time, 's[i-1]'
				dp[i][j] = dp[i][j-2] || ((s[i-1] == p[j-2] || p[j-2] == '.') && dp[i-1][j])
			}
		}
	}

	return dp[M-1][N-1]
}

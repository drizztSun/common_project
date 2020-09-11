package leetcodeH

/*
97. Interleaving String
Given s1, s2, and s3, find whether s3 is formed by the interleaving of s1 and s2.



Example 1:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true

Example 2:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false

Example 3:

Input: s1 = "", s2 = "", s3 = ""
Output: true


Constraints:

0 <= s1.length, s2.length <= 100
0 <= s3.length <= 200
s1, s2, and s3 consist of lower-case English letters.
*/

func isInterleave_dp(s1 string, s2 string, s3 string) bool {

	l1, l2, l3 := len(s1), len(s2), len(s3)

	if l1+l2 != l3 {
		return false
	}

	dp := make([][]bool, l1+1)
	for i := 0; i <= l1; i++ {
		dp[i] = make([]bool, l2+1)
		if i == 0 {
			dp[0][0] = true
			for j := 1; j <= l2; j++ {
				dp[0][j] = dp[0][j-1] && s2[j-1] == s3[j-1]
			}
			continue
		}
		dp[i][0] = dp[i-1][0] && s1[i-1] == s3[i-1]
	}

	for i := 1; i <= l1; i++ {
		for j := 1; j <= l2; j++ {
			dp[i][j] = dp[i-1][j] && s1[i-1] == s3[i-1+j] || dp[i][j-1] && s2[j-1] == s3[i+j-1]
		}
	}

	return dp[l1][l2]
}

func isInterleave_dfs(s1 string, s2 string, s3 string) bool {

	l1, l2, l3 := len(s1), len(s2), len(s3)

	if l1+l2 != l3 {
		return false
	}

	buf, seen := [][]int{[]int{0, 0}}, make([][]bool, l1+1)

	for i := 0; i < l1+1; i++ {
		seen[i] = make([]bool, l2+1)
	}

	for len(buf) > 0 {

		p := buf[len(buf)-1]
		buf = buf[:len(buf)-1]

		x, y := p[0], p[1]

		if x+y == l3 {
			return true
		}

		if x+1 <= l1 && s1[x] == s3[x+y] && seen[x+1][y] == false {
			seen[x+1][y] = true
			buf = append(buf, []int{x + 1, y})
		}

		if y+1 <= l2 && s2[y] == s3[x+y] && seen[x][y+1] == false {
			seen[x][y+1] = true
			buf = append(buf, []int{x, y + 1})
		}
	}

	return false
}

package leetcodeH

/*

903. Valid Permutations for DI Sequence

We are given S, a length n string of characters from the set {'D', 'I'}. (These letters stand for "decreasing" and "increasing".)

A valid permutation is a permutation P[0], P[1], ..., P[n] of integers {0, 1, ..., n}, such that for all i:

If S[i] == 'D', then P[i] > P[i+1], and;
If S[i] == 'I', then P[i] < P[i+1].
How many valid permutations are there?  Since the answer may be large, return your answer modulo 10^9 + 7.



Example 1:

Input: "DID"
Output: 5
Explanation:
The 5 valid permutations of (0, 1, 2, 3) are:
(1, 0, 3, 2)
(2, 0, 3, 1)
(2, 1, 3, 0)
(3, 0, 2, 1)
(3, 1, 2, 0)

*/

func p_search(i, j int, S string, dp [][]int) int {

	if !(j >= 0 && j <= i) {
		return 0
	}

	if dp[i][j] != 0 {
		return dp[i][j]
	}

	if i == 0 {
		return 1
	}

	mod := 1000000007

	if S[i-1] == 'D' {
		dp[i][j] = (p_search(i, j+1, S, dp) + p_search(i-1, j, S, dp)) % mod
	} else {
		dp[i][j] = (p_search(i, j-1, S, dp) + p_search(i-1, j-1, S, dp)) % mod
	}

	return dp[i][j]
}

func numPermsDISequence(S string) int {

	N := len(S)
	dp := make([][]int, N+1)
	for i := range dp {
		dp[i] = make([]int, N+1)
	}

	ans := 0
	for i := 0; i < N+1; i++ {
		ans += p_search(N, i, S, dp)
	}

	return ans % 1000000007
}

func Test_903_ValidPermutationsforDiSequence() {

	numPermsDISequence("DID")

	numPermsDISequence("IDDDIIDIIIIIIIIDIDID")
}

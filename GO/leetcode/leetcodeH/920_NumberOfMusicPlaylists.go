package leetcodeH

/*

920. Number of Music Playlists

Your music player contains N different songs and she wants to listen to L (not necessarily different) songs during your trip.
You create a playlist so that:

Every song is played at least once
A song can only be played again only if K other songs have been played
Return the number of possible playlists.  As the answer can be very large, return it modulo 10^9 + 7.



Example 1:

Input: N = 3, L = 3, K = 1
Output: 6
Explanation: There are 6 possible playlists. [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].
Example 2:

Input: N = 2, L = 3, K = 0
Output: 6
Explanation: There are 6 possible playlists. [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1], [2, 1, 2], [1, 2, 2]
Example 3:

Input: N = 2, L = 3, K = 1
Output: 2
Explanation: There are 2 possible playlists. [1, 2, 1], [2, 1, 2]
*/

func numMusicPlaylists(N int, L int, K int) int {

	dp := make([][]int, 2)
	for i := range dp {
		dp[i] = make([]int, L-N+1)
	}

	fk, g := 1, 0
	mod := 1000000007

	for i := 1; i <= K; i++ {
		fk = (fk * i) % mod
	}

	for i := K + 1; i <= N; i++ {
		fk = (fk * i) % mod

		g = 1 - g

		dp[g][0] = fk

		for t := i + 1; t <= L-(N-i); t++ {
			dp[g][t-i] = ((i-K)*dp[g][t-i-1]%mod + i*dp[1-g][t-i]%mod) % mod
		}
	}

	return dp[g][L-N]
}

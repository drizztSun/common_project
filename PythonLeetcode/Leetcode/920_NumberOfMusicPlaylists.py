"""
920. Number of Music Playlists

# Your music player contains N different songs and she wants to listen to L (not necessarily different) songs during your trip.  You create a playlist so that:

# Every song is played at least once
# A song can only be played again only if K other songs have been played
# Return the number of possible playlists.  As the answer can be very large, return it modulo 10^9 + 7.


# Example 1:

# Input: N = 3, L = 3, K = 1
# Output: 6
# Explanation: There are 6 possible playlists. [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].

# Example 2:

# Input: N = 2, L = 3, K = 0
# Output: 6
# Explanation: There are 6 possible playlists. [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1], [2, 1, 2], [1, 2, 2]

# Example 3:

# Input: N = 2, L = 3, K = 1
# Output: 2
# Explanation: There are 2 possible playlists. [1, 2, 1], [2, 1, 2]

"""
from functools import lru_cache


class NumMusicPlaylists:


    """
    """
    def doit_dp(self, N: int, L: int, K: int) -> int:

        dp = [[0 for _ in range(L + 1)] for _ in range(N + 1)]
        dp[0][0] = 1
        mod = 10 ** 9 + 7

        for i in range(1, N + 1):
            for j in range(1, L + 1):

                if i > K:
                    dp[i][j] += dp[i][j - 1] * (i - K)

                dp[i][j] += dp[i - 1][j - 1] * (N - i + 1)
                dp[i][j] %= mod

        return dp[N][L]

    def doit_dp(self, N: int, L: int, K: int) -> int:

        dp = [[0 for _ in range(N + 1)] for _ in range(L + 1)]
        dp[0][0] = 1
        mod = 10 ** 9 + 7

        for i in range(1, L + 1):
            for j in range(1, N + 1):
                dp[i][j] += dp[i-1][j] * max(j - K, 0)
                dp[i][j] += dp[i - 1][j - 1] * (N - j + 1)
                dp[i][j] %= mod

        return dp[L][N]

    '''
    DP
    DP[i,j] means: the number of playlists that among j songs which have played, there are i different songs.
    The problem is to find DP[N, L], which means when L songs have played, there are N different songs.
    DP[i,j] = DP[i,j-1]*(i-K) + DP[i-1, j-1]*(N-(i-1))

    The first part DP[i,j-1]*(i-K) means among i song that have played at j-1, we can choose i-K songs to play as the jth song.
    This is because A song can only be played again only if K other songs have been played.

    The second part DP[i-1, j-1]*(N-(i-1)) means we can choose one of N-(i-1) songs that is different from the i-1 songs played.

    Because DP[,j] only require DP[,j-1] to calculate, we reuse a list to store the previous j-1 results.
    Init condition, DP[0, 0] = 1. There is only one case that you have not played any song.
    Time: O(N*L)
    Space: O(N)
    '''
    def doit_dp(self, N: int, L: int, K: int):
        if N > L:
            return 0

        preDP = [0] * (N+1)
        preDP[0] = 1
        for j in range(1, L+1):
            curDP = [0] * (N+1)
            for i in range(j+1):
                if i > N:
                    break
                if i > K:
                    curDP[i] += preDP[i]*(i-K)
                if i > 0 and i -1 < N:
                    curDP[i] += preDP[i-1]*(N-(i-1))
            preDP = curDP
        return preDP[N] % (10**9 + 7)

    """
    Approach 1: Dynamic Programming
    Intuition

    Let dp[i][j] be the number of playlists of length i that have exactly j unique songs.
    We want dp[L][N], and it seems likely we can develop a recurrence for dp.

    Algorithm

    Consider dp[i][j]. Last song, we either played a song for the first time or we didn't.
    If we did, then we had dp[i-1][j-1] * (N-j) ways to choose it. If we didn't, then we repeated a previous song in dp[i-1][j] * max(j-K, 0) ways (j of them, except the last K ones played are banned.)

    Complexity Analysis

    Time Complexity: O(NL)O(NL).

    Space Complexity: O(NL)O(NL). (However, we can adapt this algorithm to only store the last row of dp to easily get O(L)O(L) space complexity.)
    """

    def doit(self, N: int, L: int, K: int):

        @lru_cache(None)
        def dp(i, j):  # To make i length list, with j different songs
            if i == 0:
                return j == 0  # if 0, 0, it is 1

            ans = dp(i-1, j-1) * (N-j+1)  # from dp(i-1, j-1)  and ith song, we pick one different from rest (N-j+1)
            ans += dp(i-1, j) * max(j - K, 0)
            # from dp(i-1, j-1), and pick a duplicate one, from j - K, ways (j of them, except the last K ones played are banned.)
            # j -k 's node makes no duplicate songs in last k songs.
            return ans % (10**9+7)

        return dp(L, N)

    def doit(self, N, L, K):
        # dp[S] at time P = <S, P> as discussed in article
        dp = [1] * (L-N+1)
        for p in range(2, N-K+1):
            for i in range(1, L-N+1):
                dp[i] += dp[i-1] * p

        # Multiply by N!
        ans = dp[-1]
        for k in range(2, N+1):
            ans *= k
        return ans % (10**9 + 7)

    """
    Approach 2: Partitions + Dynamic Programming
    (Note: This solution is extremely challenging, but is a natural consequence of trying to enumerate the playlists in this manner.)

    Intuition

    Since we are interested in playing every song at least once, let's keep track of what times x = (x_1, x_2,...) a song was played that wasn't yet played before.
    For example, if we have 5 songs abcde, and we play abacabdcbaeacbd, then x = (1, 2, 4, 7, 11)x=(1,2,4,7,11) as these are the first occurrences of a unique song.
    For convenience, we'll also put x_{N+1} = L+1. Our strategy is to count the number of playlists #x that satisfy this xx,
    so that our final answer will be ∑#x.

    Doing a direct count,
    so that it can be shown through algebraic manipulation that: \langle S, P \rangle = P \langle S-1, P-1 \rangle + \langle S, P-1 \rangle⟨S,P⟩=P⟨S−1,P−1⟩+⟨S,P−1⟩
    With this recurrence, we can perform dynamic programming similar to Approach 1. The final answer is N! \langle L-N, N-K+1 \rangleN!⟨L−N,N−K+1⟩.

    """

    def doit2(self, N, L, K):
        # dp[S] at time P = <S, P> as discussed in article
        dp = [1] * (L-N+1)
        for p in range(2, N-K+1):
            for i in range(1, L-N+1):
                dp[i] += dp[i-1] * p

        # Multiply by N!
        ans = dp[-1]
        for k in range(2, N+1):
            ans *= k
        return ans % (10**9 + 7)

    """
    Approach 3: Generating Functions
    (Note: This solution is extremely challenging and not recommended for interviews, but is included here for completeness.)
    Analysis
    Following the terminology of Approach 2, we would like to compute \langle S, P \rangle⟨S,P⟩ quickly. We can use generating functions.
    For a fixed PP, consider the function:
    so that we now have everything we need to compute the answer quickly.
    """

    def doit(self, N, L, K):
        MOD = 10**9 + 7

        def inv(x):
            return pow(x, MOD-2, MOD)

        C = 1
        for x in range(1, N-K):
            C *= -x
            C %= MOD
        C = inv(C)

        ans = 0
        for k in range(1, N-K+1):
            ans += pow(k, L-K-1, MOD) * C
            C = C * (k - (N-K)) % MOD * inv(k) % MOD

        for k in range(1, N+1):
            ans = ans * k % MOD
        return ans

    def numMusicPlaylists(self, N: int, L: int, K: int) -> int:
        import math
        s = 0
        c = 0
        r = 0
        x = math.factorial(N)

        while (True):
            c = x * ((N - r - K) ** (L - K)) * (-1) ** (r) // (math.factorial(N - r - K) * math.factorial(r))
            if (c != 0):
                s = (s + c) % (10 ** 9 + 7)
                r += 1
            else:
                return s


if __name__ == '__main__':

    NumMusicPlaylists().doit(N=3, L=3, K=1)

    NumMusicPlaylists().doit(N=2, L=3, K=0)

    NumMusicPlaylists().doit(N=2, L=3, K=1)

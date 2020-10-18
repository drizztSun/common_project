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

\#_x = N * (N-1) * \cdots * (N-K+1) 1^{x_{K+1} - x_K - 1} * (N-K+2) 2^{x_{K+2} - x_{K+1}} * \cdots#
x
​	
 =N∗(N−1)∗⋯∗(N−K+1)1 
x 
K+1
​	
 −x 
K
​	
 −1
 ∗(N−K+2)2 
x
K+2
​	
 −x 
K+1
​	
 
 ∗⋯

\Rightarrow \#_x = N! \prod_{j=1}^{N-K+1} j^{x_{K+j} - x_{K+j-1} - 1}⇒# 
x
​	
 =N!∏ 
j=1
N−K+1
​	
 j 
x 
K+j
​	
 −x 
K+j−1
​	
 −1
 

Now, let \delta_i = x_{K+i} - x_{K+i-1} - 1δ 
i
​	
 =x 
K+i
​	
 −x 
K+i−1
​	
 −1, so that \sum \delta_i = L-N∑δ 
i
​	
 =L−N. To recap, the final answer will be (for S = L-N, P = N-K+1S=L−N,P=N−K+1):

N! \Big(\sum\limits_{\delta : \sum\limits_{0 \leq i \leq P} \delta_i = S} \prod\limits_{j=1}^P j^{\delta_j} \Big)N!( 
δ: 
0≤i≤P
∑
​	
 δ 
i
​	
 =S
∑
​	
  
j=1
∏
P
​	
 j 
δ 
j
​	
 
 )

For convenience, let's denote the stuff in the large brackets as \langle S, P\rangle⟨S,P⟩.

Algorithm

We can develop a recurrence for \langle S, P\rangle⟨S,P⟩ mathematically, by factoring out the P^{\delta_P}P 
δ 
P
​	
 
  term.

\langle S, P\rangle = \sum_{\delta_P = 0}^S P^{\delta_P} \sum_{\sum\limits_{0\leq i < P} \delta_i = S - \delta_P} \prod\limits_{j=1}^{P-1} j^{\delta_j}⟨S,P⟩=∑ 
δ 
P
​	
 =0
S
​	
 P 
δ 
P
​	
 
 ∑ 
0≤i<P
∑
​	
 δ 
i
​	
 =S−δ 
P
​	
 
​	
  
j=1
∏
P−1
​	
 j 
δ 
j
​	
 
 

\Rightarrow \langle S, P\rangle = \sum_{\delta_P = 0}^S P^{\delta_P} \langle S - \delta_P, P-1\rangle⇒⟨S,P⟩=∑ 
δ 
P
​	
 =0
S
​	
 P 
δ 
P
​	
 
 ⟨S−δ 
P
​	
 ,P−1⟩

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

f(x) = (1^0x^0 + 1^1x^1 + 1^2x^2 + 1^3x^3 + \cdots) * (2^0x^0 + 2^1x^1 + 2^2x^2 + 2^3x^3 + \cdots)f(x)=(1 
0
 x 
0
 +1 
1
 x 
1
 +1 
2
 x
2
 +1 
3
 x 
3
 +⋯)∗(2 
0
 x 
0
 +2 
1
 x 
1
 +2 
2
 x 
2
 +2 
3
 x 
3
 +⋯) \cdots * (P^0x^0 + P^1x^1 + P^2x^2 + P^3x^3 + \cdots)⋯∗(P 
0
 x 
0
 +P 
1
 x 
1
 +P 
2
 x 
2
 +P 
3
 x 
3
 +⋯)

\Leftrightarrow f(x) = \prod_{k=1}^{P} (\sum_{j \geq 0} k^j x^j) = \prod_{k=1}^P \frac{1}{1-kx}⇔f(x)=∏ 
k=1
P
​	
 (∑ 
j≥0
​	
 k 
j
 x 
j
 )=∏ 
k=1
P
​	
  
1−kx
1
​	
 

The coefficient of x^Sx 
S
  in ff (denoted [x^S]f[x 
S
 ]f) is the desired \langle S, P \rangle⟨S,P⟩.

By the Chinese Remainder theorem on polynomials, this product can be written as a partial fraction decomposition:

\prod_{k=1}^P \frac{1}{1-kx} = \sum_{k=1}^P \frac{A_k}{1-kx}∏ 
k=1
P
​	
  
1−kx
1
​	
 =∑ 
k=1
P
​	
  
1−kx
A 
k
​	
 
​	
 

for some rational coefficients A_kA 
k
​	
 . We can solve for these coefficients by clearing denominators and setting x = 1/mx=1/m for 1 \leq m \leq P1≤m≤P. Then for a given mm, all the terms except the mm-th vanish, and:

A_m = \frac{1}{\prod\limits_{\substack{1 \leq j \leq P\\j \neq m}} 1 - j/m} = \prod_{j \neq m} \frac{m}{m-j}

Since a geometric series has sum \sum_{j \geq 0} (kx)^j = \frac{1}{1-kx}∑ 
j≥0
​	
 (kx) 
j
 = 
1−kx
1
​	
 , altogether it implies:

[x^S]f = \sum_{k=1}^P A_k * k^S[x 
S
 ]f=∑ 
k=1
P
​	
 A 
k
​	
 ∗k 
S
 

so that the final answer is

\text{answer} = N! \sum_{k=1}^{N-K} k^{L-N} \prod_{\substack{1 \leq j \leq N-K\\j \neq k}} \frac{k}{k-j}

\Rightarrow \text{answer} = N! \sum_k k^{L-K-1} \prod_{j \neq k} \frac{1}{k-j}⇒answer=N!∑ 
k
​	
 k 
L−K−1
 ∏ 
j 

​	
 =k
​	
  
k−j
1
​	
 

We only need a quick way to compute C_k = \prod\limits_{j \neq k} \frac{1}{k-j}C 
k
​	
 = 
j 

​	
 =k
∏
​	
  
k−j
1
​	
 . Indeed,

C_{k+1} = C_k * \frac{k - (N-K)}{k}C 
k+1
​	
 =C 
k
​	
 ∗ 
k
k−(N−K)
​	
 

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


if __name__ == '__main__':

    NumMusicPlaylists().doit(N=3, L=3, K=1)

    NumMusicPlaylists().doit(N=2, L=3, K=0)

    NumMusicPlaylists().doit(N=2, L=3, K=1)

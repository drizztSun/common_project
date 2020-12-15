"""
1621. Number of Sets of K Non-Overlapping Line Segments

 Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x = i, find the number of ways we can draw exactly k non-overlapping line segments
 such that each segment covers two or more points. The endpoints of each segment must have integral coordinates.

 The k line segments do not have to cover all n points, and they are allowed to share endpoints.

 Return the number of ways we can draw k non-overlapping line segments. Since this number can be huge, return it modulo 109 + 7.



 Example 1:


 Input: n = 4, k = 2
 Output: 5
 Explanation:
 The two line segments are shown in red and blue.
 The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)}, {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.
 Example 2:

 Input: n = 3, k = 1
 Output: 3
 Explanation: The 3 ways are {(0,1)}, {(0,2)}, {(1,2)}.
 Example 3:

 Input: n = 30, k = 7
 Output: 796297179
 Explanation: The total number of possible ways to draw 7 line segments is 3796297200. Taking this number modulo 109 + 7 gives us 796297179.
 Example 4:

 Input: n = 5, k = 3
 Output: 7
 Example 5:

 Input: n = 3, k = 2
 Output: 1


 Constraints:

 2 <= n <= 1000
 1 <= k <= n-1

https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-1621-number-of-sets-of-k-non-overlapping-line-segments/

"""


class NumberofSetsOfKNonOverlappingLineSegements:


    def doit_math(self, n: int, k: int) -> int:
        import math
        return math.comb(n + k - 1, k * 2) % (10**9 + 7)

    def doit_dp_dfs_1_TLE(self, N, K):

        from functools import lru_cache
        mod = 10**9 + 7

        @lru_cache(None)
        def dfs(n, k):

            if k >= n: return 0
            if k == 1: return n * (n-1) // 2
            if k == n - 1: return 1

            return sum((i-1) * dfs(n-i+1, k - 1) for i in range(2, n-k+2)) % mod

        return dfs(N, K)


    """
    DP2: dp(n, k) := # of k segments using n points
    Base case:
        dp(n, 0) = 1
        
    Transition:
    # case 1: k-1 segments in 1--i, put kth one segemnt from i--n, if we use n as most right pointts
    # case 2: put k segment from 1 --> n-1, left n points useless. so recursive case 2, it means we left some points in right side free.
    
    dp(n, k) = sum(dp(i, k-1)) + dp(n-1, k),  1 <= i < n - k
    Ans = dp(N, K)
    
    Can use bottom up + prefix sum to reduce the time complexity from O(n**2 * k) + O(n, k)
    
    Time complexity: O(nk)
    
    Space complexity: O(nk) 
    
    """
    def doit_dp_2(self, N, K):

        kMod = 1**9 + 7
        # dp(n, k) put k segement in n points
        dp = [[0] * (K+1) for _ in range(N+1)]

        # put 0 segments into i points always be 0
        for i in range(N+1):
            dp[i][0] = 1

        # put k more points
        for j in range(1, K+1):

            s = 0
            # sum(dp(i, k - 1))
            # put j
            for i in range(1, N+1):
                # put j segments in i-1, and sum(dp(i, j-1)), with last one on right mode, i.
                dp[i][j] = (dp[i-1][j] + s) % kMod
                s += dp[i][j-1]

        return dp[N][K] % kMod

    """
    
    """
    def doit_dp_3(self, n: int, k: int) -> int:
        from functools import lru_cache
        kMod = 10 ** 9 + 7

        @lru_cache(None)
        def dp(n: int, k: int, e: int) -> int:
            if k == 0: return 1
            if k > n: return 0
            return (dp(n - 1, k, e) + dp(n + e - 1, k - e, 1 - e)) % kMod

        return dp(n, k, 0)

    """
    math deduction
    DP4: dp(n, k) :- # of k segments using n points
    
    Base case:
        1) dp(n, 1) = n * (n-1) / 2
        2) dp(n, k) = 1 if k == n-1
        3) dp(n, k) = 0 if k >= n
        
    Transition:
    
    dp(n, k) = 2 * dp(n-1, k) - dp(n-2, k) + dp(n-1, k-1)
    
    n/k   1  |  2  | 3 | 4 | 5
    1     1
    2     3  |  1
    3     6  |  5  | 1
    4     10 |  15 | 7  | 1
    5     15 |  35 | 28 | 9 | 1
    
    Ans = dp(N, K)
    
    Time complexity: O(nk)
    Space complexity: O(nk) 
    
    """
    def doit_dp_4(self, n: int, k: int) -> int:
        from functools import lru_cache

        @lru_cache(None)
        def dp(n: int, k: int) -> int:

            if k >= n: return 0
            if k == 1: return n * (n - 1) // 2
            if k == n - 1: return 1

            return 2 * dp(n - 1, k) - dp(n - 2, k) + dp(n - 1, k - 1)

        return dp(n, k) % (10 ** 9 + 7)





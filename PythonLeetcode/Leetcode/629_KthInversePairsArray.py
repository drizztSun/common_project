

# 629. K Inverse Pairs Array

# Given two integers n and k, find how many different arrays consist of numbers from 1 to n 
# such that there are exactly k inverse pairs.

# We define an inverse pair as following: For ith and jth element in the array,
# if i < j and a[i] > a[j] then it's an inverse pair; Otherwise, it's not.

# Since the answer may be very large, the answer should be modulo 109 + 7.

# Example 1:
# Input: n = 3, k = 0
# Output: 1
# Explanation: 
# Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pair.

# Example 2:
# Input: n = 3, k = 1
# Output: 2
# Explanation: 
# The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.

# Note:
# The integer n is in the range [1, 1000] and k is in the range [0, 1000].

class KthInversePairs(object):

    # Let's try for a top-down dp. Suppose we know dp[n][k], the number of permutations of (1...n) with k inverse pairs.

    # Looking at a potential recursion for dp[n+1][k], depending on where we put the element (n+1) in our permutation,
    # we may add 0, 1, 2, ...., n new inverse pairs.
    # For example, if we have some permutation of 1 ... 4, then:

    # 5 x x x x creates 4 new inverse pairs
    # x 5 x x x creates 3 new inverse pairs
    # ..............
    # x x x x 5 creates 0 new inverse pairs
    # where in the above I'm representing any permutation of 1...4 with x's.
    # Thus, dp[n+1][k] = sum_{x=0..n} dp[n][k-x].

    # This dp has NK states with K/2 work, which isn't fast enough. We need to optimize further.

    # Let ds[n][k] = sum_{x=0..k-1} dp[n][x].
    # Then dp[n+1][k] = ds[n][k+1] - ds[n][k-n], and the left hand side is ds[n+1][k+1] - ds[n+1][k].
    # Thus, we can perform all calculations in terms of ds.

    # Finally, to save space, we will only store the two most recent rows of ds, using ds and new.

    # In the code, we refer to -ds[n][k-n+1] instead of -ds[n][k-n] because the n being considered is actually n+1.
    # For example, when n=2, we are appending information about ds[2][k] to new,
    # so our formula of dp[n+1][k] = ds[n][k+1] - ds[n][k-n] is dp[2][k] = ds[1][k+1] - ds[1][k-1].

    # Why there is a 10**9 + 7 see this https://www.geeksforgeeks.org/modulo-1097-1000000007/

    def doit(self, N, K):
        """
        :type N: int
        :type K: int
        :rtype: int
        """
        MOD = 10**9 + 7 # 1,000,000,007
        ds = [0] + [1]*(K + 1) # ds[k+1] is sum of ds[s < k] s = {0, 1, ... k-1} and when k ==0, the there is always '1'

        for n in range(2, N+1):
            new = [0]
            for k in range(K+1):
                v = ds[k+1]
                v -= ds[k-n] if k >= n else 0
                new.append((new[-1] + v) % MOD)

            ds = new

        return (ds[K+1] - ds[K]) % MOD

    # f(n, k) = sum(f(n - 1, i)), where max(k - n + 1, 0) <= i <= k
    # f(0, k) = 0
    # f(n, 0) = 1

    def doit1(self, N, K):
        """
        :type N: int
        :type K: int
        :rtype: int
        """
        dp = [1] + [0] * K
        for i in range(2, N + 1):

            for j in range(1, K+1):
                dp[j] += dp[j-1]

            for j in range(K, 0, -1):
                dp[j] -= j - i >= 0 and dp[j - i]

        return dp[K] % (10**9 + 7)


if __name__ == "__main__":

    res = KthInversePairs().doit(3, 0)

    res = KthInversePairs().doit(3, 1)

    pass
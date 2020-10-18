"""
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
"""


class KInversePairs(object):

    """
    Approach 3: Dynamic Programming
    Algorithm

    As we've seen in the discussion above, the solution for if we know the solutions for count(n-1,0)count(n−1,0), count(n-1, 1)count(n−1,1)..., count(n-1,k)count(n−1,k), we can directly obtain the solution for count(n,k)count(n,k) as count(n,k)=\sum_{0}^{min(k,n-1)} count(n-1, k-i)count(n,k)=∑
    0
    min(k,n−1)
    ​
     count(n−1,k−i).

    From this, we deduce that we can make use of Dynamic Programming to solve the given problem. To solve the given problem, we make use of a 2-D dpdp, where dp[i][j]dp[i][j] is used to store the number of arrangements with ii elements and exactly jj inverse pairs. Based on the discussions above, the dpdp updation equations become:

    If n=0n=0, no inverse pairs exist. Thus, dp[0][k]=0dp[0][k]=0.

    If k=0k=0, only one arrangement is possible, which is all numbers sorted in ascending order. Thus, dp[n][0]=1dp[n][0]=1.

    Otherwise, dp[i,j] = \sum_{p=0}^{min(j,i-1)} count(i-1, j-p)dp[i,j]=∑
    p=0
    min(j,i−1)
    ​
     count(i−1,j−p).

    Again, the limit \text{min}(j, i-1)min(j,i−1) is used to account for the cases where the number of inverse pairs needed becomes negative(p>jp>j) or the case where the new inverse pairs needed by adding the n^{th}n
    th
      number is more than n-1n−1 which isn't possible, since the new number can be added at (n-1)^{th}(n−1)
    th
      position at most from the right.

    We start filling the dpdp in a row-wise order starting from the first row. At the end, the value of dp[n][k]dp[n][k] gives the required result.

    The following animation shows how the dpdp is filled for n=4 and k=5:

    """
    def doit_dp(self, n, k):
        M = 10 **9 + 7
        dp = [[0 for _ in range(n+1)] for _ in range(k+1)]

        for i in range(k+1):

            for j in range(1, n+1):

                if i == 0:
                    dp[i][j] = 1
                else:
                    for z in range(min(i, j-1)+1):
                        dp[i][j] = (dp[i][j] + dp[i-1][j-z]) % M

        return dp[k][n]

    def doit_dp(self, n: int, k: int) -> int:
        M = 10 ** 9 + 7
        dp = [[0 for _ in range(k + 1)] for _ in range(n + 1)]

        for i in range(1, n + 1):

            for j in range(k + 1):

                if j == 0:
                    dp[i][j] = 1
                else:
                    for z in range(min(j, i - 1) + 1):
                        dp[i][j] = (dp[i][j] + dp[i - 1][j - z]) % M

        return dp[n][k]

    """
    Approach 4: Dynamic Programming with Cumulative Sum
    Algorithm
    
    From the last approach, we've observed that we need to traverse back to some limit in the previous row of the dpdp array to fill in the current dpdp entry. Instead of doing this traversal to find the sum of the required elements, we can ease the process if we fill the cumulative sum upto the current element in a row in any dpdp entry, instead of the actual value.
    
    Thus, now, dp[i][j]=count(i,j)+\sum_{k=0}^{j-1} dp[i][k]dp[i][j]=count(i,j)+∑ 
    k=0
    j−1
    ​	
     dp[i][k]. Here, count(i,j)count(i,j) refers to the number of arrangements with ii elements and exactly jj inverse pairs. Thus, each entry contains the sum of all the previous elements in the same row along with its own result.
    
    Now, we need to determine the value of count(i,j)count(i,j) to be added to the sum of previous elements in a row, in order to update the dp[i][j]dp[i][j] entry. But, we need not traverse back in the previous row , since it contains entries representing the cumulative sums now. Thus, to obtain the sum of elements from dp[i-1][j-i+1]dp[i−1][j−i+1] to dp[i-1][j]dp[i−1][j](including both), we can directly use dp[i-1][j] - dp[i-1][j-i]dp[i−1][j]−dp[i−1][j−i].
    
    Now, to reflect the condition \text{min}(j, i-1)min(j,i−1) used in the previous approaches, we can note that, we need to take the sum of only ii elements in the previous row, if ii elements exist till we reach the end of the array while traversing backwards. Otherwise, we simply take the sum of all the elements.
    
    Only ii elements are considered because for generating jj new inverse pairs, by adding ii as the new number at the j^{th}j 
    th
      position, jj could reach only upto i-1i−1, as discussed in the last approaches as well. Thus, we need to consider the sum of elements from dp[i-1][j-(i-1)]dp[i−1][j−(i−1)] to dp[i-1][j]dp[i−1][j](including both) using dp[i-1][j] - dp[i-1][j-i]dp[i−1][j]−dp[i−1][j−i] if j-i ≥ 0.
    
    Otherwise, we add all the elements of the previous row upto the current column jj being considered. In other words, we can use dp[i-1][j]dp[i−1][j] directly as the required sum.
    
    At the end, while returning the result, we need to return dp[n][k]-dp[n][k-1]dp[n][k]−dp[n][k−1] to obtain the required result from the cumulative sums.
    
    The following animation illustrates the process of filling the dpdp array.
    """
    def doit_dp_best(self, n: int, k: int) -> int:
        M = 10 ** 9 + 7
        dp = [[0 for _ in range(k + 1)] for _ in range(n + 1)]

        for i in range(1, n + 1):

            for j in range(k + 1):

                if j == 0:
                    dp[i][j] = 1
                else:
                    val = dp[i - 1][j] + M - (dp[i - 1][j - i] if j - i >= 0 else 0) % M
                    dp[i][j] = (dp[i][j - 1] + val) % M

        return (dp[n][k] + M - (dp[n][k - 1] if k > 0 else 0)) % M

    """
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
    """
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

    res = KInversePairs().doit(3, 0)

    res = KInversePairs().doit(3, 1)
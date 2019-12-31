# 813. Largest Sum of Averages

# We partition a row of numbers A into at most K adjacent (non-empty) groups, then our score is the sum of the average of each group. 
# What is the largest score we can achieve?

# Note that our partition must use every number in A, and that scores are not necessarily integers.

# Example:
# Input: 
# A = [9,1,2,3,9]
# K = 3
# Output: 20
# Explanation: 
# The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
# We could have also partitioned A into [9, 1], [2], [3, 9], for example.
# That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
 

# Note:

# 1 <= A.length <= 100.
# 1 <= A[i] <= 10000.
# 1 <= K <= A.length.
# Answers within 10^-6 of the correct answer will be accepted as correct.

class LargestSumOfAverages:
    
    def doit(self, A, K):    
        P = [0]
        for c in A:
            P.append(P[-1] + c)
            
        def average(i, j):
            return (P[j] - P[i]) / float(j - i)
        
        N = len(A)
        dp = [average(i, N) for i in range(N)]
        
        for _ in range(K-1):
            for i in range(N):
                for j in range(i+1, N):
                    dp[i] = max(dp[i], average(i, j) + dp[j])
                    
        return dp[0]


    def doit1(self, A, K):
        n = len(A)
        P = [0] * (n + 1)
        for i in range(n):
            P[i+1] = P[i] + A[i]

        memo = {}

        def dfs(s, k):
            if k == 1:
                return (P[n] - P[s]) / (n - s)

            if (s, k) in memo:
                return memo[(s, k)]

            ans = float('-inf')
            for i in range(s+1, n+2-k):
                tmp = (P[i] - P[s]) / (i - s) + dfs(i, k-1)
                if tmp > ans:
                    ans = tmp
            
            memo[(s, k)] = ans
            return ans

        return dfs(0, K)


if __name__ == '__main__':

    res = LargestSumOfAverages().doit1(A = [9,1,2,3,9], K = 3)

    pass
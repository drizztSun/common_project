"""
# 664. Strange Printer


# There is a strange printer with the following two special requirements:

# The printer can only print a sequence of the same character each time.
# At each turn, the printer can print new characters starting from and ending at any places,
# and will cover the original existing characters.
# Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.

# Example 1:
# Input: "aaabbb"
# Output: 2
# Explanation: Print "aaa" first and then print "bbb".

# Example 2:
# Input: "aba"
# Output: 2
# Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.

# Hint: Length of the given string will not exceed 100.
"""


class StrangePrinter:

    """
    # Let dp(i, j) be the number of turns needed to print S[i:j+1].

    # Note that whichever turn creates the final print of S[i], might as well be the first turn,
    # and also there might as well only be one print, since any later prints on interval [i, k] could just be on [i+1, k].

    # So suppose our first print was on [i, k]. We only need to consider prints where S[i] == S[k],
    # because we could instead take our first turn by printing up to the last printed index where S[k] == S[i] to get the same result.

    # Then, when trying to complete the printing of interval [i, k] (with S[i] == S[k]),
    # the job will take the same number of turns as painting [i, k-1].
    # This is because it is always at least as good to print [i, k] first in one turn rather than separately.

    # Also, we would need to complete [k+1, j].
    # So in total, our candidate answer is dp(i, k-1) + dp(k+1, j).

    # Of course, when k == i, our candidate is 1 + dp(i+1, j): we paint S[i] in one turn, then paint the rest in dp(i+1, j) turns.

    """
    # <DP>
    def doit_dp_2(self, s):
        """
        :type s: str
        :rtype: int
        """ 
        memo = {}

        def dp(i, j):
            if i > j:
                return 0

            if (i, j) in memo:
                return memo[(i, j)]

            ans = dp(i+1, j) + 1
            
            for k in range(i+1, j+1):
                
                if s[i] == s[k]:
                    #print(i, k) == print(i, l-1)
                    ans = min(ans, dp(i, k-1) + dp(k+1, j))

            dp[(i, j)] = ans
        
            return ans

        return dp(0, len(s) - 1)

    """
    Approach #1: Dynamic Programming [Accepted]
    Intuition
    
    It is natural to consider letting dp(i, j) be the answer for printing S[i], S[i+1], ..., S[j], but proceeding from here is difficult. We need the following sequence of deductions:
    
    Whatever turn creates the final print of S[i] might as well be the first turn, and also there might as well only be one print, since any later prints on interval [i, k] could just be on [i+1, k].
    
    Say the first print is on [i, k]. We can assume S[i] == S[k], because if it wasn't, we could print up to the last occurrence of S[i] in [i, k] for the same result.
    
    When correctly printing everything in [i, k] (with S[i] == S[k]), it will take the same amount of steps as correctly printing everything in [i, k-1]. This is because if S[i] and S[k] get completed in separate steps, we might as well print them first in one step instead.
    
    Algorithm
    
    With the above deductions, the algorithm is straightforward.
    
    To compute a recursion for dp(i, j), for every i <= k <= j with S[i] == S[k], we have some candidate answer dp(i, k-1) + dp(k+1, j), and we take the minimum of these candidates. Of course, when k = i, the candidate is just 1 + dp(i+1, j).
    
    To avoid repeating work, we memoize our intermediate answers dp(i, j).
    
    Complexity Analysis

    Time Complexity: O(N^3) where NN is the length of s. For each of O(N^2) possible states representing a subarray of s, we perform O(N)O(N) work iterating through k.
    
    Space Complexity: O(N^2), the size of our memo.
    """
    def doit_dp_1(self, s):

        def search(i, j, memo):

            if i > j:
                return 0

            if (i, j) in memo:
                return memo[(i, j)]

            ans = search(i + 1, j, memo) + 1

            for z in range(i + 1, j + 1):

                if s[i] == s[z]:
                    ans = min(ans, search(i, z - 1, memo) + search(z + 1, j, memo))

            memo[(i, j)] = ans

            return ans

        return search(0, len(s) - 1, {})

    def doit_dp(self, s):
        n = len(s)
        dp = [[0 for _ in range(n)] for _ in range(n)]

        for i in range(n):
            for j in reversed(range(i+1)):

                if j == i:
                    dp[j][i] = 1
                else:
                    ans = 1 + dp[j+1][i]
                    for k in range(j+1, i+1):
                        if s[k] == s[j]:
                            ans = min(ans, dp[j][k-1] + (dp[k+1][i] if k != i else 0))
                    dp[j][i] = ans
        return dp[0][n-1]


if __name__ == "__main__":

    res = StrangePrinter().doit_dp("aba")

    res = StrangePrinter().doit_dp("aaabbb")



    pass
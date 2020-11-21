"""
375. Guess Number Higher or Lower II

We are playing the Guessing Game. The game will work as follows:

I pick a number between 1 and n.
You guess a number.
If you guess the right number, you win the game.
If you guess the wrong number, then I will tell you whether the number I picked is higher or lower, and you will continue guessing.
Every time you guess a wrong number x, you will pay x dollars. If you run out of money, you lose the game.
Given a particular n,
return the minimum amount of money you need to guarantee a win regardless of what number I pick.



Example 1:


Input: n = 10
Output: 16
Explanation: The winning strategy is as follows:
- The range is [1,10]. Guess 7.
    - If this is my number, your total is $0. Otherwise, you pay $7.
    - If my number is higher, the range is [8,10]. Guess 9.
        - If this is my number, your total is $7. Otherwise, you pay $9.
        - If my number is higher, it must be 10. Guess 10. Your total is $7 + $9 = $16.
        - If my number is lower, it must be 8. Guess 8. Your total is $7 + $9 = $16.
    - If my number is lower, the range is [1,6]. Guess 3.
        - If this is my number, your total is $7. Otherwise, you pay $3.
        - If my number is higher, the range is [4,6]. Guess 5.
            - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay $5.
            - If my number is higher, it must be 6. Guess 6. Your total is $7 + $3 + $5 = $15.
            - If my number is lower, it must be 4. Guess 4. Your total is $7 + $3 + $5 = $15.
        - If my number is lower, the range is [1,2]. Guess 1.
            - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay $1.
            - If my number is higher, it must be 2. Guess 2. Your total is $7 + $3 + $1 = $11.
The worst case in all these scenarios is that you pay $16. Hence, you only need $16 to guarantee a win.
Example 2:

Input: n = 1
Output: 0
Explanation: There is only one possible number, so you can guess 1 and not have to pay anything.
Example 3:

Input: n = 2
Output: 1
Explanation: There are two possible numbers, 1 and 2.
- Guess 1.
    - If this is my number, your total is $0. Otherwise, you pay $1.
    - If my number is higher, it must be 2. Guess 2. Your total is $1.
The worst case is that you pay $1.

"""


class GuessNumberHigherOrLower:

    """
    Approach #3 Using DP [Accepted]
    Algorithm

    The problem of finding the minimum cost of reaching the destination number choosing ii as a pivot can be divided into the subproblem of finding the maximum out of the minimum costs of its left and right segments as explained above. For each segment, we can continue the process leading to smaller and smaller subproblems. This leads us to the conclusion that we can use DP for this problem.

    We need to use a dpdp matrix, where dp(i, j)dp(i,j) refers to the minimum cost of finding the worst number given only the numbers in the range (i, j)(i,j). Now, we need to know how to fill in the entries of this dpdp. If we are given only a single number kk, no matter what the number is the cost of finding that number is always 0 since we always hit the number directly without any wrong guess. Thus, firstly, we fill in all the entries of the dpdp which correspond to segments of length 1 i.e. all entries dp(k, k)dp(k,k) are initialized to 0. Then, in order to find the entries for segments of length 2, we need all the entries for segments of length 1. Thus, in general, to fill in the entries corresponding to segments of length lenlen, we need all the entries of length len-1len−1 and below to be already filled. Thus, we need to fill the entries in the order of their segment lengths. Thus, we fill the entries of dpdp diagonally.

    Now, what criteria do we need to fill up the dpdp matrix? For any entry dp(i, j)dp(i,j), given the current segment length of interest is lenlen i.e. if len=j-i+1len=j−i+1, we assume as if we are available only with the numbers in the range (i, j)(i,j). To fill in its current entry, we follow the same process as Approach 1, choosing every number as the pivot and finding the minimum cost as:

    \mathrm{cost}(i, j)=\mathrm{pivot} + \max\big(\mathrm{cost}(i,\mathrm{pivot}-1), \mathrm{cost}(\mathrm{pivot}+1,j)\big)cost(i,j)=pivot+max(cost(i,pivot−1),cost(pivot+1,j))

    But, we have an advantage in terms of calculating the cost here, since we already know the costs for the segments of length smaller than lenlen from dpdp. Thus, the dp equation becomes:

    \mathrm{dp}(i, j) = \min_{\mathrm{pivot} \in (i, j)} \big[ \mathrm{pivot} + \max \big( \mathrm{dp}(i,\mathrm{pivot}-1) , \mathrm{dp}(\mathrm{pivot}+1,j) \big) \big]dp(i,j)=min
    pivot∈(i,j)
    ​
     [pivot+max(dp(i,pivot−1),dp(pivot+1,j))]

    where \min_{\mathrm{pivot} \in (i, j)}min
    pivot∈(i,j)
    ​
      indicates the minimum obtained by considering every number in the range (i, j)(i,j) as the pivot.

    The following animation will make the process more clear for n=5:

    """
    def doit_dp(self, n: int) -> int:

        dp = [[0 for _ in range(n+1)] for _ in range(n+1)]

        for L in range(n+1):
            for i in range(n + 1 - L):
                j = i + L
                if i == j:
                    dp[i][j] =
                else:
                    dp[i][j] = float('inf')
                    for k in range(i, j):
                        dp[i][j] = min(dp[i][j], k + max(dp[i][k-1], dp[k+1][j]))

        return dp[1][n]

    def doit_dp_1(self, n):
        """
        :type n: int
        :rtype: int
        """
        D = [[0] * (n + 1) for _ in range(n + 1)]

        for i in range(n, 0, -1):
            for j in range(i + 1, n + 1):
                D[i][j] = min([x + max(D[i][x - 1], D[x + 1][j]) for x in range(i, j)])

        return D[1][n]


if __name__ == '__main__':

    GuessNumberHigherOrLower().doit_dp(10)

    GuessNumberHigherOrLower().doit_dp(1)

    GuessNumberHigherOrLower().doit_dp(2)
# 837. New 21 Game

# Alice plays the following game, loosely based on the card game "21".

# Alice starts with 0 points, and draws numbers while she has less than K points.
# During each draw, she gains an integer number of points randomly from the range [1, W], where W is an integer.
# Each draw is independent and the outcomes have equal probabilities.

# Alice stops drawing numbers when she gets K or more points.
#
# *** What is the probability that she has N or less points?

# Example 1:

# Input: N = 10, K = 1, W = 10
# Output: 1.00000
# Explanation:  Alice gets a single card, then stops.

# Example 2:

# Input: N = 6, K = 1, W = 10
# Output: 0.60000
# Explanation:  Alice gets a single card, then stops.
# In 6 out of W = 10 possibilities, she is at or below N = 6 points.

# Example 3:

# Input: N = 21, K = 17, W = 10
# Output: 0.73278
# Note:

# 0 <= K <= N <= 10000
# 1 <= W <= 10000
# Answers will be accepted as correct if they are within 10^-5 of the correct answer.
# The judging time limit has been reduced for this question.


"""
Approach #1: Dynamic Programming [Accepted]
Intuition

It is clear that the probability that Alice wins the game is only related to how many points x she starts the next draw with,
so we can try to formulate an answer in terms of x.

Algorithm

Let f(x) be the answer when we already have x points. When she has between K and N points, then she stops drawing and wins.
If she has more than N points, then she loses.

The key recursion is f(x) = (1/W) * (f(x+1) + f(x+2) + ... + f(x+W))
This is because there is a probability of (1/W) to draw each card from 1 to W.

With this recursion, we could do a naive dynamic programming solution as follows:

#psuedocode
dp[k] = 1.0 when K <= k <= N, else 0.0
# dp[x] = the answer when Alice has x points
for k from K-1 to 0:
    dp[k] = (dp[k+1] + ... + dp[k+W]) / W
return dp[0]

This leads to a solution with O(K * W + (N-K)) time complexity, which isn't efficient enough.
Every calculation of dp[k] does O(W) work, but the work is quite similar.

Actually, the difference is f(x) - f(x-1) = (1/W))(f(x+W) - f(x)).
This allows us to calculate subsequent f(k)'s in O(1) time, by maintaining the numerator S = f(x+1) + f(x+2) + ... + f(x+W)

As we calculate each dp[k] = S / W, we maintain the correct value of this numerator S => S + f(k) - f(k+W).

Complexity Analysis

Time and Space Complexity: O(N + W).
Note that we can reduce the time complexity to O(max(K, W)) and the space complexity to O(W)
by only keeping track of the last W values of dp, but it isn't required.

"""


class New21Game:

    def doit(self, N, K, W):
        dp = [0.0] * (N + W + 1)
        # dp[x] = the answer when Alice has x points
        for k in range(K, N + 1):
            dp[k] = 1.0

        S = min(N - K + 1, W)
        # S = dp[k+1] + dp[k+2] + ... + dp[k+W]
        for k in range(K - 1, -1, -1):
            dp[k] = S / float(W)
            S += dp[k] - dp[k + W]

        return dp[0]


if __name__ == '__main__':

    res = New21Game().doit(N=10, K=1, W=10)  # 1.00000

    res = New21Game().doit(N=6, K=1, W=10)  # 0.60000

    res = New21Game().doit(N=21, K=17, W=10)  # 0.73278

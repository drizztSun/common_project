/*
1690. Stone Game VII


Alice and Bob take turns playing a game, with Alice starting first.

There are n stones arranged in a row. On each player's turn, they can remove either the leftmost stone or the rightmost stone from the row and receive points equal to the sum of the remaining stones' values in the row. 
The winner is the one with the higher score when there are no stones left to remove.

Bob found that he will always lose this game (poor Bob, he always loses), so he decided to minimize the score's difference. Alice's goal is to maximize the difference in the score.

Given an array of integers stones where stones[i] represents the value of the ith stone from the left, return the difference in Alice and Bob's score if they both play optimally.

 

Example 1:

Input: stones = [5,3,1,4,2]
Output: 6
Explanation: 
- Alice removes 2 and gets 5 + 3 + 1 + 4 = 13 points. Alice = 13, Bob = 0, stones = [5,3,1,4].
- Bob removes 5 and gets 3 + 1 + 4 = 8 points. Alice = 13, Bob = 8, stones = [3,1,4].
- Alice removes 3 and gets 1 + 4 = 5 points. Alice = 18, Bob = 8, stones = [1,4].
- Bob removes 1 and gets 4 points. Alice = 18, Bob = 12, stones = [4].
- Alice removes 4 and gets 0 points. Alice = 18, Bob = 12, stones = [].
The score difference is 18 - 12 = 6.
Example 2:

Input: stones = [7,90,5,1,100,10,10,2]
Output: 122
 

Constraints:

n == stones.length
2 <= n <= 1000
1 <= stones[i] <= 1000

*/
#include <vector>
#include <algorithm>
#include <numeric>

using std::vector;

class StoneGameVII {

public:

    /*
        1690.Stone-Game-VII
        本题和1563.Stone-Game-V类似，典型的区间型DP。令dp[i][j]表示我方在先手处理[i:j]时可以得到的最多的、领先对手的分差。注意，这里的分差是相对于对手在这个区间内的得分而言。

        我方在处理[i:j]区间时就两种选择。

        第一种是我方选择第i个元素。这样我方在本轮得分sum[i+1:j]，之后的局势是对方处理[i+1:j]，从递归的角度来看，对手可以在此区间内领先我方的最大分差是dp[i+1][j]。所以回溯到本轮，我方先手处理[i:j]区间能够得到的最大分差就是sum[i+1:j]-dp[i+1:j].

        第二种是我方选择第j个元素，同理我方可以得到的最大分差就是sum[i:j-1]-dp[i:j-1]。

        综上，我方会在上面两种方案中选择更优的一种。

        最后答案的输出就是dp[1:n].
    */
    int doit_dp(vector<int>& stones) {

        int n = stones.size();
        stones.insert(stones.begin(), 0);

        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        vector<int>presum(n+2,0);
        for (int i=1; i<=n; i++)
            presum[i] = presum[i-1] + stones[i];        
        
        for (int i=1; i<=n; i++)
            dp[i][i] = 0;

        for (int i=1; i+1<=n; i++)
            dp[i][i+1] = std::max(stones[i], stones[i+1]);
                
        for (int len = 3; len<=n; len++)
        {
            for (int i=1; i+len-1<=n; i++)
            {
                int j = i+len-1;
                dp[i][j] = std::max(presum[j]-presum[i] - dp[i+1][j], presum[j-1]-presum[i-1] - dp[i][j-1]);
            }
        }
        return dp[1][n];        
    }
    
    /*

    Play optimally =》 Game theory Min-Max
    Always maxmize the relative score to matter who's playing the game（MaxMax)

        1) Max( my total score - opponent's total score) =>
        2) Max(my current score - opponent's relative score of the remaining game)

    game(l, r) := max relative score we can achieve given a sub-game of range [l, r]
    Subproblems overlaps => Recursion with memorization or DP, otherwise (2^n)
    Subproblems / Space complexity: O(n^2) / Time complexity: O(n^2)
    */
    int doit_dp_bottomup(vector<int>& A) {
        const int n = A.size();
        vector<int> sums(n + 1);

        for (int i = 0; i < n; ++i) 
            sums[i + 1] = sums[i] + sums[i];
        
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int c = 2; c <= n; ++c)
            for (int l = 0, r = l + c - 1; r < n; ++l, ++r)
                dp[l][r] = std::max(sums[r + 1] - sums[l + 1] - dp[l + 1][r], sums[r] - sums[l] - dp[l][r - 1]);

        return dp[0][n - 1];
    }

    int doit_dp_dfs_Topdown(vector<int>& A) {

        const int n = A.size();
        vector<vector<int>> cache(n, vector<int>(n, INT_MAX));
        std::function<int(int, int, int)> dp = [&](int l, int r, int s) {
            if (l >= r) return 0;
            if (cache[l][r] == INT_MAX)
                cache[l][r] = std::max(s - A[r] - dp(l, r - 1, s - A[r]),
                                s - A[l] - dp(l + 1, r, s - A[l]));
            return cache[l][r];
        };
        return dp(0, n - 1, std::accumulate(begin(A), end(A), 0));
    }
};
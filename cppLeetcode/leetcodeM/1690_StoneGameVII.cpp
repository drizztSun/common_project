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
/*
486. Predict the Winner

Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. 
Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.

Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

Example 1:

Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2. 
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2). 
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5. 
Hence, player 1 will never be the winner and you need to return False.
 

Example 2:

Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
 

Constraints:

. 1 <= length of the array <= 20.
. Any scores in the given array are non-negative integers and will not exceed 10,000,000.
. If the scores of both players are equal, then player 1 is still the winner.

*/

#include <vector>
#include <functional>


using std::vector;


class PredictTheWinner {


public:


    /*
        Approach #2 Similar Approach [Accepted]
        Algorithm

        We can omit the use of turnturn to keep a track of the player for the current turn. To do so, we can make use of a simple observation. If the current turn belongs to, say Player 1, we pick up an element, say xx, from either end, and give the turn to Player 2. Thus, if we obtain the score for the remaining elements(leaving xx), this score, now belongs to Player 2. Thus, since Player 2 is competing against Player 1, this score should be subtracted from Player 1's current(local) score(xx) to obtain the effective score of Player 1 at the current instant.

        Similar argument holds true for Player 2's turn as well i.e. we can subtract Player 1's score for the remaining subarray from Player 2's current score to obtain its effective score. By making use of this observation, we can omit the use of turnturn from winner to find the required result by making the slight change discussed above in the winner's implementation.

        While returning the result from winner for the current function call, we return the larger of the effective scores possible by choosing either the first or the last element from the currently available subarray. Rest of the process remains the same as the last approach.

        Now, in order to remove the duplicate function calls, we can make use of a 2-D memoization array, memomemo, such that we can store the result obtained for the function call winner for a subarray with starting and ending indices being ss and ee ] at memo[s][e]memo[s][e]. This helps to prune the search space to a great extent.

        This approach is inspired by @chidong

        **Complexity Analysis**
        Time complexity : O(n^2). The entire memomemo array of size nnxnn is filled only once. Here, nn refers to the size of numsnums array.

        Space complexity : O(n^2). memomemo array of size nnxnn is used for memoization.
    */
    bool doit_dp_topdown_minmax(vector<int>& nums) {
        
        int n = nums.size();
        vector<int> dp(n*n, INT_MAX);
        
        std::function<int(int, int)> dfs =[&](int a, int b) {
        
            if (a == b) return nums[a];
            
            if (dp[a*n+b] != INT_MAX) return dp[a*n + b]; 
            
            dp[a*n + b] = std::max(nums[a] - dfs(a+1, b), nums[b] - dfs(a, b-1));
            
            return dp[a*n + b];
        };
        
        return dfs(0, nums.size()-1) >= 0;
    }

    /**/
    bool doit_dp_bottomup_minmax(vector<int>& nums) {

        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int>(n));

        for (int i = n-1; i >= 0; i--) {
            
            dp[i][i] = nums[i];

            for (int j = i+1; j < n; j++) {

                dp[i][j] = std::max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
            }
        }

        return dp[0][n-1] >= 0;
    }

};
/*

1406. Stone Game III


Alice and Bob continue their games with piles of stones. There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.

Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take 1, 2 or 3 stones from the first remaining stones in the row.

The score of each player is the sum of values of the stones taken. The score of each player is 0 initially.

The objective of the game is to end with the highest score, and the winner is the player with the highest score and there could be a tie. The game continues until all the stones have been taken.

Assume Alice and Bob play optimally.

Return "Alice" if Alice will win, "Bob" if Bob will win or "Tie" if they end the game with the same score.

 

Example 1:

Input: values = [1,2,3,7]
Output: "Bob"
Explanation: Alice will always lose. Her best move will be to take three piles and the score become 6. Now the score of Bob is 7 and Bob wins.
Example 2:

Input: values = [1,2,3,-9]
Output: "Alice"
Explanation: Alice must choose all the three piles at the first move to win and leave Bob with negative score.
If Alice chooses one pile her score will be 1 and the next move Bob's score becomes 5. The next move Alice will take the pile with value = -9 and lose.
If Alice chooses two piles her score will be 3 and the next move Bob's score becomes 3. The next move Alice will take the pile with value = -9 and also lose.
Remember that both play optimally so here Alice will choose the scenario that makes her win.
Example 3:

Input: values = [1,2,3,6]
Output: "Tie"
Explanation: Alice cannot win this game. She can end the game in a draw if she decided to choose all the first three piles, otherwise she will lose.
Example 4:

Input: values = [1,2,3,-1,-2,-3,7]
Output: "Alice"
Example 5:

Input: values = [-1,-2,-3]
Output: "Tie"
 

Constraints:

1 <= values.length <= 50000
-1000 <= values[i] <= 1000
 
 
 
*/
#include <vector>
#include <string>


using std::string;
using std::vector;

class StoneGameIII {

public:

    /*
        1406.Stone-Game-III
        我们令dp[i]表示已经有i堆石头被拿走的情况下，当前玩家在后续的操作中最多总共能拿到多少分？

        对于当前决策而言，玩家有三种选择，拿走第1堆，拿走2堆，拿走3堆。

        我们分析第一种情况，玩家当前只拿走一堆，那么玩家可以收益stones[i+1]。接下来对手面临的问题是：已经有i+1对石头被拿走的情况下，在后续的操作中最多能拿多少分？显然对手的答案有着相同的定义，就是dp[i+1]。同时，这意味着，对手获取dp[i+1]的同时，我方能够获取的分数就是sum[i+2:n]-dp[i+1]。所以，退回到玩家的当前状态，说明如果玩家当前只拿走一堆，那么玩家的总收益就是 dp[i] = stones[i+1] + sum[i+2:n]-dp[i+1]

        以上的结论可以推广到：玩家当前决定拿走k堆。那么该轮玩家的收益是stones[i+1:i+k]。对手之后的总收益是dp[i+k]，此消彼长，玩家之后的总收益就是sum[i+k+1:n]-dp[i+k]。所以当前决策所对应的玩家总收益就是dp[i] = stones[i+1:i+k] + sum[i+k+1:n]-dp[i+1]

        因此，dp[i]的最优解就是在k=1,2,3中选择一个对应的dp[i]最大值。

        由此我们看出dp[i]的值取决于下标更大的dp值。显然，我们对于dp的计算，下标应该按照从到小的顺序。

        最终的答案是考察dp[0]。即玩家在最初始的状态下（还没有拿走任何石头）能够得到的最大分数，与对手能够得到的最大分数totalSum-dp[0]作比较。
    */
    string doit_dp(vector<int>& stoneValue) {

        int n = stoneValue.size();
        stoneValue.insert(stoneValue.begin(),0);

        vector<int>presum(n+1,0);
        for (int i=1; i<=n; i++)
            presum[i] = presum[i-1]+stoneValue[i];

        vector<int>dp(n+1,INT_MIN);  // dp[i] : the max score when player can get after i piles have been taken
        dp[n] = 0;

        for (int i = n-1; i >= 0; i--)
        {
            int sum = 0;
            for (int k=1; k<=3; k++)
            {
                if (i+k>n) break;
                sum += stoneValue[i+k];
                dp[i] = max(dp[i], sum + presum[n]-presum[i+k]-dp[i+k]);
            }
        }

        if (dp[0] > presum[n]-dp[0])
            return "Alice";
        else if (dp[0] < presum[n]-dp[0])
            return "Bob";
        else
            return "Tie";
    }

    string doit_dp_topdown(vector<int>& stoneValue) {

        int n = stoneValue.size();
        vector<int> dp(n, INT_MIN);

        std::function<int(int)> evaluate = [&](int i) {

            if (i == n) return 0;
            
            if (dp[i] != INT_MIN) return dp[i];

            int sum = 0;

            for (int j = i; j < std::min(n, i + 3); j++) {
            
                sum += stoneValue[j];

                dp[i] = std::max(dp[i], sum - evaluate(j+1));
            }

            return dp[i];
        };

        int res = evaluate(0);

        if (res == 0) return "Tie";

        return res > 0 ? "Alice" : "Bob";
    }

    string doit_dp_bottomup(vector<int>& stone) {
        
        int i = stone.size() - 1;
        int x = 0, y = 0, z = 0; // x one step profit, y two steps profit, z three steps profit
        
        while (i >= 0) {
            
            int ans = INT_MIN;
            
            ans = max( ans , stone[i] - x);
            
            if (i+1 < stone.size()) 
                ans = max( ans , stone[i] + stone[i+1] - y);
        
            if (i+2 < stone.size()) 
                ans = max( ans , stone[i]+ stone[i+1] + stone[i+2] - z);
        
            z = y;
            y = x;
            x = ans;
            i--;
        }
        
        int a = x;
        if( a > 0)return "Alice";
        if( a == 0) return "Tie";
        return "Bob";
    }
};
/*
1269. Number of Ways to Stay in the Same Place After Some Steps


You have a pointer at index 0 in an array of size arrLen. At each step, you can move 1 position to the left, 
1 position to the right in the array or stay in the same place  (The pointer should not be placed outside the array at any time).

Given two integers steps and arrLen, return the number of ways such that your pointer still at index 0 after exactly steps steps.

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: steps = 3, arrLen = 2
Output: 4
Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
Right, Left, Stay
Stay, Right, Left
Right, Stay, Left
Stay, Stay, Stay
Example 2:

Input: steps = 2, arrLen = 4
Output: 2
Explanation: There are 2 differents ways to stay at index 0 after 2 steps
Right, Left
Stay, Stay
Example 3:

Input: steps = 4, arrLen = 2
Output: 8
 

Constraints:

1 <= steps <= 500
1 <= arrLen <= 10^6

*/

#include <vector>

using std::vector;


class NumWaysToStayZero {

    /*
                1269.Number-of-Ways-to-Stay-in-the-Same-Place-After-Some-Steps
        本题的DP状态很容易定义：dp[k][i]就表示第k步能达到第i个位置的方案数。并且状态转移方程也很容易写出来：

            for (int k=1; k<=steps; k++)             
                    for (int i=0; i<arrLen; i++)
                    {
                        dp[k][i] = dp[k-1][i-1]+dp[k-1][i+1]+dp[k-1][i];
                    }
                }
        但是查看数据范围后发现，steps*arrLen达到了1e8数量级，这两个循环是会超时的。

        本题优化的技巧在于，题目只问了steps之后到达index=0的方案数，而并没有问到达任意index=i的方案数。再看到steps只有500，于是就能得到启发：我们并不关心位置大于steps/2的那些地方的状态，
        它们只有在steps/2时间之后才会被更新，而反馈影响给index=0又需要多于steps/2的时间，因此它们永远不会影响到dp[steps][0].本题的极限就是前steps/2不停向右，后steps/2不停向左，所以我们只需要在第二层循环更新到steps/2即可。

        事实上，对于任意steps/2之后的t步，我们甚至不用更新steps/2的最后t个位置的状态。因为那些时刻那些位置的状态，永远也不能赶在steps这个时刻影响到index=0.
    */
    int numWays(int steps, int arrLen) 
    {
        int n = arrLen;
        auto dp = vector<vector<long>>(steps+1, vector<long>(steps/2+2,0));
        dp[0][0] = 1;
        long M = 1e9+7;

        for (int k=1; k<=steps; k++)
        {            
            for (int i=0; i<steps/2+1; i++)
            {
                if (i==0)
                    dp[k][i] = (dp[k-1][i+1]+dp[k-1][i])%M;
                else if (i==n-1)
                    dp[k][i] = (dp[k-1][i-1]+dp[k-1][i])%M;
                else
                    dp[k][i] = (dp[k-1][i-1]+dp[k-1][i+1]+dp[k-1][i])%M;
            }
        }

        return dp[steps][0];
    }

public:
    
    int doit_dp(int steps, int arrLen) {
        int mod = 1e9 + 7;
        vector<int> dp(std::min(steps/2+1, arrLen), 0);
        dp[0] = 1;
        while (steps-- > 0) {
            vector<int> new_dp(dp.size(), 0);
            for (int i = 0; i < dp.size(); ++i) {
                if (i > 0) new_dp[i-1] = (new_dp[i-1] + dp[i]) % mod;
                new_dp[i] = (new_dp[i] + dp[i]) % mod;
                if (i < dp.size()-1) new_dp[i+1] = (new_dp[i+1] + dp[i]) % mod;
            }
            dp = new_dp;
        }
        return dp.front();
    }
};
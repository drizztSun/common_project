/*
1770. Maximum Score from Performing Multiplication Operations



You are given two integer arrays nums and multipliers of size n and m respectively, where n >= m. The arrays are 1-indexed.

You begin with a score of 0. You want to perform exactly m operations. On the ith operation (1-indexed), you will:

Choose one integer x from either the start or the end of the array nums.
Add multipliers[i] * x to your score.
Remove x from the array nums.
Return the maximum score after performing m operations.

 

Example 1:

Input: nums = [1,2,3], multipliers = [3,2,1]
Output: 14
Explanation: An optimal solution is as follows:
- Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
- Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
- Choose from the end, [1], adding 1 * 1 = 1 to the score.
The total score is 9 + 4 + 1 = 14.
Example 2:

Input: nums = [-5,-3,-3,-2,7,1], multipliers = [-10,-5,3,4,6]
Output: 102
Explanation: An optimal solution is as follows:
- Choose from the start, [-5,-3,-3,-2,7,1], adding -5 * -10 = 50 to the score.
- Choose from the start, [-3,-3,-2,7,1], adding -3 * -5 = 15 to the score.
- Choose from the start, [-3,-2,7,1], adding -3 * 3 = -9 to the score.
- Choose from the end, [-2,7,1], adding 1 * 4 = 4 to the score.
- Choose from the end, [-2,7], adding 7 * 6 = 42 to the score. 
The total score is 50 + 15 - 9 + 4 + 42 = 102.
 

Constraints:

n == nums.length
m == multipliers.length
1 <= m <= 103
m <= n <= 105
-1000 <= nums[i], multipliers[i] <= 1000


*/
#include <vector>
#include <functional>

using std::vector;

    
class MaximumScore {

public:

    /*
        better down bottomup, bottomup will calculate a lot of status, useless and never needed.
    */    
    int doit_dp_topdown(vector<int>& nums, vector<int>& mul) {
        
        int dp[1001][1001] = {0};

        std::function<int(int, int, int)> dfs = [&](int nl, int nr, int ind) {

            if (ind >= mul.size()) return 0;

            if (dp[nl][ind]) return dp[nl][ind];

            return dp[nl][ind] = std::max(nums[nl] * mul[ind] + dfs(nl + 1, nr, ind + 1), nums[nr] * mul[ind] + dfs(nl, nr - 1, ind + 1));
        };
        
        return dfs(0, nums.size() - 1, 0);
    }

    /*
        1770.Maximum-Score-from-Performing-Multiplication-Operations
        这道题是比较新颖的区间型DP。我们常见的区间型DP的定义是dp[i][j]表示在区间[i:j]内可以得到的最优解。但是本题中这样定义的话需要开辟N^2的空间，会MLE。
        我们发现本题中需要拿取的数字个数只有m个，远比nums的长度要小，所以我们转换思路，将dp[i][j]表示我们在左侧拿了i个、右侧拿了j个可以得到的最优解。虽然有两个区间，但我们同样只需要用两个下标可以表示了。

        dp[i][j]的最优解取决于最后一步拿的第i+j个数字是在左边还是右边。所以状态转移方程是：

        dp[i][j] = max(dp[i-1][j]+nums[i]*multipliers[i+j], dp[i][j-1]+nums[n-j+1]*multipliers[i+j]);  
        dp的边界条件是dp[0][0] = 0.
    */
    int doit_dp_(vector<int>& nums, vector<int>& multipliers) 
    {
        int n = nums.size(), m = multipliers.size();
        vector<vector<int>> dp(m+1, vector<int>(m+1, INT_MIN/2));
        
        nums.insert(nums.begin(), 0);
        dp[0][0] = 0;
        
        int ret = INT_MIN/2;                
        for (int len = 1; len <= m; len++)
        {
            for (int i=0; i<=len; i++)
            {
                int j = len-i;
                if (i>=1) dp[i][j] = std::max(dp[i][j], dp[i-1][j] + nums[i] * multipliers[len-1]);
                if (j>=1) dp[i][j] = std::max(dp[i][j], dp[i][j-1] + nums[n-j+1] * multipliers[len-1]);
                
                if (len==m) ret = std::max(ret, dp[i][j]);                    
            }
        }
        return ret;
    }
};
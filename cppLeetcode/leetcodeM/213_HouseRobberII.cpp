/*
213. House Robber II


You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. 
All houses at this place are arranged in a circle. 

That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

 

Example 1:

Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
Example 2:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
Example 3:

Input: nums = [0]
Output: 0
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 1000
*/


#include <vector>

using std::vector;


class HouseRobberII {

    /*
        213.House-Robber-II
        解法1：双状态动态规划
        考虑环的影响，首位和末位不能同时为yes。这说明至少有一个的选择是no。

        (1) 如果首位我们选择no，那么从nums[1]到nums[n-1]的选择就没有环形的首尾制约，完全就是一个198.House Robber I的问题。

        (2) 如果末位我们选择no，那么从nums[0]到nums[n-2]的选择就没有环形的首尾制约，同样也是一个198.House Robber I的问题。

        我们将两种情况下的最优解再取最大值，就是答案。

        注意，(1)和(2)并不是互斥的。他们是有交叠的。但是它们的并集一定是全集。

        解法2：记忆化搜索（递归）
        我们考虑是否打劫第零家（nums[0]）：是的话，那么下一步我们可以在[2,n-2]中任意选择打劫。如果不打劫第零家，那么下一步我们可以在[1,n-1]中任意选择打劫。也就是说，最顶层的答案就是max( nums[0]+dfs(2,n-2), dfs(1,n-1) )其中DFS的两个参数就是可供打劫的区间。这里特别注意的是n-2，这是因为题目中loop的要求（不能打劫任意相邻两家），打劫了第0家的话我们就不可能打劫第n-1家。

        对于任意区间[i,j]作为打劫对象，我们可以同样处理，考虑是否打劫最前面的（也就是第i家）。根据不同的决策，我们分别有：nums[i]+dfs(i+1,j)和dfs(i+1,j).两者分别递归处理得到结果后，取较大作为返回值。

        当然，我们也可以用区间型的二维dp来实现上面的算法。

        Follow-up
        此题有一个更难一点的follow up，参见1388.Pizza-With-3n-Slices.
    */
    int rob(vector<int>& nums) 
    {
        int n = nums.size();
        if (n==0) return 0;
        if (n==1) return nums[0];
        
        int ret = 0;
        
        int rob = nums[1], norob = 0;        
        for (int i=2; i<n; i++)
        {
            int rob_tmp = rob, norob_tmp = norob;
            rob = norob_tmp + nums[i];
            norob = max(rob_tmp, norob_tmp);
        }
        ret = max(rob, norob);
        
        rob = nums[0], norob =0;
        for (int i=1; i<n-1; i++)
        {
            int rob_tmp = rob, norob_tmp = norob;
            rob = norob_tmp + nums[i];
            norob = max(rob_tmp, norob_tmp);   
        }
        ret = max(ret, max(rob, norob));
        return ret;   
    }

    int rob(vector<int>& nums) 
    {
        int n = nums.size();
        if (n==0) return 0;
        if (n==1) return nums[0];
        
        auto dp = vector<vector<int>>(n, vector<int>(n,0));
        for (int i=0; i<n; i++)
            dp[i][i] = nums[i];
        
        for (int len = 2; len <=n; len++)
            for (int i= 0; i+len-1<n; i++)
            {
                int j = i+len-1;
                dp[i][j] = max(nums[i]+ ((i+2>j)?0:dp[i+2][j]), dp[i+1][j]);
            }
        
        return max(nums[0]+((2>n-2)?0:dp[2][n-2]), dp[1][n-1]);
    }

public:
    
    int doit_dp(vector<int>& nums) {
        
        if (nums.size() == 1) return nums[0];
        
        auto search = [](vector<int>& nums, int i, int j) {
          
            int norob = 0, rob = 0;
            
            for (int s = i; s <= j; s++) {
                int res = rob;
                if (norob + nums[s] > rob)
                    rob = norob + nums[s];
                norob = res;
            }
            return rob;
        };
        
        int n = nums.size();
        return std::max(search(nums, 0, n-2), search(nums, 1, n-1));
    }
};

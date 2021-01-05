/*
416. Partition Equal Subset Sum

Given a non-empty array nums containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

 

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
 

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 100
*/

/*
Solution Article
Overview
The problem is similar to the classic Knapsack problem. The basic idea is to understand that to partition an array into two subsets of equal 
sum say \text{subSetSum}subSetSum, the \text{totalSum}totalSum of given array must be twice the \text{subSetSum}subSetSum

\text{totalSum} = \text{subSetSum} * 2totalSum=subSetSum∗2

This could also be written as, \text{subSetSum} = \text{totalSum}/2subSetSum=totalSum/2

Example Assume \text{totalSum}totalSum of an array is 2020 and if we want to partition it into 2 subsets of equal sum, then the \text{subSetSum}subSetSum must be (20/2) = 10(20/2)=10.

Now, the problem to find the subset with a sum equals a given target. Here target is \text{subSetSum}subSetSum.

It must be noted that the total sum of an array must be even, only then we can divide it into 2 equal subsets. For instance, we cannot have an equal \text{subSetSum}subSetSum for an array with total sum as 2121.

*/
#include <vector>
#include <numeric>
#include <optional>

using std::optional;
using std::vector;


class PartitionEqualSubsetSum {

public:

    /*
        Approach 2: Top Down Dynamic Programming - Memoization
        Intuition
        In the above approach, we observe that the same subproblem is computed and solved multiple times.
        In the above recursion tree, we could see that \text{isSum}( 3,[6] )isSum(3,[6]) is computed twice and the result is always the same. 
        Since the same subproblem is computed again and again, the problem has Overlapping Subproblem property and can be solved using Dynamic Programming.

        Algorithm

        We could have stored the results of our computation for the first time and used it later. This technique of computing once and returning the stored value is called memoization. We use a two dimensional array \text{memo}memo and follow the following steps for each recursive call :

        Check if subSetSum for a given nn exists in \text{memo}memo to see if we can avoid computing the answer and return the result stored in memo.
        Save the results of any calculations to \text{memo}memo.


        Complexity Analysis

        Let nn be the number of array elements and mm be the \text{subSetSum}subSetSum.

        Time Complexity : \mathcal{O}(m \cdot n)O(m⋅n).

        In the worst case where there is no overlapping calculation, the maximum number of entries in the memo would be m \cdot nm⋅n. For each entry, overall we could consider that it takes constant time, i.e. each invocation of dfs() at most emits one entry in the memo.

        The overall computation is proportional to the number of entries in memo. Hence, the overall time complexity is \mathcal{O}(m \cdot n)O(m⋅n).

        Space Complexity: \mathcal{O}(m \cdot n)O(m⋅n). We are using a 2 dimensional array \text{memo}memo of size (m \cdot n)(m⋅n) and \mathcal{O}(n)O(n) space to store the recursive call stack. This gives us the space complexity as \mathcal{O}(n)O(n) + \mathcal{O}(m \cdot n)O(m⋅n) = \mathcal{O}(m \cdot n)O(m⋅n)
    */

    bool doit_topdown_dp(vector<int> &nums) {
        int totalSum = 0;
        // find sum of all array elements
        for (int num : nums) {
            totalSum += num;
        }
        // if totalSum is odd, it cannot be partitioned into equal sum subset
        if (totalSum % 2 != 0) return false;
        int subSetSum = totalSum / 2;
        int n = nums.size();
        vector<vector<optional<bool>>> memo(n + 1, vector<optional<bool>>(subSetSum + 1, std::nullopt));

        std::function<bool(int, int)> dfs = [&](int n, int subSetSum) {
            // Base Cases
            if (subSetSum == 0)
                return true;
                
            if (n == 0 || subSetSum < 0)
                return false;

            // check if subSetSum for given n is already computed and stored in memo
            if (memo[n][subSetSum] != std::nullopt) {
                return (memo[n][subSetSum] == true);
            }

            bool result = dfs(n - 1, subSetSum - nums[n - 1]) || dfs(n - 1, subSetSum);
            memo[n][subSetSum] = result;
            return result;
        };

        return dfs(n - 1, subSetSum);
    }



    bool doit_dp_topdown(vector<int>& nums) {

        int sums = std::accumulate(begin(nums), end(nums), 0);
        if (sums % 2 == 1) return false;

        int half = sums / 2;
        int N = nums.size();
        vector<vector<int>> dp(N+1, vector<int>(half+1, -1));

        std::function<int(int, int)> search = [&](int idx, int amount) {
            
            if (amount <= 0)
                return amount == 0? 1: 0;
            
            if (idx == N)
                return 0;
        
            if (dp[idx][amount] != -1)
                return dp[idx][amount];

            int res = search(idx+1, amount);
            if (res == 0 && amount >= nums[idx])
                res = search(idx+1, amount-nums[idx]);

            dp[idx][amount] = res;
            return res;
        };

        return search(0, half);
    }

    /*
    Approach 4: Optimised Dynamic Programming - Using 1D Array
    Intuition

    We could further optimize Approach 3. We must understand that for any array element ii, we need results of the previous iteration (i-1) only. Hence, we could achieve the same using a one-dimensional array as well.

    */

    bool canPartition(vector<int> &nums) {
        int totalSum = 0;
        // find sum of all array elements
        for (int num : nums) {
            totalSum += num;
        }
        // if totalSum is odd,it cannot be partitioned into equal sum subset
        if (totalSum % 2 != 0) return false;
        int subSetSum = totalSum / 2;
        vector<bool> dp(subSetSum + 1, false);
        dp[0] = true;
        for (int curr : nums) {
            for (int j = subSetSum; j >= curr; j--) {
                dp[j] = dp[j] || dp[j - curr];
            }
        }
        return dp[subSetSum];
    }
    
    bool canPartition1(vector<int>& nums) {
        int sums = accumulate(begin(nums), end(nums), 0);
        if (sums % 2 == 1) return false;
        
        int half = sums/2;
        vector<int> dp(half+1, false);
        dp[0] = true;
        
        for (auto c: nums) {
            for (int i = half; i >= c; i--) {
                if (dp[i-c]) dp[i] = true;
            }
            
            if (dp[half]) return true;
        }
        
        return false;
    }
    /*
        Approach 3: Bottom Up Dynamic Programming
        Intuition

        This is another approach to solving the Dynamic Programming problems. We use the iterative approach and store the result of subproblems in bottom-up fashion also known as Tabulation.

        Algorithm

        We maintain a 2D array , \text{dp}[n][\text{subSetSum}]dp[n][subSetSum] For an array element ii and sum jj in array \text{nums}nums,

        \text{dp}[i][j] = \text{true}dp[i][j]=true if the sum jj can be formed by array elements in subset \text{nums[0]} .. \text{nums[i]}nums[0]..nums[i],otherwise \text{dp}[i][j] = \text{false}dp[i][j]=false

        \text{dp}[i][j]dp[i][j] is \text{true}true it satisfies one of the following conditions :

        Case 1) sum jj can be formed without including i^{th}i 
        th
        element,
        \text{if } \text{dp}[i-1][j] == \text{true}if dp[i−1][j]==true

        Case 2) sum jj can be formed including i^{th}i 
        th
        element,
        \text{if } \text{dp}[i-1][j - \text{nums}[i]] == \text{true}if dp[i−1][j−nums[i]]==true
    */
    bool doit_dp_bottomup(vector<int> &nums) {
        int totalSum = 0;
        // find sum of all array elements
        for (int num : nums) {
            totalSum += num;
        }

        // if totalSum is odd,it cannot be partitioned into equal sum subset
        if (totalSum % 2 != 0) return false;
        int subSetSum = totalSum / 2;
        int n = nums.size();
        bool dp[n + 1][subSetSum + 1];
        memset(dp, 0, (n + 1) * (subSetSum + 1) * sizeof(bool));
        
        dp[0][0] = true;
        for (int i = 1; i <= n; i++) {
            int curr = nums[i - 1];
            for (int j = 0; j <= subSetSum; j++) {
                if (j < curr)
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j] || (dp[i - 1][j - curr]);
            }
        }
        return dp[n][subSetSum];
    }




    /*
    Approach 1: Brute Force
    Intuition

    We have to find a subset in an array where the sum must be equal to \text{subSetSum}subSetSum that we calculated above. The brute force approach would be to generate all the possible subsets of an array and return true if we find a subset with the required sum.

    Algorithm

    Assume, there is an array \text{nums}nums of size nn and we have to find if there exists a subset with total \text{sum} = \text{subSetSum}sum=subSetSum. For a given array element xx, there could be either of 2 possibilities:

    Case 1) xx is included in subset sum. \text{subSetSum} = \text{subSetSum} - xsubSetSum=subSetSum−x

    Case 2) xx is not included in subset sum, so we must take previous sum without xx. \text{subSetSum} = \text{subSetSum}subSetSum=subSetSum

    We can use depth first search and recursively calculate the \text{subSetSum}subSetSum for each case and check if either of them is true. This can be formulated as

    isSum (subSetSum, n) = isSum(subSetSum- nums[n], n-1) ||  isSum(subSetSum, n-1)
    Base Cases

    If \text{subSetSum}subSetSum is 00, return true ( Since we found a subset with sum subSetSum )
    If \text{subSetSum}subSetSum is less than 00, return false
    */
    bool doit_bruteforce(vector<int> &nums) {
        int totalSum = 0;
        // find sum of all array elements
        for (int num : nums) {
            totalSum += num;
        }
        
        std::function<bool(int, int)> dfs = [&](int n, int subSetSum) {
            // Base Cases
            if (subSetSum == 0)
                return true;
            if (n == 0 || subSetSum < 0)
                return false;
            bool result = dfs(n - 1, subSetSum - nums[n - 1]) || dfs(n - 1, subSetSum);
            return result;
        };
        
        // if totalSum is odd,it cannot be partitioned into equal sum subset
        if (totalSum % 2 != 0) return false;
        int subSetSum = totalSum / 2;
        int n = nums.size();
        return dfs(n - 1, subSetSum);
    }
};
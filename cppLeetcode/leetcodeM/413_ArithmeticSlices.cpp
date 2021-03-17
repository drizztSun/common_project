/*
413. Arithmetic Slices

An integer array is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
    .  For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.
Given an integer array nums, return the number of arithmetic subarrays of nums.

A subarray is a contiguous subsequence of the array.

Example 1:

Input: nums = [1,2,3,4]
Output: 3
Explanation: We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and [1,2,3,4] itself.
Example 2:

Input: nums = [1]
Output: 0
 

Constraints:

1 <= nums.length <= 5000
-1000 <= nums[i] <= 1000

*/

#include <vector>

using std::vector;


class NumberOfArithmeticSlices {

public:


    int doit_slidingwindow(vector<int>& nums) {
        
        int ans = 0;

        for (int i = 2, j = 0; i <= nums.size(); i++) {

            if (i == nums.size() || nums[i] - nums[i-1] != nums[i-1] - nums[i-2]) {
                ans += (i - j -2) * (1 + i - j - 2) / 2;
                j = i-1;
            }
        }

        return ans;
    }

    int doit_slidingwindow(vector<int>& nums) {
        
        int ans = 0;
        vector<int> diff;
        for (int i = 1; i < nums.size(); i++)
            diff.push_back(nums[i] - nums[i-1]);
        
        for (int i = 0, j = 0; i <= diff.size(); i++) {
            
            if (i == diff.size() || diff[i] != diff[j]) {
            
                if (i - j > 1) {
                    ans += (i - j -1) * (1 + i - j - 1) / 2;
                }
                
                j = i;
            }
        }
        
        return ans;
    }

    /*
        Approach 4: Dynamic Programming
        Algorithm

        In the last approach, we start with the full range (0,n-1)(0,n−1), where nn is the number of elements in the given AA array. 
        We can observe that the result for the range (0,i)(0,i) only depends on the elements in the range (0,i)(0,i) and not on any element beyond this range. Thus, we can make use of Dynamic Programming to solve the given problem.

        We can make use of a 1-D dpdp with number of elements equal to nn. dp[i]dp[i] is used to store the number of arithmetic slices possible in the range (k,i)(k,i) and not in any range (k,j) such that j<ij<i. 
        Again, kk refers to the minimum index possible such that (k,j)(k,j) constitutes a valid Arithmetic Slice.

        Instead of going in the reverse order as in the recursive approach, we can start filling the dpdp in a forward manner. The intuition remains the same as in the last approach. For the i^{th}i 
        th
        element being considered, we check if this element satsfies the common difference criteria with the previous element. 
        If so, we know the number of new arithmetic slices added will be 1+dp[i-1]1+dp[i−1] as discussed in the last approach. The sumsum is also updated by the same count to reflect the new arithmetic slices added.

        The following animation illustrates the dpdp filling process.

        Current
        1 / 9

        Complexity Analysis

        Time complexity : O(n). We traverse over the given AA array with nn elements once only.

        Space complexity : O(n). 1-D dpdp of size nn is used.    
    */
    int doit_dp(vector<int>& nums) {

        vector<int> dp(nums.size(), 0);
        int ans = 0;

        for (int i = 2; i < nums.size(); i++) {

            if (nums[i] - nums[i-1] == nums[i-1] - nums[i-2]) {
                dp[i] = 1 + dp[i-1];
            }

            ans += dp[i];
        }

        return ans;
    }

    /*
        Approach 5: Constant Space Dynamic Programming
        Algorithm

        In the last approach, we can observe that we only require the element dp[i-1]dp[i−1] to determine the value to be entered at dp[i]dp[i]. 
        Thus, instead of making use of a 1-D array to store the required data, we can simply keep a track of just the last element.

        Complexity Analysis

        Time complexity : O(n). We traverse over the given AA array with nn elements once only.
        Space complexity : O(1). Constant extra space is used
    */
    int doit_dp(vector<int>& nums) {
        
        int ans = 0, dp = 0;

        for (int i = 2; i < nums.size(); i++) {

            if (nums[i] - nums[i-1] == nums[i-1] - nums[i-2]) {
                dp = 1 + dp;
                ans += dp;
            } else 
                dp = 0;
        }

        return ans;
    }

    /*
        Approach 6: Using Formula
        Algorithm

        From the dpdp solution, we can observe that for kk consecutive elements sastisfying the common difference criteria, we update the sumsum for each such element by 1, 2, 3, ..., k1,2,3,...,k counts in that order. 
        Thus, instead of updating the sumsum at the same time, we can just keep a track of the number of consecutive elements satisfying the common differnce criteria in a countcount variable 
        and just update the sumsum directly as count*(count+1)/2count∗(count+1)/2 whenver an element not satisfying this criteria is found. At the same time, we also need to reset the countcount value.

        Complexity Analysis

        Time complexity : O(n). We iterate over AA with nn elements exactly once.
        Space complexity : O(1). Constant extra space is used.
    */

    int doit_dp(vector<int>& A) {
        
        int count = 0, sum = 0;

        for (int i = 2; i < A.size(); i++) {
            if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
                count++;
            } else {
                sum += (count + 1) * (count) / 2;
                count = 0;
            }
        }
        return sum += count * (count + 1) / 2;
    }

};

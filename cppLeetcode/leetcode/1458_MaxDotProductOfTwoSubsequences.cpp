/*
 
 1458. Max Dot Product of Two Subsequences

 Given two arrays nums1 and nums2.

 Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same length.

 A subsequence of a array is a new array which is formed from the original array by deleting some (can be none)
 of the characters without disturbing the relative positions of the remaining characters.

 (ie, [2,3,5] is a subsequence of [1,2,3,4,5] while [1,5,3] is not).



 Example 1:

 Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
 Output: 18
 Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
 Their dot product is (2*3 + (-2)*(-6)) = 18.
 Example 2:

 Input: nums1 = [3,-2], nums2 = [2,-6,7]
 Output: 21
 Explanation: Take subsequence [3] from nums1 and subsequence [7] from nums2.
 Their dot product is (3*7) = 21.
 Example 3:

 Input: nums1 = [-1,-1], nums2 = [1,1]
 Output: -1
 Explanation: Take subsequence [-1] from nums1 and subsequence [1] from nums2.
 Their dot product is -1.


 Constraints:

 1 <= nums1.length, nums2.length <= 500
 -1000 <= nums1[i], nums2[i] <= 1000

 
 
 */
#include <stdio.h>
#include <vector>

using std::vector;

class MaxDocProductOfSequence {
    
public:
    
    /*
     
     Dot product: sum(A[i] * B[i])
     
     Similar to: LC 72 Edit distance
     
     dp[i][j] := max dot product of nums1[0~i] and nums2[0~j]
     
     dp[i][j] = max(dp[i-1][j], dp[i][j-1], max(0, dp[1-1][j-1]) + nums[i] * nums2[j])
     
     Time complexity: O(mn)
     Space complexity: O(mn)
     */
    
    int doit_dp(vector<int>& nums1, vector<int>& nums2) {
        
        int m = nums1.size(), n = nums2.size();
        int ans = 0;
        vector<vector<int>> dp(m, vector<int>(n));
        
        for (int i = 0; i < m; i++) {
            
            for (int j = 0; j < n; j++) {
                
                dp[i][j] = nums1[i] * nums2[j];
                
                if (i > 0 && j > 0)
                    dp[i][j] += std::max(0, dp[i-1][j-1]);
                    
                if (i > 0)
                    dp[i][j] = std::max(dp[i][j], dp[i-1][j]);
                
                if (j>0)
                    dp[i][j] = std::max(dp[i][j], dp[i][j-1]);
                
            }
        }
        
        return dp[m-1][n-1];
    }
    
    /*
     dp[i][j] := max product of nums1[0~i], nums2[0~j].

     dp[i][j] = max(dp[i-1][j], dp[i][j -1], max(0, dp[i-1][j-1]) + nums1[i]*nums2[j])

     Time complexity: O(n1*n2)
     Space complexity: O(n1*n2)
     */
    
    int doit_dp_1(vector<int>& nums1, vector<int>& nums2) {
      const int n1 = nums1.size();
      const int n2 = nums2.size();
      // dp[i][j] = max dot product of two subsequences
      // of nums1[0:i] and nums2[0:j]
      vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, INT_MIN / 2));
          
      for (int i = 1; i <= n1; ++i)
        for (int j = 1; j <= n2; ++j)
          dp[i][j] = std::max({
            dp[i - 1][j],
            dp[i][j - 1],
            std::max(0, dp[i - 1][j - 1]) + nums1[i - 1] * nums2[j - 1]
          });
      return dp[n1][n2];
    }
    
    int doit_dp_2(vector<int>& nums1, vector<int>& nums2) {
       const int n1 = nums1.size();
       const int n2 = nums2.size();
       // dp[i][j] = max dot product of two subsequences
       // of nums1[0~i] and nums2[0~j]
       vector<vector<int>> dp(n1, vector<int>(n2));
           
       for (int i = 0; i < n1; ++i)
         for (int j = 0; j < n2; ++j) {
           dp[i][j] = nums1[i] * nums2[j];
           if (i > 0 && j > 0) dp[i][j] += std::max(0, dp[i - 1][j - 1]);
           if (i > 0) dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
           if (j > 0) dp[i][j] = std::max(dp[i][j], dp[i][j - 1]);
         }
       return dp.back().back();
     }
};

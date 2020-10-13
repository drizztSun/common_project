/*
 1246. Palindrome Removal
 
 Given an integer array arr, in one move you can select a palindromic subarray arr[i], arr[i+1], ..., arr[j] where i <= j,
 and remove that subarray from the given array. Note that after removing a subarray,
 the elements on the left and on the right of that subarray move to fill the gap left by the removal.

 Return the minimum number of moves needed to remove all numbers from the array.

  

 Example 1:

 Input: arr = [1,2]
 Output: 2
 Example 2:

 Input: arr = [1,3,4,1,5]
 Output: 3
 Explanation: Remove [4] then remove [1,3,1] then remove [5].
 
 */
#include <vector>

using std::vector;

class MinimumMoves {
    
public:
    int doit_dp(vector<int>&& arr) {
        
        auto n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, n));
        
        for (auto j = 0; j < n; j++) {
            
            for (auto i = j; i >= 0; i--) {
                
                int base = n+1;
                if (arr[i] == arr[j]) {
                    base = (j - i < 2 || dp[i+1][j-1] == 0) ? 1 : dp[i+1][j-1];
                }
                
                for (auto k = i; k < j; k++) {
                    base = std::min(base, dp[i][k] + dp[k+1][j]);
                }
                
                dp[i][j] = base;
            }
        }
        return dp[0][n-1];
    }
};


void test_1246_palindrome_removal() {
    
    MinimumMoves().doit_dp(vector<int>{1,2});
}

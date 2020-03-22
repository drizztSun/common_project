/*
 
 978. Longest Turbulent Subarray
 
 
 A subarray A[i], A[i+1], ..., A[j] of A is said to be turbulent if and only if:

 For i <= k < j, A[k] > A[k+1] when k is odd, and A[k] < A[k+1] when k is even;
 OR, for i <= k < j, A[k] > A[k+1] when k is even, and A[k] < A[k+1] when k is odd.
 That is, the subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.

 Return the length of a maximum size turbulent subarray of A.

  

 Example 1:

 Input: [9,4,2,10,7,8,8,1,9]
 Output: 5
 Explanation: (A[1] > A[2] < A[3] > A[4] < A[5])
 
 Example 2:

 Input: [4,8,12,16]
 Output: 2
 
 Example 3:

 Input: [100]
 Output: 1
 
 */

#include <vector>
using std::vector;


class MaxTurbulenceSize {
    
public:
    
    int doit(vector<int>&& A) {
    
        vector<vector<int>> dp(A.size(), vector<int>{1, 1});
        int ans = 1;
        
        for (int i = 0; i < A.size() - 1; i++) {
            
            bool odd = i % 2 == 1;
            bool bigger = A[i] > A[i+1];
            
            if (A[i] == A[i+1])
                continue;
            
            if (odd) {
                dp[i+1][0] = bigger ? dp[i][0] + 1 : 1;
                dp[i+1][1] = bigger ? 1 : dp[i][1] + 1;
            } else {
                dp[i+1][0] = bigger ? 1 : dp[i][0] + 1;
                dp[i+1][1] = bigger ? dp[i][1] + 1 : 1;
            }
            
            ans = std::max(ans, std::max(dp[i+1][0], dp[i+1][1]));
        }
        
        return ans;
    }
    
    int doit1(vector<int>&& a) {
        
        int n = a.size();
        int up = 1, down = 1, res = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] > a[i-1]) {
                up = down + 1;
                down = 1;
            }
            else if (a[i] < a[i-1]) {
                down = up + 1;
                up = 1;
            }
            else {
                down = 1;
                up = 1;
            }
            res = std::max(res,std::max(up,down));
        }
        return res;
    }
};


void test_978_longest_turbulent_subarray() {
    
    auto res1 = MaxTurbulenceSize().doit(vector<int>{9,4,2,10,7,8,8,1,9});
    
    auto res2 = MaxTurbulenceSize().doit(vector<int>{4,8,12,16});
    
    auto res3 = MaxTurbulenceSize().doit(vector<int>{9, 9});
    
    return;
}

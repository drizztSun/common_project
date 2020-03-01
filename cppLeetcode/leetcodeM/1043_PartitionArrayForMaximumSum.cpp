/*
 1043. Partition Array for Maximum Sum
 
 Given an integer array A, you partition the array into (contiguous) subarrays of length at most K.
 After partitioning, each subarray has their values changed to become the maximum value of that subarray.

 Return the largest sum of the given array after partitioning.
 
 Example 1:

 Input: A = [1,15,7,9,2,5,10], K = 3
 Output: 84
 Explanation: A becomes [15,15,15,9,10,10,10]
  

 Note:

 1 <= K <= A.length <= 500
 0 <= A[i] <= 10^6
 
 */

#include <stdio.h>
#include <numeric>
#include <vector>
using std::vector;

class MaxSumAfterPartitioning {
public:
    int doit(vector<int>&& A, int K) {
        
        vector<int> dp(A.size() + 1, 0);
        
        for (int i = 0; i < A.size(); i++) {
        
            int maxv = 0;
            
            for (int j = 0; j < K; j++) {
                
                if (i - j >= 0) {
                    maxv = std::max(maxv, A[i-j]);
                    dp[i+1] = std::max(dp[i+1], dp[i-j] + maxv * (j + 1));
                }
            }
        }
        
        return dp[A.size()];
    }
    
    int doit1(vector<int>&& A, int K) {
        
        vector<int> dp (A.size(), 0);
        int max = A[A.size()-1];
        
        for (size_t i = A.size()-1; i >= A.size()-K && i >= 0; i--) {
            if (A[i] > max)
                max = A[i];
            dp[i] = max * (dp.size() - i);
        }
        
        for (size_t i = dp.size()-K-1; i >= 0; i--) {
            int ans = 0, curr_max = A[i];
            
            for (int j = 1; j <= K; j++) {
            
                int curr_ans = curr_max * j + dp[i+j];
                if (curr_ans > ans)
                    ans = curr_ans;
                
                if (A[i+j] > curr_max)
                    curr_max = A[i+j];
            }
            dp[i] = ans;
        }
        
        return dp[0];
    }
};

void test_1043_PartitionArrayForMaximumSum() {
    
    int res = MaxSumAfterPartitioning().doit(vector<int>{1,15,7,9,2,5,10}, 3);
    
    return;
}


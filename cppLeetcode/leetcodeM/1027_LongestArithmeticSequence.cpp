
/*
 
 # 1027. Longest Arithmetic Sequence

 # Given an array A of integers, return the length of the longest arithmetic subsequence in A.

 # Recall that a subsequence of A is a list A[i_1], A[i_2], ..., A[i_k] with 0 <= i_1 < i_2 < ... < i_k <= A.length - 1,
 # and that a sequence B is arithmetic if B[i+1] - B[i] are all the same value (for 0 <= i < B.length - 1).


 # Example 1:

 # Input: [3,6,9,12]
 # Output: 4
 # Explanation:
 # The whole array is an arithmetic sequence with steps of length = 3.

 # Example 2:

 # Input: [9,4,7,2,10]
 # Output: 3
 # Explanation:
 # The longest arithmetic subsequence is [4,7,10].

 # Example 3:

 # Input: [20,1,15,3,10,5,8]
 # Output: 4
 # Explanation:
 # The longest arithmetic subsequence is [20,15,10,5].
 
 */

#include <algorithm>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class LongestArithSeqLength {
    
public:
    
    // (DP)
    int doit_dp(vector<int>&& A) {
        
        unordered_map<int, size_t> indice;
        
        // dp[][] shows if A[i] and A[j] is in a sequence size, if they are in a sequence
        vector<vector<int>> dp(A.size(), vector<int>(A.size(), 2));
        int res = 2;
        
        for (size_t i = 0; i < A.size(); i++) {
            
            for (size_t j = i+1; j < A.size(); j++) {
                
                int target = 2*A[i] - A[j];
                size_t cnt = indice.count(target);
                if (cnt > 0 && indice[target] < i) {
                    
                    dp[i][j] = std::max(dp[i][j], dp[indice[target]][i] + 1);
                    res = std::max(res, dp[i][j]);
                }
            }
            
            indice[A[i]] = i;
        }
        
        return res;
    }
    
    // (DP)
    int doit_dp_1(vector<int>&& A) {
        int res = 2;
        unordered_map<size_t, unordered_map<int, int>> dp;
        
        for (size_t i = 0; i < A.size(); i++) {
            
            for (size_t j = 0; j < i; j++) {
                
                int k = A[i] - A[j];
                
                if (dp[j].count(k) == 0) {
                    dp[j][k] = 1;
                }
                
                dp[i][k] = std::max(dp[i][k], dp[j][k] + 1);
                
                res = std::max(res, dp[i][k]);
            }
        }
        
        return res;
    }
};


void test_1027_Longest_Arithmetic_Sequence() {
    
    auto res1 = LongestArithSeqLength().doit(vector<int>{3,6,9,12});
    
    auto res2 = LongestArithSeqLength().doit(vector<int>{9,4,7,2,10});
    
    auto res3 = LongestArithSeqLength().doit(vector<int>{20,1,15,3,10,5,8});
    
    return;
}

/*
 
 903. Valid Permutations for DI Sequence
 
 We are given S, a length n string of characters from the set {'D', 'I'}. (These letters stand for "decreasing" and "increasing".)

 A valid permutation is a permutation P[0], P[1], ..., P[n] of integers {0, 1, ..., n}, such that for all i:

 If S[i] == 'D', then P[i] > P[i+1], and;
 If S[i] == 'I', then P[i] < P[i+1].
 How many valid permutations are there?  Since the answer may be large, return your answer modulo 10^9 + 7.

  

 Example 1:

 Input: "DID"
 Output: 5
 Explanation:
 The 5 valid permutations of (0, 1, 2, 3) are:
 (1, 0, 3, 2)
 (2, 0, 3, 1)
 (2, 1, 3, 0)
 (3, 0, 2, 1)
 (3, 1, 2, 0)

 */

#include <string>
using std::string;

#include <vector>
using std::vector;


class NumPermsDISequence {
    
    
    int search(string& s, int i, int j, vector<vector<int>>& dp) {
        if (!(j >= 0 && j <= i)) {
            return 0;
        }
        
        if (dp[i][j] != 0) {
            return dp[i][j];
        }
        
        if (i == 0) {
            return 1;
        }
        
        int mod = 1000000007;
        if (s[i-1] == 'D') {
            dp[i][j] = (search(s, i, j+1, dp) + search(s, i-1, j, dp)) % mod;
        } else {
            dp[i][j] = (search(s, i, j-1, dp) + search(s, i-1, j-1, dp)) % mod;
        }
        
        return dp[i][j];
    }
      
public:

    int doit(string S) {
        
        int N = S.size();
        vector<vector<int>> dp(N+1, vector<int>(N+1, 0));
        int MOD = 1000000007;
        int res = 0;
        
        for (int i = N; i>-1; i--) {
            res = (res + search(S, N, i, dp)) % MOD;
        }
        
        return res;
    }
};

void test_903_valid_permutations_for_di_sequence() {
    
    NumPermsDISequence().doit("IDDDIIDIIIIIIIIDIDID");
    
    NumPermsDISequence().doit("DID");
    
}

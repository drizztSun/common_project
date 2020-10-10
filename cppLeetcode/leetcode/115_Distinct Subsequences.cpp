/*
 115. Distinct Subsequences
 
 Given a string S and a string T, count the number of distinct subsequences of S which equals T.

 A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters
 without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

 It's guaranteed the answer fits on a 32-bit signed integer.

 Example 1:

 Input: S = "rabbbit", T = "rabbit"
 Output: 3
 Explanation:
 As shown below, there are 3 ways you can generate "rabbit" from S.
 (The caret symbol ^ means the chosen letters)

 rabbbit
 ^^^^ ^^
 rabbbit
 ^^ ^^^^
 rabbbit
 ^^^ ^^^
 Example 2:

 Input: S = "babgbag", T = "bag"
 Output: 5
 Explanation:
 As shown below, there are 5 ways you can generate "bag" from S.
 (The caret symbol ^ means the chosen letters)

 babgbag
 ^^ ^
 babgbag
 ^^    ^
 babgbag
 ^    ^^
 babgbag
   ^  ^^
 babgbag
     ^^^
 */

#include <stdio.h>
#include <vector>
#include <string>


using std::vector;
using std::string;

class NumDistinct {
    
    
public:
    
    int doit_dp(string s, string t) {
        
        auto M = s.length(), N = t.length();
        
        vector<long long> dp(M+1, 1);
        
        
        for (auto i = 1; i <= N; i++) {
            
            vector<long long> lastdp(dp.begin(), dp.end());
            dp[0] = 0;
            
            for (auto j = 1; j <= M; j++) {
                
                dp[j] = dp[j-1];
                
                if (s[j-1] == t[i-1]) {
                    dp[j] += lastdp[j-1];
                }
            }
        }
        
        return dp[M];
    }
    
    int doit_dp_1(string s, string t) {
        auto M = s.length(), N = t.length();
        vector<vector<long long>> dp(N+1, vector<long long>(M+1, 0));
        
        for (int i = 0; i <= M; i++) {
            dp[0][i] = 1;
        }
        
        for (int i = 1; i <= N; i++) {
            
            for (int j = 1; j <= M; j++) {
                // dp[i][j-1]  if don't put s[j] into sequnce
                // if s[j-1] == t[i-1], it could put it into sequence, because they are equal.
                dp[i][j] = dp[i][j-1] + (s[j-1] == t[i-1] ? dp[i-1][j-1] : 0);
            }
        }
        
        return dp[N][M];
    }
};

void test_115_distinct_subsequence() {
    
    NumDistinct().doit_dp_1("rabbbit", "rabbit");
}

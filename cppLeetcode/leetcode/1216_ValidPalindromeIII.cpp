/*
 1216. Valid Palindrome III
 
 
 Given a string s and an integer k, find out if the given string is a K-Palindrome or not.

 A string is K-Palindrome if it can be transformed into a palindrome by removing at most k characters from it.

  

 Example 1:

 Input: s = "abcdeca", k = 2
 Output: true
 Explanation: Remove 'b' and 'e' characters.
  

 Constraints:

 1 <= s.length <= 1000
 s has only lowercase English letters.
 1 <= k <= s.length
 
 */
#include<string>
#include<vector>

using std::string;
using std::vector;

class ValidPalindrome {

public:
    
    bool doit_dp(string s, int k) {
        
        auto n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        
        for (auto length = 0; length < n; length++) {
            
            
            for (auto i = 0; i < n - length; i++) {
                
                auto j = i + length;
                
                if (i == j)
                    dp[i][j] = 1;
                else {
                    dp[i][j] = std::max(dp[i+1][j], dp[i][j-1]);
                    if (s[i] == s[j]) {
                        dp[i][j] = std::max(dp[i+1][j-1] + 2, dp[i][j]);
                    }
                }
            }
        }
        
        return dp[0][n-1] >= n - k;
    }
};

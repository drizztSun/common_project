/*
 
 132. Palindrome Partitioning II
 
 Given a string s, partition s such that every substring of the partition is a palindrome.

 Return the minimum cuts needed for a palindrome partitioning of s.

  

 Example 1:

 Input: s = "aab"
 Output: 1
 Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
 Example 2:

 Input: s = "a"
 Output: 0
 Example 3:

 Input: s = "ab"
 Output: 1

 */
#include <vector>
#include <string>

using std::string;
using std::vector;


class MinCut {
public:
    int doit_dp(string s) {
        
        if (s.empty())
            return 0;
        
        int L = s.length();
        
        // dp[i] minimum partition s[i:], dp[0] is the result
        vector<int> dp(L+1);
        for (auto i = 0; i < L+1; i++) {
            dp[i] = L - i;
        }
        
        // Partitions[i][j] is s[i:j+1]
        vector<vector<bool>> partitions(L, vector<bool>(L, false));
        
        for (auto i = L-1; i >=0; i--) { // from s[i:]
            
            for (auto j = i; j < L; j++) { // check s[i:j]
                
                if (s[i] == s[j] && (j - i < 2 || partitions[i+1][j-1])) {
                    
                    partitions[i][j] = true;
                    
                    dp[i] = std::min(1 + dp[j+1], dp[i]);
                }
            }
        }
            
        return dp[0] - 1;
    }
    
    int doit_dp_1(string s) {
        
        auto L = s.length();
        
        if (L == 0)
            return 0;
            
        vector<int> dp(L+1);
        for (auto i = 0; i <= L; i++) {
            dp[i] = i+1;
        }
        
        vector<vector<bool>> partitions(L, vector<bool>(L, false));
        
        for (auto i = 0; i < L; i++) {
            
            for (auto j = i; j >= 0; j--) {
                
                if (s[i] == s[j] && (i - j < 2 || partitions[j+1][i-1])) {
                    partitions[j][i] = true;
                    dp[i+1] = std::min(1+dp[j-1], dp[i+1]);
                }
            }
        }
        
        return dp[L] - 1;
    }
};


void test_132_PalindromePartitional() {
    
    MinCut().doit_dp_1("aab");
}

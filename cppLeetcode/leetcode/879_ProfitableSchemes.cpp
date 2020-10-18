/*
 879. Profitable Schemes
 
 There is a group of G members, and a list of various crimes they could commit.

 The ith crime generates a profit[i] and requires group[i] members to participate in it.

 If a member participates in one crime, that member can't participate in another crime.

 Let's call a profitable scheme any subset of these crimes that generates at least P profit, and the total number of members participating in that subset of crimes is at most G.

 How many schemes can be chosen?  Since the answer may be very large, return it modulo 10^9 + 7.

  

 Example 1:

 Input: G = 5, P = 3, group = [2,2], profit = [2,3]
 Output: 2
 Explanation:
 To make a profit of at least 3, the group could either commit crimes 0 and 1, or just crime 1.
 In total, there are 2 schemes.
 Example 2:

 Input: G = 10, P = 5, group = [2,3,5], profit = [6,7,8]
 Output: 7
 Explanation:
 To make a profit of at least 5, the group could commit any crimes, as long as they commit one.
 There are 7 possible schemes: (0), (1), (2), (0,1), (0,2), (1,2), and (0,1,2).
  

 Note:

 1 <= G <= 100
 0 <= P <= 100
 1 <= group[i] <= 100
 0 <= profit[i] <= 100
 1 <= group.length = profit.length <= 100
 */
#include <vector>

using std::vector;

class ProfitableSchemes {
    
public:
    int doit_dp(int G, int P, vector<int>& group, vector<int>& profit) {
    
        vector<vector<int>> dp(G+1, vector<int>(P+1, 0));
        dp[0][0] = 1;
        int res = 0;
        int mod = 1e9 + 7;
        
        for (auto i = 0; i < group.size(); i++) {
            int g = group[i], p = profit[i];
            
            for (auto j = P; j >= 0; j--) {
                
                for (auto k = G - g; k >= 0; k--) {
                 
                    dp[k+g][std::min(j + p, P)] = (dp[k+g][std::min(j + p, P)] + dp[k][j]) % mod;
                }
            }
            
        }
        
        for (auto i = 1; i <= G; i++) {
            res = (res + dp[i][P]) % mod;
        }
        return res;
    }
};

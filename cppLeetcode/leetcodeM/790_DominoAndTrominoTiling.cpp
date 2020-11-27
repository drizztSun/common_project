/*
 
 790. Domino and Tromino Tiling
 
 
 We have two types of tiles: a 2x1 domino shape, and an "L" tromino shape. These shapes may be rotated.

 XX  <- domino

 XX  <- "L" tromino
 X
 Given N, how many ways are there to tile a 2 x N board? Return your answer modulo 10^9 + 7.

 (In a tiling, every square must be covered by a tile. Two tilings are different if and only if
 there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.)

 Example:
 Input: 3
 Output: 5
 Explanation:
 The five different ways are listed below, different letters indicates different tiles:
 XYZ XXZ XYY XXY XYY
 XYZ YYZ XZZ XYY XXY
 Note:

 N  will be in range [1, 1000].
 
 */
#include <vector>


using std::vector;


class DominoAndTrominoTilling {
    
    
    
public:
    
    /*
     
     dp[i][0]: ways to cover i cols, both rows of col i are covered
     dp[i][1]: ways tp cover i cols, top row of col i is covered
     dp[i][2]: ways to cover i cols, bottom row of col i is covered

     init dp[0][0] = dp[1][0] = 1

     dp[i][0] = dp[i-1][0] + dp[i-2][0] + dp[i-1][1] + dp[i-1][2]
     dp[i][1] = dp[i-2][0] + dp[i-1][2]
     dp[i][2] = dp[i-2][0] + dp[i-1][1]


     dp[i][1] is always equals to dp[i][2], we can simplify

     dp[i][0] = dp[i-1][0] + dp[i-2][0] + 2 * dp[i-1][1]
     dp[i][1] = dp[i-2][0] + dp[i-1][1]
     
     */
    
    int doit_dp(int N) {
        
        constexpr int kmod = 1e9 + 7;
        vector<vector<long>> dp(N+1, vector<long>(3, 0));
        
        dp[0][0] = dp[1][0] = 1;
        
        for (auto i = 2; i <= N; i++) {
            dp[i][0] = (dp[i-1][0] + dp[i-2][0] + dp[i-1][1] * 2) % kmod;
            dp[i][1] = (dp[i-1][2] + dp[i-2][0]) % kmod;
            dp[i][2] = (dp[i-1][1] + dp[i-2][0]) % kmod;
        }
        
        return dp[N][0];
    }
    
    int doit_dp_1(int N) {
        
        // Since dp[i][1] always equals to dp[i][2], we can simplify a bit.
        
        constexpr int kMod = 1000000007;
        vector<vector<long>> dp(N + 1, vector<long>(2, 0));
        dp[0][0] = dp[1][0] = 1;
        for (int i = 2; i <= N; ++i) {
          dp[i][0] = (dp[i - 1][0] + dp[i - 2][0] + 2 * dp[i - 1][1]) % kMod;
          dp[i][1] = (dp[i - 2][0] + dp[i - 1][1]) % kMod;
        }
        
        return dp[N][0];
    }
    
    /*
     Another way to think about this problem

     define: dp[i] ways to completely covert the i*2 board.

     dp[0] = 1 # {}
     dp[1] = 1 # {|}
     dp[2] = 2 # {||, =}
     dp[3] = 5 # {|||, |=, =|, ⌊⌉, ⌈⌋} = dp[2] ⊗ {|} + dp[1] ⊗ {=} + dp[0] ⊗ {⌊⌉, ⌈⌋}
     dp[4] = 11 # dp[3] ⊗ {|} + dp[2] ⊗ {=} + dp[1] ⊗ {⌊⌉, ⌈⌋} + dp[0] ⊗ {⌊¯⌋,⌈_⌉}
     dp[5] = 24 # dp[4] ⊗ {|} + dp[3] ⊗ {=} + 2*(dp[2] + dp[1] + dp[0])
     ...
     dp[n] = dp[n-1] + dp[n-2] + 2*(dp[n-3] + ... + dp[0])
           = dp[n-1] + dp[n-3] + [dp[n-2] + dp[n-3] + 2*(dp[n-4] + ... + dp[0])]
           = dp[n-1] + dp[n-3] + dp[n-1]
           = 2*dp[n-1] + dp[n-3]
     */
    
    int doit_dp_2(int N) {
      constexpr int kMod = 1000000007;
      vector<long> dp(N + 1, 1);
      dp[2] = 2;
      for (int i = 3; i <= N; ++i)
        dp[i] = (dp[i - 3] + dp[i - 1] * 2) % kMod;
      return dp[N];
    }
};

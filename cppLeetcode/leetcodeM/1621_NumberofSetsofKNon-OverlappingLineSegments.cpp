/*
 1621. Number of Sets of K Non-Overlapping Line Segments
 
 
 Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x = i, find the number of ways we can draw exactly k non-overlapping line segments
 such that each segment covers two or more points. The endpoints of each segment must have integral coordinates.
 
 The k line segments do not have to cover all n points, and they are allowed to share endpoints.

 Return the number of ways we can draw k non-overlapping line segments. Since this number can be huge, return it modulo 109 + 7.

  

 Example 1:


 Input: n = 4, k = 2
 Output: 5
 Explanation:
 The two line segments are shown in red and blue.
 The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)}, {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.
 Example 2:

 Input: n = 3, k = 1
 Output: 3
 Explanation: The 3 ways are {(0,1)}, {(0,2)}, {(1,2)}.
 Example 3:

 Input: n = 30, k = 7
 Output: 796297179
 Explanation: The total number of possible ways to draw 7 line segments is 3796297200. Taking this number modulo 109 + 7 gives us 796297179.
 Example 4:

 Input: n = 5, k = 3
 Output: 7
 Example 5:

 Input: n = 3, k = 2
 Output: 1
  

 Constraints:

 2 <= n <= 1000
 1 <= k <= n-1

 
 */
#include <stdio.h>
#include <vector>

using std::vector;



class NumberOfSetsOfKthNonOverlappingLineSegments {
    
    
public:
    
    /*
    // TLE O(n^2*k)
     
        DP1: dp(n, k) := # of k segements s=using n points
        
        base case:
        1) dp(n, 1) = C(n, 2) = n * (n - 1) / 2
        2) dp(n, k) = 1 if k == n- 1
        3) dp(n, k) = 0 if k >= n
     
     Transition:
     Enumerate all possible spilit point i. Use first i points for one segement, the rest of n-i+1 points
     for a subproblem of (k-1) segemetns.
     
     dp(n, k) = sum((i-1) * dp(n - i + 1, k - 1)) (2 <= i <= n - k + 1)
     
     Ans = dp(N, K)
     States: n*k, each state takes O(n) Time.
     Time complexity: O(n^2 * k)
     Space complexity: O(k)
     
     
    */
    int doit_dp_TLE(int N, int K) {
        
        constexpr int kMod = 1e9 + 7;
        vector<vector<int>> cache(N + 1, vector<int>(K + 1));
        
        std::function<int(int, int)> dp = [&](int n, int k) {
            
          if (k >= n) return 0;
          if (k == 1) return n * (n - 1) / 2;
          if (k == n - 1) return 1;
          
          int& ans = cache[n][k];
          if (ans)
              return ans;
        
          // 1 - i, one segment, i is the right end, can't pick 2--3, because i = 3 will be duplicate, because i = 4 also can have 2--3.
          // n - i + 1 points, k - 1 segments. i could be the left end if one segemets of (k-1) segements
          for (long i = 2; i < n; ++i) {
            const int t = ((i - 1) * dp(n - i + 1, k - 1)) % kMod;
            ans = (ans + t) % kMod;
          }
            
          return ans;
        };
        
        return dp(N, K);
    }
    
    /*
     
     DP2: dp(n, k) := # of k segments using n points
     Base case:
         dp(n, 0) = 1
         
     Transition:
     # case 1: k-1 segments in 1--i, put kth one segemnt from i--n, if we use n as most right pointts
     # case 2: put k segment from 1 --> n-1, left n points useless. so recursive case 2, it means we left some points in right side free.
     
     dp(n, k) = sum(dp(i, k-1)) + dp(n-1, k),  1 <= i < n - k
     Ans = dp(N, K)
     
     Can use bottom up + prefix sum to reduce the time complexity from O(n**2 * k) + O(n, k)
     
     Time complexity: O(nk)
     
     Space complexity: O(nk)
     */
    
    int doit_dp(int N, int K) {
        
        int kMod = 1e9 + 7;
        
        vector<vector<int>> dp(N+1, vector<int>(K+1, 0));
        
        for (int i = 0; i <= N; i++)
            dp[i][0] = 1;
        
        for (int j = 1; j <= K; j++) {
            
            int s = 0;
            for (int i = 1; i <= N; i++) {
                
                dp[i][j] = (s + dp[i-1][j]) % kMod;
                s = (s + dp[i][j-1]) % kMod;
                
            }
            
        }
        
        return dp[N][K];
    }
    
};

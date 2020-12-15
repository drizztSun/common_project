/*
 1563. Stone Game V
 
 There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.

 In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right row), then Bob calculates the value of each row which is the sum of the values of all the stones in this row.
 Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away.
 The next round starts with the remaining row.

 The game ends when there is only one stone remaining. Alice's is initially zero.

 Return the maximum score that Alice can obtain.

  

 Example 1:

 Input: stoneValue = [6,2,3,4,5,5]
 Output: 18
 Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14. Bob throws away the right row and Alice's score is now 11.
 In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
 The last round Alice has only one choice to divide the row which is [2], [3]. Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.
 Example 2:

 Input: stoneValue = [7,7,7,7,7,7,7]
 Output: 28
 Example 3:

 Input: stoneValue = [4]
 Output: 0
  

 Constraints:

 1 <= stoneValue.length <= 500
 1 <= stoneValue[i] <= 10^6
 
 
 */

#include <stdio.h>
#include <vector>

using std::vector;


class StoneGameV {
    
public:
    
    /*
     Q: What if I don't know the optimal partition?
     A: Try all possible partitions
     
     dp(l, r)  := max score Alice can get from range [l, r]
     
     base case : l == r: return 0
     
     Try all possible k (l <= k < r)
     l, l+1, ...,    k, k+1,    ..., r-1, r
     sum_l = sum(l~k)       sum_r = sum(k+1, r)
     
     dp(l, r) = max {
     
        sum_l + dp(l, k), if sum_l < sum_r,
        
        sum_r + dp(k+1, r), if sum_r < sum_l,
     
        sum_l + max(dp(l, k), dp(k+1, r)) if sum_r == sum_l
     
     } for k in range[l, r)
     
     ans = dp(0, n-1)
    
     Time complexity: O(n^2) * O(n) = O(n^3)
     Space complexity: O(n^2)
     */
    
    int doit_dp(vector<int>& stoneValue) {
        
        int N = stoneValue.size();
        vector<int> sums(N+1);
        for (int i = 0; i < N; i++) {
            sums[i+1] = stoneValue[i] + sums[i];
        }
        
        vector<vector<int>> cache(N, vector<int>(N, -1));
        
        std::function<int(int, int)> dp = [&](int l, int r) -> int {
            
            if (l >= r)
                return 0;
            
            if (cache[l][r] != -1)
                return cache[l][r];
            
            int ans = 0;
            for (int k = l; k < r; k++) {
                
                int sum_l = sums[k+1] - sums[l], sum_r = sums[r+1] - sums[k+1];
                
                if (sum_l > sum_r)
                    ans = std::max(ans, sum_r + dp(k+1, r));
                else if (sum_l < sum_r)
                    ans = std::max(ans, sum_l + dp(l, k));
                else
                    ans = std::max(ans, sum_l + std::max(dp(l, k), dp(k+1, r)));
            }
            
            return cache[l][r] = ans;
        };
        
        return dp(0, N-1);
    }
    
    /*
     
     O(n^3)

     Basic approach
     dp[i][j]: max score you can obtain from stones[i..j]
     sum[i][j]: sum of stoneValues[i..j]
     Try all possible k i.e. k goes from i to j-1:
     we have 2 choices for score: sum[i][k] + dp[i][k] and sum[k+1][j] + dp[k+1][j]
     but we can only pick the side where sum is smaller or either of them when both sides are equal.
     Take the maximum score from all of these choices and we have computed dp[i][j].
     In all my codes, I am building the dp table bottom-up i.e. dp[0][1], dp[1][2] gets calculated before dp[0][2].
     
     */
    int doit_dp_1(vector<int>&& stoneValue) {

        int N = stoneValue.size();
        vector<int> sums(N+1);

        for (int i = 0; i < N; i++) {
            sums[i+1] = stoneValue[i] + sums[i];
        }
        
        vector<vector<int>> dp(N, vector<int>(N));
       
        for (int L = 1; L < N; L++) {
            
            for (int i = 0; i < N-L; i++) {
                
                int j = i + L;
                
                int ans = 0;
                
                for (int k = i; k < j; k++) {
                    
                    int left = sums[k+1] - sums[i], right = sums[j+1] - sums[k+1];
                    
                    if (left < right)
                        ans = std::max(ans, left + dp[i][k]);
                    
                    else if (left > right)
                        ans = std::max(ans, right + dp[k+1][j]);
                    
                    else
                        ans = std::max(ans, left + std::max(dp[i][k], dp[k+1][j]));
                }
                
                dp[i][j] = ans;
            }
        }
        
        return dp[0][N-1];
    }
    
    
    /*
     
     O(n^2 log n)

     Optimization
     As k goes from i to j in stones[i..j], sum of left part sum[i][k] increases continuously and it remains a valid subarray for our consideration for calculating dp[i][j] until the point when it becomes greater than right half.
     From that point onwards, all the right ones are valid subarrays for consideration. We can find this critical k (= k') using binary search. Forget about boundary cases and equal halves etc for now, just try to understand the general idea.

     dp[i][j] = max( max(sum[i][k] + dp[i][k]) for k: i to k', max(sum[k][j] + dp[k][j]) for k: k'+1 to j )
     (refer to the code for exact condition for all cases)

     If we have to calculate first and second terms in above by iterating from k: i to k' or k: k'+1 to j, then it'd take O(n) time and we are back to first solution.
     
     What we can instead do is maintain 2 more arrays defined as:
     left[i][j] = max( sum[i][k] + dp[i][k] for k: i to j )
     right[i][j] = max( sum[k][j] + dp[k][j] for k: i to j )

     and use them to redefine dp[i][j] = max( left[i][k'], right[k'+1][j] )

     Note that left and right arrays can also be calculated along with dp table so they don't increase our worst case time complexity.

     left[i][j] = max( left[i][j-1], sum[i][j] + dp[i][j] )
     right[i][j] = max( right[i+1][j], sum[i][j] + dp[i][j] )

     With these ideas in mind and taking care of boundary cases like k' == i or k' == j and equal halves etc, we have our solution ready.
     
     */
    
    int doit_dp_binary_search(vector<int>& stoneValue) {
        
        int N = stoneValue.size();
        vector<int> presum(N+1);
        for (int i =0; i < N; i++)
            presum[i+1] = presum[i] + stoneValue[i];
        
        vector<vector<int>> dp(N, vector<int>(N));
        vector<vector<int>> left(N, vector<int>(N));
        vector<vector<int>> right(N, vector<int>(N));
        
        for (int i = 0; i < N; i++) {
            left[i][i] = right[i][i] = stoneValue[i];
        }
        
        auto search = [&](int l, int r) {
            
            int total = presum[r+1] - presum[l], L = l;
            
            while (l < r) {
                
                int mid = (l + r) / 2;
                
                if ((presum[mid+1] - presum[L]) * 2 >= total) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
          
            return l;
        };
        
        for (int L = 1; L < N; L++) {
            
            for (int i = 0; i < N-L; i++) {
                
                int j = i + L;
                int k = search(i, j);
                int total = presum[j+1] - presum[i], leftpart = presum[k+1] - presum[i];
                
                if (2 * leftpart == total) {
                    dp[i][j] = std::max(left[i][k], right[k+1][j]);
                    
                } else {
                    dp[i][j] = std::max(k == i ? 0: left[i][k-1], k == j ? 0 : right[k+1][j]);
                }
                
                left[i][j] = std::max(left[i][j-1], total + dp[i][j]);
                right[i][j] = std::max(right[i+1][j], total + dp[i][j]);
            }
        }
        
        return dp[0][N-1];
    }
     
    
    
    /*
     
     O(n^2)

     Optimization
     We can optimize the previous solution even further by getting rid of the binary search step needed to find the critical k (= k') of stones[i..j].
     Binary search is great when we need the answer for arbitrary i and j but why not calculate dp[i][j] in such an order where we could leverage the k' information from previous i and j.

     Suppose we know the k' for stones[i..j], what do we know about k' for stones[i..j+1]? It is either the same or it got shifted a few places to the right.
     And so if we calculate dp values in the order: dp[i][i], dp[i][i+1], dp[i][i+2], ..., dp[i][j], we can essentially keep track of k' as we go within that same linear time bound.

     Using this idea, we implement the final solution. Couple of pointers about my code:

     1) mid: represents k' or first index such that left half >= right half
     2) with i < j, max[i][j] represents left[i][j] of previous solution i.e. max(dp[i][i], dp[i][i+1], dp[i][i+2] .. dp[i][j]) and max[j][i] represents right[i][j] of previous solution i.e.
                max(dp[i][j], dp[i+1][j], dp[i+2][j] .. dp[j][j]). We could have used two different arrays left and right just like previous solution but this trick saves space.
     3) I am traversing in the order: dp[j][j], dp[j-1,j], dp[j-2, j], .., dp[i][j] instead of the above mentioned order but the idea remains same.

     
     */
    
    int doit_dp_3(vector<int>& stoneValue) {
        
        int N = stoneValue.size();
        vector<vector<int>> dp(N, vector<int>(N));
        vector<vector<int>> maxv(N, vector<int>(N));
        
        for (int i = 0; i < N; i++) {
            maxv[i][i] = stoneValue[i];
        }
        
        for (int j = 1; j < N; j++){
        
            int mid = j, sums = stoneValue[j], rightHalf = 0;
        
            for (int i = j-1; i >= 0; i--) {
                
                sums += stoneValue[i];
                
                while ((rightHalf + stoneValue[mid]) * 2 <= sums) {
                    rightHalf += stoneValue[mid--];
                }
                
                dp[i][j] = rightHalf * 2 == sums ? maxv[i][mid] : (mid == i ? 0 : maxv[i][mid - 1]);
                dp[i][j] = std::max(dp[i][j], mid == j ? 0 : maxv[j][mid+1]);
            
                maxv[i][j] = std::max(maxv[i][j-1], dp[i][j] + sums);
                maxv[j][i] = std::max(maxv[j][i+1], dp[i][j] + sums);
            }
        }
        
        return dp[0][N-1];
    }
    
    
public:

      int D[505][505];
      int D2[505][505];
      int D3[505][505];
      int midPoint[505][505];
      int sum[505][505];
  
  int stoneGameV(vector<int>& stoneValue) {
    int N = stoneValue.size();
    for (int i = 1; i <= N; i++) {
      sum[i][i] = stoneValue[i - 1];
      for (int j = i + 1; j <= N; j++) {
        sum[i][j] = sum[i][j - 1] + stoneValue[j - 1];
      }
    }
    
    for (int i = 1; i <= N; i++) {
      midPoint[i][i] = i - 1;
      int p = midPoint[i][i];
      for (int j = i + 1; j <= N; j++) {
        while (sum[i][p + 1] <= sum[p + 2][j]) {
          ++p;
        }
        midPoint[i][j] = p;
      }
    }
    
    for (int i = N; i >= 1; i--) {
      D[i][i] = stoneValue[i - 1];
      D2[i][i] = stoneValue[i - 1];
      D3[i][i] = stoneValue[i - 1];
      
      for (int j = i + 1; j <= N; j++) {
        
        int p = midPoint[i][j];
        
        if (sum[i][p] == sum[p + 1][j]) {
          D[i][j] = std::max(D2[i][p], D3[p + 1][j]);
        } else {
          D[i][j] = std::max(D2[i][p], D3[p + 2][j]);
        }
        D[i][j] += sum[i][j];
        
        D2[i][j] = std::max(D2[i][j - 1], D[i][j]);
        D3[i][j] = std::max(D3[i + 1][j], D[i][j]);
      }
    }
    
    return D[1][N] - sum[1][N];
  }
};



void test_1563_stone_game_v() {
        
    StoneGameV().doit_dp_1(vector<int>{6, 2, 3, 4, 5, 5});
    
}

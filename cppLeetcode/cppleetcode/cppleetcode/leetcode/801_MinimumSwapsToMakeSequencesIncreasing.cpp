// 801. Minimum Swaps To Make Sequences Increasing

/*
 We have two integer sequences A and B of the same non-zero length.

 We are allowed to swap elements A[i] and B[i].  Note that both elements are in the same index position in their respective sequences.

 At the end of some number of swaps, A and B are both strictly increasing.  (A sequence is strictly increasing if and only if A[0] < A[1] < A[2] < ... < A[A.length - 1].)

 Given A and B, return the minimum number of swaps to make both sequences strictly increasing.  It is guaranteed that the given input always makes it possible.

 Example:
 Input: A = [1,3,5,4], B = [1,2,3,7]
 Output: 1
 Explanation:
 Swap A[3] and B[3].  Then the sequences are:
 A = [1, 3, 5, 7] and B = [1, 2, 3, 4]
 which are both strictly increasing.
 Note:

 A, B are arrays with the same length, and that length will be in the range [1, 1000].
 A[i], B[i] are integer values in the range [0, 2000].
 */

#include <vector>

using namespace std;

class MinSwap {
public:
    int doit(vector<int>&& A, vector<int>&& B) {
        
        vector<vector<int>> dp(2);
        // dp[0][i]: min# of swapping if not swapping at i-th position
        // dp[1][i]: same as above, but swapping at i-th position
        dp[0] = vector<int>(A.size(), 2000);
        dp[1] = vector<int>(A.size(), 2000);
        
        // boundary cond
        dp[0][0] = 0;
        dp[0][0] = 1;
        
        for (int i = 1; i < A.size(); i++) {
            
            if (A[i] < A[i-1] || B[i] < B[i-1]) {
                // must swap once at i-1 or i
                dp[0][i] = dp[1][i-1];
                dp[1][i] = dp[0][i-1] + 1;
            }
            else if ( A[i] < B[i-1] || B[i] < A[i-1]) {
                // must swap i-1, i together
                dp[0][i] = dp[0][i-1];
                dp[1][i] = dp[i][i-1] + 1;
            } else {
                // Ai, Bi > A_{i-1}, B_{i-1}, free to swap :)
                dp[0][i] = min(dp[0][i-1], dp[1][i-1]);
                dp[1][i] = dp[0][i] + 1;
            }
        }
        
        return min(dp[0].back(), dp[1].back());
    }
};

void Test_801_MiniumSwapToMakeSequenceIncreasing() {
    
    int res = MinSwap().doit(vector<int>{1, 3, 5, 4}, vector<int>{1, 2, 3, 7});
}

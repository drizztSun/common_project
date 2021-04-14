/*
1824. Minimum Sideway Jumps

There is a 3 lane road of length n that consists of n + 1 points labeled from 0 to n. A frog starts at point 0 in the second lane and wants to jump to point n. However, there could be obstacles along the way.

You are given an array obstacles of length n + 1 where each obstacles[i] (ranging from 0 to 3) describes an obstacle on the lane obstacles[i] at point i. If obstacles[i] == 0, there are no obstacles at point i. There will be at most one obstacle in the 3 lanes at each point.

For example, if obstacles[2] == 1, then there is an obstacle on lane 1 at point 2.
The frog can only travel from point i to point i + 1 on the same lane if there is not an obstacle on the lane at point i + 1. To avoid obstacles, the frog can also perform a side jump to jump to another lane (even if they are not adjacent) at the same point if there is no obstacle on the new lane.

For example, the frog can jump from lane 3 at point 3 to lane 1 at point 3.
Return the minimum number of side jumps the frog needs to reach any lane at point n starting from lane 2 at point 0.

Note: There will be no obstacles on points 0 and n.

 

Example 1:


Input: obstacles = [0,1,2,3,0]
Output: 2 
Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps (red arrows).
Note that the frog can jump over obstacles only when making side jumps (as shown at point 2).
Example 2:


Input: obstacles = [0,1,1,3,3,0]
Output: 0
Explanation: There are no obstacles on lane 2. No side jumps are required.
Example 3:


Input: obstacles = [0,2,1,0,3,0]
Output: 2
Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps.
 

Constraints:

obstacles.length == n + 1
1 <= n <= 5 * 105
0 <= obstacles[i] <= 3
obstacles[0] == obstacles[n] == 0
*/
#include <vector>
using std::vector;


class MinSideJumps {


public:

    /*
        Explanation
        dp[0] = minimum jump to reach lane 1
        dp[1] = minimum jump to reach lane 2
        dp[2] = minimum jump to reach lane 3
        If meet a stone, set its dp[i] to infinity.
        result equals to min(dp)


        Complexity
        Time O(n)
        Space O(1)
    */
    int doit_dp(vector<int>& A) {
        int dp[] = {1, 0, 1};
        for (int a: A) {
            
            if (a > 0) dp[a - 1] = 1e6;
            
            for (int i = 0; i < 3; ++i)
                if (a != i + 1)
                    dp[i] = std::min(dp[i], std::min(dp[(i + 1) % 3], dp[(i + 2) % 3]) + 1);
        }
        return std::min({dp[0], dp[1], dp[2]});
    }

    int doit_dp(vector<int>& obstracles) {

        const int n = obstracles.size();
        vector<vector<int>> dp(3, vector<int>(n, INT_MAX/2));
        dp[0][0] = 1, dp[1][0] = 0, dp[2][0] = 1;

        for (int i = 1; i < n; i++) {

            for (int k = 0; k < 3; k++)
                if (obstracles[i] != k+1) dp[k][i] = dp[k][i-1];

            for (int k = 0; k < 3; k++) {

                if (obstracles[i] != k+1)
                    dp[k][i] = std::min({dp[k][i], dp[(k+1)%3][i]+1, dp[(k+2)%3][i]+1});
            }
        }

        return std::min({dp[0].back(), dp[1].back(), dp[2].back()});
    }

    int doit_dp(vector<int>& obstracles) {
        
        const int n = obstracles.size();
        
        vector<vector<int>> dp(n+1, vector<int>(3, INT_MAX/2));
        dp[0][0] = 1, dp[0][1] = 0, dp[0][2] = 1;
        
        for (int i = 1; i < dp.size(); i++) {
            
            if (obstracles[i-1] == 0) {
                dp[i][0] = std::min(dp[i-1][0], std::min(dp[i-1][1], dp[i-1][2])+1);
                dp[i][1] = std::min(dp[i-1][1], std::min(dp[i-1][0], dp[i-1][2])+1);
                dp[i][2] = std::min(dp[i-1][2], std::min(dp[i-1][1], dp[i-1][0])+1); 
            } else if (obstracles[i-1] == 1) {
                dp[i][1] = dp[i-1][1], dp[i][2] = dp[i-1][2];
                dp[i][1] = std::min(dp[i][1], dp[i][2]+1);
                dp[i][2] = std::min(dp[i][2], dp[i][1]+1);
            } else if (obstracles[i-1] == 2) {
                dp[i][0] = dp[i-1][0], dp[i][2] = dp[i-1][2];
                dp[i][0] = std::min(dp[i][0], dp[i][2]+1);
                dp[i][2] = std::min(dp[i][2], dp[i][0]+1);
            } else if (obstracles[i-1] == 3) {
                dp[i][1] = dp[i-1][1], dp[i][0] = dp[i-1][0];
                dp[i][1] = std::min(dp[i][1], dp[i][0]+1);
                dp[i][0] = std::min(dp[i][0], dp[i][1]+1);
            }
        }
        
        return std::min({dp[n][0], dp[n][1], dp[n][2]});
    }
};
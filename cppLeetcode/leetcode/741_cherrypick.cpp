/*
741. Cherry Pickup

You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.

0 means the cell is empty, so you can pass through,
1 means the cell contains a cherry that you can pick up and pass through, or
-1 means the cell contains a thorn that blocks your way.
Return the maximum number of cherries you can collect by following the rules below:

Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
 

Example 1:


Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
Output: 5
Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.
Example 2:

Input: grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
Output: 0
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 50
grid[i][j] is -1, 0, or 1.
grid[0][0] != -1
grid[n - 1][n - 1] != -1

*/


#include <vector>

using std::vector;

class CherryPickup {

    /*
        741.Cherry-Pickup
        本题可以解读为，从左上角到右下角，找出两条可行的线路，使得两条线路采集到的ｃｈｅｒｒｙ数量最多．如果两条线路有重复的部分，则只算一次．

        如果只有一条线路，那很明显用ＤＰ算法，每一个点的状态仅仅取决于它左边和上边两个点，转移方程为DP[i][j]＝max{DP[i-1][j],DP[i][j-1]}+grid[i][j]．

        那么对于两条线路，我们需要考虑两个点的状态，那么可以设置DP[i][j][x][y]表示的就是两条线路目前的两个位置(i,j),(x,y)．显然它的状态取决于这两个点分别的左边和上边的两个点．即四个之前的状态： 
        DP[i][j][x][y]＝max{DP[i-1][j][x-1][y],DP[i][j-1][x-1][y],DP[i][j-1][x-1][y],DP[i][j-1][x][y-1]} 此外还要加上当前的grid[i][j]和grid[x][y]．注意此时等考虑这两个点是否重合：

        if (i==x && j==y)
        DP[i][j][x][y]+=grid[i][j]
        else
        DP[i][j][x][y]+=grid[i][j]+grid[x][y]
        事实上，ＤＰ数组不需要设置为４维．因为i+j=x+y，所以通过三重循环，第四维可以通过y=i+j-x得到．
    */
    int cherryPickup(vector<vector<int>>& grid) 
    {
        int N = grid.size();
        //int dp[N+1][N+1][N+1];
        vector<vector<vector<int>>> dp(N+1, vector<vector<int>>(N+1, vector<int>(N+1, INT_MIN)));

        /*
        for (int i=0; i<=N; i++)
            for (int j=0; j<=N; j++)
                for (int x=0; x<=N; x++)
                    dp[i][j][x] = INT_MIN;
        */

        for (int i=1; i<=N; i++)
            for (int j=1; j<=N; j++)
                for (int x=1; x<=N; x++)
                {
                    int y = i+j-x;
                    if (y<1||y>N) continue;
                    if (grid[i-1][j-1]==-1||grid[x-1][y-1]==-1) continue;
                    if (i==1&&j==1&&x==1)
                    {
                        dp[i][j][x] = grid[0][0];
                        continue;
                    }

                    dp[i][j][x] = std::max(dp[i][j][x], dp[i-1][j][x-1]);
                    dp[i][j][x] = std::max(dp[i][j][x], dp[i][j-1][x-1]);
                    dp[i][j][x] = std::max(dp[i][j][x], dp[i-1][j][x]);
                    dp[i][j][x] = std::max(dp[i][j][x], dp[i][j-1][x]);
                    
                    if (i==x && j==y)
                        dp[i][j][x] += grid[i-1][j-1];
                    else
                        dp[i][j][x] += grid[i-1][j-1] + grid[x-1][y-1];
                    
                }
        
        return std::max(0,dp[N][N][N]);
    }

public:
    
    int doit_dp_bottomup(vector<vector<int>>& grid) {
        
        int N = grid.size();
        vector<vector<int>> dp(N, vector<int>(N, -1));
		dp[0][0] = grid[0][0];

		const int maxK = 2 * (N - 1);

		for (int k = 1; k <= maxK; k++) {

			vector<vector<int>> tmp(N, vector<int>(N, -1));

			for (int i = 0; i < N && i <= k; i++) {

				if (k - i >= N) continue;

				for (int j = 0; j < N && j <= k; j++) {

					if (k - j >= N) continue;

					if (grid[i][k - i] == -1 || grid[j][k - j] == -1) continue;

					int cherries = dp[i][j];

					if (i > 0)
						cherries = std::max(cherries, dp[i - 1][j]);
					
					if (j > 0)
						cherries = std::max(cherries, dp[i][j - 1]);

					if (i > 0 && j > 0)
						cherries = std::max(cherries, dp[i - 1][j - 1]);
                    
                    if (cherries < 0)
                        continue;

					tmp[i][j] = cherries + grid[i][k - i] + (i == j ? 0 : grid[j][k - j]);

				}
			}

			dp = std::move(tmp);
		}

		return std::max(dp[N - 1][N - 1], 0);
    }
};
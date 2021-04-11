/*
# 329. Longest Increasing Path in a Matrix


# Given an integer matrix, find the length of the longest increasing path.

# From each cell, you can either move to four directions : left, right, up or down.
# You may NOT move diagonally or move outside of the boundary(i.e.wrap - around is not allowed).

# Example 1:

# nums = [
#  [9,9,4],
#  [6,6,8],
#  [2,1,1]
# ]
# Return 4
# The longest increasing path is[1, 2, 6, 9].

# Example 2:

# nums = [
#  [3,4,5],
#  [3,2,6],
#  [2,2,1]
# ]
# Return 4
# The longest increasing path is[3, 4, 5, 6].Moving diagonally is not allowed.
*/
#include <functional>
#include <vector>
#include <algorithm>


using std::vector;

class LongestIncreasingPath {

    /*
                329.Longest-Increasing-Path-in-a-Matrix
        我们从任意点A开始递归寻找各条递增路径，最终返回的时候记录从A为起点时的最长路径长度。将此结果记忆化，这样当对其他点进行DFS的时候，如果递归调用到dfs(A)就直接返回结果。
    */
    int m,n;
    int len[200][200];

    int longestIncreasingPath(vector<vector<int>>& matrix) 
    {
        m = matrix.size();
        n = matrix[0].size();
        
        int ret = 0;
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                ret = std::max(ret, dfs(matrix,i,j));                    
            }
        
        return ret;
    }
    
    int dfs(vector<vector<int>>& matrix, int i, int j)
    {
        if (len[i][j]!=0) return len[i][j];
        vector<pair<int,int>>dir({{0,1},{0,-1},{1,0},{-1,0}});
        int ret = 0;
        for (int k=0; k<4; k++)
        {
            int x = i+dir[k].first;
            int y = j+dir[k].second;
            if (x<0||x>=m||y<0||y>=n) continue;
            if (matrix[x][y]<=matrix[i][j]) continue;
            ret = max(ret, dfs(matrix, x,y));
        }
        len[i][j] = 1+ret;
        return 1+ret;
    }

public:

	/*
     Solution 2: DFS + memorization (Top-down)
     
     dfs(x, y)  := return the max path length starting at (x, y)
     dfs(x, y) = 1 + max{dfs(tx, ty)} or 0, (tx, ty) are neighthour of (x, y) val[ty][tx] > val[y][x]
     
     Time complexity: O(mn)
     Space complexity: O(mn)
     */
    int doit_dp_dfs_Topdown(vector<vector<int>>&& matrix) {

		if (matrix.size() == 0 || matrix[0].size() == 0) {
			return 0;
		}
        
		int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        // dfs
        std::function<int(int, int)> dfs = [&](int i, int j) {
            
            if (dp[i][j] != 0) return dp[i][j];
            
            int val = matrix[i][j];
            int ans = 1;
            
            vector<std::pair<int, int>> next = { {1, 0} , {-1, 0}, {0, 1}, {0, -1} };

            for (auto c : next) {
                
                int x = i + c.first, y = j + c.second;
                
                if (x < 0 || x >= m || y < 0 || y >= n || val <= matrix[x][y])
                    continue;
                
                ans = std::max(ans, dfs(x, y) + 1);
            }
            
            return dp[i][j] = ans;
        };

		int ans = 0;
		for (size_t i = 0; i < m; i++) {
			for (size_t j = 0; j < n; j++) {
				ans = std::max(ans, dfs(i, j));
			}
		}

		return ans;
	}
    
    /*
        Solution 3: DP (Bottom-up)
        1. Scan the matix m*n times(TLE)
        2. Sort cells by val, visit cells in reverse order
        
        DP
        Time complexity: O(mn*log(mn))
        Space complexity: O(mn)
    */
    
    int doit_dp_Bottomup(vector<vector<int>>& matrix) {
        if (matrix.empty())
            return 0;
      
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 1));
        int ans = 0;
        vector<std::pair<int, std::pair<int, int>>> cells;
        
        for (int y = 0; y < m; ++y)
            for (int x = 0; x < n; ++x)
                cells.push_back({matrix[y][x], {x, y}});
        
        std::sort(cells.rbegin(), cells.rend());
      
        vector<int> dirs {0, 1, 0, -1, 0};
        
        for (const auto& cell: cells) {
            
            int x = cell.second.first, y = cell.second.second;
            
            for (int i = 0; i < 4; ++i) {

                int tx = x + dirs[i], ty = y + dirs[i + 1];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m)
                    continue;
                
                if (matrix[ty][tx] <= matrix[y][x])
                    continue;
                
                dp[y][x] = std::max(dp[y][x], 1 + dp[ty][tx]);
            }
            ans = std::max(ans, dp[y][x]);
        }
        return ans;
    }
};
#include <stdlib.h>
#include <vector>
#include <algorithm>


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

using std::vector;

class LongestIncreasingPath {
public:

	// <dp> <>
	int doit(vector<vector<int>>& matrix) {

		if (matrix.size() == 0 || matrix[0].size() == 0) {
			return 0;
		}
		int m = matrix.size(), n = matrix[0].size();
		vector<vector<int>> dp(m, vector<int>(n, 0));

		int ANS = 0;
		for (size_t i = 0; i < m; i++) {
			for (size_t j = 0; j < n; j++) {
				ANS = std::max(ANS, dfs(matrix, i, j, dp));
			}
		}

		return ANS;
	}


	// dfs
	int dfs(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& dp) {
		if (dp[i][j] == 0) {
			int val = matrix[i][j];
			int ANS = 0;
			int m = matrix.size(), n = matrix[0].size();

			vector<std::pair<int, int>> next = { {1, 0} , {-1, 0}, {0, 1}, {0, -1} };

			for (auto c : next) {
				int x = i + c.first, y = j + c.second;
				if (x < 0 || x >= m || y < 0 || y >= n || val <= matrix[x][y])
					continue;
				dp[i][j] = std::max(dp[i][j], dfs(matrix, x, y, dp));
			}
			dp[i][j]++;
		}
		return dp[i][j];
	}
};



void Test_329_longestIncreasingPath() {


	LongestIncreasingPath A;
	vector<vector<int>> matrix = { { 9, 9, 4 },{ 6, 6, 8} , { 2, 1, 1} };
	int ANS = A.doit(matrix);
	return;
}
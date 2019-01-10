/*

# 778. Swim in Rising Water

# On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).

# Now rain starts to fall. At time t, the depth of the water everywhere is t.
# You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t.
# You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.

# You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?

# Example 1:

# Input: [[0,2],[1,3]]
# Output: 3
# Explanation:
# At time 0, you are in grid location (0, 0).
# You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.

# You cannot reach point (1, 1) until time 3.
# When the depth of water is 3, we can swim anywhere inside the grid.

# Example 2:

# Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
# Output: 16
# Explanation:
#  0  1  2  3  4
#  24 23 22 21  5
#  12 13 14 15 16
#  11 17 18 19 20
#  10  9  8  7  6

# The final route is marked in bold.
# We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
# Note:

# 2 <= N <= 50.
# grid[i][j] is a permutation of [0, ..., N*N - 1].

*/

#include <queue>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class SwimInWater {

	struct cord {
		int val, x, y;
		cord(int x1, int x2, int x3) {
			val = x1, x = x2, y = x3;
		}
	};

	struct cmp {
		bool operator ()(cord& a, cord& b) {
			return a.val > b.val;
		}
	};

public:
	int doit(vector<vector<int>>& grid) {

		priority_queue<cord, vector<cord>, cmp> q;
		int m = grid.size(), n = grid[0].size();
		q.push(cord(grid[0][0], 0, 0));
		set<pair<int, int>> visited;
		visited.insert(make_pair(0, 0));
		int heighest = 0;

		while (!q.empty()) {

			auto c = q.top();
			q.pop();
			heighest = std::max(heighest, c.val);

			if (c.x == m - 1 && c.y == n - 1)
				break;

			for (auto& e : vector<pair<int, int>>({ { 0,-1 },{ 0, 1 },{ 1, 0 },{ -1, 0 } })) {
				int xx = c.x + e.first, yy = c.y + e.second;

				if (xx >= 0 && xx < m && yy >= 0 && yy < n && visited.find(make_pair(xx, yy)) == visited.end()) {
					q.push(cord(grid[xx][yy], xx, yy));
					visited.insert(make_pair(xx, yy));
				}
			}
		}
		return heighest;
	}
};


class Solution {
public:
	int swimInWater(vector<vector<int>>& grid) {
		int rows = grid.size();
		int cols = grid[0].size();
		ids = vector<vector<int>>(rows*cols, vector<int>{0, 0});
		vector<int> pos(rows*cols);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				ids[i * cols + j][0] = i * cols + j;
				ids[i * cols + j][1] = 1;
				pos[grid[i][j]] = i*cols + j;

			}
		}
		int ret = 0;
		for (ret = 0; ret < rows * cols; ret++) {
			int r = pos[ret] / cols;
			int c = pos[ret] % cols;
			if (r > 0 && grid[r - 1][c] < grid[r][c])
				ids[r*cols + c][0] = unite(findparent((r - 1)*cols + c), findparent(r*cols + c));
			if (r < rows - 1 && grid[r + 1][c] < grid[r][c]) {
				ids[r*cols + c][0] = unite(findparent((r + 1)*cols + c), findparent(r*cols + c));
			}
			if (c > 0 && grid[r][c - 1] < grid[r][c])
				ids[r*cols + c][0] = unite(findparent(r*cols + c - 1), findparent(r*cols + c));
			if (c < cols - 1 && grid[r][c + 1] < grid[r][c])
				ids[r*cols + c][0] = unite(findparent(r*cols + c + 1), findparent(r*cols + c));

			if (findparent(rows*cols - 1) == findparent(0)) break;
		}
		return ret;
	}
private:
	vector<vector<int>> ids;
	int findparent(int n) {
		if (ids[n][0] == n) return n;
		ids[n][0] = findparent(ids[n][0]);
		return ids[n][0];
	}

	int unite(int n1, int n2) {
		if (ids[n1][1] > ids[n2][1]) {
			ids[n2][0] = n1;
			return n1;
		}
		else if (ids[n1][1] < ids[n2][1]) {
			ids[n1][0] = n2;
			return n2;
		}
		else {
			ids[n1][0] = n2;
			ids[n1][1] += 1;
			return n2;
		}
	}
};

void Test_778_SwimInRisingWater() {

	vector<vector<int>> input{ { 0,1,2,3,4 },
							{24, 23, 22, 21, 5},
							{12, 13, 14, 15, 16},
							{11, 17, 18, 19, 20},
							{10, 9, 8, 7, 6} };

	int res = SwimInWater().doit(input);



	vector<vector<int>> input1{ {7, 34, 16, 12, 15, 0},
								{10, 26, 4, 30, 1, 20},
								{28, 27, 33, 35, 3, 8},
								{29, 9, 13, 14, 11, 32},
								{31, 21, 23, 24, 19, 18},
								{22, 6, 17, 5, 2, 25} };

	int res1 = SwimInWater().doit(input1);


	return;
}
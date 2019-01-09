


#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// typedef pair<int, int> CORD;

struct CORD {
	int x1, y1, x2, y2;
	
	CORD() : x1(0), x2(0), y1(0), y2(0) {}

	CORD(int x, int y, int z, int s) : x1(x), y1(y), x2(z), y2(s){ }

	bool operator == (const CORD& d) const {
		return d.x1 == this->x1 &&
			d.y1 == this->y1 &&
			d.x2 == this->x2 &&
			d.y2 == this->y2;
	}

};


namespace std {

	template <>
	class hash<CORD> {

	public:
		auto operator () (const CORD& cord) const {
			return hash<int>()(cord.x1) ^ hash<int>()(cord.y1) ^
				hash<int>()(cord.x2) ^ hash<int>()(cord.y2);
		}

	};
}

//auto cord_hash(const CORD& cord) {
//	return hash<int>()(cord.x1) ^ hash<int>()(cord.y1) ^ hash<int>()(cord.x2) ^ hash<int>()(cord.y2);
//}
// typedef unordered_map<const CORD, int, function<decltype(cord_hash)>> CORD_MAP;

class CherryPickup {


public:

	int doit1(vector<vector<int>>& grid) {
		int n = grid.size();
		if (n == 1)
			return grid[0][0];

		int steps = 2 * n - 2;
		vector<vector<int>> dp(n, vector<int>(n, -1));
		dp[0][0] = grid[0][0];

		for (int len = 1; len <= steps; ++len) {
			vector<vector<int>> temp(n, vector<int>(n, -1));
			for (int i = 0; i <= len && i < n; ++i) {
				for (int j = 0; j <= len && j < n; ++j) {
					if (grid[i][len - i] < 0 || grid[j][len - j] < 0) continue;
					int cher = dp[i][j];

					//three possible cases to reach current position in the two paths.
					if (i > 0) cher = max(cher, dp[i - 1][j]);
					if (j > 0) cher = max(cher, dp[i][j - 1]);
					if (i > 0 && j > 0) cher = max(cher, dp[i - 1][j - 1]);

					if (cher < 0) continue;
					//if i and j are the same, it means i and j are in the same position in the grid.
					cher += grid[i][len - i] + (i == j ? 0 : grid[j][len - j]);
					temp[i][j] = cher;
				}
			}
			dp = move(temp);
		}
		return max(dp[n - 1][n - 1], 0);
	}

	int doit(vector<vector<int>>& grid) {

		int N = grid.size();

		// dp holds the maximum value of two k-length path can pick up
		// the two k-length paths arrive at (i, k-i) to (j, k - j)
		// respectively
		vector<vector<int>> dp(N, vector<int>(N, -1));
		dp[0][0] = grid[0][0];

		// maxk: number of steps from (0, 0) to (n-1, n-1)
		const int maxK = 2 * (N - 1);

		for (int k = 1; k <= maxK; k++) {
			// k-th times square
			vector<vector<int>> tmp(N, vector<int>(N, -1));

			// one path of k length from (0, 0) to (i, k-i)
			for (int i = 0; i < N && i <= k; i++) {
				if (k - i >= N)
					continue;

				// another path of k  length from (0, 0) to (j, k - j)
				for (int j = 0; j < N && j <= k; j++) {
					if (k - j >= N)
						continue;

					if (grid[i][k - i] == -1 || grid[j][k - j] == -1) {
						// keep away from throns
						continue;
					}

					// # of cherries picked up by the two (k - 1) - length paths 
					int cherries = dp[i][j];

					if (i > 0)
						cherries = max(cherries, dp[i - 1][j]);
					
					if (j > 0)
						cherries = max(cherries, dp[i][j - 1]);

					if (i > 0 && j > 0)
						cherries = max(cherries, dp[i - 1][j - 1]);

					// No variable way to arrive at (i, k - i) t0 (j, k - j)
					if (cherries < 0)
						continue;

					// Pickup cherries at (i, k - i) and (j, k - j) if i != j
					// other pickup (i, k- i)
					tmp[i][j] = cherries + grid[i][k - i] + (i == j ? 0 : grid[j][k - j]);

				}
			}

			dp = std::move(tmp);
		}

		return std::max(dp[N - 1][N - 1], 0);
	}

	typedef unordered_map<CORD, int> CORD_MAP;

public:

	int dfs(CORD_MAP& dist, vector<vector<int>>& grid, CORD& pos) {

		int M = grid.size(), N = grid[0].size();
		int x1 = pos.x1, y1 = pos.y1, x2 = pos.x1, y2 = pos.y2;

		if ((x1 < 0 || x1 >= M || y1 < 0 || y1 >= N) || (x2 < 0 || y2 < 0 || x2 >= M || y2 >= N))
			return -1;

		if (dist.find(pos) != dist.end())
			return dist[pos];

		if (grid[x1][y1] == -1 || grid[x2][y2] != -1)
			return -1;

		if (x1 == M - 1 && y1 == N - 1 && x2 == M - 1 && y1 == N - 1 && grid[x1][y1] != -1)
			return 1;


		int dd = dfs(dist, grid, CORD{x1 + 1, y1, x2 + 1, y2});
		int dr = dfs(dist, grid, CORD{x1 + 1, y1, x2, y2 + 1});
		int rd = dfs(dist, grid, CORD{x1, y1 + 1, x2 + 1, y2});
		int rr = dfs(dist, grid, CORD{x1, y1 + 1, x2, y2 + 1});

		int maxv = max({ dd, dr, rd, rr });

		if (x1 == x2 && y1 == y2) {
			maxv += grid[x1][y1];
		}
		else {
			maxv += grid[x1][y1] + grid[x2][y2];
		}

		dist[pos] = maxv;
		return maxv;
	}

	int doit2(vector<vector<int>>& grid) {

		CORD_MAP dist;
		CORD pos{ 0, 0, 0, 0 };

		return dfs(dist, grid, pos);
	}

};


void Test_741_CherryPickup() {

	vector<vector<int>> input{ {0, 1, -1}, {1, 0, -1}, {1, 1, 1} };

	vector<vector<int>> input1{ {1, 1, 1, 1, 0, 0, 0},
							   {0, 0, 0, 1, 0, 0, 0},
							   {0, 0, 0, 1, 0, 0, 1},
							   {1, 0, 0, 1, 0, 0, 0},
							   {0, 0, 0, 1, 0, 0, 0},
							   {0, 0, 0, 1, 0, 0, 0},
							   {0, 0, 0, 1, 1, 1, 1} };

	int res = CherryPickup().doit(input);

	int res1 = CherryPickup().doit(input1);

	return;
}
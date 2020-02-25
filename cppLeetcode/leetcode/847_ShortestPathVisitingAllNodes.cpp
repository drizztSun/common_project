/*


*/

#include <vector>
#include <queue>


using namespace std;



/*
	Floyd + State Compression DP

	(If the data range in the problem description is small, like 12 or 15. The problem is most likely to be solved by "state compression dp" )

	In my solution,
 	
	dis[x][y] represents the minimun distance between node x and node y.
    dp[group][dst] represents the shortest distance that a man could walk through all nodes in the "group", 
	and finally finished at the node "dst" ("dst" is one of the node in "group").

	To calculate dp[][], enumerate every possible state (which is "group". For example, If group only has node 0 and node 2, the value of group is 101 in binary).
	Pick a node that is in the "group"(for example, node u), and pick a node that is not in the "group"(for example, node v). 
	Then update dp[group+v][v] by getting the minimum value between dp[group+v][v] and dp[group][u] + dis[u][v].
*/

class Solution {



public:

	int DP(const vector<vector<int>>& dist) {
		int N = dist.size();
		vector<vector<int>> dp(1<<N, vector<int>(N, 0x3f));
		for (auto i = 0; i < N; i++)
			dp[1 << i][i] = 0;

		for (int group = 1; group < 1 << N; group++)
			for (int u = 0; u < N; u++)
				for (int v = 0; v < N; v++) {
					int dst = 1 << v, src = 1 << u;
					if ((group & src) && !(group & dst))
						dp[group | dst][v] = min(dp[group | dst][v], dp[group][u] + dist[u][v]);
				}
		int min_dist = 0x3f3f3f3f;
		for (auto i = 0; i < N; i++) {
			min_dist = min(min_dist, dp[(1 << N) - 1][i]);
		}

		return min_dist;
	}

	void floyd(vector<vector<int>>& dist) {
		int N = dist.size();
		for (auto k = 0; k < N; k++)
			for (auto i = 0; i < N; i++)
				for (auto j = 0; j < N; j++)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	}

	int shortestPathLength(vector<vector<int>>& graph) {

		size_t N = graph.size();
		vector<vector<int>> dist(N, vector<int>(N, 0x3f));

		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < graph[i].size(); j++) {
				dist[i][graph[i][j]] = 1;
			}
		}

		floyd(dist);

		return DP(dist);
	}
};


class ShortestPathLength {
public:
	int doit(vector<vector<int>>&& graph) {

		int N = graph.size();

		queue<pair<int, int>> st;
		for (auto i = 0; i < N; i++) {
			st.push({ 2 << i >> 1, i });
		}

		vector<vector<int>> res( 2 << N >> 1, vector<int>(N, 0));

		while (!st.empty()) {

			int cover = st.front().first, now = st.front().second;
			st.pop();

			if (cover == (2 << N >> 1) - 1)
				return res[cover][now];

			for (auto i : graph[now]) {
				int nextCover = cover, nextNode = i;

				if (((cover >> nextNode) % 2) != 1)
					nextCover += (2 << nextNode >> 1);

				if (res[nextCover][nextNode] == 0) {
					res[nextCover][nextNode] = res[cover][now] + 1;
					st.push({ nextCover, nextNode });
				}
			}
		}
		return -1;
	};
};

void Test_847_ShortestPathVisitingAllNodes() {

	int res1 = ShortestPathLength().doit(vector<vector<int>>{ {1, 2 , 3}, {0}, {0}, {0} });

	int res2 = ShortestPathLength().doit(vector<vector<int>>{ {2,3,4,8}, {8}, {0}, {0,8}, {0,5,6}, {4,7}, {4}, {5}, {0,3,1} });

	int res3 = ShortestPathLength().doit(vector<vector<int>>{ {1}, {0,2,4}, {1,3,4}, {2}, {1,2} });

	return;
}

#include<stdlib.h>
#include<vector>
using namespace std;

class NumberOfIslandII {
public:

	vector<int> doit(int m, int n, vector<pair<int, int>>& positions) {

		vector<vector<int>> mp(m, vector<int>(n, 0));
		vector<int> parent(m*n, -1);
		vector<int> result;
		int lands = 0;

		for (auto c : positions) {

			int x = c.first, y = c.second;
			int id = x * n + y;
			mp[x][y] = 1;
			parent[id] = id;
			lands += 1;
			vector<pair<int, int>> dir = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };

			for (auto nearItem : dir) {
				int nx = x + nearItem.first, ny = y + nearItem.second;
				int nid = nx * n + ny;
				if (nx >= 0 && nx < m && ny >= 0 && ny < n &&  mp[nx][ny] != 0) {
					
					while (parent[nid] != nid) {
						parent[nid] = parent[parent[nid]];
						nid = parent[nid];
					}

					if (nid != id) {
						parent[nid] = id;
						lands -= 1;
					}
				}
			}

			result.push_back(lands);
		};

		return result;
	}
};


void Test_305_Number_Of_Island_II() {

	NumberOfIslandII A;
	auto res = A.doit(3, 3, vector<pair<int, int>>({ {0,0}, {0,1}, {1,2}, {2,1} }) );

	return;
}
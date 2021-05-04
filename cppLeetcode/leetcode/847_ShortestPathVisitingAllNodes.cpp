/*
847. Shortest Path Visiting All Nodes


An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.

graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.

Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

 

Example 1:

Input: [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]
Example 2:

Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]
 

Note:

1 <= graph.length <= 12
0 <= graph[i].length < graph.length
*/

#include <vector>
#include <queue>


using std::vector;
using std::queue;

class ShortestPathLength {

	/*
		847.Shortest-Path-Visiting-All-Nodes
		如果我们想找一条满足题意的路径，该怎么做呢？无非就是搜索嘛。但无论是DFS还是BFS，需要考虑的一个重要问题就是如何去重，否则就会无休止地搜索下去。此题中，我们应该如何记录“状态”呢？
		显然，我们不能单纯地将某个node，或者某条edge是否访问过作为存储的状态，因为我们极有可能需要访问某个node或edge多次。

		那么我们是否可以将所有访问过的node的集合作为一个状态呢？这样也是不行的。比如考虑这个网络“0-1,0-2,0-3”，我们访问完了0,1之后，不得不返回0再去访问其他的节点，
		这个过程中，node的集合其实是不变的。如果我们将node的集合作为状态存储起来做去重的操作，就会被舍弃掉正确的方案。

		所以，正确的状态应该是“当前所在节点+已经访问过的node的集合”。依据这种定义，如果在BFS中遇到重复的状态，毫无疑问，就没有继续搜索的必要了。
	*/
	int shortestPathLength(vector<vector<int>>& graph) 
    {
        int n = graph.size();
        auto visited = vector<vector<bool>>(n,vector<bool>(1<<n,0));
        
        queue<std::pair<int,int>>q; // {node, visitedNodes}
        for (int i=0; i<n; i++)
        {
            q.push({i, 1<<i});
            visited[i][1<<i] = 1;
        }
       
        int step = -1;
        while(!q.empty())
        {
            step++;
            int len = q.size();
            while (len--)
            {
                int node = q.front().first;
                int state = q.front().second;
                q.pop();
                
                for (auto& nextNode:graph[node])
                {
                    int nextState = (state | (1<<nextNode));
                    if (visited[nextNode][nextState]==1)
                        continue;
                    if (nextState == (1<<n)-1)
                        return step+1;
                    q.push({nextNode, nextState});
                    visited[nextNode][nextState] = 1;
                }
            }            
        }
        
        return 0;
        
    }

public:

	int doit_bfs_bitmask(vector<vector<int>>& graph) {
        
        int n = graph.size();
        int finalstatus = (1<<n) - 1;
        int steps = 0;
        vector<vector<bool>> visited(n, vector<bool>(1<<n, false));

        queue<std::pair<int, int>> qu;
        for(int i = 0; i < n; i++) {
            qu.push({i, 1 << i});
            visited[i][1<<i] = true;
        }
        
        while (!qu.empty()) {
            
            int sz = qu.size();
            
            while (sz--) {
                
                auto [cur, v] = qu.front(); qu.pop();
                
                if (v == finalstatus) return steps;
                
                for (auto child: graph[cur]) {
                    int status = v | 1 << child;
                    if (!visited[child][status]) {
                        visited[child][status] = true;
                        qu.push({child, status});  
                    }
                }
            }
            steps++;
        };
        
        return -1;
    }


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
						dp[group | dst][v] = std::min(dp[group | dst][v], dp[group][u] + dist[u][v]);
				}
		int min_dist = 0x3f3f3f3f;
		for (auto i = 0; i < N; i++) {
			min_dist = std::min(min_dist, dp[(1 << N) - 1][i]);
		}

		return min_dist;
	}

	void floyd(vector<vector<int>>& dist) {
		int N = dist.size();
		for (auto k = 0; k < N; k++)
			for (auto i = 0; i < N; i++)
				for (auto j = 0; j < N; j++)
					dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
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

public:

	int doit_bitmask_dp_bfs(vector<vector<int>>&& graph) {

		int N = graph.size();

		queue<std::pair<int, int>> st;
		for (auto i = 0; i < N; i++) {
			st.push({ 2 << i >> 1, i });
		}

		vector<vector<int>> res( 2 << N >> 1, vector<int>(N, 0));

		while (!st.empty()) {

			int cover = st.front().first, now = st.front().second; st.pop();

			if (cover == (2 << N >> 1) - 1) return res[cover][now];

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
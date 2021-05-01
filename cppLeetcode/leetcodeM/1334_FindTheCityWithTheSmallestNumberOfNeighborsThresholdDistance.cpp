/*
1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance

There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.

Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.

Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.

 

Example 1:



Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
Output: 3
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2] 
City 1 -> [City 0, City 2, City 3] 
City 2 -> [City 0, City 1, City 3] 
City 3 -> [City 1, City 2] 
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.
Example 2:



Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
Output: 0
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1] 
City 1 -> [City 0, City 4] 
City 2 -> [City 3, City 4] 
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3] 
The city 0 has 1 neighboring city at a distanceThreshold = 2.
 

Constraints:

2 <= n <= 100
1 <= edges.length <= n * (n - 1) / 2
edges[i].length == 3
0 <= fromi < toi < n
1 <= weighti, distanceThreshold <= 10^4
All pairs (fromi, toi) are distinct.

*/
#include <vector>
#include <functional>
#include <queue>

using std::priority_queue;
using std::vector;


class FindTheCity {

public:

	/*
		Explanation
        Becasue O(N^3) is accepted in this problem, we don't need a very fast solution.
        we can simply use Floyd algorithm to find the minium distance any two cities.

        Reference Floyd–Warshall algorithm

        I first saw @awice using it long time ago.
        It's really easy and makes a lot sense.

        Iterate all point middle point k,
        iterate all pairs (i,j).
        If it go through the middle point k,
        dis[i][j] = dis[i][k] + dis[k][j].


        Complexity
        Time O(N^3)
        Space O(N^2)
	*/
    int doit_floyd_warshall(int n, vector<vector<int>>& edges, int distanceThreshold) {
        
        vector<vector<int>> distance(n, vector<int>(n, 1e4));
        
        for(const auto& edge : edges) {
            distance[edge[0]][edge[1]] = edge[2];
            distance[edge[1]][edge[0]] = edge[2];
        }
        
        for (int i = 0; i < n; i++)
            distance[i][i] = 0;
        
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j ++) {
                    distance[i][j] = std::min(distance[i][j], distance[i][k] + distance[k][j]);
                }
            }
        }
        
        int ans = 0, mincnt = INT_MAX;
        for (int i = 0; i < n; i++) {
            
            int cnt = 0;
            
            for (int j = 0; j < n; j++) {
                if (distance[i][j] <= distanceThreshold && i != j)
                    cnt++;
            }
            
            if (cnt <= mincnt) {
                mincnt = cnt;
                ans = i;
            }
        }
        return ans;
    }

    
	int doit_dijkstra(int n, vector<vector<int>>& edges, int distanceThreshold) {

		vector<std::pair<int, int>> adj[100005];

		for (int i = 0; i < edges.size(); i++) {
			int x = edges[i][0];
			int y = edges[i][1];
			int w = edges[i][2];
			adj[x].push_back({ y,w });
			adj[y].push_back({ x,w });
		}
		int sum = 1e9;

		std::function<int(int, int, int)> dijkstra = [&](int x, int n, int d) {
			priority_queue<std::pair<int, int>> q;
			vector<int> distance(n + 1, 1e9);
			vector<int> visited(n + 1, 0);
			distance[x] = 0;
			q.push({0, x});

			while (!q.empty()) {
				
				int a = q.top().second; 
				q.pop();
				
				if (visited[a] == 0) {
					visited[a] = 1;
					for (auto u : adj[a]) {
						int b = u.first, w = u.second;
						if (distance[a] + w < distance[b]) {
							distance[b] = distance[a] + w;
							q.push({ -distance[b],b });
						}
					}
				}
			}

			int ans = 0;
			for (int i = 0; i < n; i++) {
				if (i != x) {
					if (distance[i] <= d) ans++;
				}
			}
			return ans;
		};

		for (int i = 0; i < n; i++) {
			int y = dijkstra(i, n, distanceThreshold);
			sum = std::min(sum, y);
		}

		int h = -1;
		for (int i = 0; i < n; i++) {
			int y = dijkstra(i, n, distanceThreshold);
			if (y == sum) h = i;
		}

		return h;
	}


	// custom comparator for minimum priority queue <node,distance> based on distance 
	struct comparator {
		bool operator()(std::pair<int, int> const& a, std::pair<int, int> const& b)
		{
			return a.second > b.second;
		}
	};

	int doit_dijstra(int n, vector<vector<int>>& edges, int K) {

		// graph adjacency list of  nodes and weights
		vector<vector<std::pair<int, int>>>graph(n);

		// populate graph adjacency list <node, distance>
		for (int i = 0; i < edges.size(); i++)
		{
			graph[edges[i][0]].push_back(std::make_pair(edges[i][1], edges[i][2]));
			graph[edges[i][1]].push_back(std::make_pair(edges[i][0], edges[i][2]));
		}

		// distance vector of nodes
		vector<int>distance(n);

		// minimum priority queue <node,distance> based on distance
		priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, comparator> Q;

		// minimum visited node count of nodes
		int minNodeCount = INT_MAX;

		// city with smallest number of neighbors at athreshold distance
		int expectedCity;

		// run BFS / Dijkstra from every node and count the number of visited nodes with in threshold distance
		for (int i = 0; i < n; i++)
		{
			int source = i;

			// set distance of all nodes to threshold + 1
			fill(distance.begin(), distance.end(), K + 1);

			// push the source node with distance 0 as it is the source node
			Q.push(std::make_pair(source, 0));
			distance[source] = 0;

			while (!Q.empty())
			{
				int node = Q.top().first;
				int node_dis = Q.top().second;
				Q.pop();

				// ignore nodes which has lowest distance than the node distance in queue means already visited
				if (distance[node] < node_dis) continue;

				// add neighbour nodes in to queue which has higher distance than current node distance + edge distance   
				for (int j = 0; j < graph[node].size(); j++)
				{
					int neighbour = graph[node][j].first;
					int edge_dis = graph[node][j].second;

					if (edge_dis + distance[node] < distance[neighbour])
					{
						distance[neighbour] = distance[node] + edge_dis;
						Q.push(std::make_pair(neighbour, distance[neighbour]));
					}
				}
			}

			// count the number of visited nodes in threashold distance
			int visitCount = 0;
			for (int j = 0; j < n; j++)
				if (source != j && distance[j] <= K)visitCount++;

			// update minNodeCount if count is less or equal cause 
			// we need larger node/city number incase of equal count 
			if (minNodeCount >= visitCount)
			{
				expectedCity = source;
				minNodeCount = visitCount;
			}
		}

		return expectedCity;
	}
};

/*
787. Cheapest Flights Within K Stops

There are n cities connected by m flights. Each flight starts from city u and arrives at v with a price w.

Now given all the cities and flights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.

Example 1:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
Example 2:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
Output: 500
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
 

Constraints:

The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
The size of flights will be in range [0, n * (n - 1) / 2].
The format of each flight will be (src, dst, price).
The price of each flight will be in the range [1, 10000].
k is in the range of [0, n - 1].
There will not be any duplicated flights or self cycles.
*/

#include <vector>
#include <queue>
#include <unordered_map>
#include <set>

using std::multiset;
using std::unordered_map;
using std::vector;
using std::priority_queue;


class FindCheapestPrice {

	/*
	
		787.Cheapest-Flights-Within-K-Stops
		解法1：Floyd（错误）
		Floy算法的本质就是DP。复习一下传统的Floy算法,需要三重循环:

		for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			if( e[i][k]+e[k][j]<e[i][j])
				e[i][j] = e[i][k]+e[k][j];
		在此题中,还有一个总转机次数不超过K的限制,所以除了e[i][j]表示每两个城市之间的最短距离外,还需要创建t[i][j]来存储对应e[i][j]的转机次数.于是代码转化为

		for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			if( e[i][k]+e[k][j]<e[i][j] &&  t[i][k]+t[k][j]+1<=K)
			{
				e[i][j] = e[i][k]+e[k][j];
				t[i][j] = t[i][k]+t[k][j]+1;
			}
		很不幸，以上的算法是错误的。周赛过后补充了一个例子：[[0,1,1],[0,2,5],[1,2,1],[2,3,1]]

		当要求最多转1次（即两趟飞机），从0到3的最小代价。事实上的解是: 0->2->3，代价是5+1=6. 但是上面的算法返回的却是无解。这是因为前半段0->2的行程，floyd提前算出来的最优解是0->1->2，因为代价最小(1+1=2)，但是需要转机两次。所以再加上2->3这段时，因为转机的次数限制，被算法判断为无解。

		解法2：DP
		我们可以利用dp的思想。令dp[k][b]表示从起点坐k次飞机能过够到达城市b的最小代价。显然，它之前的状态就是做k-1次飞机能到哪里。于是我们有状态转移方程：

		dp[k][b] = min(dp[k][b], dp[k-1][a] + cost[a][b]), where there is a flight from a to b.
		注意答案是 min(dp[k][dst]) for k=0,1,..,K+1

		当然我们也可以把dp[k][b]定义成：从起点“最多”坐k次飞机能过够到达城市b的最小代价。那么对应的转移方程：

		dp[b] = min(dp[k][b], dp[k-1][b], dp[k-1][a] + cost[a][b]), where there is a flight from a to b.
		相应地最终答案就是 dp[K+1][dst]，不需要再遍历飞行的次数。

		解法3：BFS(Dijkstra)
		利用Dijkstra求最短权重路径的算法思想，可以简单的理解为基于优先队列的BFS。从起点src开始不停地做BFS，但是队列里弹出的永远是权重最小的路径（所达到的点）。这样任何弹出的点，如果是第一次到达的话，
		那么它一定经历的是最短路径。所以，一旦BFS的过程中遇到了终点，就可以输出它的最短代价。

		但是本题不同之处在于，对于任何中转点（非终点），最短路径不一定就是最优方案，因为还有转机次数的考虑因素。举个例子，假设最多允许转机5次，一种方案是你转机3次花费10到达A地（非终点），
		另一种方案是转机4次花费8到达B地，对于后续的影响而言孰优孰劣我们是无法判断的。所以我们必须将它们都加入BFS的队列之中。当然，如果之前曾经以相同的转机次数到达过A，那么我们肯定只会保留最小代价的方案，
		所以我们需要一个visited[city][times]来记忆化之前所经历过的代价。
	*/
	int findCheapestPrice_DP(int n, vector<vector<int>>& flights, int src, int dst, int K) 
    {
        auto dp = vector<vector<int>>(K+2, vector<int>(n, INT_MAX/2));
        dp[0][src] = 0;
            
        for (int k=1; k<=K+1; k++)
        {                   
            for (auto flight: flights)
            {
                int a = flight[0];
                int b = flight[1];
                int w = flight[2];                
                dp[k][b] = std::min(dp[k][b], dp[k-1][b]);
                dp[k][b] = std::min(dp[k][b], dp[k-1][a]+w);
            }
        }
        
        int ret = dp[K+1][dst];
        
        return (ret>=INT_MAX/2) ? -1 : ret;
    }

	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) 
    {
        vector<vector<vector<int>>>graph(n);
        for (auto flight: flights)
            graph[flight[0]].push_back({flight[1], flight[2]}) ;

        auto visited = vector<vector<int>>(n, vector<int>(K+2, INT_MAX/2));
        visited[src][0] = 0;
        multiset<vector<int>>Set;
        Set.insert({0, 0, src});

        while (!Set.empty())
        {
            int cost = (*Set.begin())[0];
            int step = (*Set.begin())[1];
            int cur = (*Set.begin())[2];
            Set.erase(Set.begin());

            if (cur==dst) return cost;
            if (step == K+1) continue;

            for (auto ticket: graph[cur])
            {
                if (cost + ticket[1] < visited[ticket[0]][step+1])
                {
                    visited[ticket[0]][step+1] = cost + ticket[1];
                    Set.insert({cost+ticket[1], step+1, ticket[0]});
                }
            }
        }

        return -1;
    }

public:


    int doit_dp(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        
        vector<vector<int>> dp(2, vector<int>(n, INT_MAX/2));
        dp[0][src] = 0;
        
        for (int k = 1; k <= K+1; k++) {
            
            int base = k%2;
            
            for (auto& f: flights) {
             
                int s = f[0], d = f[1], w = f[2];
                
                dp[base][d] = std::min({dp[1-base][d], dp[base][d], dp[1-base][s] + w});
            }
        }
        
        K++;
        return dp[K%2][dst] == INT_MAX/2 ? -1 : dp[K%2][dst];
    }

	int doit_dijkstra(int n, vector<vector<int>>& flights, int src, int dst, int K) {
     
        vector<vector<std::pair<int, int>>> graph(n);
        
        for (auto& it: flights)
            graph[it[0]].push_back({it[1], it[2]});
        
        priority_queue<vector<int>, vector<vector<int>>, std::greater<>> pq;
        pq.push({0, 0, src});
        
        
        while (!pq.empty()) {
            
            auto it = pq.top(); pq.pop();
            
            int cost = it[0], step = it[1], cur = it[2];
            
            if (cur == dst) return cost;
            
            if (step > K) continue;
            
            
            for (auto [p, w]: graph[cur]) {
                pq.push({cost + w, step+1, p});
            }
        }
        
        return -1;
    }

	struct Edge {
		int from;
		int to;
		int price;
	};

	struct Node {
		int name;
		int cost;
		int stops;
	};


	int doit_dijkastra(int n, vector<vector<int>>&& flights, int src, int dst, int K) {

		vector<vector<Edge>> flight_prices(n, vector<Edge>());

		for (auto& c : flights) {
			flight_prices[c[0]].push_back(Edge{ c[0], c[1], c[2] });
		}

		auto compare = [](Node l, Node r) -> bool {
			return l.cost > r.cost;
		};

		std::priority_queue<Node, vector<Node>, decltype(compare)> pq(compare);
		pq.push(Node{src, 0, -1});

		while (!pq.empty()) {

			Node n = pq.top();
			pq.pop();

			if (n.name == dst) {
				return n.cost;
			}

			for (auto&c : flight_prices[n.name]) {
				if (n.stops < K) {
					pq.push(Node{ c.to, n.cost + c.price, n.stops + 1 });
				}
			}
			// visited[n.name] = true; The problem is Stop, if we reach n, with m - 1 first, then next step it is gone. 
			// but there is longer one with more step reach n again, then we can get answer follow the trip. 
			// Stop is the key to avoid infinite, not visited.
		}

		return -1;
	}
};
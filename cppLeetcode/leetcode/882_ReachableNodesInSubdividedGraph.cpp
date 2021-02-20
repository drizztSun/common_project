/*
 882. Reachable Nodes In Subdivided Graph
 
 Starting with an undirected graph (the "original graph") with nodes from 0 to N-1, subdivisions are made to some of the edges.

 The graph is given as follows: edges[k] is a list of integer pairs (i, j, n) such that (i, j) is an edge of the original graph,

 and n is the total number of new nodes on that edge.

 Then, the edge (i, j) is deleted from the original graph, n new nodes (x_1, x_2, ..., x_n) are added to the original graph,

 and n+1 new edges (i, x_1), (x_1, x_2), (x_2, x_3), ..., (x_{n-1}, x_n), (x_n, j) are added to the original graph.

 Now, you start at node 0 from the original graph, and in each move, you travel along one edge.

 Return how many nodes you can reach in at most M moves.

  

 Example 1:

 Input: edges = [[0,1,10],[0,2,1],[1,2,2]], M = 6, N = 3
 Output: 13
 Explanation:
 The nodes that are reachable in the final graph after M = 6 moves are indicated below.

 Example 2:

 Input: edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]], M = 10, N = 4
 Output: 23
  

 Note:

 0 <= edges.length <= 10000
 0 <= edges[i][0] < edges[i][1] < N
 There does not exist any i != j for which edges[i][0] == edges[j][0] and edges[i][1] == edges[j][1].
 The original graph has no parallel edges.
 0 <= edges[i][2] <= 10000
 0 <= M <= 10^9
 1 <= N <= 3000
 A reachable node is a node that can be travelled to using at most M moves starting from node 0.

 */

#include <stdlib.h>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <vector>
#include <deque>
#include <functional>


using std::deque;
using std::vector;
using std::priority_queue;
using std::unordered_map;
using std::greater;


size_t cord_hash(const std::pair<int, int>& cord) {
    return std::hash<int>()(cord.first) ^ std::hash<int>()(cord.second);
}

class ReachableNodes {
    
public:

    /*
        882.Reachable-Nodes-In-Subdivided-Graph
        我们可以用Dijkstra求出从0点到任意原始节点i的最短距离（最少需要的moves），记为dist[i]。那么这个结果对于解题有什么帮助呢？

        我们令edgeVisitedNodes[i][j]表示从i->j这条边，我们最多能再走几步（即访问多少个“细分点”）。因为总的maxMoves是固定的，我们自然希望到达i点时用的步数越少的话，那么我们在i->j这条边上能走的步数就越多。
        也就是说，我们能在i->j这条边上再走maxMoves-dist[i]步。注意，我们只考虑“细分点”而不考虑端点，因此这个数字不能超过这条边的cnt，即 VisitedSubNodes[i][j] = min(cnt, maxMoves - dist[i])

        同理，我们也可以求出我们能在j->i这条边上再走多少步，即 VisitedSubNodes[i][j] = min(cnt, maxMoves - dist[i])。

        有了以上的数据，我们再遍历所有的边i<->j，那么除了两个端点，我们能在这条边上访问到的“细分点”数目应该是min(VisitedSubNodes[i][j]+VisitedSubNodes[j][i], cnt). 我们另外从dist[i]统计所有能走到的端点。最终答案是两者之和。
    */
    typedef std::pair<int,int> PII;

    int doit_bfs_dijkstra_v1(vector<vector<int>>& edges, int maxMoves, int n) 
    {
        unordered_map<int, vector<PII>>Map;
        for (auto e:edges)
        {
            Map[e[0]].push_back({e[1], e[2]});
            Map[e[1]].push_back({e[0], e[2]});
        }
        unordered_map<int, unordered_map<int,int>>edgeVisitedNodes;

        priority_queue<PII, vector<PII>, greater<>>pq;
        pq.push({0,0});
        vector<int>resolved(n);

        while (!pq.empty())
        {
            auto [d, cur] = pq.top();
            pq.pop();

            if (resolved[cur]) continue;
            resolved[cur] = 1;

            for (auto [next, cnt]: Map[cur])
            {
                // if (resolved[next]) continue;  // Do NOT add this line.
                edgeVisitedNodes[cur][next] = std::min(maxMoves - d, cnt);
                if (maxMoves >= d+cnt+1)
                    pq.push({d+cnt+1, next});
            }
        }

        int count = 0;
        for (auto e: edges) {
            int a = e[0], b = e[1], cnt = e[2];
            count += std::min(cnt, edgeVisitedNodes[a][b]+edgeVisitedNodes[b][a]);
        }

        for (int i=0; i<n; i++)
            if (resolved[i]) count++;

        return count;
    }
    
    int dist[3000];
    int resolved[3000];
public:
    int doit_bfs_dijkstra_v2(vector<vector<int>>& edges, int maxMoves, int n) 
    {
        vector<PII> adj[3000];  // {nextNode, weight}
        for (auto e: edges)
        {
            adj[e[0]].push_back({e[1], e[2]+1});
            adj[e[1]].push_back({e[0], e[2]+1});
        }
        
        priority_queue<PII, vector<PII>, greater<>>pq;  // {dist, nodeIdx}
        pq.push({0,0});        
        
        while (!pq.empty())
        {
            auto [d, cur] = pq.top();
            pq.pop();
            if (resolved[cur]) continue;
            resolved[cur] = 1;
            dist[cur] = d;
                        
            for (auto [next, weight] : adj[cur])
            {
                if (resolved[next]) continue;
                if (d+weight <= maxMoves)
                    pq.push({d+weight, next});
            }            
        }
        
        int count = 0;
        for (auto e: edges)
        {
            int a = e[0], b = e[1];
            int sum = 0;
            if (resolved[a]) sum += maxMoves - dist[a];
            if (resolved[b]) sum += maxMoves - dist[b];
            count += std::min(sum, e[2]);
        }
        
        for (int i=0; i<n; i++)
            if (resolved[i])
                count++;
        
        return count;    
    }

    typedef std::pair<int,int> pi;
    
    int doit_bfs_dijkstra_best(vector<vector<int>>& edges, int m, int n) {
        
        vector<int> dist(n, 1e9);
        dist[0]=0;

        vector<vector<pi>> adj(n);
        for(int i=0;i<edges.size();i++)
        {
            adj[edges[i][0]].push_back({edges[i][1],edges[i][2]+1});
            adj[edges[i][1]].push_back({edges[i][0],edges[i][2]+1});
        }
        
        priority_queue<pi,vector<pi>,greater<pi>> pq;
        pq.push({0,0});
        
        while(!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            for(pi v:adj[u])
            {
                if(dist[v.first] > dist[u] + v.second)
                {
                    dist[v.first] = dist[u] + v.second;
                    pq.push({dist[v.first], v.first});
                }
            }
        }
        
        int count=0;
        for(int i=0; i < edges.size(); i++)
        {
            int u=edges[i][0];
            int v=edges[i][1];
            int w=edges[i][2];
            
            if(dist[u] < m)
            {
                int diff = m-dist[u];
                int diff2 = 0;
                if(dist[v] < m)
                {
                    diff2 = m - dist[v];
                }
                count += std::min(w, diff + diff2);
            }
            else
            {
                if(dist[v] < m)
                    count += std::min(w, m - dist[v]);
            }
        }
        
        for(int i = 0;i < n; i++)
            if(dist[i] <= m)
                count++;
        
        return count;
    }
    
    int doit_heap_bfs_dijkstra(vector<vector<int>>&& edges, int M, int N) {
        
        vector<vector<int>> graph(N, vector<int>(N, -1));
        for (auto& c: edges) {
            graph[c[0]][c[1]] = c[2];
            graph[c[1]][c[0]] = c[2];
        }
        
        priority_queue<std::pair<int, int>, vector<std::pair<int,int>>, greater<std::pair<int,int>> > heapqu;
        heapqu.push({0, 0});
        
        vector<int> distance(N, M+1);
        distance[0] = 0;
        
        unordered_map<std::pair<int, int>, int, std::function<decltype(cord_hash)>> used(100, cord_hash);
        int ans = 0;
        
        while (!heapqu.empty()) {
            
            auto c = heapqu.top();
            int dist = c.first, node = c.second;
            heapqu.pop();
            
            if (distance[node] < dist)
                continue;
            
            ans++;
            
            for (auto i = 0; i < graph[node].size(); i++) {
                if (graph[node][i] == -1)
                    continue;
                
                int weight = graph[node][i];
                used[{node, i}] = std::min(weight, M - dist);
                int d2 = dist + weight + 1;
                
                // Always to with minimal distance, because it means you can go more from this node.
                if (d2 < distance[i]) {
                    distance[i] = d2;
                    heapqu.push({d2, i});
                }
            }
        }
        
        for (auto c: edges) {
            ans += std::min(c[2], used[{c[0], c[1]}] + used[{c[1],c[0]}]);
        }

        return ans;
    }
};


void test_882_ReachableNodeInSubdividedGraph() {
    
    ReachableNodes().doit_heap(vector<vector<int>>{{3,4,8},{0,1,3},{1,4,0},{1,2,3},{0,3,2},{0,4,10},{1,3,3},{2,4,3},{2,3,3},{0,2,10}}, 7, 5);
    
    ReachableNodes().doit_heap(vector<vector<int>>{{2, 4, 2}, {3, 4, 5}, {2, 3, 1}, {0, 2, 1}, {0, 3, 5}}, 14, 5);
    
    ReachableNodes().doit_heap(vector<vector<int>>{{0, 1, 10}, {0, 2, 1}, {1, 2, 2}}, 6, 3);
}


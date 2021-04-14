/*

1786. Number of Restricted Paths From First to Last Node


There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph has n nodes labeled from 1 to n, 
and an array edges where each edges[i] = [ui, vi, weighti] denotes that there is an edge between nodes ui and vi with weight equal to weighti.

A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.

The distance of a path is the sum of the weights on the edges of the path. Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x. 
A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1) where 0 <= i <= k-1.

Return the number of restricted paths from node 1 to node n. Since that number may be too large, return it modulo 109 + 7.

 

Example 1:


Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
Output: 3
Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
1) 1 --> 2 --> 5
2) 1 --> 2 --> 3 --> 5
3) 1 --> 3 --> 5
Example 2:


Input: n = 7, edges = [[1,3,1],[4,1,2],[7,3,4],[2,5,3],[5,6,1],[6,7,2],[7,5,3],[2,6,4]]
Output: 1
Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The only restricted path is 1 --> 3 --> 7.
 

Constraints:

1 <= n <= 2 * 104
n - 1 <= edges.length <= 4 * 104
edges[i].length == 3
1 <= ui, vi <= n
ui != vi
1 <= weighti <= 105
There is at most one edge between any two nodes.
There is at least one path between any two nodes.

*/

#include <vector>
#include <queue>
#include <functional>


using std::priority_queue;
using std::vector;



class CountRestrictedPaths {

    /*
        1786.Number-of-Restricted-Paths-From-First-to-Last-Node
        题意描述：我们认为节点n是海平面，把distanceToLastNode(x)理解为节点x到节点n的海拔高度。我们需要找一条从节点1到节点n的路径，其中依次经过的每个点的“海拔”都是递减的。问这样的路径有多少条。

        首先，这是一个single source, non-negative weight的图论问题，我们会用Dijkstra算法很容易地计算出每个节点距离节点n的最短路径距离，也就是“海拔”。

        然后我们从节点1开始，用DFS来统计到达节点n的路径数目。注意，我们每次从当前节点a往后进行分支搜索的时候，根据题目要求，我们只会选择海拔相对a更低的节点递归下去，而不是选择所有的相邻节点。另外，考虑到图的结构很可能错综复杂，所以记忆化是必须的。

        另外想提的一点是，DFS的过程中我们并不需要使用visited来去重。这是因为我们在递归的过程中永远遵循“水往低处流”的规则，所以不可能会在DFS的过程中遇到任何已经访问过的节点。
    
    */
   
    typedef std::pair<int,int> PII;
    vector<PII> next[20001];
    int dist[20001];
    int visited[20001];
    int pathNum[20001];
    long M = 1e9+7;
    int n;
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) 
    {
        this->n = n;
        for (auto e:edges)
        {
            int a = e[0]-1;
            int b = e[1]-1;
            next[a].push_back({b, e[2]});
            next[b].push_back({a, e[2]});            
        }
        
        priority_queue<PII, vector<PII>, std::greater<>>pq;
        pq.push({0,n-1});        
        
        while (!pq.empty())
        {
            auto [d, cur] = pq.top();
            pq.pop();
            if (visited[cur]) continue;
            dist[cur] = d;
            visited[cur] = 1;
            
            for (auto [nxt, len] : next[cur])
            {
                if (visited[nxt]) continue;
                pq.push({ d + len, nxt});
            }            
        }
        
        for (int i=0; i<n; i++)
            pathNum[i] = -1;
        
        long ret = dfs(0);
        return ret;
    }
    
    long dfs(int cur)
    {
        if (cur==n-1) return 1;
        if (pathNum[cur]!=-1) return pathNum[cur];
        
        long sum = 0;
        for (auto [nxt, len]: next[cur])
        {
            if (dist[nxt] >= dist[cur]) continue;
            sum += dfs(nxt);
            sum %= M;
        }
        pathNum[cur] = sum;
        return sum;
    }


public:

    int doit_dfs_dijkstra(int n, vector<vector<int>>& edges) {
        
        constexpr int hmod = 1e9+7;
        vector<vector<std::pair<int, int>>> graph(n);
        
        for (auto& e: edges) {
            graph[e[0]-1].push_back({e[1]-1, e[2]});
            graph[e[1]-1].push_back({e[0]-1, e[2]});
        }
        
        using pi = std::pair<int, int>;
        priority_queue<pi, vector<pi>, std::greater<>> pq;
        pq.push({0, n-1});
        vector<int> visited(n, -1);
        
        while (!pq.empty()) {
            
            auto [dist, cur] = pq.top(); pq.pop();
            
            if (visited[cur] != -1) continue;
            
            visited[cur] = dist;
            
            for (auto& [c, v]: graph[cur]) {
                
                if (visited[c] != -1) continue;
                
                pq.push({dist+v, c});
            }
        }
        
        vector<int> pathnum(n, -1);
        
        std::function<long(int)> dfs = [&](int cur) -> long {
            
            if (cur == n-1) return 1;
            
            if (pathnum[cur] != -1) return pathnum[cur];
            
            long sums = 0;
            
            for (auto [c, w]: graph[cur]) {
                
                if (visited[c] >= visited[cur]) continue;
                
                sums = (sums + dfs(c)) % hmod;
                
            }
            
            pathnum[cur] = sums;
            return sums;
        };
        
        return dfs(0);
    }

    /*
        Solution 1: Two Stages
    
        Stage 1: Build the graph and find the shortest paths from n(not 1) to rest of the nodes using Dijkstra in O(ElogV) time.

        Stage 2: Compute the number of paths using recursion with memorization. (LC 62 Unique Paths)

        paths(u) = sum(paths(v))

        Base case: paths(n) = 1

        paths(1) = paths(2) + paths(3) = 2 + 1 = 3
        paths(2) = paths(3) + paths(5) = 1 + 1 = 2
        paths(3) = paths(5) = 1

        Time compelxity: O(ElogV + V + E)
        Space complexity: O(V + E)
    */
    int doit_dp(int n, vector<vector<int>>& edges) {
        
        constexpr int kMod = 1e9 + 7;
        using PII = std::pair<int, int>;    
        vector<vector<PII>> g(n + 1);
        for (const auto& e : edges) {
        g[e[0]].emplace_back(e[1], e[2]);
        g[e[1]].emplace_back(e[0], e[2]);
        }    
        
        // Shortest distance from n to x.
        vector<int> dist(n + 1, INT_MAX / 2);
        dist[n] = 0;
        priority_queue<PII, vector<PII>, std::greater<PII>> q;
        q.emplace(0, n);
        while (!q.empty()) {
        const auto [d, u] = q.top(); q.pop();
        if (dist[u] < d) continue;
        for (auto [v, w]: g[u]) {
            if (dist[u] + w >= dist[v]) continue;
            dist[v] = dist[u] + w;
            q.emplace(dist[v], v);
        }
        }
    
        vector<int> dp(n + 1, INT_MAX);
        std::function<int(int)> dfs = [&](int u) {      
            if (u == n) return 1;
            if (dp[u] != INT_MAX) return dp[u];
            int ans = 0;
            
            for (auto [v, w]: g[u])
                if (dist[u] > dist[v])
                ans = (ans + dfs(v)) % kMod;      
            return dp[u] = ans;
        };
        
        return dfs(1);
    }

    /*
        Solution 2: Combined

        We can combine two stages into one, count the paths with doing Dijkstra! We just need some proof.

        When a node u got popped.
        1. The shortest distance to n is determined.
        2. The # of restricted paths are also determined.
        3. i then can be the source of its neighbour node v is dist[v] > dist[u]
        4. dist[v] > dist[u] means
            a. We haven't visited v yet => dist[v] >= dist[u]
            b. Since W >= 1, dist[v] == dist[u] will never happen
            c. We can do paths[v] += paths[u]
    */
    int doit_dp(int n, vector<vector<int>>& edges) {
        constexpr int kMod = 1e9 + 7;
        using PII = std::pair<int, int>;
        vector<vector<PII>> g(n + 1);
        for (const auto& e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            g[e[1]].emplace_back(e[0], e[2]);
        }    
        
        // Shortest distance from n to x.
        vector<int> dist(n + 1, INT_MAX);
        vector<int> dp(n + 1);
        dist[n] = 0;
        dp[n] = 1;
        priority_queue<PII, vector<PII>, std::greater<PII>> q;
        q.emplace(0, n);

        while (!q.empty()) {
            const auto [d, u] = q.top(); q.pop();
            if (d > dist[u]) continue;
            if (u == 1) break;
            
            for (auto [v, w]: g[u]) {
                
                if (dist[v] > dist[u] + w)
                    q.emplace(dist[v] = dist[u] + w, v);
                
                if (dist[v] > dist[u])
                    dp[v] = (dp[v] + dp[u]) % kMod;
            }
        }
        return dp[1];
    }
};
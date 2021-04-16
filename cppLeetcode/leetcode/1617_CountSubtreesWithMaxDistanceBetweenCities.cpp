/*
1617. Count Subtrees With Max Distance Between Cities

There are n cities numbered from 1 to n. You are given an array edges of size n-1, where edges[i] = [ui, vi] represents a bidirectional edge 
between cities ui and vi. There exists a unique path between each pair of cities. In other words, the cities form a tree.

A subtree is a subset of cities where every city is reachable from every other city in the subset, where the path between each pair passes through only the cities from the subset. 
Two subtrees are different if there is a city in one subtree that is not present in the other.

For each d from 1 to n-1, find the number of subtrees in which the maximum distance between any two cities in the subtree is equal to d.

Return an array of size n-1 where the dth element (1-indexed) is the number of subtrees in which the maximum distance between any two cities is equal to d.

Notice that the distance between the two cities is the number of edges in the path between them.

 

Example 1:



Input: n = 4, edges = [[1,2],[2,3],[2,4]]
Output: [3,4,0]
Explanation:
The subtrees with subsets {1,2}, {2,3} and {2,4} have a max distance of 1.
The subtrees with subsets {1,2,3}, {1,2,4}, {2,3,4} and {1,2,3,4} have a max distance of 2.
No subtree has two nodes where the max distance between them is 3.
Example 2:

Input: n = 2, edges = [[1,2]]
Output: [1]
Example 3:

Input: n = 3, edges = [[1,2],[2,3]]
Output: [2,1]
 

Constraints:

2 <= n <= 15
edges.length == n-1
edges[i].length == 2
1 <= ui, vi <= n
All pairs (ui, vi) are distinct.


https://zxi.mytechroad.com/blog/tree/leetcode-1617-count-subtrees-with-max-distance-between-cities/
*/
#include <vector>
#include <queue>
#include <functional>

using std::queue;
using std::vector;


class CountSubgraphsForEachDiameter {

    /*
        1617.Count-Subtrees-With-Max-Distance-Between-Cities
        本题要求统计：对于每一种长度d，有多少个subtree的最大直径等于d。根据长度来“构造”满足条件的树，其实是比较困难的。我们可以反过来想，对于每个subtree，我们查看它的最大直径是多少，然后做统计的aggregation。
        根据一个固定的subtree，求最大直径，这是一个确定性的问题，通常比构造性的问题简单的多。另外这个题目中节点数目小于等于15，穷举所有subtree（包括非法的不连通的图），也就是2^15=32768种，这是可以接受的。

        给定了一棵树的拓扑结构，如何计算它的最长直径呢？这是一个经典的问题，有着经典的o(N)的解法：

        1. 以图里的任意一个节点作为起始点A（看做根），往外做BFS遍历，能够到达的最远的节点B，那么B一定是最大直径的一个端点。
        2. 我们以B作为起始点（看做根），往外做BFS遍历，能够到达的最远的节点C，那么BC的路径就是最大直径的距离。
        我们来给第一步的这个结论做个证明。第二步其实就是再次利用了这个结论。

        假设从任意点A开始，能够到达的最远的距离是B。另外，整张图里“最长的点到点距离”是S和T。我们要证明B只可能是S或者T中的一点。如果不是，那么分情况讨论：

        (1) AB与ST完全不相交。

        A --X-- B
            |
        S --Y-- T
        那么我们从A找一条能够到达ST的路径，并令分叉点是X和Y。因为AB是从A起始的最长路径，那么AB>AX+XY+XT，即BX>XY+YT.

        那么我们观察路径S->Y->X->B，其距离SY+YX+XB > SY+2XY+YT = ST+2XY > ST，这就与ST是全局“最长的点到点距离”矛盾。

        (2) AB与ST相交于X。

            A 
            |
        S ==X== T
            |
            B
        因为AB是从A起始的最长路径，那么AX+XB>AX+XS，即XB>XS.

        我们观察路径B->X->T，其距离BX+XT > XS+XT = ST，这就与ST是全局“最长的点到点距离”矛盾。

        (3) 还有一些corner cases，都容易结合图形分析。

        由此我们证明了，只要用两次BFS找到两个“最远距离”，就可以确定一棵树的最大直径。

        本题的基本思路就是：

        1. 枚举节点的组合尝试构成一棵树
        2. 如果这棵树是联通的，那么就求它的最长直径。
        3. 对于该直径的subtree统计就加1。
        如何快速判断树是联通的呢？很简单，在BFS的时候判断是否经过了所有这个树的节点就行了。
    
    */
    vector<vector<int>>adj;   
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) 
    {
        adj.resize(n);
        for (auto edge: edges)
        {
            adj[edge[0]-1].push_back(edge[1]-1);
            adj[edge[1]-1].push_back(edge[0]-1);
        }
        
        vector<int>allow(n);
        vector<int>rets(n,0);
        vector<int>dist(n);
        for (int state=1; state<(1<<n); state++)
        {
            int start;
            int count = 0;
            for (int i=0; i<n; i++)
            {
                if (((state>>i)&1)==1)
                {
                    allow[i]=1;
                    start = i;
                    count++;
                }                    
                else
                    allow[i]=0;
            }
            
            for (int i=0; i<n; i++)
                dist[i] = -1;
            int v1 = bfs(start, dist, allow);

            int countVisited = 0;
            for (int i=0; i<n; i++)
                countVisited += (dist[i]!=-1);
            if (countVisited!=count)
                continue;
            
            for (int i=0; i<n; i++)
                dist[i] = -1;
            int v2 = bfs(v1, dist, allow);
            int maxDist = *max_element(dist.begin(), dist.end());
            
            rets[maxDist]++;
        }
        
        rets.erase(rets.begin());
        return rets;        
    }
    
    int bfs(int start, vector<int>&dis, vector<int>&allow)
    {
        int n = dis.size();
        queue<int> q; 
        q.push(start);       
        dis[start] = 0; 
        int maxDis = 0;
        int maxId = start;
        
        while (!q.empty()) 
        { 
            int cur = q.front();
            q.pop(); 
            
            for (auto next: adj[cur]) 
            {       
                if (allow[next]==0) continue;
                if (dis[next] == -1) 
                { 
                    q.push(next);   
                    dis[next] = dis[cur] + 1; 
                    if (dis[next] > maxDis)
                    {
                        maxDis = dis[next];
                        maxId = next;
                    }
                } 
            } 
        }
        return maxId; 
    }

public:

    /*
        Solution2 DP on tree

        dp[i][k][d] := # of subtrees rooted at i with tree diameter of d and the distance from i to the farthest node is k.

        dp[i][k][d] := # of subtrees rooting at i that has tree diameter of d, k is the longest path that does not passing i (or distance from i to the farthest node).

        dp[i][0][0] = 1, a subtree of a single node i, d=k=0

        Enumerate existing subtrees rooted at u of (k1, d1) and merge with subtrees rooted at v of (k2, d2) where there is an edge between u and v.

        dp2[u][k][d] = sum(dp[u][k1][d1] * dp[v][k2][d2]) where k = nax(k1, k2+1), d = max(d1, d2, k1+k2+1)

        Enumerate all node from 0 ~ n-1, and use it as root to build subtrees. 

        Time complexity: O(n^5)
        Space complexity: O(n^3)
    */
    vector<int> doit_dp_best(int n, vector<vector<int>>& edges) {    
        vector<vector<int>> g(n);
        for (const auto& e : edges) {
            g[e[0] - 1].push_back(e[1] - 1);
            g[e[1] - 1].push_back(e[0] - 1);
        }

        vector<vector<vector<int>>> dp(n);
        vector<int> sizes(n);

        std::function<void(int, int)> dfs = [&](int u, int p) {
            if (!dp[u].empty()) return; 
            dp[u] = vector<vector<int>>(n, vector<int>(n));
            dp[u][0][0] = 1;
            sizes[u] = 1;
            for (int v : g[u]) {
                if (v == p) continue;
                dfs(v, u);
                vector<vector<int>> dpu(dp[u]);
                for (int d1 = 0; d1 < sizes[u]; ++d1)
                for (int k1 = 0; k1 <= d1; ++k1) {
                    if (!dp[u][k1][d1]) continue;
                    for (int d2 = 0; d2 < sizes[v]; ++d2)
                    for (int k2 = 0; k2 <= d2; ++k2) {
                        const int d = std::max({d1, d2, k1 + k2 + 1});
                        const int k = std::max(k1, k2 + 1);
                        dpu[k][d] += dp[u][k1][d1] * dp[v][k2][d2];
                    }
                }
                swap(dpu, dp[u]);
                sizes[u] += sizes[v];
            }
        };
        vector<int> ans(n - 1);
        dfs(0, -1);
        for (int i = 0; i < n; ++i) 
            for (int k = 0; k < n; ++k)
                for (int d = 1; d < n; ++d)
                    ans[d - 1] += dp[i][k][d];
        return ans;
    }

    /*
    Solution 1: Brute force

    Enumerate all subsets and check the maximum distance.
    Note: A subset might not form a tree.

    Try all subtrees and find the diameter of that subtree (longest distance between any node)
    Time complexity: O(2^n * n)
    Space complexity: O(n)
    */
    vector<int> doit_bfs(int n, vector<vector<int>>& edges, int last = -1) {
        
        vector<vector<int>> graph(n+1);

        for (auto& c : edges)
            graph[c[0]].push_back(c[1]), graph[c[1]].push_back(c[0]);

        vector<int> seen(n, -1), seen2;
        vector<int> ans(n - 1);
        queue<int> q;

        auto bfs = [&](int start, vector<int>& seen) -> std::pair<int, int> {

            q.push(start);
            seen[start] = 1;
            int count = 0, dist = -1;

            while (!q.empty()) {

                int s = q.size();
                while (s--) {
                    int last = q.front(); q.pop();
                    ++count;

                    for (int v : graph[last]) {
                        if (seen[v] != -1 && !seen[v]++)
                            q.push(v);
                    }
                }

                ++dist;
            }

            return {dist, count};
        };

        for (int s = 0; s < (1<<n); s++) {

            if (__builtin_popcount(s) < 2) continue;

            for (int i = 1; i <= n; i++) if (s & (1 << i)) seen[i] = 0;

            seen2 = seen;

            const int start = 31 - __builtin_clz(s & (s-1));
            if (bfs(start, seen).second != __builtin_popcount(s)) continue;

            ++ans[bfs(last, seen2).first - 1];
        }

        return ans;
    }
};
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

using std::queue;
using std::vector;


class CountSubgraphsForEachDiameter {

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

    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {    
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
                        const int d = max({d1, d2, k1 + k2 + 1});
                        const int k = max(k1, k2 + 1);
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
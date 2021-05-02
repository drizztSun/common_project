/*
261. Graph Valid Tree

You have a graph of n nodes labeled from 0 to n - 1. You are given an integer n and a list of edges where edges[i] = [ai, bi] indicates that there is an undirected edge between nodes ai and bi in the graph.

Return true if the edges of the given graph make up a valid tree, and false otherwise.

 

Example 1:


Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
Output: true
Example 2:


Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
Output: false
 

Constraints:

1 <= 2000 <= n
0 <= edges.length <= 5000
edges[i].length == 2
0 <= ai, bi < n
ai != bi
There are no self-loops or repeated edges.

*/
#include <vector>
#include <unordered_set>
#include <functional>
#include <queue>

using std::queue;
using std::unordered_set;
using std::vector;

class ValidTree {

public:
    
    bool doit_bfs(int n, vector<vector<int>>& edges) {
        
        if (edges.size() != n-1) return false; 
 
        vector<vector<int>> graph(n);

        for (const auto& c: edges) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }

        unordered_set<int> nodes;
        vector<int> parent(n, -1);
        queue<int> qu;
        parent[0] = -1;
        qu.push(0);

        while (!qu.empty()) {

            int cur = qu.front(); qu.pop();

            for (auto nx: graph[cur]) {
                if (parent[cur] == nx) continue;
                if (nodes.count(nx)) return false;
                parent[nx] = cur;
                qu.push(nx);
            }

            nodes.insert(cur);
        }

        return nodes.size() == n;
    }

    bool doit_dfs(int n, vector<vector<int>>& edges) {
        
        if (edges.size() != n-1) return false; 
 
        vector<vector<int>> graph(n);

        for (const auto& c: edges) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }

        unordered_set<int> nodes;

        std::function<bool(int, int)> dfs = [&](int cur, int parent) {
            if (nodes.count(cur)) return false;
            nodes.insert(cur);
            for (auto nx: graph[cur]) {
                if (nx == parent) continue;
                if (!dfs(nx, cur)) return false;
            }
            return true;
        };

        return dfs(0, -1) && nodes.size() == n;
    }

    bool doit_disjoint(int n, vector<vector<int>>& edges) {

        if (edges.size() != n-1) return false; 

        vector<int> parent(n, 0);
        std::iota(begin(parent), end(parent), 0);

        auto find = [&](int cur) {
            while (parent[cur] != cur) {
                parent[cur] = parent[parent[cur]];
                cur = parent[cur];
            }
            return cur;
        };

        auto merge = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            if (pa == pb) return;

            if (pa < pb) 
                parent[pb] = pa;
            else
                parent[pa] = pb;
        };

        for (const auto& c: edges) {
            if (find(c[0]) == find(c[1])) return false;
            merge(c[0], c[1]);
        }

        int cnt = 0;
        for (int i = 0; i < n; i++)
            cnt += (parent[i] == i);

        return cnt == 1;
    }

};
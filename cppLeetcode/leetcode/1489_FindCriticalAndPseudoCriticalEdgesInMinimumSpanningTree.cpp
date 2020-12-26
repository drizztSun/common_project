/*
1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree

Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti]
represents a bidirectional and weighted edge between nodes ai and bi.
A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.

Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST).
An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge.
On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.

Note that you can return the indices of the edges in any order.



Example 1:



Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
Output: [[0,1],[2,3,4,5]]
Explanation: The figure above describes the graph.
The following figure shows all the possible MSTs:

Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
Example 2:



Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
Output: [[],[0,1,2,3]]
Explanation: We can observe that since all 4 edges have equal weight, choosing any 3 edges from the given 4 will yield an MST. Therefore all 4 edges are pseudo-critical.


Constraints:

2 <= n <= 100
1 <= edges.length <= min(200, n * (n - 1) / 2)
edges[i].length == 3
0 <= ai < bi < n
1 <= weighti <= 1000
All pairs (ai, bi) are distinct.
*/
#include <vector>
#include <numeric>

using std::vector;


struct UnionFind {
    
    vector<int> _r, _p;

    UnionFind(int n): _r(n), _p(n) {
        iota(begin(_p), end(_p), 0);
    }

    int Find(int a) {
        while (_p[a] != a) {
            _p[a] = _p[_p[a]];
            a = _p[a];
        }
        return a;
    }

    bool Union(int a, int b) {
        int pa = Find(a);
        int pb = Find(b);

        if (pa == pb) {
            return false;
        }

        if (_r[pa] == _r[pb]) {
            _p[pa] = pb;
            _r[pb]++;
        } else if (_r[pa] > _r[pb]) {
            _p[pb] = pa; 
        } else {
            _p[pa] = pb;
        }
        return true;
    }
};


class CriticalAndPseduoCritivalEdges {

public:

    /*
    For each edge
    1. exclude it and build a MST, cost increased => critical
    2. for a non critical edge, force include it and build a MST, cost remains the same => pseudo critical

    Proof of 2, if a non critical / non pseudo critical edge was added into the MST, the total cost must be increased. 
    So if the cost remains the same, must be the other case. Since we know the edge is non-critical, so it has to be pseudo critical.

    MST: Kruskal 

    edge <= 200 => For every edge, do sth and build a MST.

    Critical edges:

    1. cost increased if removed
    2. can not form a tree anymore if removed

    Pseudo-Critical: include it and cost should remain the same.

    1. Record original edge id.
    2. Sort edges by weight (do it only once)
    3. Build a MST w/o modifying any edge to get the min_cost
    4. For edge
        a. Exclude it and build MST to find critical
        b. Include it and build MST to find pseudo-critical

    Time Complexity: O(elog(e)) + O(e^2)
    Space Complexity: O(n)
    */
    vector<vector<int>> doit_mst(int n, vector<vector<int>>& edges) {
        // Record the original id.
        for (int i = 0; i < edges.size(); i++)
            edges[i].push_back(i);
        // Sort edges by weight.
        std::sort(begin(edges), end(edges), [](auto& a, auto& b) {
            if (a[2] != b[2])
                return a[2] < b[2];

            return a < b;
        });
        // Cost of MST, ex: edge to exclude, in: edge to include.
        auto MST = [&](int ex = -1, int in = -1) -> int {
            
            UnionFind cu(n);
            int cost = 0;
            int count = 0;

            if (in != -1) {
                cost += edges[in][2];
                cu.Union(edges[in][0], edges[in][1]);
                count++;
            }

            for (int i = 0; i < edges.size(); i++) {

                if (i == ex)
                    continue;

                if (!cu.Union(edges[i][0], edges[i][1]))
                    continue;

                cost += edges[i][2];
                count++;
            }

            return count == n-1 ? cost : INT_MAX; 
        };

        const int min_cost = MST();
        vector<int> criticals, pseudos;

        for (int i = 0; i < edges.size(); i++) {
            // Cost increased or can't form a tree.
            if (MST(i) > min_cost) {
                criticals.push_back(edges[i][3]);
            } else if (MST(-1, i) == min_cost) {
                pseudos.push_back(edges[i][3]);
            }
        }

        return {criticals, pseudos};
    }
};
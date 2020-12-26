/*

1579. Remove Max Number of Edges to Keep Graph Fully Traversable

Alice and Bob have an undirected graph of n nodes and 3 types of edges:

Type 1: Can be traversed by Alice only.
Type 2: Can be traversed by Bob only.
Type 3: Can by traversed by both Alice and Bob.
Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, 
find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. 
The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.

Return the maximum number of edges you can remove, or return -1 if it's impossible for the graph to be fully traversed by Alice and Bob.

 

Example 1:



Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
Output: 2
Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
Example 2:



Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
Output: 0
Explanation: Notice that removing any edge will not make the graph fully traversable by Alice and Bob.
Example 3:



Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
Output: -1
Explanation: In the current graph, Alice cannot reach node 4 from the other nodes. Likewise, Bob cannot reach 1. Therefore it's impossible to make the graph fully traversable.
 

 

Constraints:

1 <= n <= 10^5
1 <= edges.length <= min(10^5, 3 * n * (n-1) / 2)
edges[i].length == 3
1 <= edges[i][0] <= 3
1 <= edges[i][1] < edges[i][2] <= n
All tuples (typei, ui, vi) are distinct.

*/

#include <vector>
#include <numeric>

using std::vector;

class DSU {

    vector<int> p_;
    int e_;

public:

    DSU(int n): p_(n+1), e_(0) {
        iota(begin(p_), end(p_), 0);
    }

    int find(int x) {
        while (x != p_[x]) {
            p_[x] = p_[p_[x]];
            x = p_[x];
        }
        return x;
    }

    int merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return 1;
        p_[rx] = ry;
        ++e_;
        return 0;
    }

    int edges() const { return e_; }
};



class RemoveEdgesToKeepGraphTraverable {

public:

    /*
    A type3 edge is always better than type1 or type2 or both combined
    if there are 3 edges(type1, 2, 3) connect(u, v), we can keep the type3 and remove 2 edges(type1, and type2)

    Solution: greeddy + Union Find

    key: have two trees, one for Alice and one for Bob.

    Create two disjoint-sets

    Two passes:
    1) First pass, use type3 edges.
    2) Second pass, use type1 and type2 edges

    Check there are n-1 edges, in the disjoint-set to be a fully traversalable.

    Noe: type3 edges can be redundant and can be removed as well. 
    */
    
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        DSU A(n), B(n);
        int ans = 0;

        for (auto& c : edges) {
            if (c[0] != 3)
                continue;

            ans += A.merge(c[1], c[2]);
            B.merge(c[1], c[2]);
        }

        for (auto& c : edges) {
            if (c[0] == 3)
                continue;

            DSU& t = (c[0] == 1) ? A : B;
            ans += t.merge(c[1], c[2]);
        }

        return (A.edges() == n - 1 && B.edges() == n - 1) ? ans : -1;
    }
};
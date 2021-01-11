/*
1245. Tree Diameter


Given an undirected tree, return its diameter: the number of edges in a longest path in that tree.

The tree is given as an array of edges where edges[i] = [u, v] is a bidirectional edge between nodes u and v.  Each node has labels in the set {0, 1, ..., edges.length}.

 

Example 1:



Input: edges = [[0,1],[0,2]]
Output: 2
Explanation: 
A longest path of the tree is the path 1 - 0 - 2.
Example 2:



Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
Output: 4
Explanation: 
A longest path of the tree is the path 3 - 2 - 1 - 4 - 5.
 

Constraints:

0 <= edges.length < 10^4
edges[i][0] != edges[i][1]
0 <= edges[i][j] <= edges.length
The given edges form an undirected tree.
*/
#include <vector>
#include <unordered_set>
#include <set>
#include <queue>

using std::queue;
using std::unordered_set;
using std::vector;

class TreeDiameter {

public:

    int doit_dfs(vector<vector<int>>& edges) 
    {
        std::vector<std::vector<int>> m(edges.size() + 1);
        
        for (const auto& v : edges)
        {
            m[v[0]].push_back(v[1]);
        }
        
        int diameter = 0;
        
            
        std::function<int(int, int&)> helper = [&](int currentNode, int& diameter) {
            
            auto maximumDistance = 0;
            auto maximum1 = 0;
            auto maximum2 = 0;
            
            for (auto num : m[currentNode])
            {
                auto distance = helper(num, diameter);

                if (distance > maximum1)
                {
                    maximum2 = maximum1;
                    maximum1 = distance;
                }
                else if (distance > maximum2)
                {
                    maximum2 = distance;
                }
            }

            diameter = std::max(diameter, maximum1 + maximum2);
            return maximum1 + 1;
        };
        
        helper(0, diameter);
        return diameter;
    }

    int doit_bfs(vector<vector<int>>& edges) {
        
        vector<vector<int>> graph(edges.size()+1);

        for (auto& c : edges) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }

        auto bfs = [&](int org) -> std::pair<int, int> {

            queue<std::pair<int,int>> qu;
            qu.push({org, 0});
            unordered_set<int> seen;
            seen.insert(org);
            int maxdepth = 0, node = 0;

            while (!qu.empty()) {

                int size = qu.size();

                while (size--) {

                    auto [cur, dep] = qu.front();
                    qu.pop();
                    if (maxdepth < dep) {
                        maxdepth = dep;
                        node = cur;
                    }

                    for (auto nc : graph[cur]) {

                        if (seen.find(nc) == seen.end()) {
                            seen.insert(nc);
                            qu.push({nc, dep + 1});
                        }
                    }
                }
            }

            return {node, maxdepth};
        };

        auto [n, depth1] = bfs(0);

        auto [n2, depth2] = bfs(n);

        return depth2;
    }
}
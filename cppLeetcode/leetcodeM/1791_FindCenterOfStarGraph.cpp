/*
1791. Find Center of Star Graph

There is an undirected star graph consisting of n nodes labeled from 1 to n. A star graph is a graph where there is one center node and exactly n - 1 edges that connect the center node with every other node.

You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an edge between the nodes ui and vi. Return the center of the given star graph.

 

Example 1:


Input: edges = [[1,2],[2,3],[4,2]]
Output: 2
Explanation: As shown in the figure above, node 2 is connected to every other node, so 2 is the center.
Example 2:

Input: edges = [[1,2],[5,1],[1,3],[1,4]]
Output: 1
 

Constraints:

3 <= n <= 105
edges.length == n - 1
edges[i].length == 2
1 <= ui, vi <= n
ui != vi
The given edges represent a valid star graph.
*/

#include <vector>
#include <unordered_map>
#include <queue>


using std::queue;
using std::unordered_map;
using std::vector;



class CenterOfStarGraph {

public:

    // Realized we can even make it simpler by checking only the first 2 edges, because the center must appear in both places.
    int doit_(vector<vector<int>>& edges) {
        return (edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1]) ? edges[0][0] : edges[0][1;
    }
    
    int doit_(vector<vector<int>>& edges) {
        vector<int> nodes(edges.size() + 1);
        for (const auto& e : edges)
        {
            if (nodes[e[0] - 1] > 0)
            {
                return e[0];
            }
            
            if (nodes[e[1] - 1] > 0)
            {
                return e[1];
            }
            
            ++nodes[e[0] - 1];
            ++nodes[e[1] - 1];
        }
        
        return 0; // should not reach here
    }

    int doit_topsort(vector<vector<int>>& edges) {
        
        unordered_map<int, vector<int>> graph;
        unordered_map<int, int> degrees;
        
        for (auto& c: edges) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
            
            degrees[c[0]]++;
            degrees[c[1]]++;
        }
        
        queue<int> leafs;
        
        for (auto c: degrees) {
            if (c.second == 1) leafs.push(c.first);
        }
        
        while (leafs.size()>1) {
            
            int size = leafs.size();
            
            while (size--) {
                
                auto cur = leafs.front();
                leafs.pop();
                
                for (auto c: graph[cur]) {
                 
                    degrees[c]--;
                    
                    if (degrees[c] == 1) {
                        leafs.push(c);
                    }
                }
                
            }
        }
        
        return leafs.front();
    }
};
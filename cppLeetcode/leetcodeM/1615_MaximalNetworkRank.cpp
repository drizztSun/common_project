/*
1615. Maximal Network Rank


There is an infrastructure of n cities with some number of roads connecting these cities. Each roads[i] = [ai, bi] indicates
that there is a bidirectional road between cities ai and bi.

The network rank of two different cities is defined as the total number of directly connected roads to either city.
If a road is directly connected to both cities, it is only counted once.

The maximal network rank of the infrastructure is the maximum network rank of all pairs of different cities.

Given the integer n and the array roads, return the maximal network rank of the entire infrastructure.



Example 1:



Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
Output: 4
Explanation: The network rank of cities 0 and 1 is 4 as there are 4 roads that are connected to either 0 or 1. The road between 0 and 1 is only counted once.
Example 2:



Input: n = 5, roads = [[0,1],[0,3],[1,2],[1,3],[2,3],[2,4]]
Output: 5
Explanation: There are 5 roads that are connected to cities 1 or 2.
Example 3:

Input: n = 8, roads = [[0,1],[1,2],[2,3],[2,4],[5,6],[5,7]]
Output: 5
Explanation: The network rank of 2 and 5 is 5. Notice that all the cities do not have to be connected.


Constraints:

2 <= n <= 100
0 <= roads.length <= n * (n - 1) / 2
roads[i].length == 2
0 <= ai, bi <= n-1
ai != bi
Each pair of cities has at most one road connecting them.


*/
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::unordered_map;
using std::unordered_set;
using std::vector;

class MaximalNetworkRank {

public:
    
    int doit_dfs(int n, vector<vector<int>>& roads) {
        
        unordered_map<int, unordered_set<int>> graph;
        vector<int> degree(n, 0);
        
        for (auto& c: roads) {
            degree[c[0]]++;
            degree[c[1]]++;
            graph[c[0]].insert(c[1]);
            graph[c[1]].insert(c[0]);
        }
        
        vector<std::pair<int, int>> br;
        for (int i = 0; i < n; i++) 
            br.push_back({degree[i], i});
        
        std::sort(begin(br), end(br), [](auto& a, auto& b) {
            return a < b;
        });
        
        vector<std::pair<int, int>> candidates;
        int last = br.rbegin()->first;
        for (auto it = br.rbegin(); it != br.rend(); it++) {
            if (it->first == last)
                candidates.push_back({it->second, it->first});
            else if (candidates.size() == 1){
                last = it->first;
                candidates.push_back({it->second, it->first});
            } else {
                break;
            }
        }
        
        int res = candidates[0].second + candidates[1].second - 1;
        int size = candidates[0].second == candidates[1].second ? candidates.size() : 1;
        
        for (int i = 0; i < size; i++) {
            for (int j = i+1; j < candidates.size(); j++) {
                if (graph[candidates[i].first].count(candidates[j].first) == 0)
                    return res + 1;
            }
        }
        
        return res;
    }
};
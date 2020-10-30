/*
 
 1192. Critical Connections in a Network
 
 There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network where connections[i] = [a, b]
 represents a connection between servers a and b. Any server can reach any other server directly or indirectly through the network.

 A critical connection is a connection that, if removed, will make some server unable to reach some other server.

 Return all critical connections in the network in any order.

  

 Example 1:



 Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
 Output: [[1,3]]
 Explanation: [[3,1]] is also accepted.
  

 Constraints:

 1 <= n <= 10^5
 n-1 <= connections.length <= 10^5
 connections[i][0] != connections[i][1]
 There are no repeated connections.

 
 */
#include <vector>

using std::vector;



class CriticalConnections {
public:
    
    int dfs(int current, int parent, int level, const vector<vector<int>>& graph, vector<int>& jump, vector<vector<int>>& res) {
        
        jump[current] = level+1;
        
        for (auto child : graph[current]) {
            
            if (child == parent)
                continue;
            else if (jump[child] == -1) {
                jump[current] = std::min(jump[current], dfs(child, current, level+1, graph, jump, res));
            } else if (jump[child] < jump[current]) {
                jump[current] = jump[child];
            }
        }
        
        if (jump[current] == level+1 && current != 0) {
            res.push_back({current, parent});
        }
        
        return jump[current];
    }
    
    
    vector<vector<int>> doit_dfs(int n, vector<vector<int>>& connections) {
    
        vector<vector<int>> graph(n, vector<int>());
        
        for (auto& c : connections) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }
        
        vector<int> jump(n, -1);
        vector<vector<int>> res;
        
        dfs(0, -1, 0, graph, jump, res);
        return res;
    }
};


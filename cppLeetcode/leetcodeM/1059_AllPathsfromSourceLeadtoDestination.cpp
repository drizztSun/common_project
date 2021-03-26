/*
1059. All Paths from Source Lead to Destination


Given the edges of a directed graph where edges[i] = [ai, bi] indicates there is an edge between nodes ai and bi, and two nodes source and destination of this graph, 
determine whether or not all paths starting from source eventually, end at destination, that is:

At least one path exists from the source node to the destination node
If a path exists from the source node to a node with no outgoing edges, then that node is equal to destination.
The number of possible paths from source to destination is a finite number.
Return true if and only if all roads from source lead to destination.

 

Example 1:


Input: n = 3, edges = [[0,1],[0,2]], source = 0, destination = 2
Output: false
Explanation: It is possible to reach and get stuck on both node 1 and node 2.
Example 2:


Input: n = 4, edges = [[0,1],[0,3],[1,2],[2,1]], source = 0, destination = 3
Output: false
Explanation: We have two possibilities: to end at node 3, or to loop over node 1 and node 2 indefinitely.
Example 3:


Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]], source = 0, destination = 3
Output: true
Example 4:


Input: n = 3, edges = [[0,1],[1,1],[1,2]], source = 0, destination = 2
Output: false
Explanation: All paths from the source node end at the destination node, but there are an infinite number of paths, such as 0-1-2, 0-1-1-2, 0-1-1-1-2, 0-1-1-1-1-2, and so on.
Example 5:


Input: n = 2, edges = [[0,1],[1,1]], source = 0, destination = 1
Output: false
Explanation: There is infinite self-loop at destination node.
 

Constraints:

1 <= n <= 104
0 <= edges.length <= 104
edges.length == 2
0 <= ai, bi <= n - 1
0 <= source <= n - 1
0 <= destination <= n - 1
The given graph may have self-loops and parallel edges.

*/
#include <vector>
#include <functional>

using std::vector;


class LeadsToDestination {

    /*
        1059.All-Paths-from-Source-Lead-to-Destination
        此题的本质是用DFS来检查图内是否有环。模板如下：

            bool dfs(int cur)
            {
                visited[cur] = 2;
                for (int next: graph[cur])
                {
                    if (visited[next]==1) continue;
                    if (visited[next]==2) return false;
                    if (dfs(next)==false)  return false;
                }
                visited[cur] = 1;
                return true;
            }
        另外，如果DFS到了端点节点，还要检查是否是destination。
    */
    int visited[10001];
    vector<vector<int>>nextNodes;

public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) 
    {
        nextNodes.resize(n+1);
        for (auto edge: edges)
            nextNodes[edge[0]].push_back(edge[1]);
        
        return dfs(source, destination);        
    }
    
    bool dfs(int cur, int dest)
    {
        visited[cur] = 2;
        if (nextNodes[cur].size() == 0)
        {
            if (cur!=dest)
                return false;
            else
            {
                visited[cur] = 1;
                return true;
            }                
        }
        
        for (auto next: nextNodes[cur])
        {
            if (visited[next]==1) continue;
            if (visited[next]==2) return false;
            if (dfs(next, dest)==false)
                return false;
        }
        visited[cur] = 1;
        return true;
    }


public:

    /*
        1. if destination has child, it would stop at it.
        2. 1 means visited nodes, 2 means loop. when a node has loop, we return false
        3. when it reach end, it must be destination, it is not we just return false. 
    */
    bool doit_dfs(int n, vector<vector<int>>& edges, int source, int destination) {
        
        vector<vector<int>> graph(n);
        vector<int> visited(n, 0);

        for (const auto& c: edges) {
            graph[c[0]].push_back(c[1]);
        }

        std::function<bool(int)> dfs = [&](int cur) {

            if (graph[cur].size() == 0) {

                if (cur != destination) {
                    return false;
                } else {
                    visited[cur] = 1;
                    return true;
                }
            }

            visited[cur] = 2;

            for (auto nc: graph[cur]) {
                
                if (visited[nc] == 1) continue;
                if (visited[nc] == 2) return false; 
                if (!dfs(nc)) return false;
            }

            visited[cur] = 1;
            return true;
        };

        return dfs(source);
    }
};
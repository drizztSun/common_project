/*
785. Is Graph Bipartite?

There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1. You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to. More formally, for each v in graph[u], there is an undirected edge between node u and node v. The graph has the following properties:

    . There are no self-edges (graph[u] does not contain u).
    . There are no parallel edges (graph[u] does not contain duplicate values).
    . If v is in graph[u], then u is in graph[v] (the graph is undirected).
    . The graph may not be connected, meaning there may be two nodes u and v such that there is no path between them.

A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that every edge in the graph connects a node in set A and a node in set B.

Return true if and only if it is bipartite.

 

Example 1:


Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
Output: false
Explanation: There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.
Example 2:


Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Output: true
Explanation: We can partition the nodes into two sets: {0, 2} and {1, 3}.
 

Constraints:

.graph.length == n
.1 <= n <= 100
.0 <= graph[u].length < n
.0 <= graph[u][i] <= n - 1
.graph[u] does not contain u.
.All the values of graph[u] are unique.
.If graph[u] contains v, then graph[v] contains u.

*/

#include <vector>
#include <stack>
#include <unordered_map>
#include <functional>

using std::unordered_map;
using std::stack;
using std::vector;

class isBipartite {

    /*
        785.Is-Graph-Bipartite

        对于任意一个定点（比如说节点0），假设将其归入A组，那么所有0节点的相邻节点必定都要归入B组；同理0节点的相邻节点的相邻节点，必定又都要归入A组。由此可以发现，我们从0节点开始做BFS的遍历，
        扩展的时候以A组/B组的次序交替标记，就可以将与0节点在同一个连通图内的所有节点进行分组。如果在BFS过程中遇到已经分组的节点并且发现矛盾之处，那么就可以返回false。

        注意，以上的BFS是针对同一个连通图而言。如果整个graph有若干个连通图（彼此之间不相连），那么就需要遍历所有的节点（查找未曾访问过的节点作为一个连通图的起始节点），以保证所有的连通图都被逐一访问和BFS遍历过。

        当然，本题也可以用并查集来做。根据题意，对于graph[i]内的所有节点{j}，它们必定属于同一集合。因此我们Union每个graph[i]的点集，并查看过程中是否遇到任何矛盾。
    */
    bool isBipartite(vector<vector<int>>& graph) 
    {
        int n = graph.size();
        vector<int>visited(n,-1);
        
        for (int i=0; i<n; i++)
        {
            if (visited[i]!=-1)
                continue;
            
            queue<pair<int,int>>q;
            q.push({i,0}); // {node, group}
            visited[i] = 0;
        
            while (!q.empty())
            {
                int node = q.front().first;
                int group = q.front().second;
                q.pop();
                        
                for (auto next: graph[node])
                {                   
                
                    if (visited[next]!=-1)
                    {
                        if (visited[next]!=1-group)
                            return false;
                    }
                    else
                    {
                        visited[next] = 1-group;                
                        q.push({next, 1-group});
                    }
                }
            }        
        }
                
        return true;        
    }

    
public:
    bool isBipartite_disjoint(vector<vector<int>>& graph) 
    {
        int N=graph.size();
        unordered_map<int,int>Father;


        std::function<int(int)> FindSet = [&](int x) {
            if (x!=Father[x]) Father[x]=FindSet(Father[x]);
            return Father[x];
        };
        
        auto Union = [&](int x, int y)
        {
            x=Father[x];
            y=Father[y];

            if (x<y)
                Father[y]=x;
            else
                Father[x]=y;
        };

        for (int i=0; i<N; i++)
            Father[i]=i;
        
        for (int i=0; i<N; i++)
        {
            int k;
            if (graph[i].size()>0)
                k = graph[i][0];
            
            for (auto j:graph[i])
            {
                if (FindSet(i)==FindSet(j))
                    return false;                
                Union(k,j);
            }
        }
        
        return true;
    }
    


public:

    /*
        Approach #1: Coloring by Depth-First Search [Accepted]
        Intuition

        Color a node blue if it is part of the first set, else red. We should be able to greedily color the graph if and only if it is bipartite: 
        one node being blue implies all it's neighbors are red, all those neighbors are blue, and so on.


        Diagram of coloring neighbors of nodes

        Algorithm

        We'll keep an array (or hashmap) to lookup the color of each node: color[node]. The colors could be 0, 1, or uncolored (-1 or null).

        We should be careful to consider disconnected components of the graph, by searching each node. 
        For each uncolored node, we'll start the coloring process by doing a depth-first-search on that node. 
        Every neighbor gets colored the opposite color from the current node. If we find a neighbor colored the same color as the current node, then our coloring was impossible.

        To perform the depth-first search, we use a stack. For each uncolored neighbor in graph[node], we'll color it and add it to our stack, 
        which acts as a sort of "todo list" of nodes to visit next. Our larger loop for start... ensures that we color every node. Here is a visual dry-run of the algorithm whose Python code is below.

        Complexity Analysis

        Time Complexity: O(N + E), where NN is the number of nodes in the graph, and EE is the number of edges. We explore each node once when we transform it from uncolored to colored, traversing all its edges in the process.

        Space Complexity: O(N), the space used to store the color.
    */
    bool doit_(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1);
        
        
        for (int start = 0; start < n; start++) {
            
            if (color[start] != -1) continue;
            
            color[start] = 0;
            
            stack<int> st;
            st.push(start);
            
            while (!st.empty()) {
                
                int cur = st.top(); st.pop();
                
                for (auto child : graph[cur]) {
                    
                    if (color[child] == -1) {
                        color[child] = 1 ^ color[cur];
                        st.push(child);
                    } else if (color[child] == color[cur]) {
                         return false;
                    }
                }
            }
            
        }
        
        return true;
    }
};
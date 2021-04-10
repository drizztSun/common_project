/*
1820. Maximum Number of Accepted Invitations


There are m boys and n girls in a class attending an upcoming party.

You are given an m x n integer matrix grid, where grid[i][j] equals 0 or 1. If grid[i][j] == 1, then that means the ith boy can invite the jth girl to the party. 
A boy can invite at most one girl, and a girl can accept at most one invitation from a boy.

Return the maximum possible number of accepted invitations.

 

Example 1:

Input: grid = [[1,1,1],
               [1,0,1],
               [0,0,1]]
Output: 3
Explanation: The invitations are sent as follows:
- The 1st boy invites the 2nd girl.
- The 2nd boy invites the 1st girl.
- The 3rd boy invites the 3rd girl.
Example 2:

Input: grid = [[1,0,1,0],
               [1,0,0,0],
               [0,0,1,0],
               [1,1,1,0]]
Output: 3
Explanation: The invitations are sent as follows:
-The 1st boy invites the 3rd girl.
-The 2nd boy invites the 1st girl.
-The 3rd boy invites no one.
-The 4th boy invites the 2nd girl.
 

Constraints:

grid.length == m
grid[i].length == n
1 <= m, n <= 200
grid[i][j] is either 0 or 1.


*/

#include <vector>
#include <queue>

using std::queue;
using std::vector;

class MaximumInvitations {

public:

    /*
        You'd better know some basic ideas about Hungrian algorithm and the concept of agumenting path.

        An agumenting path is a path starting from a unpaired node on the left, ending at a unpaired node on the right, and consists of several unused edges and used edges alternatively 
        (i.e. unused edge->used edge->unused edge->...). Note that the number of unsed edges is always larger than the number of used edges by 1.

        For a certain unpaired left node A, we use DFS to find one augmenting path. Then along this path, we flip the used edges to be unused, and the unused edges to be used. There would be the following consequences:

        1. No invalidity would be introduced, which means no node would be paired with two other nodes simutaneously.
        2. The number of used edges must be more than the number of unused edges by 1. It means we improved our objective (have one more node pair).
        3. The starting point A has now been paired.
        If we are not able to find such an augmenting path for this starting point A , it means there is no way to get A paird with others while making the overal objective better.
        
        There is another BFS version, much complicated than DFS. But the BFS version runs faster when the graph is sparse.
    */
    int m, n, t;
    vector<int> next[400];
    int match[400];
public:
    int maximumInvitations(vector<vector<int>>& grid) 
    {
        m = grid.size();
        n = grid[0].size();
        t = m+n;
        
        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                if (grid[i][j])
                {
                    next[i].push_back(m+j);
                    next[m+j].push_back(i);
                }
            }
        
        for (int i=0; i<t; i++)
            match[i] = -1;
        
        vector<bool>visited(t);
        
        int count = 0;
        for (int i=0; i<m; i++)
        {
            visited.assign(t, 0);
            if (dfs(i, visited))
                count++;            
        }
        return count;
    }
    
    bool dfs(int i, vector<bool>&visited)
    {
        for (int j: next[i])
        {
            if (visited[j]) continue;
            visited[j] = true;
            if (match[j]==-1 || dfs(match[j], visited))
            {
                match[i] = j;
                match[j] = i;
                return true;
            }
        }
        return false;
    }


     /*
         in bipartite graphs, the maximum matching problem is much easier to solve, because we can reduce it to the maximum flow problem.
         Edmonds-Karp algorithm - it is an implementation of Ford-Fulkerson method.
         We can add two new nodes to the graph: a source and a sink.
         we have also to use the reversed of directed edges when we are looking for augmenting paths.

         https://cp-algorithms.com/graph/edmonds_karp.html
        source                      sink
         0      1           m+1     m+n+1
                2           m+2
                3           .
                .           .
                .           .
                m           m+n
    */
    int maximumInvitations(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // stores the capacity for every pair of vertices
        vector<vector<int>> capacity(m+n+2, vector<int>(m+n+2, 0));
        // the adjacency list of the undirected graph
        vector<vector<int>> adj(m+n+2);
        
        for(int i = 1; i <= m; i++) {
            capacity[0][i] = 1;
            adj[0].push_back(i);
            adj[i].push_back(0);
        }
        for(int i = m+1; i <= m+n; i++) {
            capacity[i][m+n+1] = 1;
            adj[i].push_back(m+n+1);
            adj[m+n+1].push_back(i);
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    capacity[i+1][m+1+j] = 1;
                    adj[i+1].push_back(m+1+j);
                    adj[m+1+j].push_back(i+1);
                }
            }
        }
        
        return maxflow(capacity, adj, 0, m+n+1);
    }
    
    int maxflow(vector<vector<int>>& capacity, vector<vector<int>>& adj, int s, int t) {
        int flow = 0;
        vector<int> parent(adj.size());
        int newflow;
        
        while(newflow = bfs(capacity, adj, s, t, parent)) {  // augmenting path
            flow += newflow;
            int cur = t;
            while(cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= newflow;
                capacity[cur][prev] += newflow;
                cur = prev;
            }
        }
        return flow;
    }
    
    int bfs(vector<vector<int>>& capacity, vector<vector<int>>& adj, int s, int t, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int,int>> q; // current vertex, current flow
        q.push({s, INT_MAX});
        
        while(!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();
            
            for(auto& next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next]) {
                    parent[next] = cur;
                    int newflow = min(flow, capacity[cur][next]);
                    if (next == t) return newflow;
                    q.push({next, newflow});
                }
            }
        }
        return 0;
    }
};
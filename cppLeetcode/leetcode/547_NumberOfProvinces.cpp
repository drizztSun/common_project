/*
547. Number of Provinces



There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

 

Example 1:


Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
Example 2:


Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
 

Constraints:

1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] is 1 or 0.
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]


*/
#include <vector>
#include <queue>
#include <functional>
#include <unordered_set>

using std::unordered_set;
using std::queue;
using std::vector;


class NumberOfProvinces {

    /*
        注意，最后需要重新遍历一遍所有节点，通过FindSet来更新所有的父节点。

        unordered_set<int>Set;
        for (int i=0; i<N; i++)
        {
            Father[i] = FindSet(i);
            Set.insert(Father[i]);
        }
        return Set.size();
    */
    vector<int>Father;

    int findCircleNum(vector<vector<int>>& M) 
    {
        int N=M.size();
        
        for (int i=0; i<N; i++)
            Father.push_back(i);
        
        for (int i=0; i<N; i++)
         for (int j=0; j<N; j++)
         {
             if (M[i][j]==0) continue;
             
             if (FindSet(i)!=FindSet(j))
                 Union(i,j);             
         }
        
        unordered_set<int>Set;
        for (int i=0; i<N; i++)
        {
            Father[i] = FindSet(i);
            Set.insert(Father[i]);
        }
            
        return Set.size();
    }
    
    int FindSet(int x)
    {
        if (x!=Father[x])
        {
            Father[x]=FindSet(Father[x]);
        }
        return Father[x];
    }
    
    void Union (int x, int y)
    {
        x=Father[x];
        y=Father[y];
        if (x<=y)
            Father[y]=x;
        else
            Father[x]=y;
    }



public:

    int doit_disjoint(vector<vector<int>>& isConnected) {
        
        int m = isConnected.size();
        
        vector<int> parent(m);
        for (int i = 0; i < m; i++) 
            parent[i] = i;
        
    
        auto find = [&](int node) {
            while (node != parent[node]) {
                parent[node] = parent[parent[node]];
                node = parent[node];
            }
            return node;
        };
        
        auto merge = [&](int a, int b) {
            int pa = find(a);
            int pb = find(b);
            if (pa == pb) return;
            
            if (pa < pb)
                parent[pb] = pa;
            else
                parent[pa] = pb;
        };
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (isConnected[i][j] == 1) merge(i, j);
            }
        }
        
        unordered_set<int> groups;
        for(int i = 0; i < m; i++) {
            groups.insert(find(i));
        }
        
        return groups.size();
    }

    /*
        Approach #1 Using Depth First Search[Accepted]
        Algorithm

        The given matrix can be viewed as the Adjacency Matrix of a graph. By viewing the matrix in such a manner, our problem reduces to the problem of finding the number of connected components in an undirected graph. In order to understand the above statement, consider the example matrix below:

        M= [1 1 0 0 0 0

            1 1 0 0 0 0

            0 0 1 1 1 0

            0 0 1 1 0 0

            0 0 1 0 1 0

            0 0 0 0 0 1]

        If we view this matrix M as the adjancency matrix of a graph, the following graph is formed:

        Friend_Circles

        In this graph, the node numbers represent the indices in the matrix M and an edge exists between the nodes numbered ii and jj, if there is a 1 at the corresponding M[i][j]M[i][j].

        In order to find the number of connected components in an undirected graph, one of the simplest methods is to make use of Depth First Search starting from every node. We make use of visitedvisited array of size NN(MM is of size NxNNxN). This visited[i]visited[i] element is used to indicate that the i^{th}i 
        th
        node has already been visited while undergoing a Depth First Search from some node.

        To undergo DFS, we pick up a node and visit all its directly connected nodes. But, as soon as we visit any of those nodes, we recursively apply the same process to them as well. Thus, we try to go as deeper into the levels of the graph as possible starting from a current node first, leaving the other direct neighbour nodes to be visited later on.

        The depth first search for an arbitrary graph is shown below:

        Current
        1 / 14
        From the graph, we can see that the components which are connected can be reached starting from any single node of the connected group. Thus, to find the number of connected components, we start from every node which isn't visited right now and apply DFS starting with it. We increment the countcount of connected components for every new starting node.


        Complexity Analysis

        Time complexity : O(n^2). The complete matrix of size n^2 is traversed.

        Space complexity : O(n). visitedvisited array of size nn is used.
    
    */
    int doit_dfs(vector<vector<int>>& isConnected) {

        int N = isConnected.size();
        vector<bool> visited(N, false);

        std::function<void(int i)> dfs = [&](int i) {
            for (int j = 0; j < N; j++) {
                if (!visited[j] && isConnected[i][j] == 1) {
                    visited[j] = true;
                    dfs(j);
                }
            }
        };

        int ans = 0;
        for (int i = 0; i < N; i++) {
            if (visited[i]) 
                continue;
            
            visited[i] = true;
            dfs(i);
            ans++;
        }

        return ans;
    }

    /*
        Approach #2 Using Breadth First Search[Accepted]
        Algorithm

        As discussed in the above method, if we view the given matrix as an adjacency matrix of a graph, we can use graph algorithms easily to find the number of connected components. 
        This approach makes use of Breadth First Search for a graph.

        In case of Breadth First Search, we start from a particular node and visit all its directly connected nodes first. 
        After all the direct neighbours have been visited, we apply the same process to the neighbour nodes as well. Thus, we exhaust the nodes of a graph on a level by level basis. 
        An example of Breadth First Search is shown below:

        Current
        7 / 13
        In this case also, we apply BFS starting from one of the nodes. We make use of a visitedvisited array to keep a track of the already visited nodes. 
        We increment the countcount of connected components whenever we need to start off with a new node as the root node for applying BFS which hasn't been already visited.


        Complexity Analysis

        Time complexity : O(n^2)O(n 
        2
        ). The complete matrix of size n^2n 
        2
        is traversed.

        Space complexity : O(n)O(n). A queuequeue and visitedvisited array of size nn is used.
    */
    int doit_bfs(vector<vector<int>>& isConnected) {
        
        int N = isConnected.size();
        vector<bool> visited(N, false);
        int ans = 0;

        for (int i = 0; i < N; i++) {

            if (visited[i]) continue;

            queue<int> qu;
            visited[i] = true;
            qu.push(i);

            while (!qu.empty()) {

                int cur = qu.front();
                qu.pop();

                for (int j = 0; j < N; j++) {
                    if (isConnected[cur][j] == 1 && !visited[j]) {
                        visited[j] = true;
                        qu.push(j);
                    }
                }
            }

            ans++;
        }

        return ans;
    }
    

};
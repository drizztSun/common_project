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
#include <functional>

using std::vector;



class CriticalConnections {


    /*
        1192.Critical-Connections-in-a-Network
        本题本质就是图论中的经典问题，如何求一个无向图中的割边（critical edge）或者叫做桥（bridge）。

        网上的教程中，我觉得这一篇是最容易理解的：https://www.cnblogs.com/nullzx/p/7968110.html

        简单地说，我们可以以任意一个未访问过的节点作为根节点，用DFS的顺序来进行搜索，即永远深度优先，然后回溯再搜索其他分支。如果碰到访问过的节点，就停止，保证不行成环。

        我们在dfs的过程中维护两个数组，一个是dfs[u]，表示节点u被第一次访问时的顺序（可以理解为时间戳），这个是唯一且不变的量。另一个数组low[u]比较关键，初始的时候low[u]=dfn[u]。我们以u为节点的开始dfs（注意抵达u之前可能还有u的父节点，但我们dfs的时候不走回头路），想象它最终形成一棵搜索树，那么u的所有子节点中止的条件不外乎有两个：一个是走进了死胡同；另一个就是遇到了已经访问过的节点，特别的，这个已经访问过的节点有可能是u的祖先节点！所以，有了这样的搜索树之后，low[u]可以有机会更新为它所有的子节点v可以接触到的最小时间戳low[v]。

        令v是u的一个子节点，且有low[v]>dfn[u]，这说明什么呢？说明从v出发最终无法绕道u的前面去。因此(v,u)就是割边。如果消除了这条边，v及其子树就是一个孤岛，无法与u或u的祖先相通。同理，如果low[v]>=dfn[u]，说明u是一个割点，如果消除了这个点，那么v及其子树也是一个孤岛。

        本题中我们还设置了一个parent，其实是为了标记dfs过程中的搜索顺序。因为无向图for auto v: next[u]的遍历过程中，v可能是u的父节点，这种情况下v其实不能作为从u开始dfs的下一个目的地（否则就是走回头路了），所以得排除。
    */
    vector<vector<int>>rets;
    vector<vector<int>>next;
    int time = 0;
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) 
    {
        next.resize(n);
        for (auto x:connections)
        {
            next[x[0]].push_back(x[1]);
            next[x[1]].push_back(x[0]);
        }
            
        vector<bool>visited(n);
        vector<int>dfn(n,0);
        vector<int>low(n,0);
        vector<int>parent(n,-1);
        
        for (int i = 0; i < n; i++) 
        {            
            if (visited[i] == false) 
                DFS(i, visited, dfn, low, parent); 
        }
        
        return rets;
    }
    
    
    void DFS(int u, vector<bool>&visited, vector<int>&dfn, vector<int>&low, vector<int>&parent) 
    {  
        visited[u] = true; 
    
        dfn[u] = low[u] = ++time; 
              
        for (int v : next[u]) 
        { 
            if (v == parent[u])
                continue;
            
            if (!visited[v])
            { 
                parent[v] = u; 
                DFS(v, visited, dfn, low, parent); 
  
                if (low[v] > dfn[u]) rets.push_back({v,u}); // critical edge
                
                // if(low[v] >= dfn[u]), then u is a critical vertex
                
                low[u]  = std::min(low[u], low[v]); 
            }   
            else
            {                
                low[u]  = std::min(low[u], dfn[v]); 
            }
        } 
    } 


public:
    
    
    vector<vector<int>> doit_dfs(int n, vector<vector<int>>& connections) {
    
        vector<vector<int>> graph(n);
        
        for (auto& c : connections) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }
        
        vector<int> jump(n, -1);
        vector<vector<int>> res;

        std::function<int(int, int, int)> dfs = [&](int current, int parent, int level) {
        
            jump[current] = level+1;
            
            for (auto child : graph[current]) {
                
                if (child == parent) continue;
                
                if (jump[child] == -1) {
                    // update current node index, from child. always be the minimal value.
                    // if there is cycle, it reach some early visited node, the node id will be so small
                    // we need to update all nodes in circle to be that smaller color number.
                    jump[current] = std::min(jump[current], dfs(child, current, level+1));
                } else if (jump[child] < jump[current]) {
                    // find the circle
                    jump[current] = jump[child];
                }
            }
            
            if (jump[current] == level+1 && current != 0) {
                // if current node jump is still level + 1, it will be critial with its parent. 
                // becuase there is no cycle in its child.
                res.push_back({current, parent});
            }
            
            // return current one's color index.
            return jump[current];
        };

        dfs(0, -1, 0);
        return res;
    }
};


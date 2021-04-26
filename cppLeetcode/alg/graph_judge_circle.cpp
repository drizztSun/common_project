#include <queue>
#include <vector>
#include <unordered_set>
#include <functional>

using std::unordered_set;
using std::queue;
using std::vector;

namespace graph_check{

    constexpr int numNodes = 1000;
    int visited[numNodes];
    vector<vector<int>> next;

    bool dfs(int cur)
    {
        if (visited[cur]==1) return true;

        visited[cur] = 2;
        for (int next: next[cur])
        {
            if (visited[next]==1) continue;
            if (visited[next]==2) return false;
            if (dfs(next)==false)  return false;
        }
        visited[cur] = 1;
        return true;
    }

    bool bfs_circle() 
    {        
        queue<int>q;
        int count = 0;

        vector<int>InDegree(numNodes,0);
        for (int i=0; i<numNodes; i++)
            for (int j: next[i])
                InDegree[j]++;

        for (int i=0; i<numNodes; i++)
        {
            if (InDegree[i]==0) 
            {
                q.push(i);
                count++;
            }
        }
                    
        while (!q.empty())
        {
            int curCourse = q.front();
            q.pop();
            for (auto child: next[curCourse])
            {
                InDegree[child]--;
                if (InDegree[child]==0)
                {
                    q.push(child);
                    count++;
                }                    
            }
        }        
        
        return count==numNodes;        
    }

    void check_circle() {
        // prepare next; // next[i][j]: there is a directional path i->j

        // bfs 判断有环
        // return bfs();

        // dfs 判断有环
        for (int i=0; i<numNodes; i++)
        {            
            if (dfs(i)==false) return false;            
        }
        return true;
    }


    // check graph is tree

    bool doit_dfs(int n, vector<vector<int>>& edges) {
        
        if (edges.size() != n-1) return false; 
 
        vector<vector<int>> graph(n);

        for (const auto& c: edges) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }

        unordered_set<int> nodes;

        std::function<bool(int, int)> dfs = [&](int cur, int parent) {
            if (nodes.count(cur)) return false;
            nodes.insert(cur);
            for (auto nx: graph[cur]) {

                if (nx == parent) continue;
                if (!dfs(nx, cur)) return false;
            }
            return true;
        };

        return dfs(0, -1) && nodes.size() == n;
    }

    // Check graph is a tree
    bool doit_disjoint(int n, vector<vector<int>>& edges) {

        if (edges.size() != n-1) return false; 

        vector<int> parent(n, 0);
        std::iota(begin(parent), end(parent), 0);

        auto find = [&](int cur) {
            while (parent[cur] != cur) {
                parent[cur] = parent[parent[cur]];
                cur = parent[cur];
            }
            return cur;
        };

        auto merge = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            if (pa == pb) return;

            if (pa < pb) 
                parent[pb] = pa;
            else
                parent[pa] = pb;
        };

        for (const auto& c: edges) {
            if (find(c[0]) == find(c[1])) return false;
            merge(c[0], c[1]);
        }

        int cnt = 0;
        for (int i = 0; i < n; i++)
            cnt += (parent[i] == i);

        return cnt == 1;
    }

    bool doit_bfs(int n, vector<vector<int>>& edges) {
        
        if (edges.size() != n-1) return false; 
 
        vector<vector<int>> graph(n);

        for (const auto& c: edges) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }

        unordered_set<int> nodes;
        vector<int> parent(n, -1);
        queue<int> qu;
        parent[0] = -1;
        qu.push(0);

        while (!qu.empty()) {

            int cur = qu.front(); qu.pop();

            for (auto nx: graph[cur]) {
                if (parent[cur] == nx) continue;
                if (nodes.count(nx)) return false;
                parent[nx] = cur;
                qu.push(nx);
            }

            nodes.insert(cur);
        }

        return nodes.size() == n;
    }

    // depht a graph, for circle
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        
        vector<vector<int>> graph(n);
        
        for (const auto& edge : connections) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<int> jump(n, -1);
        vector<vector<int>> res;
        
        
        std::function<int(int, int, int)> dfs =[&] (int cur, int level, int parent) {
            
            jump[cur] = level+1;
            
            for(auto child : graph[cur]) {
                
                if (child == parent) continue;
                
                if (jump[child] == -1) {
                    jump[cur] = std::min(jump[cur], dfs(child, level+1, cur));
                } else if (jump[child] < jump[cur]) {
                    jump[cur] = jump[child];
                }
            }
            
            if (jump[cur] == level + 1 && parent != -1)
                res.push_back({parent, cur});
               
            return jump[cur];
        };    
        
        
        
        dfs(0, 0, -1);
        
        return res;
        
    }
}

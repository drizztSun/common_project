/*
1135. Connecting Cities With Minimum Cost

There are N cities numbered from 1 to N.

You are given connections, where each connections[i] = [city1, city2, cost] represents the cost to connect city1 and city2 together.  
(A connection is bidirectional: connecting city1 and city2 is the same as connecting city2 and city1.)

Return the minimum cost so that for every pair of cities, there exists a path of connections (possibly of length 1) that connects those two cities together.  
The cost is the sum of the connection costs used. If the task is impossible, return -1.

 

Example 1:



Input: N = 3, connections = [[1,2,5],[1,3,6],[2,3,1]]
Output: 6
Explanation: 
Choosing any 2 edges will connect all cities so we choose the minimum 2.
Example 2:



Input: N = 4, connections = [[1,2,3],[3,4,4]]
Output: -1
Explanation: 
There is no way to connect all cities even if all edges are used.
 

Note:

1 <= N <= 10000
1 <= connections.length <= 10000
1 <= connections[i][0], connections[i][1] <= N
0 <= connections[i][2] <= 10^5
connections[i][0] != connections[i][1]

*/
#include <vector>

using std::vector;

class MinimumCostCity {

    /*
        1135.Connecting-Cities-With-Minimum-Cost
        本题的本质是构造一个最小生成树．一个比较简单的算法就是Kruskal算法，本质就是贪心＋Union Find．

        按照边的权重顺序（从小到大）将边加入生成树中，但是若加入该边会与生成树形成环则不加入该边。直到树中含有V-1条边为止。这些边组成的就是该图的最小生成树。

        Kruskal算法的时间复杂度为 ElogE。
    */
     static bool cmp(vector<int>&a, vector<int>&b)
    {
        return a[2]<b[2];
    }
    vector<int>Father;
        
public:
    int findFather(int x)
    {
        if (Father[x]!=x)
            Father[x] = findFather(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y) Father[y] = x;
        else Father[x] = y;
    }
    
    int minimumCost(int N, vector<vector<int>>& connections) 
    {
        Father.resize(N+1);
        for (int i=1; i<=N; i++)
            Father[i] = i;
        
        std::sort(connections.begin(), connections.end(), cmp);
        
        int result = 0;
        for (auto edge: connections)
        {
            int a = edge[0];
            int b = edge[1];
            if (findFather(a)!=findFather(b))
            {
                Union(a,b);
                result+=edge[2];
            }
        }
                
        for (int i=1; i<=N; i++)
        {
            if (findFather(i)!=Father[1])
                return -1;
        }
        
        return result;
    }


public:

    int doit_(int N, vector<vector<int>>& connections) {

        std::sort(begin(connections), end(connections), [](const auto& a, const auto& b) { return a[2] < b[2]; });

        vector<int> parent(N+1, -1);
        int group = N;
    
        for (int i = 0; i <= N; i++)
            parent[i] = i;

        auto find = [&](int n) {
            while (parent[n] != n) {
                parent[n] = parent[parent[n]];
                n = parent[n];
            }
            return n;
        };

        auto merge = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            
            if (pa < pb)
                parent[pb] = pa;
            else
                parent[pa] = pb;
        };

        
        int cost = 0;
        
        for (const auto& conn : connections) {
            
            int s = conn[0], e = conn[1], c = conn[2];
            
            if (find(s) != find(e)) {
                merge(s, e);
                group--;
                cost += c;
            }
                
            if (group == 1) return cost;
        }
        
        return -1;
    }
};
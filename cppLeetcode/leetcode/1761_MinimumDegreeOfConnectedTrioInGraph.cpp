/*
1761. Minimum Degree of a Connected Trio in a Graph

You are given an undirected graph. You are given an integer n which is the number of nodes in the graph and an array edges, 

where each edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi.

A connected trio is a set of three nodes where there is an edge between every pair of them.

The degree of a connected trio is the number of edges where one endpoint is in the trio, and the other is not.

Return the minimum degree of a connected trio in the graph, or -1 if the graph has no connected trios.

 

Example 1:


Input: n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
Output: 3
Explanation: There is exactly one trio, which is [1,2,3]. The edges that form its degree are bolded in the figure above.
Example 2:


Input: n = 7, edges = [[1,3],[4,1],[4,3],[2,5],[5,6],[6,7],[7,5],[2,6]]
Output: 0
Explanation: There are exactly three trios:
1) [1,4,3] with degree 0.
2) [2,5,6] with degree 2.
3) [5,6,7] with degree 2.
 

Constraints:

2 <= n <= 400
edges[i].length == 2
1 <= edges.length <= n * (n-1) / 2
1 <= ui, vi <= n
ui != vi
There are no repeated edges.

*/
#include <vector>
#include <unordered_set>
#include <algorithm>

using std::unordered_set;
using std::vector;

class MinTrioDegree {

public:

    int doit_sort(int n, vector<vector<int>>&edges) {

        vector<unordered_set<int>> graph(n+1);

        for (auto& c : edges) {
            graph[c[0]].insert(c[1]);
            graph[c[1]].insert(c[0]);
        }

        vector<std::pair<int, int>> nds;
        for (int i = 1; i <= n; i++) {
            nds.push_back({graph[i].size(), i});
        }
        std::sort(begin(nds), end(nds));

        vector<std::pair<int, std::pair<int, int>>> edgeds;
        for (auto& c : edges) {
            edgeds.push_back({graph[c[0]].size() + graph[c[1]].size(), {c[0], c[1]}});
        }
        std::sort(begin(edgeds), end(edgeds));

        // sort can help us to find the min res as quick as possible
        int res = INT_MAX;
        for (auto& edge : edgeds) {
            if (res <= edge.first) break;

            for (auto& node : nds) {

                if (res <= edge.first + node.first) break;
                int a = node.second, b = edge.second.first, c = edge.second.second;

                if (graph[a].count(b) > 0 && graph[a].count(c) > 0)
                    res = std::min(res, edge.first + node.first);
            }
        }

        return res == INT_MAX ? -1 : res - 6;
    }

    /*
        1761.Minimum-Degree-of-a-Connected-Trio-in-a-Graph
        我们要找一个trio，肯定要先遍历其中的一个点A。而该trio的另外两个点B和C，必然也都是A的邻接节点。所以我们在A的邻接节点集合next[A]中寻找B和C显然效率更高。
        但是我们似乎没有特别高效的方法直接在next[A]中找出符合条件的二元对{B,C}，只能在next[A]中用二重循环枚举B和C，再查看B和C是否是邻接的。查看B和C是否邻接，我们可以通过预处理的邻接矩阵c[x][y]来实现o(1)的查询。
        预先构造的邻接矩阵c[x][y]表示任意两点之间是否相邻，时间复杂度是o(E)，是可以接受的。

        所以整体而言，寻找三元对{A,B,C}需要o(N^3)的大框架：

        for A in range(1,n):
        for (B,C) in next[A]:
            if c[B][C]==1: 
            (A,B,C)是一个trio
            ret += inDegree[A] + inDegree[B] + inDegree[C] - 6
        以上的方法会TLE。如何改进呢？我们发现，根据A找(B,C)，等价于根据B找(A,C)，根据C找(A,B)。所以整体的时间复杂度浪费了三倍。
        如何避免这个问题呢？解决方法是：把有向图变成无向图。也就是说，从A能找到(B,C)，但是让B不会找到(A,C)，因此我们可以令AB为单向边，即只允许A->B. 同理如果也令A->C为单向边的话，那么C就不会找到(A,B)。由这个技巧，我们可以将整体o(N^3)的复杂度降低至1/3。
    */
    int doit_(int n, vector<vector<int>>& edges) {

        vector<vector<int>> connect(n+1, vector<int>(n+1));
        vector<int> degree(n+1);
        vector<vector<int>> next(n+1);

        for (auto e: edges)
        {
            connect[e[0]][e[1]] = 1;
            connect[e[1]][e[0]] = 1;
            degree[e[0]] += 1;
            degree[e[1]] += 1;
            
            int x = std::min(e[0],e[1]), y = std::max(e[0],e[1]); 
            next[x].push_back(y);
        }
        
        int ret = INT_MAX;
        for (int a = 1; a <=n; a++)
        {
            for (int i=0; i < next[a].size(); i++)
                for (int j=i+1; j < next[a].size(); j++)
                {
                    int b = next[a][i], c = next[a][j];
                    if (connect[b][c]==1)
                        ret = std::min(ret, degree[a]+degree[b]+degree[c]-6);
                }
        }
        
        return ret == INT_MAX ? -1 : ret;
    }
};
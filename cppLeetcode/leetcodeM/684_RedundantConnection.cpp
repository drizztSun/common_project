/*
684. Redundant Connection


In this problem, a tree is an undirected graph that is connected and has no cycles.

The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.

Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3
Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

Update (2017-09-26):
We have overhauled the problem description + test cases and specified clearly the graph is an undirected graph. For the directed graph follow up please see Redundant Connection II). We apologize for any inconvenience caused.


*/
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class RedundantConnection {

    /*
        684.Redundant-Connection
        考虑这些edges所组成的网络是个无向图。那么这个图是tree的充要条件是：所有节点到另外一个节点的通路有且仅有一条。

        所以从前往后遍历edges，一旦发现某个edge的两个点，已经在之前的遍历中是联通的了，那么这个edge的加入就会导致“树”定义的不成立，故必须除去。根据题意，保证了只有唯一的答案，故就不用继续往后查下去了。

        于是本题就是一个考察union find的基本题。两个基本操作要熟练：

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
        if (x<y)
            Father[y]=x;
        else
            Father[x]=y;
        }
        在遍历edges的过程中

        int x=edges[i][0];
        int y=edges[i][1];
        if (FindSet[x]==FindSet[y])  //注意，不是 if (Father[x]==Father[y])，因为Father[x]可能还没更新到这个集合的根。
            return edges[i];
        else 
            Union(x,y);
    */
   unordered_map<int,int>Father;
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) 
    {        
        for (int i=0; i<edges.size(); i++)
        {
            Father[edges[i][0]]=edges[i][0];
            Father[edges[i][1]]=edges[i][1];
        }
        
        for (int i=0; i<edges.size(); i++)
        {
            if (FindSet(edges[i][0])==FindSet(edges[i][1]))
                return edges[i];
            else
                Union(edges[i][0],edges[i][1]);
        }
        return edges[0];
    }
    
    int FindSet(int x)
    {
        if (x!=Father[x])
        {
            Father[x]=FindSet(Father[x]);
        }
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x=FindSet(x);
        y=FindSet(y);
        if (x<=y)
            Father[y]=x;
        else
            Father[x]=y;
    }

public:

    /*
        Approach #2: Union-Find [Accepted]
        Intuition and Algorithm

        If we are familiar with a Disjoint Set Union (DSU) data structure, we can use this in a straightforward manner to solve the problem: we simply find the first edge occurring in the graph that is already connected. The rest of this explanation will focus on the details of implementing DSU.

        A DSU data structure can be used to maintain knowledge of the connected components of a graph, and query for them quickly. In particular, we would like to support two operations:

        dsu.find(node x), which outputs a unique id so that two nodes have the same id if and only if they are in the same connected component, and:

        dsu.union(node x, node y), which draws an edge (x, y) in the graph, connecting the components with id find(x) and find(y) together.

        To achieve this, we keep track of parent, which remembers the id of a smaller node in the same connected component. If the node is it's own parent, we call this the leader of that connected component.

        A naive implementation of a DSU structure would look something like this:

        Complexity Analysis

        Time Complexity: O(N\alpha(N)) \approx O(N)O(Nα(N))≈O(N), where NN is the number of vertices (and also the number of edges) in the graph, and \alphaα is the Inverse-Ackermann function. 
        We make up to NN queries of dsu.union, which takes (amortized) O(\alpha(N))O(α(N)) time. Outside the scope of this article, it can be shown why dsu.union has O(\alpha(N))O(α(N)) 
        complexity, what the Inverse-Ackermann function is, and why O(\alpha(N))O(α(N)) is approximately O(1)O(1).

        Space Complexity: O(N)O(N). The current construction of the graph (embedded in our dsu structure) has at most NN nodes.
    */
    vector<int> doit_disjoint(vector<vector<int>>& edges) {

        vector<int> parent(edges.size()+1);
        for (int i = 0; i < parent.size(); i++) parent[i] = i;

        auto find = [&](int i) {
            while (parent[i] != i) {
                parent[i] = parent[parent[i]];
                i = parent[i];
            }
            return i;
        };

        auto merge = [&](int a, int b) {
            int pa = find(a);
            int pb = find(b);

            if (pa == pb) return false;

            if (pa > pb) {
                parent[pa] = pb;
            } else {
                parent[pb] = pa;
            }
            return true;
        };


        for (auto& edge : edges) {
            if (!merge(edge[0], edge[1])) return edge;
        }

        return {};
    }
};
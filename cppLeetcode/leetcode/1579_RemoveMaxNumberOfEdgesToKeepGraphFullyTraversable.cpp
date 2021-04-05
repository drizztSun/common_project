/*

1579. Remove Max Number of Edges to Keep Graph Fully Traversable

Alice and Bob have an undirected graph of n nodes and 3 types of edges:

Type 1: Can be traversed by Alice only.
Type 2: Can be traversed by Bob only.
Type 3: Can by traversed by both Alice and Bob.
Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, 
find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. 
The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.

Return the maximum number of edges you can remove, or return -1 if it's impossible for the graph to be fully traversed by Alice and Bob.

 

Example 1:



Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
Output: 2
Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
Example 2:



Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
Output: 0
Explanation: Notice that removing any edge will not make the graph fully traversable by Alice and Bob.
Example 3:



Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
Output: -1
Explanation: In the current graph, Alice cannot reach node 4 from the other nodes. Likewise, Bob cannot reach 1. Therefore it's impossible to make the graph fully traversable.
 

 

Constraints:

1 <= n <= 10^5
1 <= edges.length <= min(10^5, 3 * n * (n-1) / 2)
edges[i].length == 3
1 <= edges[i][0] <= 3
1 <= edges[i][1] < edges[i][2] <= n
All tuples (typei, ui, vi) are distinct.

*/

#include <vector>
#include <numeric>

using std::vector;

class RemoveEdgesToKeepGraphTraverable {

    /*
        1579.Remove-Max-Number-of-Edges-to-Keep-Graph-Fully-Traversable

        我们先考虑这样一个问题：给一个包含N个点的联通图，这个图里面有M条边（M最多可以是N*(N-1)/2个），问如何找出N-1条边，恰好将这N个点都联通。

        针对这题的解法是：我们任意给一个M条边的排列（也就是说顺序无所谓），依次check这些边。如果这条边连接两个未联通的点，那我们就采用这条边，同时意味着这两个点以及与这两个点已经联通的那些点，就被联通在了一起。
        如果这条边连接了两个已经联通的点，显然这条边就是冗余的，我们就不采用。这样我们找到N-1条可以采用的边之后，任务就完成了。

        思考一下上面的方法，如果我们找到了N-1条边，是否一定意味着N个点都联通了，是否会有某个点还没被联通？假设某个点X未被选中的这N-1条边联通，那么必然有一条连接X和另一点（比如说Y）的边e没有被选中。
        但是我们当初在查验e边的时候，没有选中它是因为认为它连接的两个点已经联通了，这就引发了矛盾。所以上述的方案是完备的，我们找到的这N-1条一定能联通这N个点。

        然后我们回到这个问题。现在有三种类型的边。我们势必会优先使用第三种类型的边，希望第三种类型的边能够联通尽量多的点。可以想象，操作之后整个图变成了若干个割裂的联通块，但是每个联通块内部是最优联通的（也就是用了最少的边）。每个联通块内部，是可以让两个人都自由访问到的。

        然后我们在此联通状态的基础上，逐步添加第一类的边直至让N个点都联通。这样满足了Alice能访问所有的点。

        并行的，我们在之前的联通状态的基础上，逐步添加第二类的边直至让N个点都联通。这样满足了Bob能访问所有的点。

        这三个步骤所选中的所有的边的数目，就是需要最少的、可让两个人都联通所有点的边。剩余的都是可以删除的冗余边。    
    */
    int N;
    int Father[100001];
    int Father0[100001];
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
    
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) 
    {
        N = n;
        
        vector<vector<int>>edge0;
        vector<vector<int>>edge1;
        vector<vector<int>>edge2;
        for (auto edge: edges)
        {
            if (edge[0]==3)
                edge0.push_back({edge[1],edge[2]});
            else if (edge[0]==1) 
                edge1.push_back({edge[1],edge[2]});
            else if (edge[0]==2) 
                edge2.push_back({edge[1],edge[2]});                
        }
        
        int count0 = 1, count1=0, count2=0;
                
        for (int i=0; i<N; i++)
            Father[i] = i;
        
        for (auto edge: edge0)
        {
            int a = edge[0];
            int b = edge[1];
            if (findFather(a)!=findFather(b))
            {
                Union(a,b);
                count0++;
            }
        }
        
        memcpy(Father0, Father, sizeof(Father));
        
        for (auto edge: edge1)
        {
            int a = edge[0];
            int b = edge[1];
            if (findFather(a)!=findFather(b))
            {
                Union(a,b);
                count1++;
            }
        }
        if (count0+count1!=n) return -1;
        
        memcpy(Father, Father0, sizeof(Father));
        
        for (auto edge: edge2)
        {
            int a = edge[0];
            int b = edge[1];
            if (findFather(a)!=findFather(b))
            {
                Union(a,b);
                count2++;
            }
        }
        if (count0+count2!=n) return -1;
        
        return edge0.size()-(count0-1) + edge1.size()-count1 + edge2.size()-count2;
    }



public:

    /*
        A type3 edge is always better than type1 or type2 or both combined
        if there are 3 edges(type1, 2, 3) connect(u, v), we can keep the type3 and remove 2 edges(type1, and type2)

        Solution: greeddy + Union Find

        key: have two trees, one for Alice and one for Bob.

        Create two disjoint-sets

        Two passes:
        1) First pass, use type3 edges.
        2) Second pass, use type1 and type2 edges

        Check there are n-1 edges, in the disjoint-set to be a fully traversalable.

        Noe: type3 edges can be redundant and can be removed as well. 
    */
    struct DSU {
    
        vector<int> p_;
        int e_;

        DSU(int n): p_(n+1), e_(0) {
            iota(begin(p_), end(p_), 0);
        }

        int find(int x) {
            while (x != p_[x]) {
                p_[x] = p_[p_[x]];
                x = p_[x];
            }
            return x;
        }

        int merge(int x, int y) {
            int rx = find(x), ry = find(y);
            if (rx == ry) return 1;
            p_[rx] = ry;
            ++e_;
            return 0;
        }

        int edges() const { return e_; }
    };
    
    int maxNumEdgesToRemove_disjoint(int n, vector<vector<int>>& edges) {
        DSU A(n), B(n);
        int ans = 0;

        for (auto& c : edges) {
            if (c[0] != 3)
                continue;

            ans += A.merge(c[1], c[2]);
            B.merge(c[1], c[2]);
        }

        for (auto& c : edges) {
            if (c[0] == 3)
                continue;
            
            // Using two DSU is that because some pass only used to Alice or Bob, can't be used for another person
            // so in each DSU, all nodes must be connected to make sure that Alice and Bob could fully travel.
            DSU& t = (c[0] == 1) ? A : B;
            ans += t.merge(c[1], c[2]);
        }

        return (A.edges() == n - 1 && B.edges() == n - 1) ? ans : -1;
    }
};
/*
1724. Checking Existence of Edge Length Limited Paths II


An undirected graph of n nodes is defined by edgeList, where edgeList[i] = [ui, vi, disi] denotes an edge between nodes ui and vi with distance disi. Note that there may be multiple edges between two nodes, and the graph may not be connected.

Implement the DistanceLimitedPathsExist class:

DistanceLimitedPathsExist(int n, int[][] edgeList) Initializes the class with an undirected graph.
boolean query(int p, int q, int limit) Returns true if there exists a path from p to q such that each edge on the path has a distance strictly less than limit, and otherwise false.
 

Example 1:



Input
["DistanceLimitedPathsExist", "query", "query", "query", "query"]
[[6, [[0, 2, 4], [0, 3, 2], [1, 2, 3], [2, 3, 1], [4, 5, 5]]], [2, 3, 2], [1, 3, 3], [2, 0, 3], [0, 5, 6]]
Output
[null, true, false, true, false]

Explanation
DistanceLimitedPathsExist distanceLimitedPathsExist = new DistanceLimitedPathsExist(6, [[0, 2, 4], [0, 3, 2], [1, 2, 3], [2, 3, 1], [4, 5, 5]]);
distanceLimitedPathsExist.query(2, 3, 2); // return true. There is an edge from 2 to 3 of distance 1, which is less than 2.
distanceLimitedPathsExist.query(1, 3, 3); // return false. There is no way to go from 1 to 3 with distances strictly less than 3.
distanceLimitedPathsExist.query(2, 0, 3); // return true. There is a way to go from 2 to 0 with distance < 3: travel from 2 to 3 to 0.
distanceLimitedPathsExist.query(0, 5, 6); // return false. There are no paths from 0 to 5.
 

Constraints:

2 <= n <= 104
0 <= edgeList.length <= 104
edgeList[i].length == 3
0 <= ui, vi, p, q <= n-1
ui != vi
p != q
1 <= disi, limit <= 109
At most 104 calls will be made to query.

*/

#include <vector>
#include <unordered_set>

using std::unordered_set;
using std::vector;

/*
    1724.Checking-Existence-of-Edge-Length-Limited-Paths-II
    解法1
    本题看上去和1697 Checking Existence of Edge Length Limited Paths很像，但是做法却有很大的差别。本题要提供online的查询，每次查询时刻所对应的union tree都是不一样的形状。如果是Limit较大的query，那么图里面就有更多的联通点；反之，图里面就有更少的联通点。

    所以本题的关键，就是将不同limit所对应的连通图都要记录下来。这里对“连通图”的记录其实并不复杂，本质就是记录各个点的father即可。Limit较大时，有更多节点的father被聚合到了一起；反之，就有更多节点的father只是自己。如何记录每个node在不同limit时对应的father呢？这其实是采用了与1146 Snapshot Array相同的技巧：给每个节点创建father的时间序列快照。

    我们定义snaps[node]={{snapId1, father1}, {snapId2, father2}, ...}来记录node在不同快照时刻的父节点。所谓的快照时刻snapId，就是对应limit增长的过程。我们想象，随着limit的提升，会有越来越多的节点被联通，相应地那些被联通的node的father就会有变化。事实上，我们所关心的limit的提升是离散的，limit只在变化到某些特定的阶跃值时才会对连通图产生影响，这一系列阶跃值其实就是所有edges（排序后）的长度。比如，当limit=edge[0]时，并没有任何点被联通；当limt = edge[1]时，至少有两个点（也可能更多）被联通...

    我们将edges排序之后，就可以知道哪些阶跃值会影响连通图，我们依次标记快照时刻为0,1,2,3...比如说，快照时刻0表示Limit=edge[0]的时刻。注意，edges可能有重复值，所以我们关注的快照时刻的数量很可能会比edges的数目要少。我们只对应edges里面unique的长度来拍快照。

    具体的预处理如下：

    我们逐个考察每个快照时刻snapId对应的limit，将小于limit的边收入连通图中，这样会导致一些节点被union。
    假设节点a和b要被union，那么我们就将各自的祖宗节点fa和fb找出来（通过findFather的递归）。此时为了将两大家族合并，我们要么将fa的父亲指向fb，或者将fb的父亲指向fa。那么哪个更好呢？这就用到了Union Find里与“路径压缩”不同另外一个处理方法：按秩排序。所谓某个节点的“秩”，就是它与离自己最远的叶子的距离。我们会将fa和fb中秩更大的那个节点，选为两大家族合并后的代表（假设是fa）。这样的好处是，union之后rank[fa] = max(rank[fa], rank[fb]+1)有可能并不会继续增大，这意味着以fa为根节点的树会更“平衡”一些。这样在这棵树里的任何节点做findRoot（找根节点）所需要的递归次数就会相对少一些。注意，本题中我们不会做任何“路径压缩”，我们要原原本本的保留每个节点的原始父节点（因为需要存储快照）。
    当节点a和b被union之后，意味着fb的father就要更新为fa.这个变动要存储在snaps[fb]相应的快照记录中，即snaps[fb].push_back({snapId, fa}.
    处理query时我们需要：找出limit所对应的snap_id，然后寻找节点p在snap_id时刻的根节点、节点q在snap_id时刻的根节点，查看是否相等。同样，查找特定快照时刻的根节点，需要递归调用findSnapFather(node, snap_id)。

    解法2
    针对解法1可以有一点小改进。我们在构造snaps[node]的时候，可以用当前所用边的长度的作为snapId，不需要另行维护一个自增1的snapId变量。在query()中，我们直接用limit在snaps[node]里面二分搜寻合适的snapId，注意这里定位iter的方法应该是lower_bound({limit,0})-1.
*/
class DistanceLimitedPathsExist {

    vector<std::pair<int,int>> snaps[10000];
    int father[10000];
    int rank[10000];
    vector<int>dist;
    unordered_set<int>changed;
    int snapId = 0;

public:

    DistanceLimitedPathsExist(int n, vector<vector<int>>& edgeList) 
    {
        for (int i=0; i<n; i++)
        {
            snaps[i].push_back({-1, i});
            father[i] = i;
        }            
                
        std::sort(edgeList.begin(),edgeList.end(), [](auto const &a,auto const &b) { return a[2] < b[2]; });
        
        int cur_dist = 0;
        for (auto e: edgeList)
        {
            if (e[2] > cur_dist) 
            {
                dist.push_back(cur_dist);
                cur_dist = e[2];
                for (auto node: changed)
                {
                    snaps[node].push_back({snapId, father[node]});
                }
                changed.clear();
                snapId++;
            }
            int a = e[0], b = e[1];
            Union(a,b);            
        }
    }
    
    int findFather(int node)
    {
        while (father[node]!=node)
            node = father[node];
        return node;
    }
    
    void Union(int a, int b)
    {
        a = findFather(a);
        b = findFather(b);
        if (findFather(a)!=findFather(b))
        {
            if (rank[a]<rank[b])
            {
                father[a] = b;
                rank[b] = std::max(rank[b], rank[a]+1);
                changed.insert(a);
            }
            else
            {
                father[b] = a;
                rank[a] = std::max(rank[a], rank[b]+1);
                changed.insert(b);
            }
        }            
    }
    
    int findSnapFather(int node, int snap_id)
    {
        auto iter = upper_bound(snaps[node].begin(), snaps[node].end(), make_pair(snap_id, INT_MAX));
        iter = prev(iter,1);
        int f = iter->second;
        if (f==node)
            return f;
        else
            return findSnapFather(f, snap_id);
    }
    
    bool query(int p, int q, int limit) 
    {
        int snap_id = lower_bound(dist.begin(), dist.end(), limit) - dist.begin() - 1;
        return findSnapFather(p, snap_id)==findSnapFather(q, snap_id);
    }



    vector<std::pair<int,int>> snaps[10000];
    int father[10000];
    int rank[10000];
    unordered_set<int>changed; // the nodes whose father has been modified since last snapshot    
public:
    DistanceLimitedPathsExist(int n, vector<vector<int>>& edgeList) 
    {
        for (int i=0; i<n; i++)
        {
            father[i] = i;
            snaps[i].push_back({0, i});
        }
        
        sort(edgeList.begin(), edgeList.end(), [](auto const&a, auto const&b){return a[2]<b[2];});
        int curLen = 0;
        for (auto e: edgeList)
        {
            if (e[2] > curLen)
            {                
                for (auto node: changed)
                {
                    snaps[node].push_back({curLen, father[node]});
                }
                changed.clear();                
                curLen = e[2];
            }
            Union(e[0], e[1]);
        }        
    }
    
    int findFather(int a)
    {
        while (father[a]!=a)
            a = father[a];
        return a;
    }
        
    void Union(int a, int b)
    {
        int fa = findFather(a);
        int fb = findFather(b);
        if (fa!=fb)
        {
            if (rank[fa] < rank[fb])
            {
                father[fa] = fb;
                rank[fb] = max(rank[fb], rank[fa]+1);
                changed.insert(fa);
            }
            else
            {
                father[fb] = fa;
                rank[fa] = max(rank[fa], rank[fb]+1);
                changed.insert(fb);
            }
        }
    }
    
    int findSnapRoot(int node, int limit)
    {
        auto iter = lower_bound(snaps[node].begin(), snaps[node].end(), make_pair(limit, 0));
        iter = prev(iter,1);
        int f = iter->second;
        if (f==node)
            return f;
        else
            return findSnapRoot(f, limit);
    }
    
    bool query(int p, int q, int limit) 
    {
        return findSnapRoot(p, limit) == findSnapRoot(q, limit);
    }
};
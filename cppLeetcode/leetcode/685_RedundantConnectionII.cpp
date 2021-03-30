/*
 685. Redundant Connection II
 
 In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.

 The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

 The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.

 Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

 Example 1:
 Input: [[1,2], [1,3], [2,3]]
 Output: [2,3]
 Explanation: The given directed graph will be like this:
   1
  / \
 v   v
 2-->3
 Example 2:
 Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
 Output: [4,1]
 Explanation: The given directed graph will be like this:
 5 <- 1 -> 2
      ^    |
      |    v
      4 <- 3
 Note:
 The size of the input 2D-array will be between 3 and 1000.
 Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
 
 
 
 */
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class RedundantConnectionII {

    /*
        685.Redundant-Connection-II
        题意说了，只有一个edge有问题，要把它找出来。这多余的一个edge究竟会如何影响一个valid的tree呢？

        首先，它可能造成某个节点会有两个parent。如果我们发现一个节点A（并且只可能有一个）的parent有两个，那么我们就可以把目标迅速缩小到A和它的这两个“父节点”之间的edges，称之为candA和candB。
        最终的答案必然是二选一。我们的策略是断开candB，根据剩馀的edges来尝试构造这棵树。

        如果在重构的过程中（即遍历edges的过程），我们没有遇到“成环”的情况，说明什么？说明我们断开candB的决策是对的，答案就是candB。如果遇到成环的情况，那么说明决策错误，答案应该是candA。
        重构的过程仍然可以用union find，这和68４.Redundant-Connection-I没有太大区别，只不过union两个节点的时候已经知道明确的指向关系了．

        当然，以上前提是candA和candB非空。如果candA和candB是空的，即这些节点中并没有dual parent的情况，那么本题其实就退化成了684.Redundant-Connection-I，只需要检验这些edges是否成环就行了，也就是说，答案只要输出当前使成环的那个edge就行。

        补充：

        1.为什么不能任意断开一条边就行？考察这个例子：　0->1, 1->2, 2->1. 对于1而言有两个parent,但是如果断开0->1的话，0就成了孤悬的节点．
        事实上，0应该是根节点．分析可知，如果一个节点有两个parent，这两个入度线路可能有一个不是从根节点方向过来的，必须断开这个；如果两个入度线路都是从根方向来的，那么任意断开一个都是可以的．

        ２．有一道类似的题，给出一个二叉树的root，并且告诉你这个树里面从某个节点多飞出了一条edge连接到了其他节点上，求修复这棵树．对于这道题，因为已经告知了root，所以当你发现有两个parent的时候，删掉任意一个edge都是可以的．

        但是有一个corner case，那就是如果这个多余的edge指向了root，那么整棵树里不会有任何节点拥有两个parent，这需要额外处理．
    */
    unordered_map<int,int>Father;
public:
    vector<int> doit_disjoint(vector<vector<int>>& edges) 
    {
        vector<int>candA,candB;
        
        for (int i=0; i<edges.size(); i++)
        {
            int u=edges[i][0];
            int v=edges[i][1];
            if (Father.find(v)==Father.end())
                Father[v]=u;
            else
            {
                candA={Father[v],v};
                candB=edges[i];
                break;
            }
        }
        
        for (int i=1; i<=edges.size(); i++)        
            Father[i]=i;    
        
        for (int i=0; i<edges.size(); i++)
        {
            if (edges[i]==candB) continue;
            
            int u=edges[i][0];
            int v=edges[i][1];
            
            if (findSet(v)==findSet(u))
            {
                if (candA.size()==0)
                    return edges[i];
                else
                    return candA;
            }
            else
                Father[v]=u;
        }
        
        return candB;
    }
    
	int	findSet(int x)
	{
		if (x!=Father[x])
			Father[x]=findSet(Father[x]);
		return Father[x];
	}    

public:

    
    vector<int> doit_disjoint(vector<vector<int>>&& edges) {
        // we need to find out which point has two parents and remove one of two edges. then it will be fine
        // maybe there is no this point, but still need to check and remove the cycle one, and remove the first edge make the cycle.
        auto N = edges.size();
        vector<int> parent(N+1, 0);
        vector<int> root(N+1, 0);
        vector<int> size(N+1, 1);
        vector<int> ans1, ans2;
        
        for (auto& edge : edges) {
            
            int u = edge[0], v = edge[1];
            
            if (parent[v] > 0) {
                ans1 = {parent[v], v};
                ans2 = edge;
                // remove the second edges, save the first one. If there is a cycle, it must from it and remove, return the first one.
                edge[0] = edge[1] = -1;
            }
            parent[v] = u;
        }
        
        auto find = [&](int d) {
            while (root[d] != d) {
                root[d] = root[root[d]];
                d = root[d];
            }
            return d;
        };
        
        for (auto edge: edges) {
            
            auto u = edge[0], v = edge[1];
            
            if (u < 0 || v < 0) continue;
            if (root[u] == 0) root[u] = u;
            if (root[v] == 0) root[v] = v;
            
            auto pu = find(u);
            auto pv = find(v);
            
            if (pu == pv) {
                // case1, There is no ans1 and ans2, because no one has two parents, there is just a cycle.
                // Then current one needs to remove, we get a new point without parent.
                
                // case2, one point has two parents, so ans1 is not empty
                //
                return ans1.empty() ? edge : ans1;
            }
            
            if (size[pu] > size[pv])
                std::swap(pu, pv);
            
            root[pv] = pu;
            size[pu] += size[pv];
        }
        
        // There is no cycle, return the second one.
        return ans2;
    }

    
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
         
        vector<int> parents(edges.size() + 1, 0);
        vector<int> ans1;
        vector<int> ans2;
        bool dup_parents = false;
        
        auto cycle = [&](int v) {
            int u = parents[v];
            while (u) {
                if (u == v)
                    return true;
                u = parents[u];
            }
            return false;
        };
        
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            
            // A node has two parents
            if (parents[v] > 0) {
                ans1 = {parents[v], v};
                ans2 = edge;
                dup_parents = true;
                // Delete the later edge
                edge[0] = edge[1] = -1;
            } else {
                parents[v] = u;
            }
        }
        
        // Reset parents
        parents = vector<int>(edges.size() + 1, 0);
        
        for(const auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            
            // Invalid edge (we deleted in step 1)
            if (u < 0 || v < 0) continue;
            
            parents[v] = u;
            
            if (cycle(v))
                return dup_parents ? ans1 : edge;
        }
        
        return ans2;
    }
    
private:
    
    static const int N = 1010; // 如题：二维数组大小的在3到1000范围内
    int father[N];
    int n; // 边的数量
    // 并查集初始化
    void init() {
        for (int i = 1; i <= n; ++i) {
            father[i] = i;
        }
    }
    // 并查集里寻根的过程
    int find(int u) {
        return u == father[u] ? u : father[u] = find(father[u]);
    }
    // 将v->u 这条边加入并查集
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return ;
        father[v] = u;
    }
    // 判断 u 和 v是否找到同一个根
    bool same(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
    // 在有向图里找到删除的那条边，使其变成树
    vector<int> getRemoveEdge(const vector<vector<int>>& edges) {
        init(); // 初始化并查集
        for (int i = 0; i < n; i++) { // 遍历所有的边
            if (same(edges[i][0], edges[i][1])) { // 构成有向环了，就是要删除的边
                return edges[i];
            }
            join(edges[i][0], edges[i][1]);
        }
        return {};
    }

    // 删一条边之后判断是不是树
    bool isTreeAfterRemoveEdge(const vector<vector<int>>& edges, int deleteEdge) {
        init(); // 初始化并查集
        for (int i = 0; i < n; i++) {
            if (i == deleteEdge) continue;
            if (same(edges[i][0], edges[i][1])) { // 构成有向环了，一定不是树
                return false;
            }
            join(edges[i][0], edges[i][1]);
        }
        return true;
    }
public:

    vector<int> doit(vector<vector<int>>& edges) {
        int inDegree[N] = {0}; // 记录节点入度
        n = edges.size(); // 边的数量
        for (int i = 0; i < n; i++) {
            inDegree[edges[i][1]]++; // 统计入度
        }
        vector<int> vec; // 记录入度为2的边（如果有的话就两条边）
        // 找入度为2的节点所对应的边，注意要倒叙，因为优先返回最后出现在二维数组中的答案
        for (int i = n - 1; i >= 0; i--) {
            if (inDegree[edges[i][1]] == 2) {
                vec.push_back(i);
            }
        }
        // 处理图中情况1 和 情况2
        // 如果有入度为2的节点，那么一定是两条边里删一个，看删哪个可以构成树
        if (vec.size() > 0) {
            if (isTreeAfterRemoveEdge(edges, vec[0])) {
                return edges[vec[0]];
            } else {
                return edges[vec[1]];
            }
        }
        // 处理图中情况3
        // 明确没有入度为2的情况，那么一定有有向环，找到构成环的边返回就可以了
        return getRemoveEdge(edges);
    }
};
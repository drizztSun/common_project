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


using std::vector;


class RedundantConnectionII {

public:
    
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
            
            if (u < 0 || v < 0)
                continue;
            
            if (root[u] == 0)
                root[u] = u;
            if (root[v] == 0)
                root[v] = v;
            
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

void test_685_redundant_connection() {
    
    RedundantConnectionII().doit_disjoint(vector<vector<int>>{{1, 2}, {1, 3}, {2, 3}});
    
}

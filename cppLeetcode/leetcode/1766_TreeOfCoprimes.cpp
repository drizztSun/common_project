/*
1766. Tree of Coprimes


There is a tree (i.e., a connected, undirected graph that has no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. 
Each node has a value associated with it, and the root of the tree is node 0.

To represent this tree, you are given an integer array nums and a 2D array edges. 
Each nums[i] represents the ith node's value, and each edges[j] = [uj, vj] represents an edge between nodes uj and vj in the tree.

Two values x and y are coprime if gcd(x, y) == 1 where gcd(x, y) is the greatest common divisor of x and y.

An ancestor of a node i is any other node on the shortest path from node i to the root. A node is not considered an ancestor of itself.

Return an array ans of size n, where ans[i] is the closest ancestor to node i such that nums[i] and nums[ans[i]] are coprime, or -1 if there is no such ancestor.

 

Example 1:



Input: nums = [2,3,3,2], edges = [[0,1],[1,2],[1,3]]
Output: [-1,0,0,1]
Explanation: In the above figure, each node's value is in parentheses.
- Node 0 has no coprime ancestors.
- Node 1 has only one ancestor, node 0. Their values are coprime (gcd(2,3) == 1).
- Node 2 has two ancestors, nodes 1 and 0. Node 1's value is not coprime (gcd(3,3) == 3), but node 0's
  value is (gcd(2,3) == 1), so node 0 is the closest valid ancestor.
- Node 3 has two ancestors, nodes 1 and 0. It is coprime with node 1 (gcd(3,2) == 1), so node 1 is its
  closest valid ancestor.
Example 2:



Input: nums = [5,6,10,2,3,6,15], edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
Output: [-1,0,-1,0,0,0,-1]
 

Constraints:

nums.length == n
1 <= nums[i] <= 50
1 <= n <= 105
edges.length == n - 1
edges[j].length == 2
0 <= uj, vj < n
uj != vj

*/

#include <vector>
#include <cmath>
#include <functional>

using std::vector;

class GetCoprime {

public:

    /*
      
      这道题目考察的范围还是挺广的。基本方法是建图+DFS。但brute force做的话，当tree是一个list的时候，时间复杂度会退化到O(n^2)。本题切入点是nums[i]的取值范围很小，只有1-50。可以预先计算coprimes。
      然后DFS，用stack存储当前路径上每个num出现的深度和结点编号，对于当前结点，枚举它所有的coprimes，看看最后一次出现的祖先节点是哪个。

      Time complexity: O(n*50)
      Space complexity: O(n)
    */
    vector<int> doit_dfs(vector<int>& nums, vector<vector<int>>& edges) {

        constexpr int kmax = 50;
        const int n = nums.size();

        vector<vector<int>> graph(n);
        for (const auto& c : edges) {
          graph[c[0]].push_back(c[1]);
          graph[c[1]].push_back(c[0]);
        }

        vector<vector<int>> coprimes(kmax+1);
        for (int i = 1; i <= kmax; i++)
          for(int j = 1; j <= kmax; j++) {
            if (gcd(i, j) == 1) coprimes[i].push_back(j);
          }

        vector<vector<std::pair<int, int>>> buff(kmax+1);
        vector<int> ans(n, INT_MAX);

        std::function<void(int, int)> dfs = [&](int cur, int level) {

          int ancestor = -1;
          int cloestcoprime = -1;
          for (auto c : coprimes[nums[cur]]) {
              if (!buff[c].empty() && buff[c].back().first > cloestcoprime) {
                cloestcoprime = buff[c].back().first;
                ancestor = buff[c].back().second;
              }
          }

          ans[cur] = ancestor;
          buff[nums[cur]].emplace_back(level, cur);

          for (auto child : graph[cur])
            if (ans[child] == INT_MAX) dfs(child, level + 1);

          buff[nums[cur]].pop_back();
        };

        dfs(0, 0);

        return ans;
    }

    /*
      1766.Tree-of-Coprimes
      本题本质就是DFS。当我们考察某个节点curIdx时，在该DFS路径path上的所有节点都是它的祖先。我们需要从中找一个深度最大的、与nums[curIdx]互质的节点。理论上我们需要逆序遍历一遍path，总体复杂度是o(N^2)。

      本题特殊之处在于数据范围限制了所有节点的“数值”不超过50，于是我们可以不遍历节点、转而遍历“数值”来更高效的找到互质的节点。我们只需要在维护path的同时，维护一个哈希表records，其中records[d]存储的就是path里所有数值是d的节点的深度。
      我们在1到50里面寻找那些与nums[curIdx]互质的d，其中最大的records[d].back()就是离curIdx最近的互质节点的深度。再根据这个深度，直接从path里面读取那个节点的idx。
    */
    vector<int> path; // path[i] is the i-th node idx along the dfs path
    vector<int> records[51]; // records[i] contains the depths of all the nodes whose num = i
    vector<int> rets;
    vector<int> next[100000];
    int visited[100000];
    vector<int>nums;
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) 
    {
        this->nums = nums;
        int n = nums.size();
        rets.resize(n);
        
        for (auto e:edges)
        {
            next[e[0]].push_back(e[1]);
            next[e[1]].push_back(e[0]);
        }
        
        visited[0] = 1;
        dfs(0, 0);
        return rets;
    }
    
    void dfs(int curIdx, int depth)
    {
        int i = -1;
        for (int d=1; d<=50; d++)
        {
            if (records[d].size() > 0 && gcd(d, nums[curIdx])==1)
            {
                i = std::max(i, records[d].back());
            }
        }
        rets[curIdx] = (i==-1) ? -1 : path[i];
        
        path.push_back(curIdx);
        records[nums[curIdx]].push_back(depth);                        
        
        for (int nextIdx : next[curIdx])
        {
            if (visited[nextIdx]) continue;
            visited[nextIdx] = 1;
            dfs(nextIdx, depth+1);
            visited[nextIdx] = 0;
        }
        
        path.pop_back();
        records[nums[curIdx]].pop_back();                        
    }
};
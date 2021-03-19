/*
834. Sum of Distances in Tree

An undirected, connected tree with N nodes labelled 0...N-1 and N-1 edges are given.

The ith edge connects nodes edges[i][0] and edges[i][1] together.

Return a list ans, where ans[i] is the sum of the distances between node i and all other nodes.

Example 1:

Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: 
Here is a diagram of the given tree:
  0
 / \
1   2
   /|\
  3 4 5
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.  Hence, answer[0] = 8, and so on.
Note: 1 <= N <= 10000

*/
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>

using std::unordered_map;
using std::unordered_set;
using std::queue;
using std::vector;


class SumOfDistancesInTree {

    /*
        834.Sum-of-Distances-in-Tree
        首先回顾一下关于图论的几个概念。树是图的一种，是指没有回路的连通图。对于这种图，任意一个节点都可以当做root从而展开为一棵直观意义上的树。

        本题也是如此，我们可以任意选取一个节点定义为root，然后可以用BFS建立起一个Hash表来代表传统意义上树结构里parent->child的连接关系（注意，因为是树，反向的关系我们不记录在Hash表里）。

        然后我们可以做什么呢？比较容易用递归办到的，就是root到所有子节点的距离之和，标记为f(root)。
        
        那么接下来，如何得到一个子节点child到其他所有节点的距离之和呢？难道要以该节点为根重新展开一张树吗？其实我们可以考虑f(parent)和f(child)之间的关系。

        假设已知f(parent)，如果我们把起点从parent迁到child的话，那么到所有除child子树之外的节点，距离都增加了1；到所有child子树的节点，距离都减少了1.

        所以有如下的关系

        f(child) = f(parent)+(除child子树之外所有节点的数目)-(child子树的节点数目)
        可见，所有的f都可以自上而下通过递归得到。
    */
    unordered_map<int,unordered_set<int>>Children;
    vector<int>SubLeaves;
    vector<int>results;
    
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) 
    {
        SubLeaves.assign(N,0);
        results.assign(N,0);
        
        unordered_map<int,unordered_set<int>>Map;        
        for (int i=0; i<edges.size(); i++)
        {
            Map[edges[i][0]].insert(edges[i][1]);
            Map[edges[i][1]].insert(edges[i][0]);
        }
                        
        queue<int>q;
        q.push(0);
        while (!q.empty())
        {
            int root = q.front();            
            q.pop();
            for (auto child:Map[root])
            {
                Children[root].insert(child);    
                Map[child].erase(root);
                q.push(child);
            }                        
        }
                
        int root = 0;
        int temp = DFS1(root);        
        int AllSum = DFS2(root);        
        
        results[0] = AllSum;
        DFS3(root);
        
        return results;
    }
    
    int DFS1(int x)
    {
        if (Children[x].size()==0)
        {
            SubLeaves[x]=1;
            return 1;
        }
        int sum = 1;
        for (auto a: Children[x])        
            sum+=DFS1(a);                    
        SubLeaves[x]=sum;   
        return sum;
    }
        
    int DFS2(int x)
    {
        if (Children[x].size()==0) return 0;        
        int sum = 0;
        for (auto a: Children[x])        
            sum+=DFS2(a)+SubLeaves[a];        
        return sum;
    }
    
    void DFS3(int x)
    {        
        for (auto a: Children[x])
        {
            results[a] = results[x] - SubLeaves[a] + results.size()-SubLeaves[a];
            DFS3(a);
        }
    }


public:

    /*
        # Well, another long solution.

        # Intuition:
        # What if given a tree, with a certain root 0?
        # In O(N) we can find sum of distances in tree from root and all other nodes.
        # Now for all N nodes?
        # Of course, we can do it N times and solve it in O(N^2).
        # C++ and Java may get accepted luckly, but it's not what we want.

        # When we move our root from one node to its connected node, one part of nodes get closer, one the other part get further.
        # If we know exactly hom many nodes in both parts, we can solve this problem.

        # With one single traversal in tree, we should get enough information for it and don't need to do it again and again.

        # Explanation:
        # 0. Let's solve it with node 0 as root.

        # Initial an array of hashset tree, tree[i] contains all connected nodes to i.
        # Initial an array count, count[i] counts all nodes in the subtree i.
        # Initial an array of res, res[i] counts sum of distance in subtree i.

        # Post order dfs traversal, update count and res:
        # count[root] = count[i] + 1
        # res[root] = res[i] + count[i]

        # Pre order dfs traversal, update res:
        # When we move our root from parent to its child i, count[i] points get 1 closer to root, n - count[i] nodes get 1 futhur to root.
        # res[i] = res[root] - count[i] + N - count[i]

        # return res, done.

        # Time Complexity:
        # dfs: O(N)
        # dfs2: O(N)
    */
    vector<int> doit_(int N, vector<vector<int>>& edges) {

        vector<int> res(N, 0);
        vector<int> cnt(N, 0);
        vector<unordered_set<int>> graph(N);
        for (const auto& edge: edges) {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }

        std::function<void(int, unordered_set<int>&)> post = [&](int node, unordered_set<int>& visited) {
            visited.insert(node);

            for (auto c : graph[node]) {
                if (visited.count(c) == 0) {
                    post(c, visited);
                    cnt[node] += cnt[c];
                    res[node] += res[c] + cnt[c];
                }
            }
            cnt[node]++;
        };

        std::function<void(int, unordered_set<int>&)> pre = [&](int node, unordered_set<int>& visited) {
            visited.insert(node);

            for (auto c : graph[node]) {
                if (visited.count(c) == 0) {
                    res[c] = res[node] - cnt[c] + N - cnt[c];
                    pre(c, visited);
                }
            }
        };

        unordered_set<int> visited;
        post(0, visited);
        visited.clear();
        pre(0, visited);

        return res;
    }
};
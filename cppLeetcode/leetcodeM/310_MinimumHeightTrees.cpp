/*
310. Minimum Height Trees



A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, 
you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.

The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

 

Example 1:


Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]
Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.
Example 2:


Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]
Example 3:

Input: n = 1, edges = []
Output: [0]
Example 4:

Input: n = 2, edges = [[0,1]]
Output: [0,1]
 

Constraints:

1 <= n <= 2 * 104
edges.length == n - 1
0 <= ai, bi < n
ai != bi
All the pairs (ai, bi) are distinct.
The given input is guaranteed to be a tree and there will be no repeated edges.

*/
#include <vector>
#include <queue>
#include <set>
#include <numeric>
#include <unordered_map>

using std::set;
using std::queue;
using std::vector;
using std::unordered_map;


class MinHeightTrees {

    /*
                310.Minimum-Height-Trees
        本题表面上是关于图、关于树，本质上我觉得更像BFS，或者说树的level order traversal.

        本题的意思是，想从一棵树的一群nodes里找出一个node作为根，使得从这个根节点出发，发散到周围的叶子节点的路径范围最短。可以想见，这个根节点必然得尽可能地位于“中央”。如何确定“中央”的位置呢？我们其实可以反其道而行之，从“边疆”出发往内地进军。从所有的叶子节点（入度为1、出度为0）同步出发，一步一步地往前走，那么它们的最终汇合点，必然就是最“中央”的地方。

        很明显，这就是一棵树的层级遍历 (level order tranversal)。传统的树操作都是从root开始的（因为通常只给你一个root），必须从顶往底用队列的结构一层一层遍历。但这里给出了图的表述，这样我们就可以轻易地找出哪些是最底端的叶子节点，从叶子节点反推上去。

        基本的算法思想就是ＢＦＳ，具体的做法很像拓扑排序，可以参见269．Alien Dictionary.我们要借助一个Ｈａｓｈ表记录所有节点的度．每次我们将度为１（说明是叶子节点或边缘节点）加入队列．队列每弹出一个元素，我们就找这个元素的相邻节点，将它们的度都减一，一旦减至１（说明这个节点被砍成了边缘节点），就可以把这个节点加入队列．

        直到什么时候停止呢？直到所有已弹出的元素数目，加上已经加入队列的元素数目，恰好等于ｎ为止．这时候，队列的元素数目，要么为１，要么为２，这一个或两个元素就是答案．

        注意：为什么最后会有一个或两个元素可以作为答案。我也是看网上参考才知道的。不过这也非常好理解。如果最后还剩下三个连通的节点（因为这是一棵树，必然彼此连通），显然还有从两边“往中央进军”的余地，必然只有一个是中央；如果最后还剩下两个连通的节点，两边各进一步的话就僵持住了，显然可以是并列的“中央”
    */
    vector<int> findMinHeightTrees(int n, vector<std::pair<int, int>>& edges) 
    {
        if (n==1) return {0};
        if (n==2) return {0,1};
        
        unordered_map<int,int>Degree;
        unordered_map<int,vector<int>>Up;
        
        for (auto edge:edges)
        {
            Degree[edge.first]++;
            Degree[edge.second]++;
            Up[edge.second].push_back(edge.first);
            Up[edge.first].push_back(edge.second);
        }
        
        queue<int>q;
        for (auto a:outDegree)
            if (a.second==1) q.push(a.first);
        
        int count = 0;
        while (!q.empty())
        {
            int k = q.size();
            for (int i=0; i<k; i++)
            {
                int node = q.front();
                q.pop();
                count++;

                for (auto upNode: Up[node])
                {
                    Degree[upNode]--;
                    if (Degree[upNode]==1)
                        q.push(upNode);
                }
            }
                       
            if (count+q.size()==n)
            {
                vector<int>results;
                while (!q.empty())
                {
                    results.push_back(q.front());
                    q.pop();
                }
                return results;
            }
        }
    }

public:
    
    vector<int> doit_topsort(int n, vector<vector<int>>& edges) {
        if (n <= 2) {
            vector<int> res(n);
            std::iota(begin(res), end(res), 0);
            return res;
        }
        vector<int> indegrees(n);
        vector<set<int>> graph(n);
        for (auto& c : edges) {

            graph[c[0]].insert(c[1]);
            graph[c[1]].insert(c[0]);

            indegrees[c[0]]++;
            indegrees[c[1]]++;
        }


        queue<int> starts;
        for (int i = 0; i < n; i++) {
            if (indegrees[i] == 1)
                starts.push(i);
        }

        int remaining_node = n;
        vector<int> levels;
        while (remaining_node > 2) {

            int size = starts.size();
            remaining_node -= size;

            while (size--) {

                int cur = starts.front();
                starts.pop();

                for (auto it = begin(graph[cur]); it != end(graph[cur]);) {
                    int c = *it;
                    it = graph[cur].erase(it);

                    indegrees[c]--;
                    if (indegrees[c] == 1) {
                        starts.push(c);
                    }

                }
            }
        }

        while (!starts.empty()) {
            levels.push_back(starts.front());
            starts.pop();
        }

        return levels;
    }
};

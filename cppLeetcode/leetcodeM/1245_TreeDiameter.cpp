/*
1245. Tree Diameter


Given an undirected tree, return its diameter: the number of edges in a longest path in that tree.

The tree is given as an array of edges where edges[i] = [u, v] is a bidirectional edge between nodes u and v.  Each node has labels in the set {0, 1, ..., edges.length}.

 

Example 1:



Input: edges = [[0,1],[0,2]]
Output: 2
Explanation: 
A longest path of the tree is the path 1 - 0 - 2.
Example 2:



Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
Output: 4
Explanation: 
A longest path of the tree is the path 3 - 2 - 1 - 4 - 5.
 

Constraints:

0 <= edges.length < 10^4
edges[i][0] != edges[i][1]
0 <= edges[i][j] <= edges.length
The given edges form an undirected tree.
*/
#include <vector>
#include <unordered_set>
#include <set>
#include <queue>
#include <functional>

using std::queue;
using std::unordered_set;
using std::vector;

class TreeDiameter {

    /*
                1245.Tree-Diameter
        对于一张无向图的树，求最长的点到点距离，有一个非常成熟的做法。我们可以任意取一点A，用BFS找到距离A最远的节点B。那么B一定是就是“最长的点到点距离”的其中一个点。然后我们再以B为起点，用BFS找到距离B最远的节点C。那么BC就是答案。

        证明：从任意点A开始，能够到达的最远的距离是B。另外，整张图里“最长的点到点距离”是S和T。我们要证明B只可能是S或者T中的一点。如果不是，那么分情况讨论：

        AB与ST完全不相交。那么我们从A找一条路径能够到达ST的路径，并令交点是X。因为AB是从A起始的最长路径，那么AB>AX+XT. 那么我们观察路径B->A->X->S，其距离BA+AX+XS > 2*AX+XT+XS > 2*AX+ST > ST，这就与ST是全局“最长的点到点距离”矛盾。
        AB与ST相交于X。因为AB是从A起始的最长路径，那么AX+XB>AX+XS，即XB>XS. 我们观察路径B->X->T，其距离BX+XT > XS+XT = ST，这就与ST是全局“最长的点到点距离”矛盾。
    */
    vector<vector<int>>adj;
    int V;
    
    int treeDiameter(vector<vector<int>>& edges) 
    {
        V = edges.size()+1;
        adj.resize(V);
        for (auto edge:edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        auto t1 = bfs(0); 
        auto t2 = bfs(t1.first); 
        return t2.second;        
    }
        
    std::pair<int, int> bfs(int u) 
    { 
        vector<int>dis(V, -1);
        queue<int> q; 
        q.push(u); 
      
        dis[u] = 0; 
        
        while (!q.empty()) 
        { 
            int t = q.front();       
            q.pop(); 
            
            for (auto it = adj[t].begin(); it != adj[t].end(); it++) 
            { 
                int v = *it; 
                if (dis[v] == -1) 
                { 
                    q.push(v);   
                    dis[v] = dis[t] + 1; 
                } 
            } 
        } 
  
        int maxDis = 0; 
        int nodeIdx; 
          
        for (int i = 0; i < V; i++) 
        { 
            if (dis[i] > maxDis) 
            { 
                maxDis = dis[i]; 
                nodeIdx = i; 
            } 
        } 
        return {nodeIdx, maxDis}; 
    }     

public:

    /*
        Approach 3: DFS (Depth-First Search)
        Intuition

        We applied the BFS strategy in the first approach to solve the problem. As is often the case, we could also apply another common strategy called DFS (Depth-First Search). This happens to be the case for this problem as well.

        One can take the inspiration from another similar problem called Diameter of N-ary Tree. At the first glance, one might even consider them as the same problem.

        Actually, the only difference between them lies in the input. In this problem, our input is a list of bi-directional edges, which we could convert into a representation of Graph; While for the problem of Diameter of N-ary Tree, the input is a Tree data structure, where the edges are uni-directional.

        First of all, we will use the concepts of leaf nodes and parent nodes as in a Tree data structure. For a parent node, if we could obtain two longest distances (denoted as t1 and t2) starting from this parent node to any of its descendant leaf nodes, then the longest path that traverse this parent node would be t1 + t2.

        Since any node in the graph has the potential to be part of the path that forms the diameter of the graph, we can iterate through each node to obtain all the longest paths as we defined shortly before. The diameter of the graph would be the maximum among all the longest paths that traverse each node.

        Here we show an example where we assume the node 0 in the graph as the root node.

        longest distance

        As shown in the above example, we also indicate two longest distances for each node. Note that, if a parent node has only one child node, then it can only have one longest distance to the leaf nodes. The second longest distance for this parent node would be zero. By adding the two longest distances together for each node, we would know that the node 1 has the longest path (i.e. with distance of 4) among all.

        Algorithm

        Given the above intuition, we could apply the DFS (Depth-First Search) strategy to obtain the longest path that traverse each node.

        During the DFS traversal, we would also update the diameter with the longest path that we obtain at each node.

        First of all, we could convert the input edges into the adjacency list, which this time we would treat as Tree, rather than Graph. We assume the node with the index of 0 as the root node.

        We then define a function named dfs(curr, visited) which returns the maximal distance starting from the curr node to any of its descendant leaf nodes. The visited parameter is used to keep track of the nodes that we've visited so far.

        Within the function of dfs(curr, visited), we will obtain the top two maximal distances starting from the curr node. With these top two distances, we can then update the global diameter that we've seen so far.

        Once we traverse the entire tree once and only once, we will obtain the diameter of the tree/graph.


        Complexity Analysis

        Let NN be the number of nodes in the graph, then the number of edges in the graph would be N-1N−1 as specified in the problem.

        Time Complexity: \mathcal{O}(N)O(N)

        First we iterate through all edges to build an adjacency list representation of the graph, which we will treat as a tree with node 0 as the root node. The time complexity of this step would be \mathcal{O}(N)O(N).

        In the main algorithm, we traverse the tree/graph via DFS. During the traversal, we visit each node once and only once. As a result, it will take \mathcal{O}(N)O(N) time.

        To sum up, the overall time complexity of the algorithm is \mathcal{O}(N) + \mathcal{O}(N) = \mathcal{O}(N)O(N)+O(N)=O(N).

        Space Complexity: \mathcal{O}(N)O(N)

        Similar to the previous approach, we used an adjacency list to keep the graph, whose space complexity is \mathcal{O}(N)O(N) as we discussed before.

        During the DFS traversal, we used an array (visited) to keep track of the nodes we visited so far. The space complexity of the array is \mathcal{O}(N)O(N).

        Since we apply recursion in the DFS traversal, which will incur additional memory consumption in the function call stack. In the worst case where all the nodes are chained up as a line, starting from the root node, the memory consumption for the call stack would be \mathcal{O}(N)O(N).

        To sum up, the overall space complexity of the algorithm is \mathcal{O}(N) + \mathcal{O}(N) + \mathcal{O}(N) = \mathcal{O}(N)O(N)+O(N)+O(N)=O(N).
    */

    int doit_dfs(vector<vector<int>>& edges) 
    {
        std::vector<std::vector<int>> m(edges.size() + 1);
        
        for (const auto& v : edges)
        {
            m[v[0]].push_back(v[1]);
        }
        
        int diameter = 0;
        
            
        std::function<int(int, int&)> helper = [&](int currentNode, int& diameter) {
            
            auto maximumDistance = 0;
            auto maximum1 = 0;
            auto maximum2 = 0;
            
            for (auto num : m[currentNode])
            {
                auto distance = helper(num, diameter);

                if (distance > maximum1)
                {
                    maximum2 = maximum1;
                    maximum1 = distance;
                }
                else if (distance > maximum2)
                {
                    maximum2 = distance;
                }
            }

            diameter = std::max(diameter, maximum1 + maximum2);
            return maximum1 + 1;
        };
        
        helper(0, diameter);
        return diameter;
    }


    /*
        Approach 1: Farthest Nodes via BFS
        Intuition

        In this first approach, let us follow the hints of the problem, which suggest us to run BFS (Breadth-First Search) for two rounds. For those of you who are not familiar with the concept of BFS, we would recommend one to check out our Explore card about BFS.

        In the problem, we are asked to find the diameter of the graph, which by definition is the distance between two nodes that are the farthest apart.

        According to the definition, the problem could be solved if we could identify the two nodes that have the longest distance among all. Let us refer to these two nodes as the extreme peripheral nodes.

        First of all, we assert that starting from any node in the graph, if we run a BFS traversal, the last node that we visit would be one of the extreme nodes. An intuition that supports the above assertion is that as an extreme peripheral node, it should be the one that is far away from any of the other nodes in the graph. Given any node, the longest distance that starts from this node must end with one of the extreme peripheral nodes.

        example of peripheral nodes

        Once we identify one of the extreme peripheral nodes, we then could apply again the BFS traversal. But this time, we would start from the identified extreme peripheral node. At the end of the second BFS traversal, we would land on another extreme peripheral node. The distance that we traverse would be the diameter of the graph, according to the definition.

        Algorithm

        Following the above intuition, the main algorithm is to find two extreme peripheral nodes via BFS traversal.

        Let us define a function called bfs(start) which returns two results: 1). the farthest node starting from the start node; 2). the distance between the start and the farthest nodes.

        As the name suggests, we could apply the BFS (Breadth-First Search) traversal to implement the above function.

        Once the bfs(start) is implemented, we simply invoke it twice to solve the problem. In the first invocation, we would obtain one of the extreme peripheral nodes. With the obtained peripheral node, we then invoke the function again to obtain the other extreme peripheral node and more importantly the distance between the two extreme peripheral nodes.


        Complexity Analysis

        Let NN be the number of nodes in the graph, then the number of edges in the graph would be N-1N−1 as specified in the problem.

        Time Complexity: \mathcal{O}(N)O(N)

        First we iterate through all edges to build an adjacency list representation of the graph. The time complexity of this step would be \mathcal{O}(N)O(N).

        In the main algorithm, we perform the BFS traversal twice on the graph. Each traversal will take \mathcal{O}(N)O(N) time, where we visit each node once and only once.

        To sum up, the overall time complexity of the algorithm is \mathcal{O}(N) + 2 \cdot \mathcal{O}(N) = \mathcal{O}(N)O(N)+2⋅O(N)=O(N).

        Space Complexity: \mathcal{O}(N)O(N)

        We used an adjacency list representation for the graph, whose space would be proportional to the total number of nodes and edges in the graph. Since the graph is undirected (i.e. the edge is bi-directional), the number of neighbors in the adjacency list would be twice the number of edges. Therefore, the space needed for the graph would be \mathcal{O}(N + 2 \cdot N) = \mathcal{O}(N)O(N+2⋅N)=O(N).

        During the BFS traversal, we used an array to indicate the state of each node (whether it is visited or not). This array would consume \mathcal{O}(N)O(N) space.

        During the BFS traversal, in addition, we used some queues to keep track of the nodes to be visited at each level (i.e. hop). At any given moment, we will keep no more than two levels of nodes in the queues. In the worst case, the queue could cover almost all nodes in the graph. As a result, the space complexity of the queues would be \mathcal{O}(N)O(N).

        To sum up, the overall space complexity of the algorithm is \mathcal{O}(N) + \mathcal{O}(N) + \mathcal{O}(N) = \mathcal{O}(N)O(N)+O(N)+O(N)=O(N).
    */
    int doit_bfs(vector<vector<int>>& edges) {
        
        vector<vector<int>> graph(edges.size()+1);

        for (auto& c : edges) {
            graph[c[0]].push_back(c[1]);
            graph[c[1]].push_back(c[0]);
        }

        auto bfs = [&](int org) -> std::pair<int, int> {

            queue<std::pair<int,int>> qu;
            qu.push({org, 0});
            unordered_set<int> seen;
            seen.insert(org);
            int maxdepth = 0, node = 0;

            while (!qu.empty()) {

                int size = qu.size();

                while (size--) {

                    auto [cur, dep] = qu.front();
                    qu.pop();
                    if (maxdepth < dep) {
                        maxdepth = dep;
                        node = cur;
                    }

                    for (auto nc : graph[cur]) {

                        if (seen.find(nc) == seen.end()) {
                            seen.insert(nc);
                            qu.push({nc, dep + 1});
                        }
                    }
                }
            }

            return {node, maxdepth};
        };

        // 1). find one of the farthest nodes
        // farthest_node, distance_1 = bfs(0)
        auto [n, depth1] = bfs(0);

        // 2). find the other farthest node
        // and the distance between two farthest nodes
        // another_farthest_node, distance_2 = bfs(farthest_node)
        auto [n2, depth2] = bfs(n);

        return depth2;
    }
}
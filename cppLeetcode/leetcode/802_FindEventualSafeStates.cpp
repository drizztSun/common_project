/*
# 802. Find Eventual Safe States

# In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.
# If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.

# Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.
# More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped at a terminal node in less than K steps.

# Which nodes are eventually safe?  Return them as an array in sorted order.

# The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.
# The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.

# Example:
# Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
# Output: [2,4,5,6]
# Here is a diagram of the above graph.

# Illustration of graph

# Note:

# graph will have length at most 10000.
# The number of edges in the graph will not exceed 32000.
# Each graph[i] will be a sorted list of different integers, chosen within the range [0, graph.length - 1].
*/

#include <vector>
#include <queue>

using std::queue;
using std::vector;

class EventualSafeNodes {

	/*
		802.Find-Eventual-Safe-States
		这是一道经典的涉及有向图是否存在环的问题。DFS和BFS都有经典的解决方案。

		DFS
		用DFS来判定是否有环，可以参考 207.Course-Schedule。基本思想是，将每个节点的visited标记为三种状态。第一次遍历到节点i标记2；如果从节点i后续的DFS都没有检测到环，成功回溯到节点i时，改标记为1.
		因此在遍历的过程中，遇到了已经标记为1的点，则说明之后肯定“安全”，不用再走下去；如果遇到了已经标记为2的点，则表示该DFS的路线遇到了环。

		在本题中，对任意节点i，如果DFS(i)判定无环，则可以放入答案中。

		BFS
		拓扑排序的应用。最容易判定safe的节点，是那些出度为0的节点。将这些点剪除之后，接下来出度为0的节点，肯定还是safe的节点。以此BFS不断推进，如果还有剩下的节点，那么他们肯定出度都不为0，即是互相成环的，可以终止程序。
	*/
	vector<int>visited;
    vector<vector<int>>graph;
    vector<int> eventualSafeNodes_dfs(vector<vector<int>>& graph) 
    {
        int n = graph.size();
        visited.resize(n,0);
        this->graph = graph;
        vector<int>rets;
        for (int i=0; i<n; i++)
            if (DFS(i)) rets.push_back(i);
        return rets;
    }

    bool DFS(int cur)
    {
        if (visited[cur]==1) return true;
        if (visited[cur]==2) return false;
        visited[cur] = 2;
        for (int next: graph[cur])
        {
            if (!DFS(next)) return false;
        }
        visited[cur] = 1;
        return true;
    }

public:

	vector<int> eventualSafeNodes_bfs_topsort(vector<vector<int>>& graph) 
    {
        int n = graph.size();
        vector<int>outDegree(n,0);
        vector<vector<int>>prev(n);

        for (int i=0; i<n; i++)
            for (auto j: graph[i])
            {
                prev[j].push_back(i);
                outDegree[i]+=1;
            }

        vector<int>ret;         
        queue<int>q;
        for (int i=0; i<n; i++)
        {
            if (outDegree[i]==0) 
            {
                q.push(i);
                ret.push_back(i);
            }
        }
            
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int prev: prev[cur])
            {
                outDegree[prev] -= 1;
                if (outDegree[prev]==0)
                {
                    q.push(prev);
                    ret.push_back(prev);                    
                }
            }
        }
        sort(ret.begin(), ret.end());
        return ret;        
    }


public:

	bool dfs(int n, const vector<vector<int>>& graph, vector<int>& terminal) {

		terminal[n] = -1;

		for (auto c : graph[n]) {
			if (terminal[c] == -1 || (terminal[c] == 0 && !dfs(c, graph, terminal))) {
				terminal[c] = -1;
				return false;
			}
		}

		terminal[n] = 1;
		return true;
	}

	vector<int> doit_dfs(vector<vector<int>>&& graph) {

		vector<int> terminal(graph.size());
		vector<int> res;

		for (size_t c = 0; c < terminal.size(); c++) {
			terminal[c] = 0;
			if (graph[c].size() == 0) {
				terminal[c] = 1;
			}
		}

		for (size_t i = 0; i < graph.size(); i++) {
			if (dfs(i, graph, terminal))
				res.push_back(i);
		}

		return res;
	}
};
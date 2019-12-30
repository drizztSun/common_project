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
using std::vector;

class EventualSafeNodes {
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

	vector<int> doit(vector<vector<int>>& graph) {

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

void Test_802_FindEventualSafeStates() {

	auto res = EventualSafeNodes().doit(vector<vector<int>>{ {1, 2}, { 2, 3 }, { 5 }, { 0 }, { 5 }, {}, {}});

	int i = 0;
}
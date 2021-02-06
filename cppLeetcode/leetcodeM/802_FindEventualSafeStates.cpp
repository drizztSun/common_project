/*
802. Find Eventual Safe States

We start at some node in a directed graph, and every turn, we walk along a directed edge of the graph. If we reach a terminal node (that is, it has no outgoing directed edges), we stop.

We define a starting node to be safe if we must eventually walk to a terminal node. More specifically, there is a natural number k, so that we must have stopped at a terminal node in less than k steps for any choice of where to walk.

Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.

The directed graph has n nodes with labels from 0 to n - 1, where n is the length of graph. The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph, going from node i to node j.

 

Example 1:

Illustration of graph
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Example 2:

Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
 

Constraints:

n == graph.length
1 <= n <= 104
0 <= graph[i].legnth <= n
graph[i] is sorted in a strictly increasing order.
The graph may contain self-loops.
The number of edges in the graph will be in the range [1, 4 * 104].


*/
#include <vector>

using std::vector;

class EventualSafeNodes {

public:
    
    vector<int> doit_dfs(vector<vector<int>>& graph) {

        vector<int> terminal(graph.size());

		for (size_t c = 0; c < terminal.size(); c++) {
			terminal[c] = 0;
			if (graph[c].size() == 0) {
				terminal[c] = 1;
			}
		}

        std::function<bool(int)> dfs = [&](int n) {

            terminal[n] = -1;

            for (auto c : graph[n]) {
                if (terminal[c] == -1 || (terminal[c] == 0 && !dfs(c, graph, terminal))) {
                    terminal[c] = -1;
                    return false;
                }
            }

            terminal[n] = 1;
            return true;
        };

		for (size_t i = 0; i < graph.size(); i++) {
			dfs(i, graph, terminal);
		}

		vector<int> res;
		for (size_t t = 0; t < terminal.size(); t++) {
			if (terminal[t] == 1) {
				res.push_back(t);
			}
		}

		return res;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {

        int WHITE = 0, GRAY = 1, BLACK = 2;
        //unordered_map<int, int> colors(graph.size(), 0);
        vector<int> colors(graph.size(), WHITE);
        
        std::function<bool(int)> dfs = [&](int node) {
            
            if (colors[node] != WHITE)
                return colors[node] == BLACK;
            
            colors[node] = GRAY;
            for (auto child : graph[node]) {
                
                if (colors[child] == BLACK) continue;
                
                if (colors[child] == GRAY || !dfs(child))
                    return false;
            }
            
            colors[node] = BLACK;
            return true;
        };
        
        vector<int> res;
        // vector<int> input;
        // std::iota(begin(input), end(input), graph.size());
        // std::copy_if(begin(input), end(input), back_inserter(res), dfs);
        
        for (int i = 0; i < graph.size(); i++) {
            if (dfs(i)) res.push_back(i);
        }
        return res;
    }
};
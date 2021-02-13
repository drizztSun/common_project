/*
1514. Path with Maximum Probability

You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of traversing that edge succProb[i].

Given two nodes start and end, find the path with the maximum probability of success to go from start to end and return its success probability.

If there is no path from start to end, return 0. Your answer will be accepted if it differs from the correct answer by at most 1e-5.

 

Example 1:



Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.
Example 2:



Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
Output: 0.30000
Example 3:



Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.
 

Constraints:

2 <= n <= 10^4
0 <= start, end < n
start != end
0 <= a, b < n
a != b
0 <= succProb.length == edges.length <= 2*10^4
0 <= succProb[i] <= 1
There is at most one edge between every two nodes.

*/
#include <vector>
#include <queue>

using std::priority_queue;
using std::vector;


class PathMaximumProbability {
public:
    
    struct comparator { 
        bool operator()(std::pair<int,double> const& a, std::pair<int,double> const& b)  
        { 
            // get max probability cost item from priority queue
            return (b.second - a.second) > 0.00001;  
        } 
    }; 
    
    double doit_dijkstra(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        
        // graph Adjacency list containing connected node and probability cost
        vector<vector<std::pair<int,double>>> graph(n);
        
        // edge cost
        int edge_size = edges.size();
        
        // populate adjacency list from given edges containing both node and probability cost
        for(int i=0;i<edge_size;i++)
        {
            graph[edges[i][0]].push_back(std::make_pair(edges[i][1],succProb[i]));
            graph[edges[i][1]].push_back(std::make_pair(edges[i][0],succProb[i]));
        }
        
        // max probability cost track vector of nodes
        vector<double> probCost(n, DBL_MIN);

        // priority queue of <node,probability cost> based on maximum probability cost
        priority_queue<std::pair<int,double>,vector<std::pair<int,double>>, comparator>Q;
        
        // insert start node with max probability 1
        Q.push(std::make_pair(start, 1.0));
        
        // update start node probability in probCost
        probCost[start] = 1.0;
        
        // max probability of end node
        double maxProb = 0.0;
        
        int node;
        double nodeProb;
        int neighbour;
        double edgeProb;
        
        // Run BFS until end node is reached or Q is empty
        while(!Q.empty())
        {
            node = Q.top().first;
            nodeProb = Q.top().second;
            
            Q.pop();
            
            // If current node probability cost > nodeProb then ignore 
            if(probCost[node]>nodeProb) continue;
            
            // If end node is reached then retuen node probability and end BFS
            if(node == end) {
                maxProb = std::max(maxProb,nodeProb);
                break;
            }
            
            // Loop through all neighbour nodes
            for(int i=0;i<graph[node].size();i++)
            {
                neighbour = graph[node][i].first;
                edgeProb = graph[node][i].second;
                
                // If node-> neighbour probability cost * nodeProb > probCost[neighbour] 
                // then update probCost of neigbour and push it to the queue
                if(edgeProb*probCost[node] > probCost[neighbour])
                {
                    probCost[neighbour] = edgeProb*probCost[node];
                    Q.push(std::make_pair(neighbour,probCost[neighbour]));
                }
            }
        }
        
        // return max probability of end node
        return maxProb;
    }

};
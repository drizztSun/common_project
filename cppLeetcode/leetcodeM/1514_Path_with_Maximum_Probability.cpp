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
#include <set>

using std::set;
using std::queue;
using std::priority_queue;
using std::vector;


class PathMaximumProbability {


    /*
        1514.Path-with-Maximum-Probability
        解法1：常规BFS
        常规的BFS解法就是从start出发往周围的点遍历。但是，并不是某个点被遍历过之后就不要再遍历了。这是因为通过不同路径到达某个点时的概率是不同的。某些路径虽然在BFS的算法中晚遍历到点A，但路径概率更大，这就意味着从A往后延伸的路径必须再次重新遍历。这个算法的时间复杂度可以很高。

        解法2：Dijkstra 贪心
        回顾一下Dijkstra算法。它适合单源非负权重图。所谓“单源”，就是它只能求某个特定节点作为起点的最短路径。思想是基于BFS的贪心策略。在队列中的所有节点都按照“（从起点）到达路径长度”排序，任何轮次中，最先弹出的节点A如果之前从没有访问过，那么它所对应的路径就一定是从起点到A的最短路径。

        本题需要改造一番才能使用Dijkstra算法。原本的题意是求最大乘积路径问题：

        maxmize prob(E1)*prob(E2)*...*prob(Ek) 
        = maxmize log[prob(E1)]+log[prob(E2)] + ... + log[prob(Ek)] 
        = minimize -log[prob(E1)] -log[prob(E2)] - ... -log[prob(Ek)]
        我们发现每条边的-log[prob(Ek)]都是正数，并且目标是最小化路径之和。所以考虑-log[prob(Ek)]为权重的图，原题就可以转化成标准的最短路径问题。
    */
    double doit_dijkstra(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) 
    {
        vector<vector<std::pair<int, double>>>Next(n);
        for (int i=0; i<edges.size(); i++)
        {
            Next[edges[i][0]].push_back({edges[i][1], -log(succProb[i])});
            Next[edges[i][1]].push_back({edges[i][0], -log(succProb[i])});
        }

        set<std::tuple<double, int>> Set; // {dist, node}
        Set.insert({0, start});
        vector<double>prob(n,-1);

        while (!Set.empty())
        {
            double dist = std::get<0>(*Set.begin());
            int curNode = std::get<1>(*Set.begin());            
            Set.erase(Set.begin());

            if (prob[curNode]!=-1) continue;
            prob[curNode] = dist;
            
            if (curNode==end) return exp(-prob[curNode]);

            for (auto next: Next[curNode])
            {
                int nextNode = next.first;
                double edge = next.second;
                if (prob[nextNode]!=-1) continue;
                Set.insert({dist + edge, nextNode});
            }
        }

        return 0;
    }

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) 
    {
        vector<vector<std::pair<int, double>>>Next(n);
        for (int i=0; i<edges.size(); i++)
        {
            Next[edges[i][0]].push_back({edges[i][1], succProb[i]});
            Next[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }
        
        vector<double>prob(n);
        prob[start] = 1;
        queue<int>q;
        q.push(start);
        
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (auto next: Next[cur])
            {
                if (prob[next.first] >= prob[cur] * next.second) continue;
                prob[next.first] = prob[cur]*next.second;
                q.push(next.first);
            }
        }
        return prob[end];
    }


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
            if(probCost[node] > nodeProb) continue;
            
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
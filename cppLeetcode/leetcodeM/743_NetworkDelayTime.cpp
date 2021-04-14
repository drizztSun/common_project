/*
743. Network Delay Time


You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), 
where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. Return the time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.

 

Example 1:


Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
Example 2:

Input: times = [[1,2,1]], n = 2, k = 1
Output: 1
Example 3:

Input: times = [[1,2,1]], n = 2, k = 2
Output: -1
 

Constraints:

1 <= k <= n <= 100
1 <= times.length <= 6000
times[i].length == 3
1 <= ui, vi <= n
ui != vi
0 <= wi <= 100
All the pairs (ui, vi) are unique. (i.e., no multiple edges.)


*/
#include <vector>
#include <unordered_map>
#include <queue>

using std::priority_queue;
using std::queue;
using std::unordered_map;
using std::vector;

class NetworkDelayTime {

    /*
        743.Network-Delay-Time
        BFS
        此题和＂913　Cat and Mouse＂一样，扩展了我们对于BFS的认识．BFS的节点的状态可以是多个参数的．在这里，队列里每个节点的状态表示为(node,ArrivalTime).注意，这里的ArrivalTime是只入队列时候的．此外，我们还需要一个map，来记录每个节点当前最新的earliestArrivalTime，这个是实时更新的．

        我们取出一个节点，查看它的ArrivalTime是否能给它的邻接点带来时间上的更新．也就是比较ArrivalTime+weight < earliestArrivalTime[nextNode]，是的话，我们就更新nextNode并且把这个新状态(nextNode,ArrivalTime+weight)加入队列．

        当队列为空时，说明没有什么可以更新的了．此时查看map里存放的就是每个节点的最终earliestArrivalTime．

        Dijkstra (BFS+PQ)
        对于BFS，每一次扩展对应的只是“几何意义上的”层级的自增1，只适合寻找“最少步数”。如果每一步有权重（相当于边有权值）、求起点到终点最短权重总和的问题，那么传统的BFS就不太方便。

        Dijkstra的本质就是将BFS的传统队列替换为优先队列，采用贪心的策略。每次从优先队列中弹出当前离起点最近的点cur，然后将它所有邻接的点以{dist, next}的形式加入队列，其中dist就是起点到cur的距离再加上cur->next的这条边权。我们有这样一个贪心的结论：如果某个节点第一次从这个优先队列中弹出来，它所对应的dist就是起点到该节点的最短距离。

        这种方法的时间复杂度是ElogE. 通常情况下，如果不是稠密图，ElogE会比N^2有优势。

        Dijkstra也有o(N^2)的实现方法。每个回合在所有的点中找到未收录的、离起点最近的那个节点，然后收录这个节点（确认这个节点的最短距离），并以这个节点更新它的所有邻接节点的距离。重复N个回合。

        Floyd
        求两点之间的最短路径，典型的图论中的基本算法。Floyd是我的首选，因为代码短，容易理解，而且对于边权的值没有正数的限制。本质就是轮遍所有的节点k看是否能对dp[i][j]的更新做贡献。即 dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j])
    */



public:
    
    int doit_bfs(vector<vector<int>>& times, int N, int K) {

        unordered_map<int,int>EarliestTime; // node->earliestTime;
        for (int i=1; i<=N; i++)
            EarliestTime[i] = INT_MAX;
        EarliestTime[K] = 0;
        
        unordered_map<int,vector<std::pair<int,int>>>next;
        for (auto time: times) {
            next[time[0]].push_back({time[1],time[2]});
        }
        
        queue<std::pair<int,int>>q; // {node,earliestTime}
        q.push({K,0});
        
        while (!q.empty())
        {
            int curNode = q.front().first;
            int curTime = q.front().second;
            q.pop();
            
            if (curTime>EarliestTime[curNode]) continue;
            
            for (auto t: next[curNode])
            {
                int nextNode = t.first;
                int weight = t.second;
                
                if (EarliestTime[nextNode] <= EarliestTime[curNode]+weight)
                    continue;
                    
                EarliestTime[nextNode] = EarliestTime[curNode]+weight;
                q.push({nextNode,EarliestTime[nextNode]});
            }
        }
        
        int result = 0;
        for (int i=1; i<=N; i++)
            result = std::max(result, EarliestTime[i]);

        return result==INT_MAX ? -1 : result;
    }

    /*
        Approach #2: Dijkstra's Algorithm [Accepted]
        Intuition and Algorithm

        We use Dijkstra's algorithm to find the shortest path from our source to all targets. This is a textbook algorithm, refer to this link for more details.

        Dijkstra's algorithm is based on repeatedly making the candidate move that has the least distance travelled.

        In our implementations below, we showcase both O(N^2) (basic) and O(NlogN) (heap) approaches.

        Basic Implementation

        Complexity Analysis

        Time Complexity: O(N^2 + E) where E is the length of times in the basic implementation, and O(ElogE) in the heap implementation, as potentially every edge gets added to the heap.

        Space Complexity: O(N+E), the size of the graph O(E), plus the size of the other objects used O(N).
    */

    typedef std::pair<int,int> PII;
    // O(elog(e)) Heap Implementation
    int doit_dijkstra_eloge(vector<vector<int>>& times, int n, int k) 
    {
        unordered_map<int, vector<PII>>Map;
        for (auto t: times)
            Map[t[0]].push_back({t[1], t[2]});


        priority_queue<PII, vector<PII>, std::greater<PII>>pq;
        pq.push({0,k});
        vector<int>visited(n+1,0);
        
        int ret = 0;
        while (!pq.empty())
        {
            auto [d, cur] = pq.top();
            pq.pop();
            
            if (visited[cur]) continue;
            visited[cur] = 1;
            
            ret = std::max(ret, d);
            
            for (auto next: Map[cur])
                pq.push({d+next.second, next.first});
        }

        for (int i=1; i<=n; i++)
            if (visited[i]==0) return -1;

        return ret;
    }

    // O(n^2)
    int doit_dijkstra_1(vector<vector<int>>& times, int n, int k) 
    {
        unordered_map<int, vector<PII>> Map;
        for (auto t: times)
            Map[t[0]].push_back({t[1], t[2]});

        vector<int>dist(n+1, INT_MAX);
        vector<bool>seen(n+1, 0);
        dist[k] = 0;
        
        for (int i=1; i<=n; i++)
        {
            int minVal = INT_MAX;
            int minNode = -1;
            for (int j=1; j<=n; j++)
            {
                if (!seen[j] && dist[j]<minVal)
                {
                    minVal = dist[j];
                    minNode = j;
                }
            }    
            if (minNode==-1) break;
            seen[minNode] = 1;
                
            for (auto [next, d]: Map[minNode])
                dist[next] = std::min(dist[next], dist[minNode]+d);
        }
        
        int ret = 0;
        for (int i=1; i<=n; i++)
            ret = std::max(ret, dist[i]);

        return ret == INT_MAX ? -1: ret;
    }

    // O(n^3)
    int doit_floyd(vector<vector<int>>& times, int N, int K) {
        
        vector<vector<int>> dp(N+1, vector<int>(N+1, INT_MAX/2));
        
        for (auto& t: times)
            dp[t[0]][t[1]] = t[2];

        for (int i=1; i<=N; i++)
            dp[i][i] = 0;
        
        for (int k =1; k<=N; k++)
            for (int i=1; i<=N; i++)
                for (int j=1; j<=N; j++)
                    dp[i][j] = std::min(dp[i][j], dp[i][k]+dp[k][j]);
        
        int ret = 0;
        for (int i = 1; i <= N; i++)
            ret = std::max(ret, dp[K][i]);
        
        return (ret == INT_MAX/2) ? -1: ret;
    }
};
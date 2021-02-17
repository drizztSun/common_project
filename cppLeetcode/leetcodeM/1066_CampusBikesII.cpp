/*
 1066. Campus Bikes II
 
 On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. Each worker and bike is a 2D coordinate on this grid.

 We assign one unique bike to each worker so that the sum of the Manhattan distances between each worker and their assigned bike is minimized.

 The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.

 Return the minimum possible sum of Manhattan distances between each worker and their assigned bike.

  

 Example 1:


 Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
 Output: 6
 Explanation:
 We assign bike 0 to worker 0, bike 1 to worker 1. The Manhattan distance of both assignments is 3, so the output is 6.
 Example 2:


 Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
 Output: 4
 Explanation:
 We first assign bike 0 to worker 0, then assign bike 1 to worker 1 or worker 2, bike 2 to worker 2 or worker 1. Both assignments lead to sum of the Manhattan distances as 4.
 Example 3:

 Input: workers = [[0,0],[1,0],[2,0],[3,0],[4,0]], bikes = [[0,999],[1,999],[2,999],[3,999],[4,999]]
 Output: 4995
  

 Constraints:

 N == workers.length
 M == bikes.length
 1 <= N <= M <= 10
 workers[i].length == 2
 bikes[i].length == 2
 0 <= workers[i][0], workers[i][1], bikes[i][0], bikes[i][1] < 1000
 All the workers and the bikes locations are unique.

 
 
 */
#include <vector>
#include <functional>
#include <queue>
#include <algorithm>

using std::priority_queue;
using std::vector;


class CampusBikes {
    
public:

    /*
        1066.Campus-Bikes-II
        此题是著名的带权二分图的最优匹配问题，可由KM算法解决。在这里我们尝试用比较容易理解的搜索的方法来解决。

        我们将“自行车被选取的状态”作为节点，状态之间的跳转理解为节点之间的相邻关系，状态之间的权重差就是相邻边的权重，就可以用Dijkstra算法了。举个例子，状态0110表示前两个工人（0号和1号）已经被配对1号和2号自行车的最优价值（即最小的配对距离之和）。
        注意，这个状态中我们不再区分前两个工人分别配对了哪辆自行车，我们不关心，我们只关心前两个工人的总和状态。
        状态0110可以转移到另外两种状态：如果2号工人选择0号自行车，即转移到了1110，权重的变化就是dist[2][2]；如果2号工人选择3号自行车，即转移到了0111，权重的变化就是dist[3][2]。

        我们的起点是全为0的state，终点是一个包含m个1（工人数目）的state，求其最短路径。至此，我们已经完全把这道题转化为了Dijkstra的模板了。
        BFS+PQ利用贪心法的思想就可以很容易解决：利用优先队列来进行BFS搜索，所有状态在队列里按照cost从小到大排序。如果某个状态第一次被PQ弹出，那么它对应的cost就是实现该状态的最优解。
    */
    typedef std::pair<int,int> PII;
    
    int doit_bfs(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        
        int m = workers.size(), n = bikes.size();

        vector<vector<int>> dist(m, vector<int>(n, 0));
        vector<int> visited(1<<n);

        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
            {
                int x1=workers[i][0];
                int y1=workers[i][1];
                int x2=bikes[j][0];
                int y2=bikes[j][1];
                dist[i][j] = abs(x1-x2) + abs(y1-y2);
            }
        
        priority_queue<PII, vector<PII>, std::greater<>>pq;        
        pq.push({0, 0});        
        
        while (!pq.empty())
        {
            auto [cost, state] = pq.top();
            pq.pop();
                        
            if (visited[state]) continue;
            visited[state] = 1;
            
            int i = __builtin_popcount(state);
            if (i == m) return cost;
                
            for (int j = 0; j < bikes.size(); j++)
            {
                if ((state >> j) & 1) continue;
                int newState = state + (1<<j);
                if (visited[newState]) continue;                    
                pq.push({cost + dist[i][j], newState});
            }
        }
                
        return 0;
    }
    
    int doit_dp_bitmask_backtracking(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        auto n = workers.size();
        auto m = bikes.size();
        
        vector<vector<int> > dp(n, vector<int>(1<<m, -1));
        
        std::function<int(int, int)> solve = [&](int i, int mask) {
            if(i == dp.size()) return 0;

            if(dp[i][mask] != -1) return dp[i][mask];
            
            int &res = dp[i][mask];
            res = 1e7;
            
            for(int j = 0; j < bikes.size(); j++) {
                if((mask & (1<<j)) == 0) {
                    int cost = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]) + solve(i+1, mask | (1<<j));
                    res = std::min(res, cost);
                }
            }
            return res;
        };
        
        return solve(0, 0);
    }
};

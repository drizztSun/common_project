/*
815. Bus Routes

You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.

For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.

Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.

 

Example 1:

Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
Output: 2
Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
Example 2:

Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
Output: -1
 

Constraints:

1 <= routes.length <= 500.
1 <= routes[i].length <= 105
All the values of routes[i] are unique.
sum(routes[i].length) <= 105
0 <= routes[i][j] < 106
0 <= source, target < 106

*/





#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using std::unordered_set;
using std::unordered_map;
using std::queue;
using std::vector;


class BusRoute {

    /*
    815.Bus-Routes
    此题求最短的路径，可以尝试ＢＦＳ．有两种完全对称的思路．

    第一种：因为题目问搭乘最少的route数目，我们可以尝试队列里放的就是routes.初始时，队列放S所连接的所有routes，然后对队列里的route查看它所到达的stop继而遍历这些stop可以继续延伸的routes．如果新的路线没有被访问过，就可以加入队列．结果是TLE．原因在于，从一个curRoute，考察所有的stop继而再考察所有延伸的nextRoute，这散开的规模非常大．

    针对上面的算法，一个显而易见的改进就是，不仅考虑visitedRoutes，也需要考虑visitedStops，用两个集合来剪枝．这样可以勉强AC．之所以勉强，是因为在代码里我们需要先考虑的是ｖisitedStops，而一个stop所对应的route数量比较少，所以能对应节省的routes搜索比较有限．

    第二种：我们考虑另外一种队列的结果，里面存放的不是route而是stop．初始时，队列里只有Ｓ．从起点开始，查看这个站点可以搭乘哪些routes，继而遍历这些routes可以继续到达的stops.同样，我们需要两个集合visitedRoutes和visitedStops来一起去重．这个算法和第一种算法完全对偶，但要比第一种快得多．这是因为代码里我们会先根据visitedRoutes来筛选，通常一条线路会有很多的stops,所以我们通过这个步骤先期筛除的stop会更多．
    */
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) 
    {
        if (S==T) return 0;
        
        unordered_map<int,vector<int>>stop2routes;
        for (int i=0; i<routes.size(); i++)        
            for (int j=0; j<routes[i].size(); j++)
                stop2routes[routes[i][j]].push_back(i);
        
        queue<std::pair<int,int>>q;
        unordered_set<int>visitedRoutes;
        unordered_set<int>visitedStops;
        for (auto route: stop2routes[S])
        {
            q.push({route,1});
            visitedRoutes.insert(route);
            visitedStops.insert(S);
        }            
        
        while (!q.empty())
        {
            int curRoute = q.front().first;
            int step = q.front().second;
            q.pop();
            
            for (int stop: routes[curRoute])
            {
                if (stop==T) return step;
                if (visitedStops.find(stop)!=visitedStops.end()) continue;
                    
                visitedStops.insert(stop);
                for (int nextRoute: stop2routes[stop])
                {
                    if (visitedRoutes.find(nextRoute)!=visitedRoutes.end())
                        continue;
                    visitedRoutes.insert(nextRoute);
                    q.push({nextRoute,step+1});
                }
            }            
        }
        return -1;
    }

public:

    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) 
    {
        if (S==T) return 0;
        
        unordered_map<int,vector<int>>stop2bus;
        for (int i=0; i<routes.size(); i++)
        {
            for (auto j: routes[i])
                stop2bus[j].push_back(i);
        }
        
        unordered_set<int>visitedStop;
        unordered_set<int>visitedBus;
        
        queue<int>q;
        q.push(S);
        visitedStop.insert(S);
        int step = -1;
        
        while (!q.empty())
        {
            step += 1;
            
            int len = q.size();
            while (len--)
            {
                int curStop = q.front();
                q.pop();
                
                for (auto bus: stop2bus[curStop])
                {
                    if (visitedBus.find(bus)!=visitedBus.end())
                        continue;
                    visitedBus.insert(bus);                        
                    
                    for (auto nextStop: routes[bus])
                    {
                        if (visitedStop.find(nextStop)!=visitedStop.end())
                            continue;
                        if (nextStop==T)
                            return step+1;
                        
                        q.push(nextStop);
                        visitedStop.insert(nextStop);
                    }
                }
            }
        }
        
        return -1;
    }

public:

    int doit_bfs(vector<vector<int>>& routes, int source, int target) {
        
        if (source == target) return 0;
        
        unordered_map<int, unordered_set<int>> bus;
        
        for (int i = 0; i < routes.size(); i++) {
            for (auto c: routes[i])
                bus[c].insert(i);
        }
        
        unordered_set<int> stations;
        unordered_set<int> lines;
        queue<int> qu;
        qu.push(source);
        stations.insert(source);
        int stops = 0;
        
        while(!qu.empty()) {
            
            int sz = qu.size();
            
            while (sz--) {
                
                int c = qu.front();
                qu.pop();
                
                if (c == target) return stops;
                
                for (auto line: bus[c]) {
                    
                    if (lines.count(line) != 0) continue;
                
                    lines.insert(line);
                    
                    for (auto s: routes[line]) {
                        
                        if (stations.count(s) == 0) {
                            
                            stations.insert(s);
                            
                            qu.push(s);
                        }
                    }
                }
                
            }
            
            stops++;
        }
        
        return -1;
    }

};
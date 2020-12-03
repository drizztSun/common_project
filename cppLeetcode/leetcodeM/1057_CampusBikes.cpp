/*
 1057. Campus Bikes
 
 On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. Each worker and bike is a 2D coordinate on this grid.

 Our goal is to assign a bike to each worker. Among the available bikes and workers, we choose the (worker, bike) pair with the shortest Manhattan distance between each other,
 and assign the bike to that worker. (If there are multiple (worker, bike) pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index;
 if there are multiple ways to do that, we choose the pair with the smallest bike index). We repeat this process until there are no available workers.

 The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.

 Return a vector ans of length N, where ans[i] is the index (0-indexed) of the bike that the i-th worker is assigned to.

  

 Example 1:



 Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
 Output: [1,0]
 Explanation:
 Worker 1 grabs Bike 0 as they are closest (without ties), and Worker 0 is assigned Bike 1. So the output is [1, 0].
 Example 2:



 Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
 Output: [0,2,1]
 Explanation:
 Worker 0 grabs Bike 0 at first. Worker 1 and Worker 2 share the same distance to Bike 2, thus Worker 1 is assigned to Bike 2,
 and Worker 2 will take Bike 1. So the output is [0,2,1].
  

 Note:

 0 <= workers[i][j], bikes[i][j] < 1000
 All worker and bike locations are distinct.
 1 <= workers.length <= bikes.length <= 1000
 */
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using std::priority_queue;
using std::vector;
using std::unordered_set;
using std::unordered_map;


class CampusBikes {
    
    struct node{
        int dist, worker, bike;
    };
    
public:
    vector<int> doit_(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        
        unordered_map<int, vector<std::pair<int, int>>> buckets;
        priority_queue<int, vector<int>, std::greater<int>> que;
        
        for (unsigned int i = 0; i < workers.size(); i++) {
            for (unsigned int j = 0; j < bikes.size(); j++) {
                const unsigned int dist = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);
                buckets[dist].push_back({i, j});
                que.push(dist);
            }
        }
        
        vector<bool> bikeVisited(bikes.size(), false);
        vector<int>  res(workers.size(), -1);
        auto cnt = workers.size();
        
        while (!que.empty()) {
            auto c = que.top();
            for (auto& val : buckets[c]) {
                const unsigned int bikeId   = val.first;
                const unsigned int workerId = val.second;
                if ((res[workerId] == -1) && !bikeVisited[bikeId]) {
                    res[workerId] = bikeId;
                    bikeVisited[bikeId] = true;
                    cnt--;
                }
                if (cnt == 0) {
                    return res;
                }
            }
            que.pop();
            
        }
        
        return res;
    }
    
    // O(NM)
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        static const int bucketsSize = 2001;
        vector<vector<unsigned int>> buckets(bucketsSize, vector<unsigned int>());
        for (unsigned int i = 0; i < workers.size(); i++) {
            for (unsigned int j = 0; j < bikes.size(); j++) {
                const unsigned int dist = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);
                buckets[dist].push_back((i << 10) + j);
            }
        }
        
        vector<bool> bikeVisited(bikes.size(), false);
        vector<int>  res(workers.size(), -1);
        auto cnt = workers.size();
        for (const auto& vec : buckets) {
            for (auto val : vec) {
                const unsigned int bikeId   = val & 0x3FF;
                const unsigned int workerId = val >> 10;
                if ((res[workerId] == -1) && !bikeVisited[bikeId]) {
                    res[workerId] = bikeId;
                    bikeVisited[bikeId] = true;
                    cnt--;
                }
                if (cnt == 0) { return res; }
            }
        }
        return res;
    }
    
    // O(NMlog(NM))
    vector<int> doit_greedy(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
    
        
        auto myfunc = [&](node& a, node& b){
            if(a.dist != b.dist)
                return a.dist < b.dist;
            else{
                if(a.worker != b.worker)
                    return a.worker < b.worker;
                else
                    return a.bike < b.bike;
            }
        };
        
        vector<node> nodes;
        auto m = workers.size(), n = bikes.size();
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                int dist = abs(workers[i][1] - bikes[j][1]) + abs(workers[i][0] - bikes[j][0]);
                node cur = {dist, i, j};
                nodes.push_back(cur);
            }
        }
        
        sort(nodes.begin(), nodes.end(), myfunc);
        
        vector<int> result(m, -1);
        unordered_set<int> marked;
        
        for(int i=0; i<nodes.size(); i++){
            if(result[nodes[i].worker] == -1 && marked.find(nodes[i].bike) == marked.end()){
                result[nodes[i].worker] = nodes[i].bike;
                marked.insert(nodes[i].bike);
            }
        }
        
        return result;
    }
    
};
/*
1584. Min Cost to Connect All Points



You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

 

Example 1:



Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation:

We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.
Example 2:

Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18
Example 3:

Input: points = [[0,0],[1,1],[1,0],[-1,1]]
Output: 4
Example 4:

Input: points = [[-1000000,-1000000],[1000000,1000000]]
Output: 4000000
Example 5:

Input: points = [[0,0]]
Output: 0
 

Constraints:

1 <= points.length <= 1000
-106 <= xi, yi <= 10^6
All pairs (xi, yi) are distinct.


*/
#include <vector>
#include <array>
#include <algorithm>
#include <queue>

using std::priority_queue;
using std::array;
using std::vector;


class MinCostConnectPoints {

public:
    int doit_(vector<vector<int>>& points) {

        int p = points.size(), res = 0, cur = 0;
        vector<int> minCost(p, INT_MAX);
        vector<bool> visited(p, false);

        auto manhattan = [&](vector<int> &p1, vector<int> &p2) {
            return((abs(p2[0] - p1[0]) + abs(p2[1] - p1[1])));
        };

        for (int i = 0; i < p-1; i++)
        {
            int nextmin = INT_MAX;
            int next = cur;
            visited[cur] = true;
            
            for (int j = 0; j < p; j++)
            {
                if (visited[j]) continue;
                minCost[j] = std::min(minCost[j], manhattan(points[cur], points[j]));
                if (minCost[j] < nextmin)
                {
                    nextmin = minCost[j];
                    next = j;
                }
            }
            res += nextmin;
            cur = next;
        }    
        return res;
    }

    /*
        We can imagine that every point is a node of the graph, connected to all other points, and the lenght of the edge is the manhattan distance between two points.

        To find the min cost, we therefore need to find the minimum spanning tree.

        Kruskal vs. Prim's
        Based on the OJ test cases, the performance of both algorithms is similar (accepted in ~500 ms), and Kruskal seems to have a small advantage (~50 ms) in avarage.

        Note: I tried to sort all edges first, but I got TLE during the contest. I think that limits for C++ are too tight. I then used a min heap, and it worked.

        For Kruskal, the complexity when using sort is O(n * n log (n * n)) - we have n * n edges. Using a min heap is O(k log (n * n)), where k is the number of edges we need to pull to complete the tree. It's much smaller than n * n in the average case.

        At the same time, Prim's implementation is simpler/shorter. Also, we can do an optimization for a complete graph, as suggested by mithuntm below.

        Check out the optiized Prim's impementation below- it has a blasting 80 ms runtime!!

        Kruskal
        Kruskal involves min heap to pick the smallest edge, and union-find to check if the edge is redundant. We exit when all points are connected.

    */
    int doit_(vector<vector<int>>& ps) {
        int n = ps.size(), res = 0;
        vector<int> ds(n, -1);
        vector<array<int, 3>> arr;

        auto find = [](vector<int> &ds, int i) {
            return ds[i] < 0 ? i : ds[i] = find(ds, ds[i]);
        };

        for (auto i = 0; i < n; ++i) {
            for (auto j = i + 1; j < n; ++j) {
                arr.push_back({abs(ps[i][0] - ps[j][0]) + abs(ps[i][1] - ps[j][1]), i, j});
            }
        }

        std::make_heap(std::begin(arr), std::end(arr), std::greater<array<int, 3>>());

        while (!arr.empty()) {

            std::pop_heap(std::begin(arr), std::end(arr), std::greater<array<int, 3>>());
            auto [dist, i, j] = arr.back();

            arr.pop_back();
            i = find(ds, i), j = find(ds, j);
            if (i != j) {
                res += dist;
                ds[i] += ds[j];
                ds[j] = i;
                if (ds[i] == -n)
                    break;
            }
        }
        return res;
    }
    /*
        Prim's
        In the Prim's algorithm, we are building a tree starting from some initial point. We track all connected points in visited. 
        For the current point, we add its edges to the min heap. Then, we pick a smallest edge that connects to a point that is not visited. Repeat till all points are visited.
    */
    int doit_prim(vector<vector<int>>& ps) {
        int n = ps.size(), res = 0, i = 0, connected = 0;
        vector<bool> visited(n);
        priority_queue<std::pair<int, int>> pq;

        while (++connected < n) {
            visited[i] = true;
            for (int j = 0; j < n; ++j)
                if (!visited[j])
                    pq.push({-(abs(ps[i][0] - ps[j][0]) + abs(ps[i][1] - ps[j][1])), j});
            while (visited[pq.top().second])
                pq.pop();
            res -= pq.top().first;
            i = pq.top().second;
            pq.pop();
        }
        return res;
    }
    
    /*
        Prim's for Complete Graph
        For this problem, any two points can be connected, so we are dealing with the complete graph. Thus, the number of edges is much larger (a square of) the number of points.

        As suggested by mithuntm, we can keep track of the minimal distance to each point, and update that distance as we connect more points. For each round, we need to scan all points to find the next point to connect to.
    */
    int doit_prim_(vector<vector<int>>& ps) {
        int n = ps.size(), res = 0, i = 0, connected = 0;
        vector<int> min_d(n, 10000000);

        while (++connected < n) {
            min_d[i] = INT_MAX;
            int min_j = i;
            for (int j = 0; j < n; ++j)
                if (min_d[j] != INT_MAX) {
                    min_d[j] = std::min(min_d[j], abs(ps[i][0] - ps[j][0]) + abs(ps[i][1] - ps[j][1]));
                    min_j = min_d[j] < min_d[min_j] ? j : min_j;
                }
            res += min_d[min_j];
            i = min_j;
        }
        
        return res;
    }
};


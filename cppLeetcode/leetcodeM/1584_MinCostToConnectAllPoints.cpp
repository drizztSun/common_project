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
#include <functional>
#include <algorithm>
#include <queue>

using std::priority_queue;
using std::array;
using std::vector;


class MinCostConnectPoints {

    /*
        1584.Min-Cost-to-Connect-All-Points
        解法1：Kruskal
        本题依然是MST的基本题，但是时间要求非常严格。对于Krusal算法而言，需要将所有的边进行排序。时间复杂度ElogE。本题中，任意两点之间都可能有路径，所以复杂度是N^2logN，对于不开o2优化的C++而言极有可能TLE。

        降低TLE的方法有两个：

        使用priority_queue而不是直接排序整个边长数组。原因是pq不会将所有装入其中的元素马上排序（建堆过程是o(E)），而是只有访问顶堆元素的时候才将最小值推出来。因为我们只需要找到N条边，数量级比N^2的总边数要少的多，所以可以省去不需要的排序过程。
        避免使用vector（时空非常坑爹），改用定长数组array<int,N>这个数据结构。

        解法2：Prim
        Prim算法通常的复杂度也是ElogV，本题就是o(N^2logN)。

        Prim的基本思想是，MST从节点0开始生长。MST里面只有节点0时，从所有节点0出发的边里面挑一个最短的，这时MST里就有两个点。第二步是从这两个点所出发的所有边里面挑一个最短的，如果对应的第三点是已经访问过的，那就换下一个最短边，
        直到能确定第三个点。依次继续，直至确定N个点，则MST构建完成。

        同理，priority_queue的模板类尽量避免用vector。

        解法3：Prim, o(N^2)
        在特殊情况下，Prim有o(N^2)的实现，那就是可以用邻接表来表示任意的边。这样对于稠密图而言，Prim的这种实现在时间上会有优势。

        本题是个完全图，任意两点之间都有边，所以是可以有o(N^2)的实现，具体方法是：我们在构建MST的过程中收入了一个新点k，此时收录的点集是{q}. 查看所有未被收入的点pi到k点的距离，用来更新di，其中di就是pi到距离点集{q}最小的长度。
        这样我们就可以在{di}找到最小的那个，对应的点就是下一次要收入的新点k'. 因此这样的算法就不要使用priority_queue.
    */
    int Father[1000];
    
    int findFather(int x)
    {
        if (Father[x]!=x)
            Father[x] = findFather(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y) Father[y] = x;
        else Father[x] = y;
    }    

    int minCostConnectPoints_kruskal_mst_disjoint(vector<vector<int>>& points) 
    {
        int n = points.size();
        for (int i=0; i<n; i++)
            Father[i] = i;
        
        priority_queue<array<int,3>, vector<array<int,3>>, std::greater<array<int,3>>>edges;
        for (int i=0; i<n; i++)
            for (int j=i+1; j<n; j++)
            {
                int dis = abs(points[i][0]-points[j][0])+abs(points[i][1]-points[j][1]);
                edges.push({dis, i, j});
            }
               
        int result = 0;
        int count = 1;
        while (count < n)
        {       
            auto edge = edges.top();
            edges.pop();
            int a = edge[1];
            int b = edge[2];
            int dis = edge[0];
            if (findFather(a)!=findFather(b))
            {
                Union(a,b);
                count++;
                result+=dis;
                if (count==n) break;
            }
        }
        
        return result;        
    }

public:
    

    int minCostConnectPoints(vector<vector<int>>& points) 
    {
        int n = points.size();
        int visited[1000];
        
        vector<vector<std::pair<int,int>>>edges(n);
        for (int i=0; i<n; i++)
            for (int j=i+1; j<n; j++)
            {
                int dis = abs(points[i][0]-points[j][0])+abs(points[i][1]-points[j][1]);
                edges[i].push_back({dis, j});
                edges[j].push_back({dis, i});
            }
        
        priority_queue<std::pair<int,int>, vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq(edges[0].begin(), edges[0].end());
        visited[0] = 1;
        int result = 0;
                
        for (int k=0; k<n-1; k++)
        {
            while (!pq.empty() && visited[pq.top().second]==1)
                pq.pop();            
            int next = pq.top().second;
            visited[next] = 1;
            result += pq.top().first;
            pq.pop();
            
            for (auto edge: edges[next])
                pq.push(edge);
        }                
        
        return result;
    }

public:


    int minCostConnectPoints(vector<vector<int>>& points) 
    {
        int visited[1000];
        int n = points.size();
        if (n==1) return 0;
        
        vector<int>minDist(n,INT_MAX);  // the min dist from point i to the current MST
        minDist[0] = 0;
                
        int ret = 0;
        int cur = 0;
        for (int k=0; k<n; k++)
        {
            int next;
            int gmin = INT_MAX;
            for (int j = 0; j < n; ++j) {
                if (visited[j]==0 && minDist[j] <= gmin) 
                {
                    gmin = minDist[j];
                    next = j;
                }
            }
            visited[next] = 1;
            ret += gmin;
            
            for (int j = 0; j < n; ++j) 
                if (visited[j] == 0) 
                {
                    int new_dist = abs(points[j][0] - points[next][0]) + abs(points[j][1] - points[next][1]);
                    minDist[j] = std::min(minDist[j], new_dist);
                }
        }                
        return ret;        
    }

public:

    // becuase it is a full graphic
    int doit_mst_best(vector<vector<int>>& points) {

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

        std::function<int(vector<int>&, int)> find = [&](vector<int> &ds, int i) {
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
    int doit_prim_best(vector<vector<int>>& ps) {
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


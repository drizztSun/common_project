/*
 
 1595. Minimum Cost to Connect Two Groups of Points
 
 
 You are given two groups of points where the first group has size1 points, the second group has size2 points, and size1 >= size2.

 The cost of the connection between any two points are given in an size1 x size2 matrix where cost[i][j] is the cost of connecting point i of the first group and point j of the second group.
 The groups are connected if each point in both groups is connected to one or more points in the opposite group.
 In other words, each point in the first group must be connected to at least one point in the second group, and each point in the second group must be connected to at least one point in the first group.

 Return the minimum cost it takes to connect the two groups.

  

 Example 1:


 Input: cost = [[15, 96], [36, 2]]
 Output: 17
 Explanation: The optimal way of connecting the groups is:
 1--A
 2--B
 This results in a total cost of 17.
 Example 2:


 Input: cost = [[1, 3, 5], [4, 1, 1], [1, 5, 3]]
 Output: 4
 Explanation: The optimal way of connecting the groups is:
 1--A
 2--B
 2--C
 3--A
 This results in a total cost of 4.
 Note that there are multiple points connected to point 2 in the first group and point A in the second group.
 This does not matter as there is no limit to the number of points that can be connected. We only care about the minimum total cost.
 
 Example 3:

 Input: cost = [[2, 5, 1], [3, 4, 7], [8, 1, 2], [6, 2, 4], [3, 8, 8]]
 Output: 10
  

 Constraints:

 size1 == cost.length
 size2 == cost[i].length
 1 <= size1, size2 <= 12
 size1 >= size2
 0 <= cost[i][j] <= 100

 
 */
#include <vector>
#include <numeric>
#include <queue>


using std::vector;
using std::queue;


class MinimumCostToConnectTwoGroupsOfPoints {
    
public:
    
    // O(m* 3^n * n)
    int doit_(vector<vector<int>>& cost) {
        
        int dp[12][1<<12];
        // dp[i][state]: Cosiding the first i points on the ldft, adn the visited points on the right cooresponds to state, the the minimum cost
        // 1. dp[i][state] => dp[i-1][state - subset] + i visites a subset of state.
        // 2. dp[i][state] => dp[i-1][state] + i visites an already visited point w/ minimum edge
        // https://github.com/wisdompeak/LeetCode/tree/master/Dynamic_Programming/1595.Minimum-Cost-to-Connect-Two-Groups-of-Points
        
        int m = cost.size();
        int n = cost[0].size();

        dp[0][0] = INT_MAX/2;
        for (int state = 1; state < (1<<n); state++)
        {
            int sum = 0;
            for (int j=0; j<n; j++)
            {
                if (((state>>j)&1)==1)
                    sum += cost[0][j];
            }
            dp[0][state] = sum;
        }

        for (int i=1; i<m; i++)
        {
            dp[i][0] = INT_MAX/2;
            for (int state = 1; state < (1<<n); state++)
            {
                dp[i][state] = INT_MAX/2;
                for (int subset=state; subset>0; subset=(subset-1)&state)
                {
                    int sum = 0;
                    for (int j=0; j<n; j++)
                    {
                        if (((subset>>j)&1)==1)
                            sum += cost[i][j];
                    }
                    dp[i][state] = std::min(dp[i][state], dp[i-1][state-subset]+sum);
                }

                int minPath = INT_MAX;
                for (int j=0; j<n; j++)
                    minPath = std::min(minPath, cost[i][j]);
                dp[i][state] = std::min(dp[i][state], dp[i-1][state] + minPath);
            }
        }

        return dp[m-1][(1<<n)-1];
    }
};


// 当最小带权边覆盖问题的权值均为非负数时，可以转换成最大带权匹配问题
// https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/discuss/855686/C%2B%2B-4ms-beats-100-Bipartite-graph-maximum-weight-matching
template <typename T>
struct hungarian {
    // km
    int n;
    vector<int> matchx;
    vector<int> matchy;
    vector<int> pre;
    vector<bool> visx;
    vector<bool> visy;
    vector<T> lx;
    vector<T> ly;
    vector<vector<T>> g;
    vector<T> slack;
    T inf;
    T res;
    queue<int> q;
    int org_n;
    int org_m;

    hungarian(int _n, int _m) {
        org_n = _n;
        org_m = _m;
        n = std::max(_n, _m);
        inf = std::numeric_limits<T>::max();
        res = 0;
        g = vector<vector<T>>(n, vector<T>(n));
        matchx = vector<int>(n, -1);
        matchy = vector<int>(n, -1);
        pre = vector<int>(n);
        visx = vector<bool>(n);
        visy = vector<bool>(n);
        lx = vector<T>(n, -inf);
        ly = vector<T>(n);
        slack = vector<T>(n);
    }

    void addEdge(int u, int v, int w) {
        g[u][v] = std::max(w, 0);
    }

    bool check(int v) {
        visy[v] = true;
        if (matchy[v] != -1) {
            q.push(matchy[v]);
            visx[matchy[v]] = true;
            return false;
        }
        while (v != -1) {
            matchy[v] = pre[v];
            std::swap(v, matchx[pre[v]]);
        }
        return true;
    }

    void bfs(int i) {
        while (!q.empty()) {
            q.pop();
        }
        q.push(i);
        visx[i] = true;
        while (true) {
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; v++) {
                    if (!visy[v]) {
                        T delta = lx[u] + ly[v] - g[u][v];
                        if (slack[v] >= delta) {
                            pre[v] = u;
                            if (delta) {
                                slack[v] = delta;
                            } else if (check(v)) {
                                return;
                            }
                        }
                    }
                }
            }
            T a = inf;
            for (int j = 0; j < n; j++) {
                if (!visy[j]) {
                    a = std::min(a, slack[j]);
                }
            }
            for (int j = 0; j < n; j++) {
                if (visx[j]) { // S
                    lx[j] -= a;
                }
                if (visy[j]) { // T
                    ly[j] += a;
                } else { // T'
                    slack[j] -= a;
                }
            }
            for (int j = 0; j < n; j++) {
                if (!visy[j] && slack[j] == 0 && check(j)) {
                    return;
                }
            }
        }
    }

    int solve() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                lx[i] = std::max(lx[i], g[i][j]);
            }
        }

        for (int i = 0; i < n; i++) {
            fill(slack.begin(), slack.end(), inf);
            fill(visx.begin(), visx.end(), false);
            fill(visy.begin(), visy.end(), false);
            bfs(i);
        }

        for (int i = 0; i < n; i++) {
            if (g[i][matchx[i]] > 0) {
                res += g[i][matchx[i]];
            } else {
                matchx[i] = -1;
            }
        }
        return res;
    }
};

class MinimumCostToConnectTwoGroupsOfPointsI {
public:
    /**
    // 带memo的搜索写法
    int dp[13][4096] = {}; // 1 << 12 = 4096
    int connectTwoGroups(vector<vector<int>>& cost) {
        vector<int> min_sz2(cost[0].size(), INT_MAX);
        for (int j = 0; j < min_sz2.size(); j++) {
            for (int i = 0; i < cost.size(); i++) {
                min_sz2[j] = min(min_sz2[j], cost[i][j]);
            }
        }
        return dfs(cost, min_sz2, 0, 0);
    }
    int dfs(vector<vector<int>> &cost, vector<int> &min_sz2, int i, int mask) {
        if (dp[i][mask]) return dp[i][mask];
        int res = i >= cost.size() ? 0 : INT_MAX;
        if (i >= cost.size()) {
            for (auto j = 0; j < cost[0].size(); j++) {
                if ((mask & (1 << j)) == 0) {
                    res += min_sz2[j];
                }
            }
        } else {
            for (auto j = 0; j < cost[0].size(); j++) {
                res = min(res, cost[i][j] + dfs(cost, min_sz2, i + 1, mask | (1 << j)));
            }
        }
        dp[i][mask] = res;
        return res;
    }
    */
    
    // KM算法改造。
    int connectTwoGroups(vector<vector<int>>& cost) {
        int n = cost.size(), m = cost[0].size();
        hungarian<int> hg(n, m);  // 这里是用到了template的例子。表明hungarian中的T是int
        vector<int> lmin(n, INT_MAX), rmin(m, INT_MAX);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                lmin[i] = std::min(lmin[i], cost[i][j]);
                rmin[j] = std::min(rmin[j], cost[i][j]);
            }
        }
        int ans = accumulate(lmin.begin(), lmin.end(), 0) + accumulate(rmin.begin(), rmin.end(), 0);
        // 按照最greedy的算法对于每个i取最小的对于每个j取最小的。那么显然有冗余。
        // 我们求出最大冗余，减掉就是最小的cost
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                hg.addEdge(i, j, lmin[i] + rmin[j] - cost[i][j]);
            }
        }
        return ans - hg.solve();
    }
};

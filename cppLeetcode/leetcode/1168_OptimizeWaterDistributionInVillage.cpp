/*
1168. Optimize Water Distribution in a Village

There are n houses in a village. We want to supply water for all the houses by building wells and laying pipes.

For each house i, we can either build a well inside it directly with cost wells[i - 1] (note the -1 due to 0-indexing), or pipe in water from another well to it. 
The costs to lay pipes between houses are given by the array pipes, where each pipes[j] = [house1j, house2j, costj] represents the cost to connect house1j and house2j together using a pipe. Connections are bidirectional.

Return the minimum total cost to supply water to all houses.

 

Example 1:



Input: n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
Output: 3
Explanation: 
The image shows the costs of connecting houses using pipes.
The best strategy is to build a well in the first house with cost 1 and connect the other houses to it with cost 2 so the total cost is 3.
 

Constraints:

1 <= n <= 104
wells.length == n
0 <= wells[i] <= 105
1 <= pipes.length <= 104
pipes[j].length == 3
1 <= house1j, house2j <= n
0 <= costj <= 105
house1j != house2j

*/

#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class WaterDistributionInVillage {

    /*
        1168.Optimize-Water-Distribution-in-a-Village
        此题的解法非常巧妙。你增加一个隐藏的0号节点，把每个节点自建井的费用wells[i]想象成连接[0,i]的边的费用。这样，这道题就变成了求最少的费用将所有的节点（包括隐藏的0号）连接起来。
        这就是最基本的最小生成树问题（MST），和1135.Connecting-Cities-With-Minimum-Cost一模一样。
    */


    static bool cmp(vector<int>&a, vector<int>&b)
    {
        return a[2]<b[2];
    }
    unordered_map<int,int>Father;

public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) 
    {
        for (int i=0; i<wells.size(); i++)
        {
            pipes.push_back({i+1,0,wells[i]});
        }
        
        std::sort(pipes.begin(),pipes.end(),cmp);
        
        for (int i=0; i<=wells.size(); i++)
            Father[i] = i;

        int ret  = 0;
        
        for (auto p:pipes)
        {
            int a = p[0];
            int b = p[1];
            if (FindSet(a)!=FindSet(b))
            {
                Union(a,b);
                ret+=p[2];
            }
        }
        
        return ret;
    }
    
    int FindSet(int x)
    {
        if (Father[x]!=x)
            Father[x] = FindSet(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y)
            Father[y] = x;
        else
            Father[x] = y;
    }

public:

    int doit_disjoint(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        
        vector<int> parents(n+1);
        std::iota(begin(parents), end(parents), 0);
        
        auto find = [&](int a) {
            while (parents[a] != a) {
                parents[a] = parents[parents[a]];
                a = parents[a];
            }
            return a;
        };
        
        auto merge = [&](int a, int b) {
          
            int pa = find(a), pb = find(b);
            
            if (pa < pb)
                parents[pb] = pa;
            else
                parents[pa] = pb;
        };
        
        for (int i = 0; i < wells.size(); i++) {
            pipes.push_back({0, i+1, wells[i]});
        }
        
        std::sort(begin(pipes), end(pipes), [](const auto& a, const auto& b) { return a[2] < b[2]; });
        
        int ans = 0;
        for (const auto& c: pipes) {
            
            if (find(c[0]) != find(c[1])) {
                merge(c[0], c[1]);
                
                ans += c[2];
            }
        }
        
        return ans;
    }
};
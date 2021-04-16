/*

1462. Course Schedule IV

There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have direct prerequisites, for example, to take course 0 you have first to take course 1, which is expressed as a pair: [1,0]

Given the total number of courses n, a list of direct prerequisite pairs and a list of queries pairs.

You should answer for each queries[i] whether the course queries[i][0] is a prerequisite of the course queries[i][1] or not.

Return a list of boolean, the answers to the given queries.

Please note that if course a is a prerequisite of course b and course b is a prerequisite of course c, then, course a is a prerequisite of course c.

 

Example 1:


Input: n = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
Output: [false,true]
Explanation: course 0 is not a prerequisite of course 1 but the opposite is true.
Example 2:

Input: n = 2, prerequisites = [], queries = [[1,0],[0,1]]
Output: [false,false]
Explanation: There are no prerequisites and each course is independent.
Example 3:


Input: n = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
Output: [true,true]
Example 4:

Input: n = 3, prerequisites = [[1,0],[2,0]], queries = [[0,1],[2,0]]
Output: [false,true]
Example 5:

Input: n = 5, prerequisites = [[0,1],[1,2],[2,3],[3,4]], queries = [[0,4],[4,0],[1,3],[3,0]]
Output: [true,false,true,false]
 

Constraints:

2 <= n <= 100
0 <= prerequisite.length <= (n * (n - 1) / 2)
0 <= prerequisite[i][0], prerequisite[i][1] < n
prerequisite[i][0] != prerequisite[i][1]
The prerequisites graph has no cycles.
The prerequisites graph has no repeated edges.
1 <= queries.length <= 10^4
queries[i][0] != queries[i][1]

*/

#include <functional>
#include <vector>
#include <unordered_set>
#include <queue>

using std::queue;
using std::unordered_set;
using std::vector;

class CheckIfPrerequisite {

    /*
        1462.Course-Schedule-IV
        考虑到n<=100，即使将每个节点的所有先修课程都记录下来，时间复杂度o(n^2)也是可以接受的。
        于是本题就是常规的拓扑排序算法，需要特别处理的是：每次从cur拓展到下一个next节点时，要把cur的所有先修课程都复制一遍给next。至于数据结构，显然用集合来实现去重和查询query都很方便。
    */
    vector<bool> checkIfPrerequisite_topsort(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) 
    {
        vector<unordered_set<int>>next(n);
        vector<int>inDegree(n,0);
        vector<unordered_set<int>>preSet(n);
        
        for (auto edge: prerequisites)
        {
            next[edge[0]].insert(edge[1]);
            inDegree[edge[1]] += 1;
        }
        
        queue<int>q;
        for (int i=0; i<n; i++)
        {
            preSet[i].insert(i);
            if (inDegree[i]==0)
                q.push(i);
        }            
        
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            
            for (int next: next[cur])
            {
                for (auto x: preSet[cur])
                    preSet[next].insert(x);
                
                inDegree[next] -= 1;
                if (inDegree[next]==0)
                    q.push(next);
            }
        }
        
        vector<bool>rets;
        for (auto query: queries)
        {
            rets.push_back(preSet[query[1]].find(query[0])!=preSet[query[1]].end());
        }
        return rets;
    }

public:

    vector<bool> doit_dfs(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {

        vector<int> degrees(n, 0);
        vector<unordered_set<int>> graph(n);
        vector<vector<bool>> related(n, vector<bool>(n, false));    
        for (auto& pre: prerequisites) {
            graph[pre[0]].insert(pre[1]);
            related[pre[0]][pre[1]] = true;
            degrees[pre[1]]++;
        }

        queue<int> qu;
        for (int i = 0; i < n; i++)
            if (degrees[i] == 0) qu.push(i);

        while (!qu.empty()) {

            int cur = qu.front(); qu.pop();

            for (auto child: graph[cur]) {    
                degrees[child]--;

                for (int i = 0; i < n; i++)
                    if (i != cur && related[i][cur]) related[i][child] = true;
                
                if (degrees[child] == 0)
                    qu.push(child);
            }
        }        

        vector<bool> ans;
        for (auto& c: queries) 
            ans.push_back(related[c[0]][c[1]]);

        return ans;
    }
    
    vector<bool> doit_dfs(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {

        vector<unordered_set<int>> graph(n);
        vector<vector<int>> related(n, vector<int>(n, -1));
        for (auto& pre: prerequisites) {
            graph[pre[0]].insert(pre[1]);
            related[pre[0]][pre[1]] = 1;
        }
        
        std::function<bool(int, int)> dfs = [&](int cur, int end) {
            if (cur == end) return true;

            if (related[cur][end] != -1) return related[cur][end] == 1;

            bool done = false;
            for (auto c: graph[cur]) {

                if (dfs(c, end)) {
                    done = true;
                    break;
                }
            }
            related[cur][end] = done;

            return done;
        };

        vector<bool> ans(queries.size());
        for (int i = 0; i < queries.size(); i++)
            ans[i] = dfs(queries[i][0], queries[i][1]);

        return ans;
    }
};
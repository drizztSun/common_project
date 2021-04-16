/*
210. Course Schedule II

There are a total of n courses you have to take labelled from 0 to n - 1.

Some courses may have prerequisites, for example, if prerequisites[i] = [ai, bi] this means you must take the course bi before the course ai.

Given the total number of courses numCourses and a list of the prerequisite pairs, return the ordering of courses you should take to finish all courses.

If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]
 

Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
All the pairs [ai, bi] are distinct.

*/

#include <vector>
#include <queue>
#include <unordered_map>

using std::unordered_map;
using std::queue;
using std::vector;


class CourseScheduleII {

    /*
            210.Course-Schedule-II
    拓扑排序最基本的应用。显然我们应该优先访问那些入度为零的节点（也就是不需要先修课程的课程）。删去第一批最外围的节点后，再继续访问此时入度更新为零的节点。依次类推。使用的数据结构就是BFS，

    如何确定第二批最外围的节点呢？一个拓扑排序最基本的技巧就是：对于每一个当前最外围的节点x，我们都找它的后继y。删除x意味着y的入度减少了一。当y的入度刚好被删到为零的时候，就说明它就能成为新的外围节点。
    */
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
    {
        int n = numCourses;
        unordered_map<int,vector<int>>nextCourses(n);
        unordered_map<int,int>degree(n);
        
        for (auto edge: prerequisites)
        {
            int a = edge[0];
            int b = edge[1];
            nextCourses[b].push_back(a);
            degree[a]+=1;
        }
        
        queue<int>q;
        for (int i=0; i<n; i++)
            if (degree[i]==0)
                q.push(i);
        
        vector<int>rets;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            rets.push_back(cur);
            
            for (auto next: nextCourses[cur])
            {
                degree[next] -= 1;
                if (degree[next]==0)
                    q.push(next);
            }
        }
        
        if (rets.size()!=n)
            return {};
        else
            return rets;
    }

public:
    
    vector<int> doit_topsort_bfs(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> degrees(numCourses, 0);
        vector<vector<int>> next(numCourses);

        for (auto& e: prerequisites) {
            next[e[1]].push_back(e[0]);
            degrees[e[0]]++;
        }
        
        queue<int> qu;
        int total = 0;
        for (int i = 0; i < numCourses; i++) {
            if (degrees[i] == 0) {
                qu.push(i);
                total++;
            }
        }
        
        vector<int> ans;

        while (!qu.empty()) {
            
            int cur = qu.front(); qu.pop();

            ans.push_back(cur);
            
            for (auto child: next[cur]) {
                
                degrees[child]--;
                if (degrees[child] == 0) {
                    total++;
                    qu.push(child);
                }
            }
        }
        return total == numCourses ? ans : vector<int>{};
    }
};
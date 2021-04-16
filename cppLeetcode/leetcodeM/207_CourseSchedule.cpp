/*
207. Course Schedule

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
 

Constraints:

1 <= numCourses <= 105
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.

*/
#include <vector>
#include <queue>

using std::queue;
using std::vector;

class CourseSchedule {

    /*
        207.Course-Schedule
        我们将依赖关系表述成一条有向边。课程a需要先修课程b，那么就有一条边从a指向b。本题的本质就是在一个有向图中判断是否有环。如果有环，意味着循环依赖，就需要返回false。

        在图论中，判断有向图是否有环，一般有DFS和BFS两种做法。

        解法1： DFS
        DFS的基本思想是从任意一个未访问过的节点开始做DFS的遍历。如果在某条支路的遍历过程中（没有遍历到出度为0的端点）遇到了任何在这条支路中已经访问过的节点，那么就能判断成环。

        注意，“遇到了任何在这条支路中已经访问过的节点”和“遇到了任何已经访问过的节点”，是不同的概念。比如：

        1 -> 2 -> 3 -> 4 
                ^
        5 -> 6 -> 7 -> 8 
                ^____|
        我们从1开始依次访问1->2->3->4，然后遍历结束。然后从5开始依次访问5->6->7->3的时候，3已经被访问过了。但是这不会误判成环。因为3并不是在当前未完待续的支路中。我们再看5->6->7->8->7这条线路，此时的7已经被这条支路访问过，并且这条支路并没有走到底，这个时候就应该判断成环。

        所以我们需要标记两种visited[i]。如果节点i已经在其他遍历到底的支路中被访问过了，标记1.如果节点i是在当前未完待续的支路中被访问过了，标记2.只有在遍历过程中遇到了2，才算是判断有环。那么是什么时候标记1什么时候标记2呢？方法是：在某条DFS的路径上，第一次遇到的节点i的时候标记2.在回溯返回节点i的时候标记1（因为能成功返回的话，说明后续的节点都没有环，都是死胡同，此后任何任何入度指向这个节点i的话，我们都不用担心后续的遍历会遇到环）.

        核心的dfs代码很简单：

            bool dfs(int cur)
            {
                visited[cur] = 2;
                for (int next: graph[cur])
                {
                    if (visited[next]==1) continue;
                    if (visited[next]==2) return false;
                    if (dfs(next)==false)  return false;
                }
                visited[cur] = 1;
                return true;
            }
        解法2： BFS
        BFS的算法思想是拓扑排序：从外围往核心进发。我们每次在图中找入度为0的点，然后移除。如果最后没有入度为0的点，但是图中仍有点存在，那么这些剩下来的点一定是交错成环的。
    */
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
    {
        vector<vector<int>>next(numCourses);
        vector<int>InDegree(numCourses);
        for (auto p: prerequisites)
        {
            next[p[0]].push_back(p[1]);
            InDegree[p[1]]++;
        }
        queue<int>q;
        int count = 0;
        for (int i=0; i<numCourses; i++)
        {
            if (InDegree[i]==0) 
            {
                q.push(i);
                count++;
            }
        }
                    
        while (!q.empty())
        {
            int curCourse = q.front();
            q.pop();
            for (auto nextCourse: next[curCourse])
            {
                InDegree[nextCourse]--;
                if (InDegree[nextCourse]==0)
                {
                    q.push(nextCourse);
                    count++;
                }                    
            }
        }        
        
        return count==numCourses;        
    }


    vector<int>visited;
    vector<vector<int>>next;
public:
    bool canFinish_dfs(int numCourses, vector<vector<int>>& prerequisites) 
    {
        visited.resize(numCourses, 0);
        next.resize(numCourses);        
        for (auto p: prerequisites)        
            next[p[0]].push_back(p[1]);
        
        for (int i=0; i<numCourses; i++)
        {            
            if (dfs(i)==false) return false;            
        }
        
        return true;
    }
    
    bool dfs(int cur)
    {
        if (visited[cur]==1) return true;

        visited[cur] = 2;
        for (int next: next[cur])
        {
            if (visited[next]==1) continue;
            if (visited[next]==2) return false;
            if (dfs(next)==false)  return false;
        }
        visited[cur] = 1;
        return true;
    }

public:
    
    bool doit_topsort(int numCourses, vector<vector<int>>& prerequisites) {

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
        
        while (!qu.empty()) {
            
            int cur = qu.front(); qu.pop();
            
            for (auto child: next[cur]) {
                
                degrees[child]--;
                if (degrees[child] == 0) {
                    total++;
                    qu.push(child);
                }
            }
        }
        return total == numCourses;
    }
};
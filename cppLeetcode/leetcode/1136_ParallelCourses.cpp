/*
 1136. Parallel Courses
 
 There are N courses, labelled from 1 to N.

 We are given relations[i] = [X, Y], representing a prerequisite relationship between course X and course Y: course X has to be studied before course Y.

 In one semester you can study any number of courses as long as you have studied all the prerequisites for the course you are studying.

 Return the minimum number of semesters needed to study all courses.  If there is no way to study all the courses, return -1.

  

 Example 1:



 Input: N = 3, relations = [[1,3],[2,3]]
 Output: 2
 Explanation:
 In the first semester, courses 1 and 2 are studied. In the second semester, course 3 is studied.
 Example 2:



 Input: N = 3, relations = [[1,2],[2,3],[3,1]]
 Output: -1
 Explanation:
 No course can be studied because they depend on each other.
  

 Note:

 1 <= N <= 5000
 1 <= relations.length <= 5000
 relations[i][0] != relations[i][1]
 There are no repeated relations in the input.

 
 
 */
#include <stdio.h>
#include <vector>
#include <queue>

using std::queue;
using std::vector;


class ParallelCourses {

    /*
                1136.Parallel-Courses
        常规的拓扑排序。在BFS的过程中，将层级遍历的“层数”记录下来，就是答案。
    */
    int minimumSemesters(int N, vector<vector<int>>& relations) 
    {
        vector<vector<int>>next(N+1);
        vector<int>inDegree(N+1,0);
        for (auto x:relations)
        {
            next[x[0]].push_back(x[1]);
            inDegree[x[1]] += 1;
        }
        
        queue<int>q;        
        int count = 0;
        for (int i=1; i<=N; i++)
        {
            if (inDegree[i]==0)
            {
                count += 1;
                q.push(i);
            }                
        }
                
        int step = 0;
        
        while (!q.empty())
        {
            int len = q.size();
            step += 1;
            while (len--)
            {
                int cur = q.front();
                q.pop();
                for (auto next: next[cur])
                {
                    inDegree[next] -= 1;
                    if (inDegree[next]==0)
                    {
                        q.push(next);
                        count++;
                    }                        
                }
            }                        
        }
        
        if (count!=N)
            return -1;
        else
            return step;
    }
    
public:
    
    int doit_bfs_topsort(int N, vector<vector<int>>&& relations) {
        
        
        vector<vector<int>> graph(N+1);
        vector<int> degree(N+1);
        
        for (const auto& c : relations) {
            graph[c[0]].push_back(c[1]);
            degree[c[1]]++;
        }
        
        queue<int> buf;
        for (int i = 1; i <= N; i++) {
            if (degree[i] == 0)
                buf.push(i);
        }
        
        int ans = 0;
        N -= buf.size();
        while (!buf.empty()) {
            
            ans++;
            int size = buf.size();
            
            while (size > 0) {
                
                int p = buf.front();
                buf.pop();
                
                for (auto& n : graph[p]) {
                    degree[n]--;
                    if (degree[n] ==0) {
                        buf.push(n);
                        N--;
                    }
                }
                size--;
            }
        }
            
        return N == 0 ? ans : -1;
    }
};
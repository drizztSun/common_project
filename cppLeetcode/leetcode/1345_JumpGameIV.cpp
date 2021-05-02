/*
1345. Jump Game IV


Given an array of integers arr, you are initially positioned at the first index of the array.

In one step you can jump from index i to index:

i + 1 where: i + 1 < arr.length.
i - 1 where: i - 1 >= 0.
j where: arr[i] == arr[j] and i != j.
Return the minimum number of steps to reach the last index of the array.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
Example 2:

Input: arr = [7]
Output: 0
Explanation: Start index is the last index. You don't need to jump.
Example 3:

Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: You can jump directly from index 0 to index 7 which is last index of the array.
Example 4:

Input: arr = [6,1,9]
Output: 2
Example 5:

Input: arr = [11,22,7,7,7,7,7,7,7,22,13]
Output: 3
 

Constraints:

1 <= arr.length <= 5 * 10^4
-10^8 <= arr[i] <= 10^8


*/
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using std::queue;
using std::unordered_set;
using std::unordered_map;
using std::vector;


class JumpGameIV {

    /*
        1345.Jump-Game-IV
        一道基本的BFS题。每增加一步，可以延展到一些新的位置，包括+1, -1, 以及所有arr数值相同的位置。

        本题需要注意的是：如果你扩展了所有数值是val的点，那么请立即将val从Hash表里删除。否则一旦遇到再次一个值为val的点，你会依然继续考察所有值为val的点，即使你使用了visited做了去重标记，但这些不必要的考察还是很低效的。
        极端的例子就是[1,1,1,1,1,1,1....]。你的第一步，就会在队列中收录N个1. 此后每弹出一个1，都会再试图考察所有值为1的点。
    */
    int minJumps_bfs(vector<int>& arr) 
    {
        int n = arr.size();
        if (n==1) return 0;
        unordered_map<int,vector<int>>Map;
        for (int i=0; i<n; i++)
            Map[arr[i]].push_back(i);
        
        vector<int>visited(n,0);
        queue<int>q;
        q.push(0);
        visited[0] = 1;
        
        int step = 0;
        while (!q.empty())
        {
            int len = q.size();
            while (len--)
            {
                int cur = q.front();
                q.pop();
                
                if (cur+1 < n && visited[cur+1]==0)
                {
                    q.push(cur+1);
                    visited[cur+1] = 1;
                }
                if (cur-1 >= 0 && visited[cur-1]==0)
                {
                    q.push(cur-1);
                    visited[cur-1] = 1;
                }
                for (int next: Map[arr[cur]])
                {
                    if (visited[next] == 0)
                    {
                        q.push(next);
                        visited[next] = 1;
                    }
                } 
                Map.erase(arr[cur]);
                
            }
            step += 1;
            if (visited[n-1] == 1)
                return step;
        }
        
        return -1;
    }

public:
    

    int minJumps_bfs_bidirection(vector<int>& arr)  {

        if (arr.size() <= 1) return 0;
        
        int n = arr.size();
        if (arr[0] == arr[n-1]) return 1;
        
        unordered_map<int, vector<int>> posMap;
        
        for (int i = 0; i < n; i++)
            posMap[arr[i]].push_back(i);

        int step = 0;
        unordered_set<int> begin, end;
        begin.insert(0), end.insert(n - 1);
        unordered_set<int> *pb = &begin, *pe = &end;
        vector<bool> visited(n, false);
        visited[0] = visited[n - 1] = true;

        while (!begin.empty() && !end.empty()) {
            
            unordered_set<int> tmp;

            for (auto cur : *pb) {

                for (auto child : posMap[arr[cur]]) {

                    if (pe->count(child)) return step+1;

                    if (visited[child]) continue;

                    visited[child] = true;
                    tmp.insert(child);
                }
                
                for (auto child: vector<int>{cur-1, cur+1}) {
                    
                    if (child < 0 | child >= n) continue;
                    if (pe->count(child)) return step+1;
                    if (visited[child]) continue;

                    visited[child] = true;
                    tmp.insert(child);
                }
            }

            std::swap(*pb, tmp);

            if (pb->size() > pe->size()) {
                std::swap(pb, pe);
            }

            step++;
        }

        return -1;
    }
};
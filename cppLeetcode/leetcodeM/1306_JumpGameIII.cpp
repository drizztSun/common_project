/*
1306. Jump Game III

Given an array of non-negative integers arr, you are initially positioned at start index of the array. 
When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach to any index with value 0.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation: 
All possible ways to reach at index 3 with value 0 are: 
index 5 -> index 4 -> index 1 -> index 3 
index 5 -> index 6 -> index 4 -> index 1 -> index 3 
Example 2:

Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true 
Explanation: 
One possible way to reach at index 3 with value 0 is: 
index 0 -> index 4 -> index 1 -> index 3
Example 3:

Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.
 

Constraints:

1 <= arr.length <= 5 * 10^4
0 <= arr[i] < arr.length
0 <= start < arr.length

*/

#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <stack>

using std::queue;
using std::stack;
using std::vector;

class CanReach {

    /*
        1306.Jump-Game-III
        基本的搜索，DFS或者BFS均可。在DFS的过程中，任何已经访问过的节点都不需要再访问。因为它们要么是已经证实是通往dead end；要么是当前的探索路径中已经访问过的节点，再访问的话就成环会变死循环。
    */
    int visited[50001];

    bool canReach(vector<int>& arr, int start) 
    {
        if (start<0 || start>=arr.size()) 
            return false;
        if (arr[start]==0)
            return true;
        if (visited[start]==1) 
            return false;

        visited[start] = 1;
        
        if (canReach(arr, start-arr[start]))
            return true;
        
        if (canReach(arr, start+arr[start]))
            return true;

        return false;
    }


public:
    
    bool doit_dfs(vector<int>& arr, int start) {
        
        int N = arr.size();
        
        vector<int> visited(N, 0);
        
        std::function<bool(int index)> dfs = [&](int index) {
         
            if (arr[index] == 0) return true;
            
            if (visited[index] == 1) return false;
            
            visited[index] = 1;
            
            if (index + arr[index] < N && dfs(index+arr[index])) return true;
            
            if (index - arr[index] >= 0 && dfs(index-arr[index])) return true;
            
            return false;
        };
        
        return dfs(start);
    }

    bool doit_bfs(vector<int>& arr, int start) {
        
        int N = arr.size();
        vector<int> visited(N, 0);
        stack<int> src;
        src.push(start);
        visited[start] = 1;
        
        while (!src.empty()) {
            
            int cur = src.top();
            src.pop();
            
            if (arr[cur] == 0) return true;
            
            if (cur+arr[cur] < N && visited[cur+arr[cur]] != 1) {
                src.push(cur+arr[cur]);
                visited[cur+arr[cur]] = 1;
            }
                
            
            if (cur-arr[cur] >= 0 && visited[cur-arr[cur]] != 1) {
                src.push(cur-arr[cur]);
                visited[cur-arr[cur]] = 1;
            }
        }
        
        return false;
    }

    bool doit_bfs(vector<int>& arr, int start) {

        int N = arr.size();
        vector<int> visited(N, 0);
        queue<int> src;
        src.push(start);
        visited[start] = 1;
        
        while (!src.empty()) {
            
            int cur = src.front();
            src.pop();
            
            if (arr[cur] == 0) return true;
            
            if (cur+arr[cur] < N && visited[cur+arr[cur]] != 1) {
                src.push(cur+arr[cur]);
                visited[cur+arr[cur]] = 1;
            }
                
            
            if (cur-arr[cur] >= 0 && visited[cur-arr[cur]] != 1) {
                src.push(cur-arr[cur]);
                visited[cur-arr[cur]] = 1;
            }
        }
        
        return false;
    }
};

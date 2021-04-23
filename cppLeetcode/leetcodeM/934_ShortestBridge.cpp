/*
934. Shortest Bridge


In a given 2D binary array A, there are two islands.  (An island is a 4-directionally connected group of 1s not connected to any other 1s.)

Now, we may change 0s to 1s so as to connect the two islands together to form 1 island.

Return the smallest number of 0s that must be flipped.  (It is guaranteed that the answer is at least 1.)

 

Example 1:

Input: A = [[0,1],[1,0]]
Output: 1
Example 2:

Input: A = [[0,1,0],[0,0,0],[0,0,1]]
Output: 2
Example 3:

Input: A = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1
 

Constraints:

2 <= A.length == A[0].length <= 100
A[i][j] == 0 or A[i][j] == 1

*/

#include <queue>
#include <vector>
#include <functional>

using std::queue;
using std::vector;


class ShortestBridge {

public:

    /*
        Approach 1: Find and Grow
        
        Intuition

        Conceptually, our method is very straightforward: find both islands, then for one of the islands, keep "growing" it by 1 until we touch the second island.

        We can use a depth-first search to find the islands, and a breadth-first search to "grow" one of them. This leads to a verbose but correct solution.

        Algorithm

        To find both islands, look for a square with a 1 we haven't visited, and dfs to get the component of that region. Do this twice. After, we have two components source and target.

        To find the shortest bridge, do a BFS from the nodes source. When we reach any node in target, we will have found the shortest distance.

        Please see the code for more implementation details.
    */

    int doit_bfs_dfs(vector<vector<int>>& A) {
        
        int r, c, row, col, level=0, N;
        int R = A.size(), C = A[0].size();
        
        vector<std::pair<int, int> > dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
        queue<std::pair<int, int> > src;
        vector<vector<bool>> visited(R, vector<bool>(C, false));

        // find boundary 0 of island found
        std::function<void(vector<vector<int>>&, int, int)> dfs = [&](vector<vector<int>>& A, int r, int c) {
            if(r<0 || r>=R || c<0 || c>=C || visited[r][c]) return;
            
            visited[r][c] = true;
            
            if(A[r][c]==0) {
                src.push({r, c});
                return;
            }
            
            for(auto dir: dirs) {
                dfs(A, r+dir.first, c+dir.second);
            }
        };

        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                // we found an island, now mark this island and it's boundary
                if(A[r][c]) {
                    dfs(A, r, c);
                    r = R;
                    c = C;
                }
            }
        }
        
        // from all 0 on boundary of island start moving towards other island
        while(src.size()) {
            level++;
            N = src.size();
            while(N--) {
                auto cell = src.front();
                src.pop();
                r = cell.first;
                c = cell.second;
                for(auto dir: dirs) {
                    row = r+dir.first;
                    col = c+dir.second;
                    if(row<0 || row>=R || col<0 || col>=C) {
                        continue;
                    }
                    if(!visited[row][col]) {
                        visited[row][col] = true;
                        if(A[row][col]) {
                            return level;
                        }
                        src.push({row, col});
                    }
                }
                
            }
        }
        
        return -1;
    }
};
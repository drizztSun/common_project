/*
1102. Path With Maximum Minimum Value

Given a matrix of integers A with R rows and C columns, find the maximum score of a path starting at [0,0] and ending at [R-1,C-1].

The score of a path is the minimum value in that path.  For example, the value of the path 8 →  4 →  5 →  9 is 4.

A path moves some number of times from one visited cell to any neighbouring unvisited cell in one of the 4 cardinal directions (north, east, west, south).

 

Example 1:



Input: [[5,4,5],[1,2,6],[7,4,6]]
Output: 4
Explanation: 
The path with the maximum score is highlighted in yellow. 
Example 2:



Input: [[2,2,1,2,2,2],[1,2,2,2,1,2]]
Output: 2
Example 3:



Input: [[3,4,6,3,4],[0,2,1,1,7],[8,8,3,2,7],[3,2,4,9,8],[4,1,2,0,0],[4,6,5,4,3]]
Output: 3
 

Note:

1 <= R, C <= 100
0 <= A[i][j] <= 10^9

*/
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;
using std::queue;

class MaxMinPath {

    /*
        1102.Path-With-Maximum-Minimum-Value
        此题是二分法的非常精彩的应用．

        我们想，如果这个maximum score是ｘ，那么意味着存在一条路径，里面不能有任何小于ｘ的格子．因此，如果给定ｘ，我们尝试用ＢＦＳ的方法从左上角走到右下角．
        如果能抵达，说明至少存在一条成功的路，他们所有的元素都不会小于ｘ，而且ｘ还可能有提升的空间．相反，如果不能走到，说明从左上到右下被一些列小于ｘ的各自给阻断了，因此我们对于maximum score的预期必须下调，至少得小于ｘ．

        所以二分的策略就非常清楚了：

                while (left<right)
                {
                    int mid = right-(right-left)/2;                        
                    if (isOK(A,mid))
                        left = mid;
                    else
                        right = mid-1;
                }
        因为我们在收缩范围的时候，永远是将可行解放在闭区间[left,right]内，不可行解排除在闭区间外.所以当left和right收敛的时候，一定是一个可行解，直接返回left即可．
    
    */
    int maximumMinimumPath(vector<vector<int>>& A) 
    {
        int left = INT_MAX;
        int right = INT_MIN;
        int M = A.size();
        int N = A[0].size();
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
            {
                left = std::min(left,A[i][j]);
                right = std::max(right,A[i][j]);
            }
        
        while (left<right)
        {
            int mid = right-(right-left)/2;
                        
            if (check(A,mid))
                left = mid;
            else
                right = mid-1;
        }
        return left;        
    }
    
    bool check(vector<vector<int>> A, int K)
    {
        if (A[0][0]<K) return false;
        auto dir = vector<std::pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1}});
        
        int M = A.size();
        int N = A[0].size();
        
        queue<std::pair<int,int>>q;
        q.push({0,0});
        A[0][0] = -1;
        
        while (q.size()>0)
        {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
            
            for (int k=0; k<4; k++)
            {
                int i = x+dir[k].first;
                int j = y+dir[k].second;

                if (i<0||i>=M||j<0||j>=N)continue;
                
                if (A[i][j]==-1)continue;
                
                if (A[i][j]<K) continue;
                
                if (i==M-1 && j==N-1) return true;
                A[i][j]=-1;
                
                q.push({i,j});                
            }
        }
                
        return false;
    
    }

    /*
        1. Setup a "val" map that stores the current maximum path value of each cell in A.
        2. Use triplet {row, column, minimum value of the path} to keep track of the end of a specific path and push into a maximum heap "pq". That is, we always pick the path which have maximum value and try approaching to the bottum right corner.
        3. Pop the top of "pq" and try extend the end of this path to next cell vertically and horinzotally.
        4. During extension, if the updated value of a new path end is greater than the value stored at the same position in "val", 
            which means there's a new path that has greater value would pass through this cell, and we should try routing from this new path to bottum right corner to get the maximum value .
    */
    int maximumMinimumPath(vector<vector<int>>& A) {

        auto mycomp = [](auto& a, auto& b) {
            return b[2] > a[2];
        };

        vector<vector<int>> val(A.size(), vector<int>(A[0].size(), INT_MIN));
        priority_queue<vector<int>, vector<vector<int>>, mycomp> pq;
        vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        val[0][0] = A[0][0];
        pq.push({0,0,A[0][0]});
        
        while (pq.size()) {
            
            for (int i = 0; i < dir.size(); i++) {
                
                int r = pq.top()[0] + dir[i][0];
                int c = pq.top()[1] + dir[i][1];

                if (r >= 0 && r < A.size() && c >=0 && c < A[0].size()) {
                    int mini = std::min(pq.top()[2], A[r][c]);

                    if (r == A.size() - 1 && c == A[0].size() - 1) return mini; 
                    
                    if (mini > val[r][c]) {
                        val[r][c] = mini;
                        pq.push({r, c, mini});
                    }
                }
            }
            pq.pop();
        }
        return val.back().back();
    }

public:
    
    int doit_bfs_heap_dijstra(vector<vector<int>>& A) {

        int maxscore = A[0][0];
        int n = A.size(), m = A[0].size();

        int dx[4] = {1,0,-1,0};
        int dy[4] = {0,1,0,-1};

        priority_queue<std::pair<int, std::pair<int,int>>> heap;
        heap.push({A[0][0], {0, 0}});
        A[0][0]=-1;

        while(!heap.empty()) {

            // maxheap always popup current maximum val path
            auto p = heap.top();
            heap.pop();
            
            int value = p.first;
            int i = p.second.first;
            int j = p.second.second;
            
            // Each time, we popup the current maximum path, like[10, 9, 8]. if new point 4 on 10 path is 4, then it will be [9, 8, 4] 
            // Then 9 is the next path can move forward. Any one will smaller score will be the final value on th path.
            maxscore = std::min(maxscore, value);

            if(i == n-1 && j == m-1) break;

            for(int k = 0; k < 4; k++)
            {
                int x = i + dx[k], y = j + dy[k];

                if( x >= 0 && x < n && y >= 0 && y < m && A[x][y] >= 0)
                {
                    // Why using current value?
                    // heap.push({std::min(A[x][y], value), {x, y}}); ok also.
                    heap.push({A[x][y], {x,y}});
                    A[x][y]=-1;
                }
            }
        }

        return maxscore;
    }


    int doit_binary_search(vector<vector<int>>& A) {

        int low = 1, high = INT_MAX / 2;

        auto reach = [](vector<vector<int>> A, int level) {

            if (level < A[0][0]) return false;
            
            int M = A.size(), N = A[0].size();
            int direct[5] = {-1, 0, 1, 0, -1};
            
            queue<std::pair<int, std::pair<int, int>>> qu;
            qu.push({A[0][0], {0, 0}});

            while (!qu.empty()) {

                auto it = qu.front();

                if (it.first <= level) {

                    int val = it.first;
                    int x = it.second.first, y = it.second.second;

                    for (int k = 0; k < 4; k++) {

                        int x1 = x + direct[k], y1 = y + direct[k+1];

                        if (x1 < 0 || x1 > M || y1 < 0 || y1 > N || A[x1][y1] == -1) continue;

                        
                        int nv = std::min(val, A[x1][y1]);

                        A[x1][y1] = -1;

                        if (x1 == M-1 && y1 == N-1) return true;

                        qu.push({nv, {x1, y1}});

                    }
                }
                qu.pop();
            }

            return false;
        };

        while (low < high) {

            int mid = high - (high - low) / 2;

            if (!reach(A, mid))
                high = mid - 1;
            else
                low = mid;
        }

        return low;
    }
};
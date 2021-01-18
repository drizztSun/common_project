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

class Solution {
public:
    int maximumMinimumPath(vector<vector<int>>& A) {

        int maxscore=A[0][0];

        int n = A.size();
        int m = A[0].size();

        int dx[4] = {1,0,-1,0};
        int dy[4] = {0,1,0,-1};

        priority_queue<std::pair<int, std::pair<int,int>>> heap;
        heap.push(std::make_pair(A[0][0], std::make_pair(0,0)));
        A[0][0]=-1;

        while(!heap.empty()) {

            auto p = heap.top();
            heap.pop();
            
            int value = p.first;
            int i = p.second.first;
            int j = p.second.second;
            
            maxscore = std::min(maxscore,value);

            if(i == n-1 && j == m-1) break;

            for(int k = 0; k < 4; k++)
            {
                int x = i + dx[k], y = j + dy[k];

                if( x >= 0 && x < n && y >= 0 && y < m && A[x][y] >= 0)
                {
                    heap.push(std::make_pair(A[x][y], std::make_pair(x,y)));
                    A[x][y]=-1;
                }
            }
        }
        return maxscore;
    }
};
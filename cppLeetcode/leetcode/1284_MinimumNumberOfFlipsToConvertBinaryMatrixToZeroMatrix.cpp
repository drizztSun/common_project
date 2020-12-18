/*
 
 1284. Minimum Number of Flips to Convert Binary Matrix to Zero Matrix
 
 
 
 Given a m x n binary matrix mat. In one step, you can choose one cell and flip it and all the four neighbours of it if they exist (Flip is changing 1 to 0 and 0 to 1). A pair of cells are called neighboors if they share one edge.

 Return the minimum number of steps required to convert mat to a zero matrix or -1 if you cannot.

 Binary matrix is a matrix with all cells equal to 0 or 1 only.

 Zero matrix is a matrix with all cells equal to 0.

  

 Example 1:

 0 0      1 0       0 1     0 0
 0 1  ->  1 0  ->   1 1 ->  0 0
 
 

 Input: mat = [[0,0],[0,1]]
 Output: 3
 Explanation: One possible solution is to flip (1, 0) then (0, 1) and finally (1, 1) as shown.
 Example 2:

 Input: mat = [[0]]
 Output: 0
 Explanation: Given matrix is a zero matrix. We don't need to change it.
 Example 3:

 Input: mat = [[1,1,1],[1,0,1],[0,0,0]]
 Output: 6
 Example 4:

 Input: mat = [[1,0,0],[1,0,0]]
 Output: -1
 Explanation: Given matrix can't be a zero matrix
 
 Constraints:

 m == mat.length
 n == mat[0].length
 1 <= m <= 3
 1 <= n <= 3
 mat[i][j] is 0 or 1.
 
 */
#include <vector>
#include <deque>

using std::deque;
using std::vector;


class MinFlips {
    

public:
    
    /*
        STATE COMPRESSION
    */
    int doit_bfs(vector<vector<int>>&& mat) {
        
        
        auto m = mat.size(), n = mat[0].size();
        const vector<int> dirs{0, 1, 0, -1, 0, 0}; // tricky way to define 4 directions and i, j itself.
        size_t start = 0;
        
        // suppress the 0/1 matrix to a bit status
        for (auto i = 0; i < m; i++) {
            for (auto j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    start ^= 1 << (i * n + j);
                }
            }
        }
        
        auto flip = [&](size_t status, int i, int j) {
            for (int s = 0; s < 5; s++) {
                const int tx = i + dirs[s];
                const int ty = j + dirs[s+1];
                if (tx >=0 && tx< m && ty >= 0 && ty < n)
                    status ^= 1 << (tx * n + ty);
            }
            return status;
        };
        
        vector<bool> seen(1 << (n*m), false);
        seen[start] = true;
        deque<size_t> que;
        que.push_back(start);
        int steps = 0;
        
        while (que.size()) {
            
            for (auto i = que.size(); i > 0; i--) {
                auto c = que.front();
                que.pop_front();
                if (c == 0)
                    return steps;
                
                for (auto i = 0; i < m; i++) {
                    for (auto j = 0; j < n; j++) {
                        auto t = flip(c, i, j);
                        if (seen[t])
                            continue;
                        
                        seen[t] = true;
                        que.push_back(t);
                    }
                }
            }
            steps++;
        }
        
        return -1;
    }
};

void test_1284_minimum_number_of_flip() {
    
    MinFlips().doit_bfs(vector<vector<int>>{{0, 0}, {0, 1}});
    
    MinFlips().doit_bfs(vector<vector<int>>{{1, 1, 1}, {1, 0, 1}, {0, 0, 0}});
}

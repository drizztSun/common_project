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
#include <bitset>

using std::bitset;
using std::deque;
using std::vector;


class MinFlips {

    /*
        1284.Minimum-Number-of-Flips-to-Convert-Binary-Matrix-to-Zero-Matrix
        首先我们应该有这样一个认识，每个元素最多只需要flip一次，flip两次及以上都是没有意义的操作。再考虑到矩阵的维度非常小（不超过3x3），因此即使穷举每个元素是否flip，
        最多只有2^9种不同的可能性。对于每种可能性，我们最多再花o(4mn)的时间来验证是否能实现矩阵全部翻零。因此这种暴力的方法的时间复杂度是可以接受的。

        如果还想优化一点的话，可以用Gosper's hack，按照“1-bit的个数”从小到大地枚举状态。一旦发现可以实现矩阵翻零，即可输出答案。
    */
    int m,n;

    int doit_(vector<vector<int>>& mat) 
    {
        m = mat.size();
        n = mat[0].size();
        int ret = INT_MAX;

        for (int state=0; state<(1<<(m*n)); state++)
        {
            if (check(mat, state))
                ret = std::min(ret, (int)bitset<9>(state).count());
        }
        if (ret==INT_MAX)
            return -1;
        else
            return ret;
    }

    bool check(vector<vector<int>>& mat, int state)
    {
        auto temp = mat;
        auto dir = vector<pair<int,int>>({{0,1},{0,-1},{1,0},{-1,0},{0,0}});        

        for (int s=0; s<(m*n); s++)
        {
            int t = state%2;            
            state/=2;
            if (t==0) continue;

            int i = s/n;
            int j = s%n;

            for (int k=0; k<5; k++)
            {
                int x = i+dir[k].first;
                int y = j+dir[k].second;
                if (x<0||x>=m||y<0||y>=n) continue;
                temp[x][y] = 1-temp[x][y];
            }            
        }

        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
                if (temp[i][j]!=0) return false;
        return true;
    }

    int m,n;
public:
    int minFlips(vector<vector<int>>& mat) 
    {
        m = mat.size();
        n = mat[0].size();
        if (check(mat,0)) return 0;

        for (int k=1; k<=m*n; k++)
        {
            int state = (1 << k) - 1;                                  
            while (state < (1 << (m*n)))
            {
                if (check(mat, state))
                    return k;

                int c = state & - state;
                int r = state + c;
                state = (((r ^ state) >> 2) / c) | r;
            }
        }
        return -1;
    }

    bool check(vector<vector<int>>& mat, int state)
    {
        auto temp = mat;
        vector<std::pair<int,int>> dir({{0,1},{0,-1},{1,0},{-1,0},{0,0}});        

        for (int s=0; s<(m*n); s++)
        {
            int t = state%2;            
            state/=2;
            if (t==0) continue;

            int i = s/n;
            int j = s%n;

            for (int k=0; k<5; k++)
            {
                int x = i+dir[k].first;
                int y = j+dir[k].second;
                if (x<0||x>=m||y<0||y>=n) continue;
                temp[x][y] = 1-temp[x][y];
            }            
        }

        for (int i=0; i<m; i++)
            for (int j=0; j<n; j++)
                if (temp[i][j]!=0) return false;
        return true;
    }

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
                const int tx = i + dirs[s];ß
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
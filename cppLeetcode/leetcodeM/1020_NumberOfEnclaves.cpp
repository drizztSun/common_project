/*
 
 
 # 1020. Number of Enclaves

 # Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)

 # A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.

 # Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.


 # Example 1:

 # Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
 # Output: 3
 # Explanation:
 # There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.

 # Example 2:

 # Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
 # Output: 0
 # Explanation:
 # All 1s are either on the boundary or can reach the boundary.


 # Note:

 # 1 <= A.length <= 500
 # 1 <= A[i].length <= 500
 # 0 <= A[i][j] <= 1
 # All rows have the same size.
 
 
 */

#include <vector>
using std::vector;

#include <unordered_set>
using std::unordered_set;

class NumEnclaves {
    

    
public:
    
    int doit(vector<vector<int>>&& A) {
        
        int cnt = 0;
        size_t row = A.size(), col = A[0].size();
        vector<std::pair<int, int>> edges;
        
        for (size_t i = 0; i < row; i++) {
            for (size_t j = 0; j < col; j++) {
                if (A[i][j] == 1) {
                    cnt++;
                    if (i == 0 || i == row - 1 || j == 0 || j == col - 1)
                        edges.push_back({i, j});
                }
            }
        }
        
        while (!edges.empty()) {
            
            auto c = edges.back();
            edges.pop_back();
            if (A[c.first][c.second] == 2)
                continue;
            
            A[c.first][c.second] = 2;
            cnt--;
            for (auto n : vector<vector<int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
                int x = c.first + n[0], y = c.second + n[1];
                if (x >= 0 && x < row && y >= 0 && y < col && A[x][y] == 1) {
                    edges.push_back({x, y});
                }
            }
        }
    
        return cnt;
    }
    
public:
    
    int doit1(vector<vector<int>>&& A) {
        
        int row = A.size(), col = A[0].size();
        
        auto search = [row, col, &A](int r, int c){
            if (A[r][c] == 0)
                return;
            
            vector<std::pair<int, int>> buf;
            buf.push_back({r, c});
            
            while (!buf.empty()) {
                auto c = buf.back();
                buf.pop_back();
                A[c.first][c.second] = 0;
                
                for (auto n : vector<vector<int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
                    int x = c.first + n[0], y = c.second + n[1];
                    if (x >= 0 && x < row && y >= 0 && y < col && A[x][y] == 1) {
                        buf.push_back({x, y});
                    }
                }
            }
        };
        
        
        for (size_t i = 0; i < row; i++) {
            search(i, 0);
            search(i, col-1);
        }
            
        for (size_t j = 0; j < col; j++) {
            search(0, j);
            search(row-1, j);
        }
     
        int cnt = 0;
        for (size_t i = 0; i < row; i++) {
            for (size_t j =0; j < col; j++) {
                cnt += A[i][j];
            }
        }
        return cnt;
    }
    
public:
    
        // *** It is weird, but true, that normal function call far much more efficient than lambda func
        // if we use dfs to replace lambda in 'doit', we can see it.
         void dfs(vector<vector<int>>& A, int i, int j)
         {
             if (i < 0 || j < 0 || i >= A.size() || j >= A[0].size() || A[i][j] == 0)
             {
                 return;
             }
             
             A[i][j] = 0;
             dfs(A, i + 1, j);
             dfs(A, i - 1, j);
             dfs(A, i, j + 1);
             dfs(A, i, j - 1);
         }

         int doit2(vector<vector<int>>& A)
         {
             int count = 0;
             
             for (int i = 0; i < A.size(); i++)
             {
                 for (int j = 0; j < A[0].size(); j++)
                 {
                     if (i == 0 || j == 0 || i == A.size() - 1 || j == A[0].size() - 1)
                     {
                         dfs(A, i, j);
                     }
                 }
             }
             
             for (int i = 0; i < A.size(); i++)
             {
                 for (int j = 0; j < A[0].size(); j++)
                 {
                     if (A[i][j])
                     {
                         count++;
                     }
                 }
             }
             
             return count;
         }
    
public:
    
    
    
    class UnionFindSet {
    public:
        UnionFindSet(int n) {
            pa   = vector<int>(n + 1, 0);
            rank = vector<int>(n + 1, 0);
            
            for(int i = 0; i < n + 1; ++i) {
                pa[i] = i;
            }
        }
        
        int Find(int x) {
            return pa[x] = (pa[x] == x ? x : Find(pa[x]));
        }
        
        void Union(int a, int b) {
            int fa = Find(a), fb = Find(b);
            //if(fa == fb) return false;
            if(rank[fa] > rank[fb])
                pa[fb] = fa;
            else if(rank[fa] < rank[fb])
                pa[fb] = fa;
            else {
                pa[fb] = fa;
                rank[fa] += 1;
            }
            //return true;
        }
    private:
        vector<int> pa;
        vector<int> rank;
    };

    
    
    int d[5] = {0, -1, 0, 1, 0};
    
    int getIndex(int i, int j, int n) {
        return i * n + j + 1;
    }
    
    bool onBound(int i, int j, int m, int n) {
        return i == 0 || j == 0 || i == m - 1 || j == n - 1;
    }
    
    bool inBound(int i, int j, int m, int n) {
        return i >= 0 && i < m && j >=0 && j < n;
    }
    
    int numEnclaves(vector<vector<int>>& A) {
        
        if(A.empty()) return 0;
        const int m = A.size(), n = A[0].size();
        UnionFindSet s(n * m);
        
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(A[i][j] == 0)
                    continue;
                
                int index = getIndex(i, j, n);
                if(onBound(i, j, m, n))
                    s.Union(index, 0);
                
                for(int k = 0; k < 4; ++k) {
                    int x = i + d[k], y = j + d[k + 1];
                    if(!inBound(x, y, m, n) || A[x][y] == 0)
                        continue;
                    s.Union(index, getIndex(x, y, n));
                }
            }
            
        }
        
        int res = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(A[i][j] == 1 && s.Find(getIndex(i, j, n)) != s.Find(0))
                    ++res;
            }
        }
        return res;
    }
};



void test_1020_number_of_enclave() {
    
    /*
    auto res1 = NumEnclaves().doit(vector<vector<int>> {
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    });
    
    auto res2 = NumEnclaves().doit(vector<vector<int>> {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    });
    */
    auto res3 = NumEnclaves().doit(vector<vector<int>> {
        {0,0,0,1,1,1,0,1,0,0},
        {1,1,0,0,0,1,0,1,1,1},
        {0,0,0,1,1,1,0,1,0,0},
        {0,1,1,0,0,0,1,0,1,0},
        {0,1,1,1,1,1,0,0,1,0},
        {0,0,1,0,1,1,1,1,0,1},
        {0,1,1,0,0,0,1,1,1,1},
        {0,0,1,0,0,1,0,1,0,1},
        {1,0,1,0,1,1,0,0,0,0},
        {0,0,0,0,1,1,0,0,0,1}
    });
    
    return;
}

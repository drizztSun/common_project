/*
 
 1559. Detect Cycles in 2D Grid
 
 
 Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.

 A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell,
 you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.

 Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1)
 is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.

 Return true if any cycle of the same value exists in grid, otherwise, return false.



 Example 1:



 Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
 Output: true
 Explanation: There are two valid cycles shown in different colors in the image below:

 Example 2:



 Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
 Output: true
 Explanation: There is only one valid cycle highlighted in the image below:

 Example 3:



 Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
 Output: false


 Constraints:

 m == grid.length
 n == grid[i].length
 1 <= m <= 500
 1 <= n <= 500
 grid consists only of lowercase English letters.

 */
#include <stdio.h>
#include <stdlib.h>

#include <vector>


using std::vector;


class DetectContainsCycle {

    
public:
    
    bool search(const vector<vector<char>>& matrix, int i, int j, int lastx, int lasty, vector<vector<bool>>& seen) {

        auto m = matrix.size(), n = matrix[0].size();
        int delta[4][2]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        bool ans = false;
        seen[i][j] = true;

        for (auto k = 0; k < 4; k++) {
            int x = i + delta[k][0], y = j + delta[k][1];
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] == matrix[i][j] && !(lastx == x && lasty == y)) {

                if (seen[x][y])
                    return true;
                
                ans |= search(matrix, x, y, i, j, seen);
                if (ans)
                    break;
            }
        }

        return ans;
    }
    
    bool doit_dfs(vector<vector<char>>& matrix) {
        
        auto m = matrix.size(), n = matrix[0].size();
        vector<vector<bool>> seen(m, vector<bool>(n, false));

        for (auto i = 0; i < m; i++) {

            for (auto j = 0; j < n; j++) {

                if (!seen[i][j] && search(matrix, i, j, -1, -1, seen))
                   return true;
            }
        }

       return false;
    }

    
public:
    
    auto Find(int i, vector<int>& parent) {
        while (parent[i] != i) {
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return parent[i];
    };
    
    auto Union(int a, int b, vector<int>& parent) {
        int pa = Find(a, parent);
        int pb = Find(b, parent);
        
        bool check = false;
        if (pa == pb)
            check = true;
            
        parent[pa] = pb;
        return check;
    };
    
    
    bool doit_disjoint(vector<vector<char>>&& grid) {

        auto n = grid.size(), m = grid[0].size();
        vector<int> parent(n*m + 1, 0);
        for (auto i = 0; i < n*m+1; i++)
            parent[i] = i;
        
        for (auto i = 0; i < n; i++) {
            
            for (auto j = 0; j < m; j++) {
                
                auto val = i * m + j;
                
                if (j != m-1 && grid[i][j+1] == grid[i][j] && Union(val, val+1, parent))
                    return true;
                
                if (i != n-1 && grid[i+1][j] == grid[i][j] && Union(val, val+m, parent))
                    return true;
            }
        }
        return false;
    }
    
public:
    
    int check = 0;
    bool doit_disjoint_1(vector<vector<char>>& grid) {
        
        check =0;
        auto n = grid.size(), m = grid[0].size() ;
        int parent[n*m+1] ;
        
        //iota(parent,parent+(n*m+1),0) ;
        
        for(int i=0;i<n;i++){
            
            if(check)break ;
            
            for(int j=0;j<m;j++){
                
                if( check )break ;
                
                int val = (i*m) + j ;
                
                if(j != m-1 && grid[i][j+1] == grid[i][j])
                    union_it(val , val+1,parent) ;
                
                if(i != n-1 && grid[i+1][j]==grid[i][j])
                    union_it(val,val+m,parent) ;
                
            }
            
        }
        return check ;
    }

    void union_it(int a,int b,int parent[]){
        
        int p1 = find_parent(parent,a) ;
        int p2 = find_parent(parent,b) ;
        
        if (p1 == p2) {
            check = 1;
            return ;
        }
        
        parent[p2] = p1 ;
        return ;
    }

    int find_parent(int parent[],int v){
        if(parent[v] == v)
            return v ;
        
        return parent[v] = find_parent(parent,parent[v]);
    }
    
};


void test_1559_detect_cycle() {
    
    DetectContainsCycle().doit_disjoint(vector<vector<char>>{{'a', 'b', 'b'}, {'b', 'z', 'b'}, {'b', 'b', 'a'}});
}

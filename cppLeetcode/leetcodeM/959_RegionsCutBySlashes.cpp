/*
 
 959. Regions Cut By Slashes
 
 In a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \, or blank space.
 These characters divide the square into contiguous regions.

 (Note that backslash characters are escaped, so a \ is represented as "\\".)

 Return the number of regions.

  
 # Example 1:

 # Input:
 # [
 #   " /",
 #   "/ "
 # ]
 # Output: 2
 # Explanation: The 2x2 grid is as follows:

 # Example 2:

 # Input:
 # [
 #   " /",
 #   "  "
 # ]
 # Output: 1
 # Explanation: The 2x2 grid is as follows:

 # Example 3:

 # Input:
 # [
 #   "\\/",
 #   "/\\"
 # ]

 # Output: 4
 # Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
 # The 2x2 grid is as follows:

 # Example 4:

 # Input:
 # [
 #   "/\\",
 #   "\\/"
 # ]

 # Output: 5
 # Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\, and "\\/" refers to \/.)
 # The 2x2 grid is as follows:

 # Example 5:

 # Input:
 # [
 #   "//",
 #   "/ "
 # ]
 # Output: 3
 # Explanation: The 2x2 grid is as follows:


 # Note:

 # 1 <= grid.length == grid[0].length <= 30
 # grid[i][j] is either '/', '\', or ' '.
 
 
 */

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <algorithm>

class DSU {
    
    vector<int> parent_;
public:
    
    DSU(int n) : parent_(n) {
        for (int i = 0; i < n; i++) {
            parent_[i] = i;
        }
    }
    
    int Find(int a) {
        while (parent_[a] != a) {
            parent_[a] = parent_[parent_[a]];
            a = parent_[a];
        }
        
        return a;
    }

    void Union(int a, int b) {
        int pa = Find(a), pb = Find(b);
        parent_[pa] = pb;
    }
};

class RegionsBySlashes {
    
public:
    
    int doit(vector<string>&& grid) {
        
        int N = grid.size();
        DSU dsu(4 * N * N);
        
        for (int i = 0; i <N; i++) {
            
            for (int j = 0; j < N; j++) {
                
                int root = 4 * (i * N + j);
                
                // {north: 0, south: 3, west: 1, east: 2}
                if (grid[i][j] == '\\') {
                    dsu.Union(root + 0, root + 2);
                    dsu.Union(root + 1, root + 3);
                    
                } else if (grid[i][j] == '/') {
                    
                    dsu.Union(root + 0, root + 1);
                    dsu.Union(root + 2, root + 3);
                } else {
                    dsu.Union(root + 0, root + 1);
                    dsu.Union(root + 1, root + 2);
                    dsu.Union(root + 2, root + 3);
                }
                
                if (i > 0)
                    dsu.Union(root + 0, root - 4 * N + 3);
                
                if (i < N - 1)
                    dsu.Union(root + 3, root + 4 * N + 0);
                
                if (j >= 1)
                    dsu.Union(root + 1, root - 4 + 2);
                
                if (j < N - 1)
                    dsu.Union(root + 2, root + 4 + 1);
            }
        }
        
        int res = 0;
        for (int i = 0; i < 4 * N * N; i++) {
            res += dsu.Find(i) == i ? 1 : 0;
        }
            
        return res;
    }
};

class RegionsBySlashesI {
public:
    vector<int> fa;
    
    int getfa(int x) {
        if (x == fa[x])
            return x;
        fa[x] = getfa(fa[x]);
        return fa[x];
    }
    
    void unify(int x, int y) {
        int a = getfa(x), b = getfa(y);
        if (a != b)
            fa[a] = b;
    }
    
    int regionsBySlashes(vector<string>& g) {
        int n = g.size();
        int tot = n * n * 2;
        
        fa = vector<int>(tot+1);
        for (int i = 1; i <= tot; ++i)
            fa[i] = i;
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int a = (i*n + j) * 2 + 1;
                int b = a + 1;
                
                if (g[i][j] == ' ')
                    unify(a, b);
                
                if (j < n-1) {
                    int x = g[i][j] == '/' ? b : a;
                    int y = g[i][j+1] == '/' ? b+1 : b+2;
                    unify(x, y);
                }
                
                if (i < n-1)
                    unify(b, a + 2*n);
            }
        
        int ans = 0;
        for (int i = 1; i <= tot; ++i)
            if (fa[i] == i)
                ++ans;
        
        return ans;
    }
};

void test_959_region_cut_by_slashes() {
    
    auto res1 = RegionsBySlashes().doit(vector<string>{" /", "/ "});
    
    auto res2 = RegionsBySlashes().doit(vector<string>{" /", "  "});
    
    auto res3 = RegionsBySlashes().doit(vector<string>{"\\/", "/\\"});
    
    auto res4 = RegionsBySlashes().doit(vector<string>{"/\\", "\\/"});
    
    auto res5 = RegionsBySlashes().doit(vector<string>{"//", "/ "});
    
    return;
    
}

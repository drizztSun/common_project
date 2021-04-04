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
#include <string>
#include <algorithm>

using std::vector;
using std::string;



class RegionsBySlashes {

    /*
        959.Regions-Cut-By-Slashes
        解法1：将每个格子倍增9倍
        此题非常巧妙。我们将每一个格子都再细化为3*3的像素，那么“\”和“/”就各自变成了一条斜对角线。于是我们再看这个细化之后的3N*3N的矩阵，就会惊奇地发现，题目中定义的Regions此时都变成是像素联通的了。
        这就转换成了number of islands的题，用DFS,BFS或者Union Find都可以很轻松地解决。

        解法2：Union Find
        有一个更高效和巧妙的解法，不需要拆分格子。我们不考虑每个cell，而是考虑每个网点（即经纬线的相交点）。这样的网点有(N+1)*(N+1)个。最初始的时候我们将所有外围的点聚为一类，即满足i==0||i==N||j==0||j==N的网点聚在一起。其他内陆的网点都自成一类。

        然后我们逐个考察cell。如果这个cell包含了斜线，那么会将两个网点a和b相连接（左上和右下，或者左下和右上）。此时如果a和b两点属于不同的类，那么意味着这个斜线不会生成一个新的封闭空间！但是记得我们需要紧接着将a和b聚类在一起。
        相反，如果a和b两点已经聚属于同一类，那么意味着这个斜线一定会生成一个新的封闭空间！这个时候计数器就要加1.

        我们考察完每个cell和所包含斜线的影响，最终返回计数器的值即可。注意，计数器的初始值应该是1.
    */
    int regionsBySlashes(vector<string>& grid) 
    {
        int N = grid.size();
        auto Grid = vector<vector<int>>(N*3,vector<int>(N*3,0));
        for (int i=0; i<N; i++)
            for (int j=0; j<N; j++)
            {
                if (grid[i][j]=='/')
                {
                    Grid[i*3+0][j*3+2] = 1;
                    Grid[i*3+1][j*3+1] = 1;
                    Grid[i*3+2][j*3+0] = 1;
                }
                else if (grid[i][j]=='\\')
                {
                    Grid[i*3+0][j*3+0] = 1;
                    Grid[i*3+1][j*3+1] = 1;
                    Grid[i*3+2][j*3+2] = 1;
                }
            }

        int count = 0;
        for (int i=0; i<N*3; i++)
            for (int j=0; j<N*3; j++)
            {
                if (Grid[i][j]==0)
                {
                    DFS(Grid,i,j);
                    count++;
                }
            }
        return count;
    }
    
    void DFS(vector<vector<int>>&Grid, int x, int y)
    {
        int M = Grid.size();
        if (x<0||x>=M||y<0||y>=M) return;
        if (Grid[x][y]!=0) return;
        Grid[x][y]=2;
        
        vector<pair<int,int>>dir({{0,1},{0,-1},{1,0},{-1,0}});
        for (int k=0; k<4; k++)
        {
            int i = x+dir[k].first;
            int j = y+dir[k].second;
            DFS(Grid,i,j);
        }
    }

    
public:
    
    vector<int>Father;

    int regionsBySlashes(vector<string>& grid) 
    {
        int N = grid.size();
        Father.resize((N+1)*(N+1));
        for (int i=0; i<=N; i++)
            for (int j=0; j<=N; j++)
            {
                int id = i*(N+1)+j;
                Father[id] = id;
                if (i==0 || i==N || j==0 || j==N)
                    Father[id] = 0;
            }

        int count = 1;
        for (int i=0; i<N; i++)
            for (int j=0; j<N; j++)
            {
                int a,b;
                if (grid[i][j]==' ')
                    continue;

                if (grid[i][j]=='/')
                {
                    a = i*(N+1)+j+1;
                    b = (i+1)*(N+1)+j;
                }
                else if (grid[i][j]=='\\')
                {
                    a = i*(N+1)+j;
                    b = (i+1)*(N+1)+j+1; 
                }

                if (FindFather(a)!=FindFather(b))
                    Union(a,b);
                else
                    count++;
            }
        return count;
    }

    int FindFather(int x)
    {
        if (Father[x]!=x)
            Father[x] = FindFather(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y)
            Father[y] = x;
        else
            Father[x] = y;
    }    



public:    


    /*
        Approach 1: Union-Find
        Intuition

        To find the number of components in a graph, we can use either depth-first search or union find. The main difficulty with this problem is in specifying the graph.

        One "brute force" way to specify the graph is to associate each grid square with 4 nodes (north, south, west, and east), representing 4 triangles inside the square if it were to have both slashes. Then, we can connect all 4 nodes if the grid square is " ", and connect two pairs if the grid square is "/" or "". Finally, we can connect all neighboring nodes (for example, the east node of the square at grid[0][0] connects with the west node of the square at grid[0][1]).

        This is the most straightforward approach, but there are other approaches that use less nodes to represent the underlying information.

        Algorithm

        Create 4*N*N nodes, one for each grid square, and connect them as described above. After, we use a union find structure to find the number of connected components.

        We will skip the explanation of how a DSU structure is implemented. Please refer to https://leetcode.com/problems/redundant-connection/solution/ for a tutorial on DSU.


        Complexity Analysis

        Time Complexity: O(N * N * \alpha(N))O(N∗N∗α(N)), where NN is the length of the grid, and \alphaα is the Inverse-Ackermann function (if we were to use union-find by rank.)

        Space Complexity: O(N * N)O(N∗N).
    */
    struct DSU {

        vector<int> parent_;
        
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

public:
    
    int doit_disjoint(vector<string>&& grid) {
        
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
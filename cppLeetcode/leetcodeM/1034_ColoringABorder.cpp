/*
 
 # 1034. Coloring A Border

 # Given a 2-dimensional grid of integers, each value in the grid represents the color of the grid square at that location.

 # Two squares belong to the same connected component if and only if they have the same color and are next to each other in any of the 4 directions.

 # The border of a connected component is all the squares in the connected component that are either 4-directionally adjacent to a square not in the component, or on the boundary of the grid (the first or last row or column).

 # Given a square at location (r0, c0) in the grid and a color, color the border of the connected component of that square with the given color, and return the final grid.


 # Example 1:

 # Input: grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
 # Output: [[3, 3], [3, 2]]

 # Example 2:

 # Input: grid = [[1,2,2],[2,3,2]], r0 = 0, c0 = 1, color = 3
 # Output: [[1, 3, 3], [2, 3, 3]]

 # Example 3:

 # Input: grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
 # Output: [[2, 2, 2], [2, 1, 2], [2, 2, 2]]


 # Note:

 # 1 <= grid.length <= 50
 # 1 <= grid[0].length <= 50
 # 1 <= grid[i][j] <= 1000
 # 0 <= r0 < grid.length
 # 0 <= c0 < grid[0].length
 # 1 <= color <= 1000

 */

#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <functional>
#include <set>

using std::pair;
using std::vector;
using std::unordered_set;
using std::set;

/*
namespace std{

    template<>
    class pair<int, int> {
        
    public:
        int _a, _b;
        
        pair(int a, int b): _a(a), _b(b) {
            
        }
        
        bool operator == (pair<int, int>& item) {
            return _a == item._a && _b == item._b;
        }
        
        pair<int, int>& operator = (const pair<int, int> & item) {
            _a = item._a;
            _b = item._b;
            return *this;
        }
    };

    template<>
    class hash<pair<int, int>> {
        
    public:
        auto operator()(pair<int, int> a) {
            return hash<int>()(a._a) ^ hash<int>()(a._b);
        }
    };

} */

namespace std {
    template <> struct hash<std::pair<int, int>> {
        inline size_t operator()(const std::pair<int, int> &v) const {
            std::hash<int> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

class ColorBorder {
    
    typedef pair<int, int> point;

public:

    // BFS
    vector<vector<int>> doit(vector<vector<int>>&& grid, int r0, int c0, int color) {
        
        unordered_set<point> component, border;
        component.insert(point{r0, c0});
        vector<point> buff;
        buff.push_back(point{r0, c0});
        int row = grid.size(), col = grid[0].size();
        
        
        while (!buff.empty()) {
            
            auto pt = buff.back();
            buff.pop_back();
            
            for (auto v : vector<point>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
                
                int x = pt.first + v.first, y = pt.second + v.second;
                
                if (x >= 0 && x < row && y >= 0 && y < col && grid[x][y] == grid[r0][c0]) {
                    if (component.count(point{x, y}) == 0) {
                        component.insert(point{x, y});
                        buff.push_back(point{x, y});
                    }
                } else {
                    border.insert(pt);
                }
            }
        }
        
        for (auto pt : border) {
            grid[pt.first][pt.second] = color;
        }
        
        return grid;
    }

public:
    set<pair<int, int> > v;
    
    // dfs logic
    vector<vector<int>> doit1(vector<vector<int>>& grid, int r0, int c0, int color) {
        dfs(grid, r0, c0, grid[r0][c0], color);
        return grid;
    }
    
    bool dfs(vector<vector<int>>& grid, int x, int y, int src, int color) {
        if(v.count({x, y}))
            return true;
        
        if(x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] != src )
            return false;
        
        v.insert({x, y});
        bool res = dfs(grid, x , y + 1, src, color);
        res = dfs(grid, x + 1, y, src, color) && res;
        res = dfs(grid, x , y - 1, src, color) && res;
        res = dfs(grid, x - 1, y, src, color) && res;
        
        if(!res)
            grid[x][y] = color;
        
        return true;
    }
    
    
/*
 This problem is not difficult, it just has too many details. In fact, I made two wrong submissions due to misunderstanding the problem.
 OK, so everybody knows that this must be a DFS (or BFS) from r0, c0 to search for all cells of the connected component. What do we need to pay attention here:

 In dfs, we often have to keep an array of visited node (so we will not visit this node again). At the beginning, I thought I can use the existing color or the color to be painted as a flag for visited. But then thing can be very complicated: what if the color to be painted is the same as the color of a neibour cell. So I decided to use two unused colors, i.e.
 outside the range 1 .. 1000, as the flags: a cell with color INVALID_CELL belongs to the component, but not in the border, and a cell with color INVALID_BORDER is in border. (INVALID just means it is not an invalid color).
 After coloring the components with INVALID_CELL and INVALID_BORDER, I scan the grid again, and replace them with real color. I thought it is expensive, but my solution still beats 99.36% C++ submissions.
 */
    
    
    
        int M;
        int N;
        int old;
        int INVALID_CELL = 1001;
        int INVALID_BORDER = 1002;
    
    public:
        vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
            // set internal data
            M = grid.size();
            N = grid[0].size();
            old = grid[r0][c0];
            // no need to paint
            if (old == color) return grid;
            dfsPaintBorder(grid, r0, c0);
            // OK, we are done. Paint with real color
            for(int i = 0; i< M; i++){
                for(int j = 0; j < N; ++j){
                    if(grid[i][j] == INVALID_CELL){
                        grid[i][j] = old;
                    } else if(grid[i][j] == INVALID_BORDER){
                        grid[i][j] = color;
                    }
                }
            }
            return grid;
        }
        
        void dfsPaintBorder(vector<vector<int>>& grid, int i, int j){
            int M = grid.size();
            int N = grid[0].size();
            if(i < 0 || i >= M || j < 0 || j >= N || grid[i][j] != old){
                // invalid cell
                return;
            }
            
            if(isBorder(grid, i, j)){
                grid[i][j] = INVALID_BORDER;
            } else{
                grid[i][j] = INVALID_CELL;
            }
            
            dfsPaintBorder(grid, i - 1, j);
            dfsPaintBorder(grid, i + 1, j);
            dfsPaintBorder(grid, i, j - 1);
            dfsPaintBorder(grid, i, j + 1);
        }
        
        bool isBorder(vector<vector<int>>& grid, int i, int j){
            return isOutside(grid, i - 1, j) || isOutside(grid, i + 1, j)
                || isOutside(grid, i, j - 1) || isOutside(grid, i, j + 1);
        }

        bool isOutside(vector<vector<int>>& grid, int i, int j){
            if(i < 0 || i >= M || j < 0 || j >= N){
                return true;
            }
            int cell = grid[i][j];
            return cell != INVALID_CELL && cell != INVALID_BORDER && cell != old;
        }
    
};


void test_1034_Coloring_A_Border() {

    
    auto res = ColorBorder().doit(vector<vector<int>>{{1, 1}, {1, 2}}, 0, 0, 3);
    
    auto res1 = ColorBorder().doit(vector<vector<int>>{{1, 2, 2}, {2, 3, 2}}, 0, 1, 3);
    
    auto res2 = ColorBorder().doit(vector<vector<int>>{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, 1, 1, 2);
    
    return;
}

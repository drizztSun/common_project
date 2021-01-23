/*
1631. Path With Minimum Effort


You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). 
You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). 
You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.

A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

 

Example 1:



Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.
Example 2:



Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
Output: 1
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].
Example 3:


Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort.
 

Constraints:

rows == heights.length
columns == heights[i].length
1 <= rows, columns <= 100
1 <= heights[i][j] <= 10^6
*/
#include <vector>
#include <queue>

using std::queue;
using std::priority_queue;
using std::vector;



class PathWithMinimumEffort {

    class Cell {
    public:
        int x, y;
        int difference;
        Cell(int x, int y, int difference) {
            this->x = x;
            this->y = y;
            this->difference = difference;
        }
    };

    struct Comparator {
        bool operator()(Cell const &p1, Cell const &p2) {
            return p2.difference < p1.difference;
        }
    };

public:

    /*
    
    */
    
    int doit_bfs_dijstra(vector<vector<int>>& heights) {
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int row = heights.size();
        int col = heights[0].size();
        vector<vector<int>> differenceMatrix(row, vector<int>(col, INT_MAX));
        differenceMatrix[0][0] = 0;
        priority_queue<Cell, vector<Cell>, Comparator> queue;
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        queue.push(Cell(0, 0, differenceMatrix[0][0]));

        auto isValidCell = [&](int x, int y, int row, int col) -> bool {
            return x >= 0 && x <= row - 1 && y >= 0 && y <= col - 1;
        };

        while (!queue.empty()) {
            Cell curr = queue.top();
            queue.pop();
            visited[curr.x][curr.y] = true;
            if (curr.x == row - 1 && curr.y == col - 1) return curr.difference;
            for (auto direction : directions) {
                int adjacentX = curr.x + direction[0];
                int adjacentY = curr.y + direction[1];
                if (isValidCell(adjacentX, adjacentY, row, col) &&
                    !visited[adjacentX][adjacentY]) {
                    int currentDifference = abs(heights[adjacentX][adjacentY] -
                                                heights[curr.x][curr.y]);
                    int maxDifference = max(currentDifference,
                                            differenceMatrix[curr.x][curr.y]);
                    if (differenceMatrix[adjacentX][adjacentY] >
                        maxDifference) {
                        differenceMatrix[adjacentX][adjacentY] = maxDifference;
                        queue.push(Cell(adjacentX, adjacentY, maxDifference));
                    }
                }
            }
        }
        return differenceMatrix[row - 1][col - 1];
    }


    int doit_disjoint(vector<vector<int>>& heights) {
        int row = heights.size();
        int col = heights[0].size();
        if (row == 1 && col == 1) return 0;
        UnionFind unionFind(heights);
        vector<Edge> edgeList = unionFind.edgeList;
        sort(edgeList.begin(), edgeList.end(), compareInterval);

        for (int i = 0; i < edgeList.size(); i++) {
            int x = edgeList[i].x;
            int y = edgeList[i].y;
            unionFind.makeUnion(x, y);
            if (unionFind.find(0) == unionFind.find(row * col - 1))
                return edgeList[i].difference;
        }
        return -1;
    }

private:

    class Edge {
    public:
        int x, y;
        int difference;

        Edge(int x, int y, int difference) {
            this->x = x;
            this->y = y;
            this->difference = difference;
        }
    };

    static bool compareInterval(const Edge& p1, const Edge& p2) {
        return (p1.difference < p2.difference);
    }

    class UnionFind {
    public:
        vector<int> parent;
        vector<int> rank;
        vector<Edge> edgeList;

        UnionFind(vector<vector<int>>& heights) {
            int row = heights.size();
            int col = heights[0].size();
            parent.assign(row * col, 0);
            rank.assign(row * col, 0);
            for (int currentRow = 0; currentRow < row; currentRow++) {
                for (int currentCol = 0; currentCol < col; currentCol++) {
                    if (currentRow > 0) {
                        edgeList.push_back(
                            Edge(currentRow * col + currentCol,
                                 (currentRow - 1) * col + currentCol,
                                 abs(heights[currentRow][currentCol] -
                                     heights[currentRow - 1][currentCol])));
                    }
                    if (currentCol > 0) {
                        edgeList.push_back(
                            Edge(currentRow * col + currentCol,
                                 currentRow * col + currentCol - 1,
                                 abs(heights[currentRow][currentCol] -
                                     heights[currentRow][currentCol - 1])));
                    }
                    parent[currentRow * col + currentCol] =
                        currentRow * col + currentCol;
                }
            }
        }

        int find(int i) {
            if (parent[i] != i) parent[i] = find(parent[i]);
            return parent[i];
        }

        void makeUnion(int x, int y) {
            int parentX = find(x);
            int parentY = find(y);
            if (parentX != parentY) {
                if (rank[parentX] > rank[parentY])
                    parent[parentY] = parentX;
                else if (rank[parentX] < rank[parentY])
                    parent[parentX] = parentY;
                else {
                    parent[parentY] = parentX;
                    rank[parentX] += 1;
                }
            }
        }
    };

};

class MinimumEffort {


    bool isValidCell(int x, int y, int row, int col) {
        return x >= 0 && x <= row - 1 && y >= 0 && y <= col - 1;
    }

    class Cell {
    public:
        int x, y;
        Cell(int x, int y) {
            this->x = x;
            this->y = y;
        }
    };

public:

    int doit_bfs_binary_search(vector<vector<int>> &heights) {
        int left = 0;
        int right = 1000000;
        int result = right;
        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};


        // use bfs to check if we can reach destination with max absolute difference
        // k
        auto canReachDestinaton = [&](vector<vector<int>> &heights, int mid){
            int row = heights.size();
            int col = heights[0].size();

            queue<Cell> qu;
            vector<vector<bool>> visited(row, vector<bool>(col, false));
            qu.push(Cell(0, 0));
            visited[0][0] = true;
            while (!qu.empty()) {
                Cell curr = qu.front();
                qu.pop();
                if (curr.x == row - 1 && curr.y == col - 1) {
                    return true;
                }
                for (auto direction : directions) {
                    int adjacentX = curr.x + direction[0];
                    int adjacentY = curr.y + direction[1];
                    if (isValidCell(adjacentX, adjacentY, row, col) &&
                        !visited[adjacentX][adjacentY]) {
                        int currentDifference = abs(heights[adjacentX][adjacentY] - heights[curr.x][curr.y]);
                        if (currentDifference <= mid) {
                            visited[adjacentX][adjacentY] = true;
                            qu.push(Cell(adjacentX, adjacentY));
                        }
                    }
                }
            }
            return false;
        };

        while (left <= right) {
            int mid = (left + right) / 2;
            if (canReachDestinaton(heights, mid)) {
                result = std::min(result, mid);
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return result;
    }

    int doit_dfs_binary_search(vector<vector<int>> &heights) {
        int left = 0;
        int right = 1000000;
        int result = right;
        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        auto = dfsUtil(vector<vector<int>> &heights, int mid) {
            int row = heights.size();
            int col = heights[0].size();
            vector<vector<bool>> visited(row, vector<bool>(col, false));

            std::function<bool(int, int, int, int, int)> canReachDestinaton = [&](int x, int y, int row, int col,int mid) {
                if (x == row - 1 && y == col - 1) {
                    return true;
                }
                visited[x][y] = true;
                for (auto direction : directions) {
                    int adjacentX = x + direction[0];
                    int adjacentY = y + direction[1];
                    if (isValidCell(adjacentX, adjacentY, row, col) &&
                        !visited[adjacentX][adjacentY]) {
                        int currentDifference =
                            abs(heights[adjacentX][adjacentY] - heights[x][y]);
                        if (currentDifference <= mid) {
                            if (canReachDestinaton(adjacentX, adjacentY,row, col, mid))
                                return true;
                        }
                    }
                }
                return false;
            }
            return canReachDestinaton(0, 0, row, col, mid);
        };

        while (left <= right) {
            int mid = (left + right) / 2;
            if (dfsUtil(heights, mid)) {
                result = min(result, mid);
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return result;
    }
};

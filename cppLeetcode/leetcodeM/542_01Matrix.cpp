/*
542. 01 Matrix


Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

 

Example 1:

Input:
[[0,0,0],
 [0,1,0],
 [0,0,0]]

Output:
[[0,0,0],
 [0,1,0],
 [0,0,0]]
Example 2:

Input:
[[0,0,0],
 [0,1,0],
 [1,1,1]]

Output:
[[0,0,0],
 [0,1,0],
 [1,2,1]]
 

Note:

The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.




*/
#include <vector>
#include <queue>

using std::queue;
using std::vector;

class Matrix01 {

public:

    /*
        Approach #2 Using BFS [Accepted]
        Intuition

        A better brute force: Looking over the entire matrix appears wasteful and hence, we can use Breadth First Search(BFS) to limit the search to the nearest 0 found for each 1. 
        As soon as a 0 appears during the BFS, we know that the 0 is nearest, and hence, we move to the next 1.

        Think again: But, in this approach, we will only be able to update the distance of one 1 using one BFS, which could in fact, result in slightly higher complexity than the Approach #1 brute force. 
        But hey,this could be optimised if we start the BFS from 0s and thereby, updating the distances of all the 1s in the path.

        Algorithm

        For our BFS routine, we keep a queue, q to maintain the queue of cells to be examined next.
        We start by adding all the cells with 0s to q.
        Intially, distance for each 0 cell is 0 and distance for each 1 is INT_MAX, which is updated during the BFS.
        Pop the cell from queue, and examine its neighbours. If the new calculated distance for neighbour {i,j} is smaller, we add {i,j} to q and update dist[i][j].

        Complexity analysis

        Time complexity: O(r⋅c).

        Since, the new cells are added to the queue only if their current distance is greater than the calculated distance, cells are not likely to be added multiple times.
        Space complexity: O(r⋅c). Additional O(r⋅c) for queue than in Approach #1

    */
    vector<vector<int>> doit_bfs(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return matrix;
        int cols = matrix[0].size();
        vector<vector<int> > dist(rows, vector<int>(cols, INT_MAX));
        queue<std::pair<int, int> > q;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({ i, j }); //Put all 0s in the queue.
                }

        int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
        while (!q.empty()) {
            std::pair<int, int> curr = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int new_r = curr.first + dir[i][0], new_c = curr.second + dir[i][1];
                if (new_r >= 0 && new_c >= 0 && new_r < rows && new_c < cols) {
                    if (dist[new_r][new_c] > dist[curr.first][curr.second] + 1) {
                        dist[new_r][new_c] = dist[curr.first][curr.second] + 1;
                        q.push({ new_r, new_c });
                    }
                }
            }
        }
        return dist;
    }

    /*
        Approach #3 DP Approach [Accepted]
        Intuition

        The distance of a cell from 0 can be calculated if we know the nearest distance for all the neighbours, in which case the distance is minimum distance of any neightbour + 1. And, instantly, the word come to mind DP!!
        For each 1, the minimum path to 0 can be in any direction. So, we need to check all the 4 direction. In one iteration from top to bottom, we can check left and top directions, and we need another iteration from bottom to top to check for right and bottom direction.

        Algorithm

        Iterate the matrix from top to bottom-left to right:
        Update \text{dist}[i][j]=\min(\text{dist}[i][j],\min(\text{dist}[i][j-1],\text{dist}[i-1][j])+1)dist[i][j]=min(dist[i][j],min(dist[i][j−1],dist[i−1][j])+1) i.e., minimum of the current dist and distance from top or left neighbour +1, that would have been already calculated previously in the current iteration.
        Now, we need to do the back iteration in the similar manner: from bottom to top-right to left:
        Update \text{dist}[i][j]=\min(\text{dist}[i][j],\min(\text{dist}[i][j+1],\text{dist}[i+1][j])+1)dist[i][j]=min(dist[i][j],min(dist[i][j+1],dist[i+1][j])+1) i.e. minimum of current dist and distances calculated from bottom and right neighbours, that would be already available in current iteration.

        Complexity analysis

        Time complexity: O(r \cdot c)O(r⋅c). 2 passes of r \cdot cr⋅c each
        Space complexity: O(r \cdot c)O(r⋅c). No additional space required than dist vector<vector<int> >
    */
    vector<vector<int> > updateMatrix(vector<vector<int> >& matrix)
    {
        int rows = matrix.size();
        if (rows == 0) return matrix;
        int cols = matrix[0].size();
        
        vector<vector<int> > dist(rows, vector<int>(cols, INT_MAX - 100000));

        //First pass: check for left and top
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 0)
                    dist[i][j] = 0;
                else {
                    if (i > 0)
                        dist[i][j] = std::min(dist[i][j], dist[i - 1][j] + 1);
                    if (j > 0)
                        dist[i][j] = std::min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }

        //Second pass: check for bottom and right
        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 0; j--) {
                if (i < rows - 1)
                    dist[i][j] = std::min(dist[i][j], dist[i + 1][j] + 1);
                if (j < cols - 1)
                    dist[i][j] = std::min(dist[i][j], dist[i][j + 1] + 1);
            }
        }

        return dist;
    }


};
/*
296. Best Meeting Point


Given an m x n binary grid grid where each 1 marks the home of one friend, return the minimal total travel distance.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

 

Example 1:


Input: grid = [[1,0,0,0,1],[0,0,0,0,0],[0,0,1,0,0]]
Output: 6
Explanation: Given three friends living at (0,0), (0,4), and (2,2).
The point (0,2) is an ideal meeting point, as the total travel distance of 2 + 2 + 2 = 6 is minimal.
So return 6.
Example 2:

Input: grid = [[1,1]]
Output: 1
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
grid[i][j] is either 0 or 1.
There will be at least two friends in the grid.

*/

#include <vector>
#include <algorithm>

using std::vector;


class MinTotalDistance {

public:
    
    // Treat the two dimensions x and y separately, first collecting the k coordinates of the dimension and then using them to update the total travel distance.
    // O(nm)
    int doit_sort(vector<vector<int>>& grid) {
        
        int total = 0, X = grid.size(), Y = grid[0].size();
        for (int dim=0; dim<2; ++dim) {
            vector<int> c(X*Y);
            int k = 0;
            for (int x=0; x<X; ++x)
                for (int y=0; y<Y; ++y)
                    if (grid[x][y] == 1)
                        c[k++] = dim ? y : x;
            std::nth_element(begin(c), begin(c)+k/2, begin(c)+k);
            int louis = c[k/2];  // (co)median
            while (k--)
                total += abs(louis - c[k]);
        }
        return total;
    }

    /*
        Solution 2 ... sort ... 12 ms, O(mn log(mn))
        Sort the coordinates and use larrywang2014's way to add the travel distances.
    */
    int doit_sort(vector<vector<int>>& grid) {
        int total = 0, X = grid.size(), Y = grid[0].size();
        for (int dim=0; dim<2; ++dim) {
            int i = 0, k = 0, c[X*Y];
            for (int x=0; x<X; ++x)
                for (int y=0; y<Y; ++y)
                    if (grid[x][y])
                        c[k++] = dim ? y : x;
            std::sort(c, c+k);
            while (i < --k)
                total += c[k] - c[i++];
        }
        return total;
    }
};
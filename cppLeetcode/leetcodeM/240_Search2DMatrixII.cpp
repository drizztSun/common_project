/*
240. Search a 2D Matrix II

Write an efficient algorithm that searches for a target value in an m x n integer matrix. The matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
 

Example 1:


Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true
Example 2:


Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-109 <= matix[i][j] <= 10^9
All the integers in each row are sorted in ascending order.
All the integers in each column are sorted in ascending order.
-10^9 <= target <= 10^9
*/

#include <vector>
#include <functional>

using std::vector;

class SearchMatrix {

public:
    
    bool doit_(vector<vector<int>>& matrix, int target) {

        std::function<bool(int, int, int, int)> search = [&](int r1, int c1, int r2, int c2) {
            
            if (r1 > r2 || c1 > c2) return false;

            int r = (r1 + r2) / 2, c = (c1 + c2) / 2;

            if (matrix[r][c] == target) return true;

            if (matrix[r][c] > target)
                return search(r+1, c1, r2, c2) || search(r1, c+1, r2, c2);

            return search(r1, c2, r, c2) || search(r1, c2, r2, c);
        };

        return search(0, 0, matrix.size(), matrix[0].size());
    }

    /*
        Approach 4: Search Space Reduction
        Intuition

        Because the rows and columns of the matrix are sorted (from left-to-right and top-to-bottom, respectively), we can prune \mathcal{O}(m)O(m) or \mathcal{O}(n)O(n) elements when looking at any particular value.

        Algorithm

        First, we initialize a (row, col)(row,col) pointer to the bottom-left of the matrix.[1] Then, until we find target and return true (or the pointer points to a (row, col)(row,col) 
        that lies outside of the dimensions of the matrix), we do the following: if the currently-pointed-to value is larger than target we can move one row "up". 
        
        Otherwise, if the currently-pointed-to value is smaller than target, we can move one column "right". It is not too tricky to see why doing this will never prune the correct answer; 
        because the rows are sorted from left-to-right, we know that every value to the right of the current value is larger. 
        Therefore, if the current value is already larger than target, we know that every value to its right will also be too large. 
        A very similar argument can be made for the columns, so this manner of search will always find target in the matrix (if it is present).

        Check out some sample runs of the algorithm in the animation below:

        Complexity Analysis

        Time complexity : \mathcal{O}(n+m)O(n+m)

        The key to the time complexity analysis is noticing that, on every iteration (during which we do not return true) either row or col is is decremented/incremented exactly once. 
        Because row can only be decremented mm times and col can only be incremented nn times before causing the while loop to terminate, the loop cannot run for more than n+mn+m iterations. 
        Because all other work is constant, the overall time complexity is linear in the sum of the dimensions of the matrix.

        Space complexity : \mathcal{O}(1)O(1)

        Because this approach only manipulates a few pointers, its memory footprint is constant.
    */
    bool doit_reduction(const vector<vector<int>>& matrix, int target) {

        int rows = matrix.size();
        if (rows == 0) return false;
        
        int cols = matrix[0].size();
        if (cols == 0) return false;
        
        int r = 0;
        int c = cols - 1;
        
        while (r < rows && c >= 0) {
            const auto elem = matrix[r][c];
            if (elem == target) {
                return true;
            } else if (elem > target) {
                --c;
            } else {
                ++r;
            }
        }
        
        return false;
    }

};
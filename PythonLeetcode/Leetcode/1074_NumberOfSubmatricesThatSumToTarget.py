"""
1074. Number of Submatrices That Sum to Target

Given a matrix and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different:
for example, if x1 != x1'.



Example 1:


Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.
Example 2:

Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.
Example 3:

Input: matrix = [[904]], target = 0
Output: 0


Constraints:

1 <= matrix.length <= 100
1 <= matrix[0].length <= 100
-1000 <= matrix[i] <= 1000
-10^8 <= target <= 10^8


"""


class NumberOfSubmatricaSumsToTarget:



    """"
    Approach 1: Number of Subarrays that Sum to Target: Horizontal 1D Prefix Sum

    Algorithm

    Initialize the result: count = 0.

    Compute the number of rows: r = len(matrix) and number of columns: c = len(matrix[0]).

    Compute 2D prefix sum ps. To simplify the code, we allocate one more row and one more column, reserving row 0 and column 0 for zero values.
    This way, we avoid computing the first row and the first column separately.

    Iterate over the rows: r1 from 1 to r, and r2 from r1 to r:

    Inside this double loop, the left and right row boundaries are fixed. Now it's time to initialize a hashmap:
    1D prefix sum -> number of matrices which use [r1, r2] rows and sum to this prefix sum. Sum of empty matrix is equal to zero: h[0] = 1.

    Iterate over the columns from 1 to c + 1. At each step:

    Compute current 1D prefix sum curr_sum using previously computed 2D prefix sum ps: curr_sum = ps[r2][col] - ps[r1 - 1][col].

    The number of times the sum curr_sum - target occurred, defines the number of matrices which use r1 ... r2 rows and sum to target.
    Increment the count: count += h[curr_sum - target].

    Add the current 1D prefix sum into hashmap.

    Return count.

    Implementation

    Complexity Analysis

    Time complexity: O(R^2 C), where RR is the number of rows and CC is the number of columns.

    Space complexity: O(RC) to store 2D prefix sum.

    """
    def doit_dp_presum(self, matrix: list, target: int) -> int:
        from collections import defaultdict

        r, c = len(matrix), len(matrix[0])

        # compute 2D prefix sum
        ps = [[0] * (c + 1) for _ in range(r + 1)]
        for i in range(1, r + 1):
            for j in range(1, c + 1):
                ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + matrix[i - 1][j - 1]

        count = 0
        # reduce 2D problem to 1D one
        # by fixing two rows r1 and r2 and
        # computing 1D prefix sum for all matrices using [r1..r2] rows
        for r1 in range(1, r + 1):
            for r2 in range(r1, r + 1):
                h = defaultdict(int)
                h[0] = 1

                for col in range(1, c + 1):
                    # current 1D prefix sum
                    curr_sum = ps[r2][col] - ps[r1 - 1][col]

                    # add subarrays which sum up to (curr_sum - target)
                    count += h[curr_sum - target]

                    # save current prefix sum
                    h[curr_sum] += 1

        return count

    def doit_dp(self, matrix: list, target: int) -> int:

        rows, cols = len(matrix) + 1, len(matrix[0]) + 1
        psum = [[0] * cols for _ in range(rows)]

        for r in range(1, rows):
            t = 0
            for c in range(1, cols):
                t += matrix[r - 1][c - 1]
                psum[r][c] = psum[r - 1][c] + t

        ans = 0
        for r1 in range(rows - 1):
            for r2 in range(r1 + 1, rows):
                d = {target: 1}
                for c in range(1, cols):
                    x = psum[r2][c] - psum[r1][c]
                    if x in d:
                        ans += d[x]
                    x += target
                    d[x] = d.get(x, 0) + 1
        return ans

    """
    Approach 2: Number of Subarrays that Sum to Target: Vertical 1D Prefix Sum
    In Approach 1, we were fixing two rows, and computing the "horizontal" 1D prefix sum. 
    One could follow the same logic by fixing two columns, and computing the "vertical" 1D prefix sum.
    
    Complexity Analysis

    Time complexity: O(R C^2) where RR is the number of rows and CC is the number of columns.
    
    Space complexity: O(RC) to store 2D prefix sum.
    """
    def doit_dp_presum(self, matrix: list, target: int) -> int:
        from collections import defaultdict
        r, c = len(matrix), len(matrix[0])

        # compute 2D prefix sum
        ps = [[0] * (c + 1) for _ in range(r + 1)]
        for i in range(1, r + 1):
            for j in range(1, c + 1):
                ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + matrix[i - 1][j - 1]

        count = 0
        # reduce 2D problem to 1D one
        # by fixing two columns c1 and c2 and
        # computing 1D prefix sum for all matrices using [c1..c2] columns
        for c1 in range(1, c + 1):
            for c2 in range(c1, c + 1):
                h = defaultdict(int)
                h[0] = 1

                for row in range(1, r + 1):
                    # current 1D prefix sum
                    curr_sum = ps[row][c2] - ps[row][c1 - 1]

                    # add subarrays which sum up to (curr_sum - target)
                    count += h[curr_sum - target]

                    # save current prefix sum
                    h[curr_sum] += 1

        return count
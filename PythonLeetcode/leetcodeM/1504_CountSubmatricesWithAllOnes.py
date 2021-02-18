"""
1504. Count Submatrices With All Ones


Given a rows * columns matrix mat of ones and zeros, return how many submatrices have all ones.



Example 1:

Input: mat = [[1,0,1],
              [1,1,0],
              [1,1,0]]
Output: 13
Explanation:
There are 6 rectangles of side 1x1.
There are 2 rectangles of side 1x2.
There are 3 rectangles of side 2x1.
There is 1 rectangle of side 2x2.
There is 1 rectangle of side 3x1.
Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.
Example 2:

Input: mat = [[0,1,1,0],
              [0,1,1,1],
              [1,1,1,0]]
Output: 24
Explanation:
There are 8 rectangles of side 1x1.
There are 5 rectangles of side 1x2.
There are 2 rectangles of side 1x3.
There are 4 rectangles of side 2x1.
There are 2 rectangles of side 2x2.
There are 2 rectangles of side 3x1.
There is 1 rectangle of side 3x2.
Total number of rectangles = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24.
Example 3:

Input: mat = [[1,1,1,1,1,1]]
Output: 21
Example 4:

Input: mat = [[1,0,1],[0,1,0],[1,0,1]]
Output: 5


Constraints:

1 <= rows <= 150
1 <= columns <= 150
0 <= mat[i][j] <= 1

"""


class SubmatricesAllOnes:

    """
        O(n^3)
    """
    def doit_(self, mat: list) -> int:
        m, n = len(mat), len(mat[0])
        count = 0
        for left in range(n):
            row_sums = [0 for _ in range(m)]
            for right in range(left, n):
                consec_count = 0
                width = right - left + 1
                for bottom in range(m):
                    row_sums[bottom] += mat[bottom][right]
                    if row_sums[bottom] != width:
                        consec_count = 0
                    else:
                        consec_count += 1
                        count += consec_count
        return count

    """
        Algo
        In the first step, stack mat row by row to get the "histogram model". For example,
        
        mat = [[1,0,1],
               [1,1,0],
               [1,1,0]]
        becomes
        
        mat = [[1,0,1],
               [2,1,0],
               [3,2,0]]
        In the second step, traverse the stacked matrix row by row. At each position i, j, compute the number of all-1 submatrices like below.
        
        Define a stack to store indices of non-decreasing height, and a variable cnt for the number of all-1 submatrices at given position (i, j). 
        Take the height of row i as an example, say h = mat[i]. At column j, if h[j-1] <= h[j], it is apparent that cnt[j] = cnt[j-1] + h[j], 
        since every case that contributes to cnt[j-1] could be added a new column of 1's from the jth column to contribute to cnt[j].
        
        The tricky part is when h[j-1] > h[j]. In this case, we need to "hypothetically" lower h[j-1] to h[j] to get an updated cnt*[j-1] before adding h[j] to get cnt[j]. 
        Suppose that the histogram is like below to reflect 3,3,3,2. 
        To compute cnt[3], we have to adjust cnt[2] to a hypothetical height of 2 by removing top row before adding the new column to get cnt[3]. 
        The specific operation is done using a mono-stack which stores indices of non-decreasing height. 
        
        Whenever a new height comes in, pop out the heights in the stack that are higher than the new height while removing the quota contributed by the extra height (between poped height and new height).
        
        * * * 
        * * * * 
        * * * *
    
        O(m*n)
    """
    def doit_(self, mat: list) -> int:

        m, n = len(mat), len(mat[0])

        # precipitate mat to histogram
        for i in range(m):
            for j in range(n):
                if mat[i][j] and i > 0:
                    mat[i][j] += mat[i - 1][j]  # histogram

        ans = 0
        for i in range(m):
            stack = []  # mono-stack of indices of non-decreasing height
            cnt = 0
            for j in range(n):
                while stack and mat[i][stack[-1]] > mat[i][j]:
                    jj = stack.pop()  # start
                    kk = stack[-1] if stack else -1  # end
                    cnt -= (mat[i][jj] - mat[i][j]) * (jj - kk)  # adjust to reflect lower height, no possible to make matrix with that part

                cnt += mat[i][j]  # count submatrices bottom-right at (i, j)
                ans += cnt
                stack.append(j)

        return ans
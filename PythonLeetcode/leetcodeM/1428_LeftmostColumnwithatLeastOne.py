"""
1428. Leftmost Column with at Least a One

(This problem is an interactive problem.)

A binary matrix means that all elements are 0 or 1. For each individual row of the matrix, this row is sorted in non-decreasing order.

Given a row-sorted binary matrix binaryMatrix, return leftmost column index(0-indexed) with at least a 1 in it. If such index doesn't exist, return -1.

You can't access the Binary Matrix directly.  You may only access the matrix using a BinaryMatrix interface:

BinaryMatrix.get(row, col) returns the element of the matrix at index (row, col) (0-indexed).
BinaryMatrix.dimensions() returns a list of 2 elements [rows, cols], which means the matrix is rows * cols.
Submissions making more than 1000 calls to BinaryMatrix.get will be judged Wrong Answer.
Also, any solutions that attempt to circumvent the judge will result in disqualification.

For custom testing purposes you're given the binary matrix mat as input in the following four examples.
You will not have access the binary matrix directly.


Example 1:



Input: mat = [[0,0],[1,1]]
Output: 0
Example 2:



Input: mat = [[0,0],[0,1]]
Output: 1
Example 3:



Input: mat = [[0,0],[0,0]]
Output: -1
Example 4:



Input: mat = [[0,0,0,1],[0,0,1,1],[0,1,1,1]]
Output: 1


Constraints:

rows == mat.length
cols == mat[i].length
1 <= rows, cols <= 100
mat[i][j] is either 0 or 1.
mat[i] is sorted in a non-decreasing way.

"""


# """
# This is BinaryMatrix's API interface.
# You should not implement it, or speculate about its implementation
# """
# class BinaryMatrix(object):
#    def get(self, row: int, col: int) -> int:
#    def dimensions(self) -> list[]:

class LeftmostColumnWith:

    """
    Approach 2: Binary Search Each Row
    Intuition

    This isn't the best approach, but it passes, and coding it up is a good opportunity to practice binary search.

    When linear search is too slow, we should try to find a way to use binary search. If you're not familiar with binary search,
     check out this Explore Card!. We recommend doing the first couple of binary search questions to get familiar with the algorithm before coming back to this problem.

    Also, have a go at First Bad Version. The only difference between that problem and this one is that instead of 0 and 1, it uses false and true.

    Like we did with the linear search, we're going to apply binary search independently on each row. The target element we're searching for is the first 1 in the row.

    The core part of a binary search algorithm is how it decides whether the target element is to the left or the right of the middle element. Let's figure this out by thinking through a couple of examples.

    In the row below, we've determined that the middle element is a 0. On what side must the target element (first 1) be? The left, or the right? Don't forget, all the 0's are before all the 1's.
    """
    def doit_binary_search(self, binaryMatrix: 'BinaryMatrix') -> int:

        m, n = binaryMatrix.dimensions()

        ans = n

        for i in range(m):

            left, right = 0, n
            found = False

            while left < right:

                mid = (left + right) // 2
                d = binaryMatrix.get(i, mid)

                if d >= 1:
                    right = mid
                    found = True
                else:
                    left = mid + 1

            if found:
                ans = min(left, ans)

        return -1 if ans == n else ans

    """
    Approach 3: Start at Top Right, Move Only Left and Down
    Intuition
    
    Did you notice in Approach 2 that we didn't need to finish searching all the rows? One example of this was row 3 on the example in the animation. At the point shown in the image below, it was clear that row 3 could not possibly be better than the minimum we'd found so far.
    
    Diagram showing redundant search in Row 3
    
    Therefore, an optimization we could have made was to keep track of the minimum index so far, and then abort the search on any rows where we have discovered a 0 at, or to the right of, that minimum index.
    
    We can do even better than that; on each search, we can set hi = smallest_index - 1, where smallest_index is the smallest index of a 1 we've seen so far. In most cases, this is a substantial improvement. It works because we're only interested in finding 1s at lower indexes than we previously found. Here is an animation of the above example with this optimized algorithm. The algorithm eliminates as many cells as it can with each API call. It also starts by checking the last cell of the row before proceeding with the binary search, to eliminate needless binary searches where the row only had 0s left in it.
    
    Current
    1 / 17
    Here is what the worst-case looks like. Like before, its time complexity is still O(M \, \log \, N)O(MlogN).
    
    The worst case for the optimized algorithm
    
    While this is no worse than Approach 2, there is a better algorithm.
    
    Start in the top right corner, and if the current value is a 0, move down. If it is a 1, then move left.
    
    The easiest way to see why this works is an example. Here is an animation of it.
    
    Current
    1 / 17
    You probably gained some intuitive sense as to why this works, just from watching the animation.
    
    When we encounter a 0, we know that the leftmost 1 can't be to the left of it.
    When we encounter a 1, we should continue the search on that row (move pointer to the left), in order to find an even smaller index.
    Algorithm
    Complexity Analysis

    Let NN be the number of rows, and MM be the number of columns.
    
    Time complexity : O(N+M).
    
    At each step, we're moving 1 step left or 1 step down. 
    Therefore, we'll always finish looking at either one of the M rows or N columns. 
    Therefore, we'll stay in the grid for at most N + MN+M steps, and therefore get a time complexity of O(N+M).
    
    Space complexity : O(1).
    
    We are using constant extra space.
    
    """
    def doit_(self, binaryMatrix: 'BinaryMatrix') -> int:

        rows, cols = binaryMatrix.dimensions()

        # Set pointers to the top-right corner.
        current_row = 0
        current_col = cols - 1

        # Repeat the search until it goes off the grid.
        while current_row < rows and current_col >= 0:
            if binaryMatrix.get(current_row, current_col) == 0:
                current_row += 1
            else:
                current_col -= 1

        # If we never left the last column, it must have been all 0's.
        return current_col + 1 if current_col != cols - 1 else -1
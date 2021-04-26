/*
1428. Leftmost Column with at Least a One

A row-sorted binary matrix means that all elements are 0 or 1 and each row of the matrix is sorted in non-decreasing order.

Given a row-sorted binary matrix binaryMatrix, return the index (0-indexed) of the leftmost column with a 1 in it. If such an index does not exist, return -1.

You can't access the Binary Matrix directly. You may only access the matrix using a BinaryMatrix interface:

BinaryMatrix.get(row, col) returns the element of the matrix at index (row, col) (0-indexed).
BinaryMatrix.dimensions() returns the dimensions of the matrix as a list of 2 elements [rows, cols], which means the matrix is rows x cols.
Submissions making more than 1000 calls to BinaryMatrix.get will be judged Wrong Answer. Also, any solutions that attempt to circumvent the judge will result in disqualification.

For custom testing purposes, the input will be the entire binary matrix mat. You will not have access to the binary matrix directly.

 

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
mat[i] is sorted in non-decreasing order.

*/
#include <vector>
using std::vector;

/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class LeftMostColumnWithOne {

    class BinaryMatrix {
    public:
      int get(int row, int col);
      vector<int> dimensions();
    };

public:

    int doit_best(BinaryMatrix &binaryMatrix) {
        
        auto d = binaryMatrix.dimensions();
        int m = d[0], n = d[1];
        int row = 0, col = n-1;
        
        while (row < m && col >= 0) {

            if (binaryMatrix.get(row, col) == 1) {
                col--;
            } else {
                row++;
            }
        }
        
        return col == n-1 ? -1 : col+1;
    }


    /*
        Approach 3: Start at Top Right, Move Only Left and Down
        Intuition

        Did you notice in Approach 2 that we didn't need to finish searching all the rows? One example of this was row 3 on the example in the animation. 
        At the point shown in the image below, it was clear that row 3 could not possibly be better than the minimum we'd found so far.

        Diagram showing redundant search in Row 3

        Therefore, an optimization we could have made was to keep track of the minimum index so far, and then abort the search on any rows where we have discovered a 0 at, or to the right of, that minimum index.

        We can do even better than that; on each search, we can set hi = smallest_index - 1, where smallest_index is the smallest index of a 1 we've seen so far. 
        In most cases, this is a substantial improvement. It works because we're only interested in finding 1s at lower indexes than we previously found. 
        Here is an animation of the above example with this optimized algorithm. The algorithm eliminates as many cells as it can with each API call. 
        It also starts by checking the last cell of the row before proceeding with the binary search, to eliminate needless binary searches where the row only had 0s left in it.

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

        Time complexity : O(N + M).

        At each step, we're moving 1 step left or 1 step down. Therefore, we'll always finish looking at either one of the M rows or N columns. 
        Therefore, we'll stay in the grid for at most N + M steps, and therefore get a time complexity of O(N + M).

        Space complexity : O(1).

        We are using constant extra space.
    
    */
    int doit_search(BinaryMatrix &binaryMatrix) {

        auto size = binaryMatrix.dimensions();
        int m = size[0], n = size[1];

        // Set pointers to the top-right corner.
        int i = 0, j = n-1;
        
        // Repeat the search until it goes off the grid.
        while (j >= 0 && i < m) {
            if (binaryMatrix.get(i, j) == 1)
                j--;
            else
                i++;
        }

        // If we never left the last column, this is because it was all 0's.
        return j == n - 1 ? -1 : j + 1;
    }

    /*
        Approach 2: Binary Search Each Row

        Intuition

        This isn't the best approach, but it passes, and coding it up is a good opportunity to practice binary search.

        When linear search is too slow, we should try to find a way to use binary search. If you're not familiar with binary search, check out this Explore Card!. We recommend doing the first couple of binary search questions to get familiar with the algorithm before coming back to this problem.

        Also, have a go at First Bad Version. The only difference between that problem and this one is that instead of 0 and 1, it uses false and true.

        Like we did with the linear search, we're going to apply binary search independently on each row. The target element we're searching for is the first 1 in the row.

        The core part of a binary search algorithm is how it decides whether the target element is to the left or the right of the middle element. Let's figure this out by thinking through a couple of examples.

        In the row below, we've determined that the middle element is a 0. On what side must the target element (first 1) be? The left, or the right? Don't forget, all the 0's are before all the 1's.

        Diagram showing a single uncovered 0 at the "middle" index

        In this next row, the middle element is a 1? What side must the target element be on? Could it also possibly be the 1 we just found?

        Diagram showing a single uncovered 1 at the "middle" index

        For the first example, we can conclude that the target element (if it exists) must be to the right of the middle element. This is because we know that everything to the left of a 0 must also be a 0,

        For the second example, we can conclude that the target element is either the middle element itself or it is some other 1 to the left of the middle element. We know that everything to the right of a 1 is also a 1, but these can't possibly be further left than the one we just found.

        In summary, if the middle element is a:

        0, then the target must be to the right.
        1, then the target is either this element or to the left.
        We can then put this together into an algorithm that finds the index of the target element (first 1) in each row, and then returns the minimum of those indexes. Here is an animation of how that algorithm would look. The light grey numbers are the ones that we could infer without needing to make an API call. They are only there to help you understand.

        Current
        1 / 33
        Algorithm

        If you're already quite familiar with binary search, feel free to skip down to the implementation below. I've decided to include lots of details here, as binary search is one of those algorithms that a lot of people get frustrated with easily and find it difficult to master.

        In a binary search, we always keep track of the range that the target might be in by using two variables: lo to represent the lowest possible index it could be, and hi to represent the highest possible index it could be. Ignoring the binaryMatrix API details for the moment, here is a rough outline of our binary search in pseudocode.

        define function binary_search(input_list):
            lo = the lowest possible index
            hi = the highest possible index
            while the search space contains 2 or more items:
                mid = the middle index in the remaining search space
                if the element at input_list[mid] is 0:
                    lo = mid + 1 (the first 1 is *further right*, and can't be mid itself)
                else:
                    hi = mid (the first 1 is either mid itself, *or is further left*)
            return the only index remaining in the search space
        As always in binary search, there are a couple more key implementation details we still need to deal with:

        An even-length search space has two middles. Which do we choose?
        The row might be all 0's.
        Let's tackle these issues one at a time.

        The first issue, the choice of middle, is important, as otherwise, the search space might stop shrinking when it gets down to two elements. When the search space doesn't shrink, the algorithm does the exact same thing the next loop cycle, resulting in an infinite loop. Remember that when the search space only contains two elements, they are the ones pointed to by lo and hi. This means that the lower middle equals lo, and the upper-middle equals hi. We, therefore, need to think about which cases would shrink the search space, and which would not.

        If we use the lower-middle

        If it is a 0, then we set lo = mid + 1. Because hi == mid + 1, this means that lo == hi (search space is of length-one).
        If it is a 1, then we set hi = mid. Because mid == lo, this means that hi == lo (search space is of length-one).
        If we use the upper-middle

        If it is a 0, then we set lo = mid + 1. Because hi = mid, we now have hi > lo (search space is of length-zero).
        If it is a 1, then we set hi = mid. Because hi == mid was already true, the search space stays as is (of length-two).
        If we use the lower-middle, we know the search space will always shrink. If we use the upper-middle, it might not. Therefore, we should go with the lower-middle. The formula for this is mid = (low + high) / 2.

        The second issue, a row of all zeroes, is solved by recognizing that the algorithm always shrinks down the search space to a single element. This is supposed to be the first 1, but if that doesn't exist, then it has to be a 0. Therefore, we can detect this case by checking whether or not the last element in the search space is a 1.

        It is good practice to think these details through carefully so that you can write your binary search algorithm decisively and confidently. Resist the urge to Program by Permutation!

        Anyway, putting this all together, we get the following code.


        Complexity Analysis

        Let NN be the number of rows, and MM be the number of columns.

        Time complexity : O(N \, \log \, M)O(NlogM).

        There are MM items in each row. Therefore, each binary search will have a cost of O(\log \, M)O(logM). We are performing NN of these binary searches, giving a time complexity of N \cdot O(\log \, M) = O(N \, \log \, M)N⋅O(logM)=O(NlogM).

        Space complexity : O(1)O(1).

        We are using constant extra space.
    */
    int doit_bruteforce(BinaryMatrix &binaryMatrix) {
        
        auto size = binaryMatrix.dimensions();
        int m = size[0], n = size[1];

        int leftmost = n;

        for (int i = 0; i < m; i++) {

            int left = 0, right = n;

            while (left < right) {
                int mid = (left + right) / 2;

                if (binaryMatrix.get(i, mid) == 1) {
                    right = mid;
                } else {
                    left = mid + 1;
                } 
            }

            leftmost = std::min(left, leftmost);
        }

        return leftmost == n ? -1 : leftmost;
    }

    /*
        Approach 1: Linear Search Each Row
        Intuition

        This approach won't pass, but we'll use it as a starting point. Also, it might be helpful to you if you just needed an example of how to use the API, but don't want to see a complete solution yet!

        The leftmost 1 is the 1 with the lowest column index.

        The problem can be broken down into finding the index of the first 1 in each row and then taking the minimum of those indexes.

        Diagram showing a linear search that has uncovered all the zeroes, along with the first 1 in each row.

        The simplest way of doing this would be a linear search on each row.

        Algorithm


        Complexity Analysis

        If you ran this code, you would have gotten the following error.

        You made too many calls to BinaryMatrix.get().
        The maximum grid size is 100 by 100, so it would contain 10000 cells. In the worst case, the linear search algorithm we implemented has to check every cell. With the problem description telling us that we can only make up to 1000 API calls, this clearly isn't going to work.

        Let NN be the number of rows, and MM be the number of columns.

        Time complexity : O(N⋅M)

        We don't know the time complexity of binaryMatrix.get() as its implementation isn't our concern. Therefore, we can assume it's O(1)O(1).

        In the worst case, we are retrieving a value for each of the N \cdot MN⋅M cells. At O(1) per operation, this gives a total of O(N \cdot M)O(N⋅M).

        Space complexity : O(1).

        We are only using constant extra space.
    */
    int doit_bruteforce(BinaryMatrix &binaryMatrix) {

        auto size = binaryMatrix.dimensions();
        int m = size[0], n = size[1];

        int leftmost = n;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (binaryMatrix.get(i, j) == 1) {
                    leftmost = std::min(leftmost, j);
                }
            }
        }

        return leftmost == n ? -1 : leftmost;
    }
};
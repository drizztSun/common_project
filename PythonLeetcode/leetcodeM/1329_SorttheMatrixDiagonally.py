"""
1329. Sort the Matrix Diagonally

Given a m * n matrix mat of integers, sort it diagonally in ascending order from the top-left to the bottom-right then return the sorted array.



Example 1:


Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]


Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 100
1 <= mat[i][j] <= 100

"""


class SortTheMatrixDiagonally:

    """
    Approach 1: HashMap of Heaps.
    The most straightforward idea is to create a hashmap of heaps to store the diagonals.
    This way, the diagonals are automatically sorted, and one has nothing to do but to push these sorted diagonals back into the matrix.

    simple Fig 1. Approach 1: HashMap of Heaps.

    Implementation

    Complexity Analysis

    Time complexity: \mathcal{O}(N \times M \times \log (\min(N, M)))O(N×M×log(min(N,M))), where NN is a number of rows and MM is a number of columns.
    We perform N \times MN×M operations in two nested loops. At each iteration, we push an element into a heap that contains the current diagonal.
    The longest diagonal contains not more than \min(N, M)min(N,M) elements.

    Space complexity: \mathcal{O}(N \times M)O(N×M) to keep the hashmap with all input elements, where NN is a number of rows and MM is a number of columns.

    """

    def doit_heap(self, mat: list) -> list:
        from collections import defaultdict
        from heapq import heappush, heappop
        # hashmap to keep the diagonals
        h = defaultdict(list)

        # fill the hashmap
        n, m = len(mat), len(mat[0])
        for i in range(n):
            for j in range(m):
                heappush(h[i - j], mat[i][j])

        # build output
        for i in range(n):
            for j in range(m):
                mat[i][j] = heappop(h[i - j])

        return mat

    """
    Approach 2: Sort Diagonals One by One Using Heap.
    To optimize the space, we could sort diagonals one by one. That would decrease the space complexity from \mathcal{O}(N \times M)O(N×M) down to \mathcal{O}(\min(N, M))O(min(N,M)).
    Complexity Analysis

    Time complexity: \mathcal{O}(N \times M \times \log (\min(N, M)))O(N×M×log(min(N,M))), where NN is a number of rows and MM is a number of columns. We perform N \times MN×M operations in two nested loops. 
    At each iteration, we push an element into a heap that contains the current diagonal.
    The longest diagonal contains not more than \min(N, M)min(N,M) elements.
    
    Space complexity: \mathcal{O}(\min(N, M))O(min(N,M)), where NN is a number of rows and MM is a number of columns. The space is used by the heap with diagonal elements, and the longest diagonal contains not more than \min(N, M)min(N,M) elements.
    """

    def doit_sort_heap(self, mat: list) -> list:
        from heapq import heappush, heappop
        n, m = len(mat), len(mat[0])

        def sort_diagonal(i, j):
            """
            Sort the current diagonal
            """
            diagonal = []
            # store the current diagonal
            # in the heap
            while i < n and j < m:
                # max heap -> to keep max element always on top
                heappush(diagonal, -mat[i][j])
                i += 1
                j += 1

            # push the sorted values
            # back into the matrix
            while i > 0 and j > 0:
                i -= 1
                j -= 1
                mat[i][j] = -heappop(diagonal)

        # sort all diagonals
        # in the lower left corner
        for i in range(n):
            sort_diagonal(i, 0)
        # sort all diagonals
        # in the upper right corner
        for j in range(m):
            sort_diagonal(0, j)

        return mat

    """
    Approach 3: Sort Diagonals One by One Using Sort.
    This approach is a variation of Approach 2: we sort the diagonals one by one. The only difference is that instead of heap, we use built-in sort functions.
    
    """
    def doit_sort_2(self, mat: list) -> list:
        n, m = len(mat), len(mat[0])

        def sort_diagonal(i, j):
            """
            Sort the current diagonal
            """
            diagonal = []
            # store the current diagonal
            # in the list
            while i < n and j < m:
                diagonal.append(mat[i][j])
                i += 1
                j += 1

            # sort the diagonal values
            diagonal.sort()

            # push the sorted values
            # back into the matrix
            while i > 0 and j > 0:
                j -= 1
                i -= 1
                mat[i][j] = diagonal.pop()

        # sort all diagonals
        # in the lower left corner
        for i in range(n):
            sort_diagonal(i, 0)
        # sort all diagonals
        # in the upper right corner
        for j in range(m):
            sort_diagonal(0, j)

        return mat
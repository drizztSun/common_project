


# 378. Kth Smallest Element in a Sorted Matrix


# Given a n x n matrix where each of the rows and columns are sorted in ascending order,
# find the kth smallest element in the matrix.
# Note that it is the kth smallest element in the sorted order, not the kth distinct element.

# Example:

# matrix = [
#   [ 1,  5,  9],
#   [10, 11, 13],
#   [12, 13, 15]
# ],
# k = 8,
# return 13.

import heapq

class kthSmallest:
    def doit(self, matrix, k):
        """
        :type matrix: List[List[int]]
        :type k: int
        :rtype: int
        """
        n, m = len(matrix), len(matrix[0])
        buff = []

        def push(i, j):
            if i < n and j < m:
                heapq.heappush(buff, [matrix[i][j], i, j])

        push(0, 0)
        ans = -1

        while buff and k > 0:
            ans, i, j = heapq.heappop(buff)

            push(i, j+1)

            if j == 0:
                push(i+1, 0)

            k -= 1

        return ans


if __name__ == "__main__":

    res = kthSmallest().doit([
       [ 1,  5,  9],
       [10, 11, 13],
       [12, 13, 15]
     ], 8)


    pass
        
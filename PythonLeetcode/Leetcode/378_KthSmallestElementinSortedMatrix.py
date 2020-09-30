"""
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
"""

import heapq


class KthSmallest:

    def doit_binary_search(self, matrix, k):

        def search(mid):
            j = len(matrix[0]) - 1
            count = 0
            for i in range(len(matrix)):
                while j >= 0 and matrix[i][j] > mid:
                    j -= 1
                count += j+1
            return count

        low, high = matrix[0][0], matrix[-1][-1]

        while low < high:

            mid = (low + high) >> 1

            if search(mid) >= k:
                high = mid
            else:
                low = mid+1

        return low


    def doit_heap(self, matrix, k):
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

    res = KthSmallest().doit_binary_search([
       [ 1,  5,  9],
       [10, 11, 13],
       [12, 13, 15]
     ], 8)

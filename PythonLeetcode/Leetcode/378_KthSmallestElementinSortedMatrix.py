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



    def kthSmallest(self, matrix, k):

        def countLessEqual(matrix, mid, smaller, larger):

            count, n = 0, len(matrix)
            row, col = n - 1, 0

            while row >= 0 and col < n:
                if matrix[row][col] > mid:

                    # As matrix[row][col] is bigger than the mid, let's keep track of the
                    # smallest number greater than the mid
                    larger = min(larger, matrix[row][col])
                    row -= 1

                else:

                    # As matrix[row][col] is less than or equal to the mid, let's keep track of the
                    # biggest number less than or equal to the mid

                    smaller = max(smaller, matrix[row][col])
                    count += row + 1
                    col += 1

            return count, smaller, larger

        n = len(matrix)
        start, end = matrix[0][0], matrix[n - 1][n - 1]
        while start < end:
            mid = start + (end - start) / 2
            smaller, larger = (matrix[0][0], matrix[n - 1][n - 1])

            count, smaller, larger = countLessEqual(matrix, mid, smaller, larger)

            if count == k:
                return smaller
            if count < k:
                start = larger  # search higher
            else:
                end = smaller  # search lower

        return start

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

    def kthSmallest(self, matrix, k: int) -> int:

        # The size of the matrix
        N = len(matrix)

        # Preparing our min-heap
        minHeap = []
        for r in range(min(k, N)):
            # We add triplets of information for each cell
            minHeap.append((matrix[r][0], r, 0))

        # Heapify our list
        heapq.heapify(minHeap)

        # Until we find k elements
        while k:

            # Extract-Min
            element, r, c = heapq.heappop(minHeap)

            # If we have any new elements in the current row, add them
            if c < N - 1:
                heapq.heappush(minHeap, (matrix[r][c + 1], r, c + 1))

            # Decrement k
            k -= 1

        return element


if __name__ == "__main__":

    res = KthSmallest().doit_binary_search([
       [ 1,  5,  9],
       [10, 11, 13],
       [12, 13, 15]
     ], 8)

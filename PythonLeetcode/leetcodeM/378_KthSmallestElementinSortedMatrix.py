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

    """
        It's O(n) where n is the number of rows (and columns), not the number of elements. So it's very efficient. The algorithm is from the paper Selection in X + Y and matrices with sorted rows and columns, which I first saw mentioned by @elmirap (thanks).

        The basic idea: Consider the submatrix you get by removing every second row and every second column.
        This has about a quarter of the elements of the original matrix. And the k-th element (k-th smallest I mean) of the original matrix is roughly the (k/4)-th element of the submatrix. So roughly get the (k/4)-th element of the submatrix and then use that to find the k-th element of the original matrix in O(n) time.
        It's recursive, going down to smaller and smaller submatrices until a trivial 2×2 matrix. For more details I suggest checking out the paper, the first half is easy to read and explains things well. Or @zhiqing_xiao's solution+explanation.

        Cool: It uses variants of saddleback search that you might know for example from the Search a 2D Matrix II problem. And it uses the median of medians algorithm for linear-time selection.

        Optimization: If k is less than n, we only need to consider the top-left k×k matrix. Similar if k is almost n2. So it's even O(min(n, k, n^2-k)), I just didn't mention that in the title because I wanted to keep it simple and because those few very small or very large k are unlikely, most of the time k will be "medium" (and average n2/2).

        Implementation: I implemented the submatrix by using an index list through which the actual matrix data gets accessed. If [0, 1, 2, ..., n-1] is the index list of the original matrix, then [0, 2, 4, ...] is the index list of the submatrix and [0, 4, 8, ...] is the index list of the subsubmatrix and so on.
        This also covers the above optimization by starting with [0, 1, 2, ..., k-1] when applicable.

        Application: I believe it can be used to easily solve the Find K Pairs with Smallest Sums problem in time O(k) instead of O(k log n), which I think is the best posted so far. I might try that later if nobody beats me to it (if you do, let me know :-). Update: I did that now.
    """

    def kthSmallest(self, matrix, k):

        # The median-of-medians selection function.
        def pick(a, k):
            if k == 1:
                return min(a)
            groups = (a[i:i + 5] for i in range(0, len(a), 5))
            medians = [sorted(group)[len(group) / 2] for group in groups]
            pivot = pick(medians, len(medians) / 2 + 1)
            smaller = [x for x in a if x < pivot]
            if k <= len(smaller):
                return pick(smaller, k)
            k -= len(smaller) + a.count(pivot)
            return pivot if k < 1 else pick([x for x in a if x > pivot], k)

        # Find the k1-th and k2th smallest entries in the submatrix.
        def biselect(index, k1, k2):

            # Provide the submatrix.
            n = len(index)

            def A(i, j):
                return matrix[index[i]][index[j]]

            # Base case.
            if n <= 2:
                nums = sorted(A(i, j) for i in range(n) for j in range(n))
                return nums[k1 - 1], nums[k2 - 1]

            # Solve the subproblem.
            index_ = index[::2] + index[n - 1 + n % 2:]
            k1_ = (k1 + 2 * n) / 4 + 1 if n % 2 else n + 1 + (k1 + 3) / 4
            k2_ = (k2 + 3) / 4
            a, b = biselect(index_, k1_, k2_)

            # Prepare ra_less, rb_more and L with saddleback search variants.
            ra_less = rb_more = 0
            L = []
            jb = n  # jb is the first where A(i, jb) is larger than b.
            ja = n  # ja is the first where A(i, ja) is larger than or equal to a.
            for i in range(n):
                while jb and A(i, jb - 1) > b:
                    jb -= 1
                while ja and A(i, ja - 1) >= a:
                    ja -= 1
                ra_less += ja
                rb_more += n - jb
                L.extend(A(i, j) for j in range(jb, ja))

            # Compute and return x and y.
            x = a if ra_less <= k1 - 1 else \
                b if k1 + rb_more - n * n <= 0 else \
                    pick(L, k1 + rb_more - n * n)
            y = a if ra_less <= k2 - 1 else \
                b if k2 + rb_more - n * n <= 0 else \
                    pick(L, k2 + rb_more - n * n)
            return x, y

        # Set up and run the search.
        n = len(matrix)
        start = max(k - n * n + n - 1, 0)
        k -= n * n - (n - start) ** 2
        return biselect(range(start, min(n, start + k)), k, k)[0]

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

    """
    Complexity Analysis
    
    Time Complexity: \text{let X=} \text{min}(K, N); X + K \log(X)let X=min(K,N);X+Klog(X)
    
    Well the heap construction takes O(X)O(X) time.
    After that, we perform KK iterations and each iteration has two operations. We extract the minimum element from a heap containing XX elements. 
    Then we add a new element to this heap. Both the operations will take O(\log(X))O(log(X)) time.
    
    Thus, the total time complexity for this algorithm comes down to be O(X + K\log(X))O(X+Klog(X)) where XX is \text{min}(K, N)min(K,N).
    Space Complexity: O(X)O(X) which is occupied by the heap.
    """
    def doit_heap_kthSmallest(self, matrix, k: int) -> int:

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

    """
    Complexity Analysis

    Time Complexity: O(N \times log(\text{Max}-\text{Min}))O(N×log(Max−Min))
    
    Let's think about the time complexity in terms of the normal binary search algorithm. For a one-dimensional binary search over an array with NN elements, 
    the complexity comes out to be O(log(N)).
    
    For our scenario, we are kind of defining our binary search space in terms of the minimum and the maximum numbers in the array. 
    Going by this idea, the complexity for our binary search should be O(log(\text{Max}-\text{Min}))O(log(Max−Min)) 
    where \text{Max}Max is the maximum element in the array and likewise, \text{Min}Min is the minimum element.
    However, we update our search space after each iteration. So, even if the maximum element is super large as compared to the remaining elements in the matrix, 
    we will bring down the search space considerably in the next iterations. But, going purely by the extremes for our search space, 
    the complexity of our binary search in search of K^{\text{th}}K 
    th
      smallest element will be O(log(\text{Max}-\text{Min}))O(log(Max−Min)).
    In each iteration of our binary search approach, we iterate over the matrix trying to determine the size of the left-half as explained before. That takes O(N)O(N).
    Thus, the overall time complexity is O(N \times log(\text{Max}-\text{Min}))O(N×log(Max−Min))
    Space Complexity: O(1)O(1) since we don't use any additional space for performing our binary search.
        
    """
    def doit_binary_search(matrix: list, k: int) -> int:

        def countLessEqual(self, matrix, mid, smaller, larger):

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


if __name__ == "__main__":

    res = KthSmallest().doit_binary_search([
       [ 1,  5,  9],
       [10, 11, 13],
       [12, 13, 15]
     ], 8)

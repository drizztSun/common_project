"""
1439. Find the Kth Smallest Sum of a Matrix With Sorted Rows

You are given an m * n matrix, mat, and an integer k, which has its rows sorted in non-decreasing order.

You are allowed to choose exactly 1 element from each row to form an array. Return the Kth smallest array sum among all possible arrays.

Example 1:

Input: mat = [[1,3,11],[2,4,6]], k = 5
Output: 7
Explanation: Choosing one element from each row, the first k smallest sum are:
[1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.

Example 2:

Input: mat = [[1,3,11],[2,4,6]], k = 9
Output: 17
Example 3:

Input: mat = [[1,10,10],[1,4,5],[2,3,6]], k = 7
Output: 9
Explanation: Choosing one element from each row, the first k smallest sum are:
[1,1,2], [1,1,3], [1,4,2], [1,4,3], [1,1,6], [1,5,2], [1,5,3]. Where the 7th sum is 9.

Example 4:

Input: mat = [[1,1,10],[2,2,9]], k = 7
Output: 12


Constraints:

m == mat.length
n == mat.length[i]
1 <= m, n <= 40
1 <= k <= min(200, n ^ m)
1 <= mat[i][j] <= 5000
mat[i] is a non decreasing array.
"""


class kthSmallest(object):

    """
    Intuition:
    We need to keep at most 200 smallest sums. 1 <= k <= min(200, n ^ m)
    For the input with one row the answer is the smallest k-th element or top of the max priority queue of size k.

    Algorithm:
    Calculate max priority queue of sizr k for the first row.

    Add the rest rows one by one to the max priority queue and make sure that max priority queue size is less than or equal to k.

    Time: O(m * n * k * log(k))
    Space: O(k)
    """
    def doit_heap(self, mat, k):
        """
        :type mat: List[List[int]]
        :type k: int
        :rtype: int
        """
        import heapq
        rows, cols = len(mat), len(mat[0])

        # choose exactly 1 element from each row as the sum
        index = [0] * rows
        val = sum([row[0] for row in mat])

        heap = []
        heapq.heappush(heap, [val, index, 0])

        for _ in range(k):
            val, n_idx, row = heapq.heappop(heap)
            res = val

            for i in range(row, rows):

                n_idx = list(n_idx)
                n_idx[i] += 1

                if (j := n_idx[i]) < cols:
                    n_val = val + mat[i][j] - mat[i][j - 1]
                    heapq.heappush(heap, [n_val, n_idx, i])
        return res

    """
    Since 1 <= mat[i][j] <= 5000, m <= 40, we can do binary search for our target kth smallest sum in range [m, 5000*m]
    For each sum, we use backtracking to count the number of array whose sum is less than or equal to sum, prune when count > k
    If we found a sum that count >= k, we record current ans = sum, try to find better answer in the left side.
    Else try to find in the right side.
    Complexity
    
    Time: O(m * k * log(5000*m)), where m <= 40 is the number of rows, k <= min(200, n^m)
    
    countArraysHaveSumLessOrEqual() can run up to (m-i+1) * min(k,n^i), 1<=i<=m times. And n^i can go up to k very quickly while i is small, so time complexity will be O(m*k)
    Can check the following picture to understand more about complexity:
    
        Credit @yuhan-wang for provide the example
    binary search to find targetSum in range [m, 5000*m] costs log(5000*m)
    Space: O(m), it's the depth of recursion
    """
    def doit_binary_search(self, mat, k):
        m, n = len(mat), len(mat[9])

        def search(target, i, total, k):

            if target < total:
                return 0

            # no more row, total > target, count 1
            if i == m:
                return 1

            ans = 0
            for j in range(n):

                cnt = search(target, i + 1, total + mat[i][j], k - ans)
                if cnt == 0:
                    break

                ans += cnt
                if ans > k:
                    break

            return ans

        left, right = sum(mat[i][0] for i in range(m)), sum(mat[i][n-1] for i in range(m))
        ans = -1

        while left <= right:

            mid = (left + right) / 2

            res = search(mid, 0, 0, k)

            if res >= k:
                ans = mid
                right = mid - 1
            else:
                left = mid + 1

        return ans


if __name__ == '__main__':

    #kthSmallest().doit_binary_search(mat = [[1,3,11],[2,4,6]], k=5)

    #kthSmallest().doit_binary_search(mat = [[1,3,11],[2,4,6]], k=9)

    kthSmallest().doit_heap(mat = [[1,10,10],[1,4,5],[2,3,6]], k=7)
# 915. Partition Array into Disjoint Intervals

# Given an array A, partition it into two (contiguous) subarrays left and right so that:

# Every element in left is less than or equal to every element in right.
# left and right are non-empty.
# left has the smallest possible size.
# Return the length of left after such a partitioning.  It is guaranteed that such a partitioning exists.


# Example 1:

# Input: [5,0,3,8,6]
# Output: 3
# Explanation: left = [5,0,3], right = [8,6]
# Example 2:

# Input: [1,1,1,0,6,12]
# Output: 4
# Explanation: left = [1,1,1,0], right = [6,12]


# Note:

# 2 <= A.length <= 30000
# 0 <= A[i] <= 10^6
# It is guaranteed there is at least one way to partition A as described.

class PartitionDisjoint:

    """
    Approach 1: Next Array
    Intuition

    Instead of checking whether all(L <= R for L in left for R in right), let's check whether max(left) <= min(right).

    Algorithm

    Let's try to find max(left) for subarrays left = A[:1], left = A[:2], left = A[:3], ... etc. Specifically,
    maxleft[i] will be the maximum of subarray A[:i]. They are related to each other: max(A[:4]) = max(max(A[:3]), A[3]), so maxleft[4] = max(maxleft[3], A[3]).

    Similarly, min(right) for every possible right can be found in linear time.

    After we have a way to query max(left) and min(right) quickly, the solution is straightforward.

    Complexity Analysis

    Time Complexity: O(N), where NN is the length of A.

    Space Complexity: O(N).
    """

    def doit(self, A):
            N = len(A)
        maxleft = [None] * N
        minright = [None] * N

        m = A[0]
        for i in range(N):
            m = max(m, A[i])
            maxleft[i] = m

        m = A[-1]
        for i in range(N-1, -1, -1):
            m = min(m, A[i])
            minright[i] = m

        for i in range(1, N):
            if maxleft[i-1] <= minright[i]:
                return i

    def doit(self, A):

        left = [(A[0], A[0])]
        for c in A[1:]:
            left.append((max(left[-1][0], c), min(left[-1][1], c)))

        right = [(A[-1], A[-1])]
        for c in reversed(A[:-1]):
            right.append((max(right[-1][0], c), min(right[-1][1], c)))

        for i in range(len(left)-1):
            if left[i][0] <= right[-(i+2)][1]:
                return i+1


        def partitionDisjoint(self, A: List[int]) -> int:
            curr_num=A[0]

    def doit(self, A):
        i = 1
        while i<len(A):
            if curr_num > A[i]:
                i += 1
            else:
                bigger_num = A[i]
                j = i+1
                while j < len(A) and curr_num <= A[j]:
                    if bigger_num < A[j]:
                        bigger_num = A[j]
                    j += 1
                if j >= len(A):
                    return i
                else:
                    curr_num = bigger_num
                    i = j

if __name__ == '__main__':

    res = PartitionDisjoint().doit([5, 0, 3, 8, 6])  # 3

    res = PartitionDisjoint().doit([1, 1, 1, 0, 6, 12])  # 4

    pass

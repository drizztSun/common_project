# 1031. Maximum Sum of Two Non-Overlapping Subarrays

# Given an array A of non-negative integers, return the maximum sum of elements in two non-overlapping (contiguous) subarrays,
# which have lengths L and M.  (For clarification, the L-length subarray could occur before or after the M-length subarray.)

# Formally, return the largest V for which V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ... + A[j+M-1]) and either:

# 0 <= i < i + L - 1 < j < j + M - 1 < A.length, or
# 0 <= j < j + M - 1 < i < i + L - 1 < A.length.


# Example 1:

# Input: A = [0, 6, 5, 2, 2, 5, 1, 9, 4], L = 1, M = 2
# Output: 20
# Explanation: One choice of subarrays is [9] with length 1, and [6, 5] with length 2.

# Example 2:

# Input: A = [3, 8, 1, 3, 2, 1, 8, 9, 0], L = 3, M = 2
# Output: 29
# Explanation: One choice of subarrays is [3, 8, 1] with length 3, and [8, 9] with length 2.

# Example 3:

# Input: A = [2, 1, 5, 6, 0, 9, 5, 0, 3, 8], L = 4, M = 3
# Output: 31
# Explanation: One choice of subarrays is [5, 6, 0, 9] with length 4, and [3, 8] with length 3.


# Note:

# L >= 1
# M >= 1
# L + M <= A.length <= 1000
# 0 <= A[i] <= 1000

class MaxSumTwoNoOverlap:

    def doit(self, A, L, M):

        L_Arr, M_Arr = [[0, 0]
                        for _ in range(len(A))], [[0, 0] for _ in range(len(A))]
        lwnd, mwnd = 0, 0

        for i in range(len(A)):

            lwnd += A[i]
            if i - L >= -1:
                L_Arr[i][0] = lwnd
                if i - L >= 0:
                    L_Arr[i - L][1] = lwnd
                lwnd -= A[i-L+1]

            mwnd += A[i]
            if i - M >= -1:
                M_Arr[i][0] = mwnd
                if i - M >= 0:
                    M_Arr[i - M][1] = mwnd
                mwnd -= A[i-M+1]

        for i in range(1, len(A)):
            L_Arr[i][0] = max(L_Arr[i][0], L_Arr[i-1][0])
            M_Arr[i][0] = max(M_Arr[i][0], M_Arr[i-1][0])

        for i in range(len(A)-1):
            L_Arr[i][1] = max(L_Arr[i][1], L_Arr[i+1][1])
            M_Arr[i][1] = max(M_Arr[i][1], M_Arr[i+1][1])

        ans = 0
        for i in range(len(A)):
            ans = max(ans, L_Arr[i][0] + M_Arr[i][1], L_Arr[i][1] + M_Arr[i][0])

        return ans

    """
    The methodology here is to use two sliding windows, one on the left (l) and one on the right (m), to cover the array provided, and keep track of the highest sum under the left window, and the highest sum total. Note that we can't keep track of the highest sum under the right window, because with each slide the left window will take an item from the right window, so if we kept both sum maxes instead of the left sum max and the overall sum max, we could be double dipping.

    By the time we've advanced each window all the way to the right, we've got the maximum sums for each as if we'd stopped advancing each window when it was over the ideal subarray.

    Each window is represented as a double-ended queue (Python's deque implementation under collections). Time complexity is O(n) though we run through A twice, and space complexity is O(n+l+m) accounting for both the input and the two double-ended queues.

    Final important point before we get into the code: the two windows could appear in either order (l then m or m then l), but our algorithm assumes l is to the left, so we run it twice with l and m switched the second time.
    """

    def doit(self, A, L, M):
        # Take the best result of the two possible orders for the l and m windows
        return max(slidingWindows(A, L, M), slidingWindows(A, M, L))

        def slidingWindows(A, L, M):
            from collections import deque
            # Create deques and starting sums for the 'l' and 'm' sliding windows
            lQ = deque(maxlen=L)
            mQ = deque(maxlen=M)
            lSum = 0
            mSum = 0

            # Fill deques and sums with their appropriate starter values, l then m
            for i in range(L):
                lQ.append(A[i])
                lSum += A[i]

            for j in range(i+1, i+1+M):
                mQ.append(A[j])
                mSum += A[j]

            # Slide windows, retaining the max sums for the left (l) deque and overall
            maxLSum = lSum
            maxOverall = maxLSum + mSum
            for k in range(j+1, len(A)):
                # Shift the leftmost elem from mQ into lQ and the next elem into mQ
                shiftedFromM = mQ.popleft()
                shiftedFromL = lQ.popleft()
                lQ.append(shiftedFromM)
                mQ.append(A[k])

                # Update the deque sums to account for the shifts in and out
                lSum = lSum - shiftedFromL + shiftedFromM
                mSum = mSum - shiftedFromM + A[k]

                # Update the max sums for the left deque and overall
                maxLSum = max(maxLSum, lSum)
                maxOverall = max(maxOverall, maxLSum + mSum)

            return maxOverall


if __name__ == '__main__':

    res = MaxSumTwoNoOverlap().doit(A=[0, 6, 5, 2, 2, 5, 1, 9, 4], L=1, M=2)

    res = MaxSumTwoNoOverlap().doit(A=[3, 8, 1, 3, 2, 1, 8, 9, 0], L=3, M=2)

    res = MaxSumTwoNoOverlap().doit(A=[2, 1, 5, 6, 0, 9, 5, 0, 3, 8], L=4, M=3)

    pass

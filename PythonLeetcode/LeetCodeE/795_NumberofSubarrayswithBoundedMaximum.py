# 795 Number of Subarrays with Bounded Maximum

# We are given an array A of positive integers, and two positive integers L and R (L <= R).

# Return the number of (contiguous, non-empty) subarrays such that the value of the maximum array element in that subarray is at least L and at most R.

# Example :
# Input:
# A = [2, 1, 4, 3]
# L = 2
# R = 3
# Output: 3
# Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
# Note:

# L, R  and A[i] will be an integer in the range [0, 10^9].
# The length of A will be in the range of [1, 50000].


class NumSubarrayBoundedMax:

    # Whenever we come accross any counting subarray type of questions, the approach is to use two pointer and maintain a counter "num_subarrays" to keep the count of number of subarrays.
    # Let i, j be the two pointers, then total number of subarrays from i:j is num_subarrays += (j-i+1). see below for eg.
    # [1 2 3]
    # i | j | num_subarrays
    # 0 | 0 | 0 + (0-0+1) = 1
    # 0 | 1 | 1 + (1-0+1) = 3
    # 0 | 2 | 3 + (2-0+1) = 6

    # total subarrays is 6!

    # We have to use the same strategy here whenever the currently element is between [L,R].
    # If the element is below L, then we add the previous count the subarray.
    # If the element is above R, then we change the i = j + 1 and reset the prev value.

    # Python

    def doit(self, A, L, R):
        i = j = count = prev = 0
        while(j < len(A)):
            if (L <= A[j] <= R):
                prev = j - i + 1
                count += prev
            elif (A[j] < L):
                count += prev
            else:
                i = j+1
                prev = 0
            j += 1
        return count


if __name__ == '__main__':

    res = NumSubarrayBoundedMax().doit([2, 1, 4, 3], 2, 3)  # 3

    # 7 [2] [2] [2, 5] [2, 5, 6], [5, 6], [5], [6]
    res = NumSubarrayBoundedMax().doit([2, 9, 2, 5, 6], 2, 8)

    # 22
    res = NumSubarrayBoundedMax().doit(
        [73, 55, 36, 5, 55, 14, 9, 7, 72, 52], 32, 69)

    pass

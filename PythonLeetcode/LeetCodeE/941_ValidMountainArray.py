# 941. Valid Mountain Array

# Given an array A of integers, return true if and only if it is a valid mountain array.

# Recall that A is a mountain array if and only if:

# A.length >= 3
# There exists some i with 0 < i < A.length - 1 such that:
# A[0] < A[1] < ... A[i-1] < A[i]
# A[i] > A[i+1] > ... > A[A.length - 1]

# Example 1:

# Input: [2,1]
# Output: false

# Example 2:

# Input: [3,5,5]
# Output: false

# Example 3:

# Input: [0,3,2,1]
# Output: true


class ValidMountainArray:

    def doit(self, A):

        inc, dec = False, False

        for i in range(len(A)-1):

            if A[i] < A[i+1]:
                if dec:
                    return False
                inc = True
            elif A[i] > A[i+1]:
                if not inc:
                    return False
                dec = True
            else:
                return False

        return inc and dec

    """
    Approach 1: One Pass
    Intuition

    If we walk along the mountain from left to right, we have to move strictly up, then strictly down.

    Algorithm

    Let's walk up from left to right until we can't: that has to be the peak. We should ensure the peak is not the first or last element.
    Then, we walk down. If we reach the end, the array is valid, otherwise its not.

    Complexity Analysis

    Time Complexity: O(N), where NN is the length of A.

    Space Complexity: O(1).
    """

    def doit(self, A):
        N = len(A)
        i = 0

        # walk up
        while i+1 < N and A[i] < A[i+1]:
            i += 1

        # peak can't be first or last
        if i == 0 or i == N-1:
            return False

        # walk down
        while i+1 < N and A[i] > A[i+1]:
            i += 1

        return i == N-1


if __name__ == '__main__':

    res = ValidMountainArray().doit([2, 1])

    res = ValidMountainArray().doit([3, 5, 5])

    res = ValidMountainArray().doit([0, 3, 2, 1])

    pass

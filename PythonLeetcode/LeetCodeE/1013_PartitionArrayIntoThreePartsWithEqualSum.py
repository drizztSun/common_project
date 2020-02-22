# 1013. Partition Array Into Three Parts With Equal Sum

# Given an array A of integers, return true if and only if we can partition the array into three non-empty parts with equal sums.

# Formally, we can partition the array if we can find indexes i+1 < j with
# (A[0] + A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... + A[A.length - 1])


# Example 1:

# Input: [0,2,1,-6,6,-7,9,1,2,0,1]
# Output: true
# Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1

# Example 2:

# Input: [0,2,1,-6,6,7,9,-1,2,0,1]
# Output: false

# Example 3:

# Input: [3,3,6,5,-2,2,5,1,-9,4]
# Output: true
# Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4

class CanThreePartsEqualSum:

    def doit(self, A):

        total = sum(A)
        if len(A) < 3 or total % 3 != 0:
            return False

        l, r, ave = 0, 0, total // 3
        for i in range(len(A)):
            l += A[i]
            if l == ave:
                break

        for j in range(len(A)-1, -1, -1):
            r += A[j]
            if r == ave:
                break

        return i < j and sum(A[i+1:j]) == ave

    def doit1(self, A):

        left, right, temp, k, n = 0, 0, 0, sum(A) // 3, len(A)
        for i, a in enumerate(A):  # left part (forward)
            temp += a
            if temp == k:
                left = i  # left boundary
                break
        temp = 0  # reset
        for j, a in reversed(list(enumerate(A))):  # right part (backward)
            temp += a
            if temp == k:
                right = j  # right boundary
                break
        return sum(A[left + 1:right]) == k and left < right


if __name__ == '__main__':

    res = CanThreePartsEqualSum().doit([0, 2, 1, -6, 6, -7, 9, 1, 2, 0, 1])

    res = CanThreePartsEqualSum().doit([0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1])

    res = CanThreePartsEqualSum().doit([3, 3, 6, 5, -2, 2, 5, 1, -9, 4])

    res = CanThreePartsEqualSum().doit([18, 12, -18, 18, -19, -1, 10, 10])

    pass

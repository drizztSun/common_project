# 1005. Maximize Sum Of Array After K Negations

# Given an array A of integers, we must modify the array in the following way:
# we choose an i and replace A[i] with -A[i], and we repeat this process K times in total.
# (We may choose the same index i multiple times.)

# Return the largest possible sum of the array after modifying it in this way.


# Example 1:

# Input: A = [4,2,3], K = 1
# Output: 5
# Explanation: Choose indices (1,) and A becomes [4,-2,3].

# Example 2:

# Input: A = [3,-1,0,2], K = 3
# Output: 6
# Explanation: Choose indices (1, 2, 2) and A becomes [3,1,0,2].

# Example 3:

# Input: A = [2,-3,-1,5,-4], K = 2
# Output: 13
# Explanation: Choose indices (1, 4) and A becomes [2,3,-1,5,4].


# Note:

# 1 <= A.length <= 10000
# 1 <= K <= 10000
# -100 <= A[i] <= 100

class LargestSumAfterKNegations:
    def doit(self, A, K):

        A.sort()

        i = 0
        while K > 0 and i < len(A):
            if A[i] < 0:
                A[i] = -A[i]
                K -= 1
            elif A[i] == 0:
                return sum(A)
            else:
                break
            i += 1

        total = sum(A)

        if K % 2 == 0:
            return total
        elif K % 2 == 1:
            return max(total - 2 * A[i], total - 2 * A[i-1]) if i != 0 else total - 2 * A[i]

    def doit(self, A, K):

        A.sort()
        ret = 0

        for i in range(len(A)):
            if (K):
                if (A[i] < 0):
                    ret += -A[i]
                    K -= 1
                elif (A[i] == 0):
                    K = 0
                else:
                    if (K & 1):
                        if (i == 0 or -A[i - 1] > A[i]):
                            ret -= A[i]
                        else:
                            ret += A[i] + 2 * A[i - 1]
                    else:
                        ret += A[i]

                    K = 0
            else:
                ret += A[i]

        return ret

    def doit(self, xs, K):

        xs.sort()
        S = i = 0
        mn = 100
        for x in xs:
            if i < K and x < 0:
                x = -x
                i += 1
            if x < mn:
                mn = x
            S += x
        return S - 2*mn if (K-i) % 2 else S


if __name__ == '__main__':

    res = LargestSumAfterKNegations().doit(A=[4, 2, 3], K=1)

    res = LargestSumAfterKNegations().doit(A=[3, -1, 0, 2], K=3)

    res = LargestSumAfterKNegations().doit(A=[2, -3, -1, 5, -4], K=2)

    pass

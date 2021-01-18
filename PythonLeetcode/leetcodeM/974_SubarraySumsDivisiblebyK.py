"""
# 974. Subarray Sums Divisible by K

# Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.


# Example 1:

# Input: A = [4,5,0,-2,-3,1], K = 5
# Output: 7
# Explanation: There are 7 subarrays with a sum divisible by K = 5:
# [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]


# Note:

# 1 <= A.length <= 30000
# -10000 <= A[i] <= 10000
# 2 <= K <= 10000
"""

class SubarraysDivByK:

    """
    Compute the prefix sum at each index i in the array and track the count of how many times each remainder (prefix_sum % K) occurs.

    Logic is that if a remainder R occurs more than once in prefix sums it means that there is a subarray with remainder 0.
    For e.g. if remainder R occurs at indices i and j (i < j) then the subarray i+1 to j has remainder 0.

    Thus if remainder R (!=0) occurs T times in prefix_sums it means that there are T-1 consecutive subarrays with remainder 0
    (-1 because the 1st occurrence should not be counted as R != 0). For T-1 consecutive subarrays, the total number of combinations possible are T*(T-1)/2.

    Similarly if R=0 in the previous argument then there are T consecutive subarrays with remainder 0. Thus possible number of combinations are T*(T+1)/2
    """

    def doit(self, A, K):

        buff = {}
        total = 0

        for c in A:
            total += c
            if total % K not in buff:
                buff[total % K] = 0
            buff[total % K] += 1

        cnt = 0
        for k, v in buff.items():
            if k == 0:
                cnt += v * (v + 1) // 2
            else:
                cnt += v * (v - 1) // 2

        return cnt

    """
        Complexity Analysis

        Time Complexity: O(N), where NN is the length of A.

        Space Complexity: O(N). (However, the solution can be modified to use O(K) space by storing only count.)
    """
    def doit_(self, A, K):
        import collections
        P = [0]
        for x in A:
            P.append((P[-1] + x) % K)

        count = collections.Counter(P)
        return sum(v*(v-1)/2 for v in count.values())

if __name__ == "__main__":

    # res = SubarraysDivByK().doit(A=[4, 5, 0, -2, -3, 1], K=5)

    res = SubarraysDivByK().doit([-1, 2, 9], 2)

    pass

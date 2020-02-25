# 930. Binary Subarrays With Sum

# In an array A of 0s and 1s, how many non-empty subarrays have sum S

# Example 1:

# Input: A = [1,0,1,0,1], S = 2
# Output: 4
# Explanation:
# The 4 subarrays are bolded below:
# [1,0,1,0,1]
# [1,0,1,0,1]
# [1,0,1,0,1]
# [1,0,1,0,1]


# Note:

# A.length <= 30000
# 0 <= S <= A.length
# A[i] is either 0 or 1.

import collections


class NumSubarraysWithSum:

    """
    Approach 1: Index of Ones
    Intuition

    Say we number the 1s in A: (x_1, x_2, ... , x_n) with A[x_i] = 1

    Then, if we have a subarray of sum S, it has to use the ones x_i, x_{i+1}, ..., x_{i+S-1}x.
    For each ii, we can count the number of such subarrays individually.

    Algorithm

    In general, the number of such subarrays (for ii) is (x_i - x_{i-1}) * (x_{i+S} - x_{i+S-1})

    For example, if S = 2S=2, then in A = [1,0,1,0,1,0,0,1], let's count the number of subarrays [i, j] that use the middle two 1s.
    There are 2 choices for the i (i = 1, 2) and 3 choices for the j (j = 4, 5, 6).
    The corner cases are when S = 0S=0, i = 1i=1, or i+S = n+1i+S=n+1. We can handle these gracefully.
    """

    def doit(self, A, S):

        indexes = [-1] + [ix for ix, v in enumerate(A) if v] + [len(A)]
        ans = 0

        if S == 0:
            for i in range(len(indexes) - 1):
                # w: number of zeros between two consecutive ones
                w = indexes[i+1] - indexes[i] - 1
                ans += w * (w+1) // 2
            return ans

        for i in range(1, len(indexes) - S):
            j = i + S - 1
            left = indexes[i] - indexes[i-1]
            right = indexes[j+1] - indexes[j]
            ans += left * right

        return int(ans)

    """
    Approach 2: Prefix Sums
    Intuition

    Let P[i] = A[0] + A[1] + ... + A[i-1]. Then P[j+1] - P[i] = A[i] + A[i+1] + ... + A[j], the sum of the subarray [i, j].

    Hence, we are looking for the number of i < j with P[j] - P[i] = S.

    Algorithm

    For each j, let's count the number of i with P[j] = P[i] + S. This is analogous to counting the number of subarrays ending in j with sum S.

    It comes down to counting how many P[i] + S we've seen before. We can keep this count on the side to help us find the final answer.

    Complexity Analysis

    Time Complexity: O(N), where N is the length of A.

    Space Complexity: O(N).

    """

    def doit(self, A, S):

        P = [0]
        for c in A:
            P.append(P[-1] + c)

        cnt = {}
        ans = 0
        for c in P:

            if c - S in cnt:
                ans += cnt[c - S]

            cnt[c] = cnt.get(c, 0) + 1

        return ans

    def doit1(self, A, S):
        P = [0]
        for x in A:
            P.append(P[-1] + x)

        count = collections.Counter()
        ans = 0

        for x in P:
            ans += count[x]
            count[x + S] += 1

        return ans

    """
    Approach 3: Three Pointer
    Intuition

    For each j, let's try to count the number of i's that have the subarray [i, j] equal to S.

    It is easy to see these i's form an interval [i_lo, i_hi], and each of i_lo, i_hi are increasing with respect to j.
    So we can use a "two pointer" style approach.

    Algorithm

    For each j (in increasing order), let's maintain 4 variables:

    sum_lo : the sum of subarray [i_lo, j]
    sum_hi : the sum of subarray [i_hi, j]
    i_lo : the smallest i so that sum_lo <= S
    i_hi : the largest i so that sum_hi <= S
    Then, (provided that sum_lo == S), the number of subarrays ending in j is i_hi - i_lo + 1.

    As an example, with A = [1,0,0,1,0,1] and S = 2, when j = 5, we want i_lo = 1 and i_hi = 3.

    Complexity Analysis

    Time Complexity: O(N)O(N), where NN is the length of A.

    Space Complexity: O(1)O(1).

    """

    def doit(self, A, S):

        i_lo = i_hi = 0
        sum_lo = sum_hi = 0
        ans = 0
        for j, x in enumerate(A):
            # Maintain i_lo, sum_lo:
            # While the sum is too big, i_lo += 1
            sum_lo += x
            while i_lo < j and sum_lo > S:
                sum_lo -= A[i_lo]
                i_lo += 1

            # Maintain i_hi, sum_hi:
            # While the sum is too big, or equal and we can move, i_hi += 1
            sum_hi += x
            while i_hi < j and (
                    sum_hi > S or sum_hi == S and not A[i_hi]):
                sum_hi -= A[i_hi]
                i_hi += 1

            if sum_lo == S:
                ans += i_hi - i_lo + 1

        return ans


if __name__ == '__main__':

    res = NumSubarraysWithSum().doit(A=[1, 0, 1, 0, 1], S=2)

    res = NumSubarraysWithSum().doit(A=[0, 0, 0, 0, 0], S=0)

    res = NumSubarraysWithSum().doit1(A=[0, 0, 0, 0, 0], S=0)

    pass
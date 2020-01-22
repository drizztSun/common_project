# 898. Bitwise ORs of Subarrays

# We have an array A of non-negative integers.

# For every (contiguous) subarray B = [A[i], A[i+1], ..., A[j]] (with i <= j),
# we take the bitwise OR of all the elements in B, obtaining a result A[i] | A[i+1] | ... | A[j].

# Return the number of possible results.  (Results that occur more than once are only counted once in the final answer.)


# Example 1:

# Input: [0]
# Output: 1
# Explanation:
# There is only one possible result: 0.

# Example 2:

# Input: [1,1,2]
# Output: 3
# Explanation:
# The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
# These yield the results 1, 1, 2, 1, 3, 3.
# There are 3 unique values, so the answer is 3.

# Example 3:

# Input: [1,2,4]
# Output: 6
# Explanation:
# The possible results are 1, 2, 3, 4, 6, and 7.


# Note:

# 1 <= A.length <= 50000
# 0 <= A[i] <= 10^9

class SubarrayBitwiseORs:

    # (DP) TLE O(n^2)
    def doit(self, A):

        N = len(A)
        dp = [[A[i-1] if i != 0 and i ==
               j else 0 for i in range(N+1)] for j in range(N+1)]

        ans = set([dp[i][i] for i in range(1, N+1)])
        for i in range(1, N+1):
            for step in range(1, N+1 - i):
                j = i + step
                dp[i][j] = A[j-1] | dp[i][j-1]
                ans.add(dp[i][j])

        return len(ans)

    """
    Approach 1: Frontier Set
    Intuition

    Let's try to speed up a brute force answer. Evidently, the brute force approach is to calculate every result result(i, j) = A[i] | A[i+1] | ... | A[j].
    We can speed this up by taking note of the fact that result(i, j+1) = result(i, j) | A[j+1]. Naively, this approach has time complexity O(N^2),
    where NN is the length of the array.

    Actually, this approach can be better than that. At the kth step, say we have all the result(i, k) in some set cur.
    Then we can find the next cur set (for k -> k+1) by using result(i, k+1) = result(i, k) | A[k+1].

    However, the number of unique values in this set cur is at most 32, since the list result(k, k), result(k-1, k), result(k-2, k), ... is monotone increasing,
    and any subsequent values that are different must have more 1s in it's binary representation (to a maximum of 32 ones).

    Algorithm

    In the kth step, we'll maintain cur: the set of results A[i] | ... | A[k] for all i. These results will be included in our final answer set.

    Complexity Analysis
    Time Complexity: O(NlogW), where N is the length of A, and W is the maximum size of elements in A.
    Space Complexity: O(NlogW), the size of the answer.

    """

    def doit(self, A):
        res, cur = set([A[0]]), set([A[0]])
        for i in range(1, len(A)):
            tmp = set([A[i]])
            for num in cur:
                tmp.add(A[i] | num)
            cur = tmp
            for num in cur:
                res.add(num)
        return len(res)

    def doit1(self, A):
        ans = set()
        cur = {0}
        for x in A:
            cur = {x | y for y in cur} | {x}
            ans |= cur
        return len(ans)


if __name__ == '__main__':

    res = SubarrayBitwiseORs().doit([0])  # 1

    res = SubarrayBitwiseORs().doit([1, 1, 2])  # 3

    res = SubarrayBitwiseORs().doit1([1, 2, 4])  # 6

    pass

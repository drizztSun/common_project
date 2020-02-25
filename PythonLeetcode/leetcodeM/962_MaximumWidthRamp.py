# 962. Maximum Width Ramp

# Given an array A of integers, a ramp is a tuple (i, j) for which i < j and A[i] <= A[j].
# The width of such a ramp is j - i.

# Find the maximum width of a ramp in A.  If one doesn't exist, return 0.


# Example 1:

# Input: [6,0,8,2,1,5]
# Output: 4
# Explanation:
# The maximum width ramp is achieved at (i, j) = (1, 5): A[1] = 0 and A[5] = 5.

# Example 2:

# Input: [9,8,1,0,1,9,4,0,4,1]
# Output: 7
# Explanation:
# The maximum width ramp is achieved at (i, j) = (2, 9): A[2] = 1 and A[9] = 1.


# Note:

# 2 <= A.length <= 50000
# 0 <= A[i] <= 50000

class MaxWidthRamp:

    """
    Approach 1: Sort
    Intuition and Algorithm

    For all elements like A[i] = v, let's write the indices i in sorted order of their values v.
    For example with A[0] = 7, A[1] = 2, A[2] = 5, A[3] = 4, we can write the order of indices i=1, i=3, i=2, i=0.

    Then, whenever we write an index i, we know there was a ramp of width i - min(indexes_previously_written)
    (if this quantity is positive). We can keep track of the minimum of all indexes previously written as m.

    Complexity Analysis

    Time Complexity: O(NlogN), where N is the length of A.

    Space Complexity: O(N), depending on the implementation of the sorting function.
    """

    def doit(self, A):

        ans = 0
        m = float('inf')

        for i in sorted(range(len(A)), key=A.__getitem__):

            ans = max(ans, i - m)
            m = min(m, i)

        return ans

    """
    Approach 2: Binary Search Candidates
    Intuition
    Consider i in decreasing order. We want to find the largest j with A[j] >= A[i] if it exists.
    Thus, the candidates for j are decreasing: if there is j1 < j2 and A[j1] <= A[j2] then we strictly prefer j2.

    Algorithm
    Let's keep a list of these candidates j.
    For example, with A = [0,8,2,7,5], the candidates for i = 0 would be candidates = [(v=5, i=4), (v=7, i=3), (v=8, i=1)].
    We keep the list of candidates in decreasing order of i and increasing order of v.
    Now we can binary search to find the largest j with A[j] >= A[i]: it's the first one in this list of candidates with v >= A[i].

    Complexity Analysis

    Time Complexity: O(NlogN), where N is the length of A.
    Space Complexity: O(N).
    """

    import bisect

    def doit1(self, A):
        N = len(A)
        ans = 0
        candidates = [(A[N-1], N-1)]

        # candidates: i's decreasing, by increasing value of A[i]
        for i in range(N-2, -1, -1):

            # Find largest j in candidates with A[j] >= A[i]
            jx = bisect.bisect(candidates, (A[i],))

            if jx < len(candidates):
                ans = max(ans, candidates[jx][1] - i)
            else:
                candidates.append((A[i], i))

        return ans


if __name__ == '__main__':

    res = MaxWidthRamp().doit([7, 2, 5, 4])

    res = MaxWidthRamp().doit([6, 0, 8, 2, 1, 5])  # 4

    res = MaxWidthRamp().doit([9, 8, 1, 0, 1, 9, 4, 0, 4, 1])  # 7

    pass
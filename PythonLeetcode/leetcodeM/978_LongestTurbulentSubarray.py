# 978. Longest Turbulent Subarray

# A subarray A[i], A[i+1], ..., A[j] of A is said to be turbulent if and only if:

# For i <= k < j, A[k] > A[k+1] when k is odd, and A[k] < A[k+1] when k is even;
# OR, for i <= k < j, A[k] > A[k+1] when k is even, and A[k] < A[k+1] when k is odd.
# That is, the subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.

# Return the length of a maximum size turbulent subarray of A.


# Example 1:

# Input: [9,4,2,10,7,8,8,1,9]
# Output: 5
# Explanation: (A[1] > A[2] < A[3] > A[4] < A[5])
# Example 2:

# Input: [4,8,12,16]
# Output: 2
# Example 3:

# Input: [100]
# Output: 1

class MaxTurbulenceSize:

    """
    Approach 1: Sliding Window
    Intuition
    Evidently, we only care about the comparisons between adjacent elements. If the comparisons are represented by -1, 0, 1 (for <, =, >),
    then we want the longest sequence of alternating 1, -1, 1, -1, ... (starting with either 1 or -1).
    These alternating comparisons form contiguous blocks. We know when the next block ends: when it is the last two elements being compared, or when the sequence isn't alternating.

    For example, take an array like A = [9,4,2,10,7,8,8,1,9]. The comparisons are [1,1,-1,1,-1,0,-1,1]. The blocks are [1], [1,-1,1,-1], [0], [-1,1].
    Algorithm

    Scan the array from left to right. If we are at the end of a block (last elements OR it stopped alternating),
    then we should record the length of that block as our candidate answer, and set the start of the new block as the next element.

    Complexity Analysis

    Time Complexity: O(N), where N is the length of A.

    Space Complexity: O(1).

    """

    def doit(self, A):

        def cmp(a, b):
            return 0 if a == b else 1 if a > b else -1

        ans, last = 1, 0

        for i in range(1, len(A)):

            c = cmp(A[i-1], A[i])

            if c == 0:
                last = i
            elif i == len(A) - 1 or c * cmp(A[i], A[i+1]) != -1:
                ans = max(ans, i - last + 1)
                last = i

        return ans

    def doit(self, A):
        res = 0
        count = 0
        sign = 0
        prev = None

        for a in A:
            if prev is None:
                res = 1
                count = 1
            else:
                if prev < a:
                    if sign != 1:
                        count += 1
                    else:
                        res = max(res, count)
                        count = 2
                    sign = 1
                elif prev > a:
                    if sign != -1:
                        count += 1
                    else:
                        res = max(res, count)
                        count = 2
                    sign = -1
                else:
                    res = max(res, count)
                    count = 1
                    sign = 0
            prev = a
        res = max(res, count)
        return res

if __name__ == '__main__':

    res = MaxTurbulenceSize().doit([9, 4, 2, 10, 7, 8, 8, 1, 9])  # 5

    res = MaxTurbulenceSize().doit([4, 8, 12, 16])  # 2

    res = MaxTurbulenceSize().doit([100])  # 1

    res = MaxTurbulenceSize().doit([9, 9])

    res = MaxTurbulenceSize().doit([8,8,9,10,6,8,2,4,2,2,10,6,6,10,10,2,3,5,1,2,10,4,2,0,9,4,9,3,0,6,3,2,3,10,10,6,4,6,4,4,2,5,1,4,1,1,9,8,9,5,3,5,5,4,5,5,6,5,3,3,7,2,0,10,9,7,7,3,5,1,0,9,6,3,1,3,4,4,3,6,3,2,1,4,10,2,3,4,4,3,6,7,6,2,1,7,0,6,8,10])

    pass

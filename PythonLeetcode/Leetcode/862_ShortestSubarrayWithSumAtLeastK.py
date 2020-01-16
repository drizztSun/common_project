# 862. Shortest Subarray with Sum at Least K

# Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.

# If there is no non-empty subarray with sum at least K, return -1.

# Example 1:

# Input: A = [1], K = 1
# Output: 1

# Example 2:

# Input: A = [1,2], K = 4
# Output: -1

# Example 3:

# Input: A = [2,-1,2], K = 3
# Output: 3


# Note:

# 1 <= A.length <= 50000
# -10 ^ 5 <= A[i] <= 10 ^ 5
# 1 <= K <= 10 ^ 9

class ShortestSubarray:

    """
    Approach 1: Sliding Window
    Intuition

    We can rephrase this as a problem about the prefix sums of A. Let P[i] = A[0] + A[1] + ... + A[i-1].
    We want the smallest y-x such that y > x and P[y] - P[x] >= K.

    Motivated by that equation, let opt(y) be the largest x such that P[x] <= P[y] - K.
    We need two key observations:

    If x1 < x2 and P[x2] <= P[x1], then opt(y) can never be x1, as if P[x1] <= P[y] - K, then P[x2] <= P[x1] <= P[y] - K but y - x2 is smaller.
    This implies that our candidates x for opt(y) will have increasing values of P[x].
    If opt(y1) = x, then we do not need to consider this x again. For if we find some y2 > y1 with opt(y2) = x, 
    then it represents an answer of y2 - x which is worse (larger) than y1 - x.

    Algorithm
    Maintain a "monoqueue" of indices of P: a deque of indices x_0, x_1, ... such that P[x_0], P[x_1], ... is increasing.
    When adding a new index y, we'll pop x_i from the end of the deque so that P[x_0], P[x_1], ..., P[y] will be increasing.
    If P[y] >= P[x_0] + K, then (as previously described), we don't need to consider this x_0 again, and we can pop it from the front of the deque.

    Complexity Analysis
    Time Complexity: O(N), where NN is the length of A.
    Space Complexity: O(N).
    """

    def doit(self, A, K):
        N = len(A)
        P = [0]
        for x in A:
            P.append(P[-1] + x)

        # Want smallest y-x with Py - Px >= K
        ans = N+1  # N+1 is impossible
        monoq = collections.deque()  # opt(y) candidates, represented as indices of P
        for y, Py in enumerate(P):
            # Want opt(y) = largest x with Px <= Py - K
            while monoq and Py <= P[monoq[-1]]:
                monoq.pop()

            while monoq and Py - P[monoq[0]] >= K:
                ans = min(ans, y - monoq.popleft())

            monoq.append(y)

        return ans if ans < N+1 else -1

    def doit(self, A, K):
        prefix_sums = list(itertools.accumulate(A, initial=0))
        min_length = inf = len(A) + 1
        queue = collections.deque()

        for index, prefix_sum in enumerate(prefix_sums):
            while queue and prefix_sum <= prefix_sums[queue[-1]]:
                queue.pop()

            while queue and prefix_sum - prefix_sums[queue[0]] >= K:
                min_length = min(min_length, index - queue.popleft())

            queue.append(index)

        return -1 if min_length == inf else min_length

    def doit1(self, A, K):

        length = float('inf')
        i = -1
        subtotal = 0

        for j in range(len(A)):
            subtotal += A[j]

            while subtotal >= K and i < j:
                if length > j - i:
                    length = j - i

                i += 1
                subtotal -= A[i]

        for i in range(i+1, len(A)):
            subtotal -= A[i]

            if subtotal >= K and length > len(A) - i - 1:
                length = len(A) - i - 1

        return -1 if length == float('inf') else length


if __name__ == '__main__':

    res = ShortestSubarray().doit1(A=[1], K=1)  # 1

    res = ShortestSubarray().doit1(A=[1, 2], K=4)  # -1

    res = ShortestSubarray().doit1(A=[2, -1, 2], K=3)  # 3

    res = ShortestSubarray().doit1([48, 99, 37, 4, -31], 140)  # 2

    res = ShortestSubarray().doit1([84, -37, 32, 40, 95], 167)  # 3

    res = ShortestSubarray().doit1([-28, 81, -20, 28, -29], 89)  # 3

    pass

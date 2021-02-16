"""
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
"""


class ShortestSubarray:


    """
        Prepare
        From @Sarmon:
        "What makes this problem hard is that we have negative values.
        If you haven't already done the problem with positive integers only,
        I highly recommend solving it first"

        209. Minimum Size Subarray Sum

        Explanation
        Calculate prefix sum B of list A.
        B[j] - B[i] represents the sum of subarray A[i] ~ A[j-1]
        Deque d will keep indexes of increasing B[i].
        For every B[i], we will compare B[i] - B[d[0]] with K.


        Complexity:
        Every index will be pushed exactly once.
        Every index will be popped at most once.

        Time O(N)
        Space O(N)


        How to think of such solutions?
        Basic idea, for array starting at every A[i], find the shortest one with sum at leat K.
        In my solution, for B[i], find the smallest j that B[j] - B[i] >= K.
        Keep this in mind for understanding two while loops.


        What is the purpose of first while loop?
        For the current prefix sum B[i], it covers all subarray ending at A[i-1].
        We want know if there is a subarray, which starts from an index, ends at A[i-1] and has at least sum K.
        So we start to compare B[i] with the smallest prefix sum in our deque, which is B[D[0]], hoping that [i] - B[d[0]] >= K.
        So if B[i] - B[d[0]] >= K, we can update our result res = min(res, i - d.popleft()).
        The while loop helps compare one by one, until this condition isn't valid anymore.


        Why we pop left in the first while loop?
        This the most tricky part that improve my solution to get only O(N).
        D[0] exists in our deque, it means that before B[i], we didn't find a subarray whose sum at least K.
        B[i] is the first prefix sum that valid this condition.
        In other words, A[D[0]] ~ A[i-1] is the shortest subarray starting at A[D[0]] with sum at least K.
        We have already find it for A[D[0]] and it can't be shorter, so we can drop it from our deque.


        What is the purpose of second while loop?
        To keep B[D[i]] increasing in the deque.


        Why keep the deque increase?
        If B[i] <= B[d.back()] and moreover we already know that i > d.back(), it means that compared with d.back(),
        B[i] can help us make the subarray length shorter and sum bigger. So no need to keep d.back() in our deque.


        More Similar Sliding Window Problems
        Here are some similar sliding window problems.
        Also find more explanations.
        Good luck and have fun.

        Sliding window:

            1248. Count Number of Nice Subarrays
            1234. Replace the Substring for Balanced String
            1004. Max Consecutive Ones III
            930. Binary Subarrays With Sum
            992. Subarrays with K Different Integers
            904. Fruit Into Baskets
            862. Shortest Subarray with Sum at Least K
            209. Minimum Size Subarray Sum
    """
    def doit_sliding_window(self, A, K):
        from collections import deque
        d = deque([[0, 0]])
        res, cur = float('inf'), 0

        for i, a in enumerate(A):
            cur += a
            while d and cur - d[0][1] >= K:
                res = min(res, i + 1 - d.popleft()[0])
            while d and cur <= d[-1][1]:
                d.pop()
            d.append([i + 1, cur])
        
        return res if res < float('inf') else -1
    
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

        Monotonic_queue
    """
    def doit_sliding_window(self, A, K):
        from collections import deque
        N, P = len(A), [0]
        for x in A:
            P.append(P[-1] + x)

        # Want smallest y-x with Py - Px >= K
        ans = N+1  # N+1 is impossible
        monoq = deque()  # opt(y) candidates, represented as indices of P
        for y, Py in enumerate(P):

            # Want opt(y) = largest x with Px <= Py - K
            while monoq and Py <= P[monoq[-1]]:
                monoq.pop()

            # Monotonic queue increasing, save index, 
            while monoq and Py - P[monoq[0]] >= K:
                ans = min(ans, y - monoq.popleft())

            monoq.append(y)

        return ans if ans < N+1 else -1

    def doit(self, A, K):
        import itertools, collections
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

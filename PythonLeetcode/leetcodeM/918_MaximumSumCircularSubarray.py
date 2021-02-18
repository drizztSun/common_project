"""
# 918. Maximum Sum Circular Subarray

# Given a circular array C of integers represented by A, find the maximum possible sum of a non-empty subarray of C.

# Here, a circular array means the end of the array connects to the beginning of the array.
# (Formally, C[i] = A[i] when 0 <= i < A.length, and C[i+A.length] = C[i] when i >= 0.)

# Also, a subarray may only include each element of the fixed buffer A at most once.
# (Formally, for a subarray C[i], C[i+1], ..., C[j], there does not exist i <= k1, k2 <= j with k1 % A.length = k2 % A.length.)


# Example 1:

# Input: [1,-2,3,-2]
# Output: 3
# Explanation: Subarray [3] has maximum sum 3

# Example 2:

# Input: [5,-3,5]
# Output: 10
# Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10

# Example 3:

# Input: [3,-1,2,-1]
# Output: 4
# Explanation: Subarray [2,-1,3] has maximum sum 2 + (-1) + 3 = 4

# Example 4:

# Input: [3,-2,2,-3]
# Output: 3
# Explanation: Subarray [3] and [3,-2,2] both have maximum sum 3

# Example 5:

# Input: [-2,-3,-1]
# Output: -1
# Explanation: Subarray [-1] has maximum sum -1


# Note:

# -30000 <= A[i] <= 30000
# 1 <= A.length <= 30000
"""

"""
Notes and A Primer on Kadane's Algorithm
About the Approaches

In both Approach 1 and Approach 2, "grindy" solutions are presented that require less insight, but may be more intuitive to those with a solid grasp of the techniques in those approaches. Without prior experience, these approaches would be very challenging to emulate.

Approaches 3 and 4 are much easier to implement, but require some insight.

Explanation of Kadane's Algorithm

To understand the solutions in this article, we need some familiarity with Kadane's algorithm. In this section, we will explain the core idea behind it.

For a given array A, Kadane's algorithm can be used to find the maximum sum of the subarrays of A. Here, we only consider non-empty subarrays.

Kadane's algorithm is based on dynamic programming. Let dp[j] be the maximum sum of a subarray that ends in A[j]. That is,

\text{dp}[j] = \max\limits_i (A[i] + A[i+1] + \cdots + A[j])dp[j]= 
i
max
​	
 (A[i]+A[i+1]+⋯+A[j])

Then, a subarray ending in j+1 (such as A[i], A[i+1] + ... + A[j+1]) maximizes the A[i] + ... + A[j] part of the sum by being equal to dp[j] if it is non-empty, and 0 if it is. Thus, we have the recurrence:

\text{dp}[j+1] = A[j+1] + \max(\text{dp}[j], 0)dp[j+1]=A[j+1]+max(dp[j],0)

Since a subarray must end somewhere, \max\limits_j dp[j] 
j
max
​	
 dp[j] must be the desired answer.

To compute dp efficiently, Kadane's algorithm is usually written in the form that reduces space complexity. We maintain two variables: ans as \max\limits_j dp[j]
j
max
​	
 dp[j], and cur as dp[j]; and update them as j iterates from 0 to A.length−1.

Then, Kadane's algorithm is given by the following psuedocode:

#Kadane's algorithm
ans = cur = None
for x in A:
    cur = x + max(cur, 0)
    ans = max(ans, cur)
return ans

"""


class MaxSubarraySumCircular:

    """
        Intuition
        I guess you know how to solve max subarray sum (without circular).
        If not, you can have a reference here: 53. Maximum Subarray


        Explanation
        So there are two case.
        Case 1. The first is that the subarray take only a middle part, and we know how to find the max subarray sum.
        Case2. The second is that the subarray take a part of head array and a part of tail array.
        We can transfer this case to the first one.
        The maximum result equals to the total sum minus the minimum subarray sum.


        Here is a diagram by @motorix:
        image

        So the max subarray circular sum equals to
        max(the max subarray sum, the total sum - the min subarray sum)


        Prove of the second case
        max(prefix+suffix)
        = max(total sum - subarray)
        = total sum + max(-subarray)
        = total sum - min(subarray)


        Corner case
        Just one to pay attention:
        If all numbers are negative, maxSum = max(A) and minSum = sum(A).
        In this case, max(maxSum, total - minSum) = 0, which means the sum of an empty subarray.
        According to the deacription, We need to return the max(A), instead of sum of am empty subarray.
        So we return the maxSum to handle this corner case.


        Complexity
        One pass, time O(N)
        No extra space, space O(1)

        OnePass
    """
    def doit_(self, A):

        minsum, maxsum, total, cursum, curmin = float('inf'), float('-inf'), 0, 0, 0

        for a in A:
            
            cursum = max(cursum + a, a)
            maxsum = max(maxsum, cursum)

            curmin = min(curmin + a, a)
            minsum = min(minsum, curmin)

            total += a

        return max(maxsum, total - minsum) if maxsum > 0 else maxsum

    """
    Approach 1: Next Array
    Intuition and Algorithm

    Subarrays of circular arrays can be classified as either as one-interval subarrays, or two-interval subarrays,
    depending on how many intervals of the fixed-size buffer A are required to represent them.

    For example, if A = [0, 1, 2, 3, 4, 5, 6] is the underlying buffer of our circular array,
    we could represent the subarray [2, 3, 4] as one interval [2, 4][2,4], but we would represent the subarray [5, 6, 0, 1] as two intervals [5, 6], [0, 1][5,6],[0,1].

    Using Kadane's algorithm, we know how to get the maximum of one-interval subarrays, so it only remains to consider two-interval subarrays.

    Let's say the intervals are [0, i], [j, A.length - 1].
    Let's try to compute the i-th candidate: the largest possible sum of a two-interval subarray for a given ii.
    Computing the [0, i][0,i] part of the sum is easy. Let's write

    T[j] = A[j] + A[j+1] + ... + A[A.length - 1]
    and
    R[j] = max{T[k]} (k≥j)
​
    so that the desired i-th candidate is:

    (A[0]+A[1]+⋯+A[i])+R[i+2]
    Since we can compute T[j] and R[j] in linear time, the answer is straightforward after this setup.

    Complexity Analysis

    Time Complexity: O(N), where NN is the length of A.
    Space Complexity: O(N).
    """

    def doit_(self, A):

        ans = cur = float('-inf')
        for c in A:
            cur = c + max(cur, 0)
            ans = max(ans, cur)

        N = len(A)
        rights, accum = [0] * N, A[-1]
        rights[N-1] = accum
        for i in range(N-2, -1, -1):
            accum += A[i]
            rights[i] = max(rights[i+1], accum)

        leftsum = 0
        for i in range(N-2):
            leftsum += A[i]
            ans = max(ans, leftsum + rights[i+1])

        return ans

    """
    Approach 2: Prefix Sums + Monoqueue

    Intuition
    First, we can frame the problem as a problem on a fixed array.
    We can consider any subarray of the circular array with buffer A, to be a subarray of the fixed array A+A.
    For example, if A = [0,1,2,3,4,5] represents a circular array, then the subarray [4,5,0,1] is also a subarray of fixed array [0,1,2,3,4,5,0,1,2,3,4,5].
    Let B = A+A be this fixed array.

    Now say N=A.length, and consider the prefix sums

    P(k) = B[0]+B[1]+ ⋯ + B[k−1]
    Then, we want the largest P(j) - P(i) where j - i ≤ N.

    Now, consider the j-th candidate answer: the best possible P(j) - P(i) for a fixed j.
    We want the i, so that P[i] is smallest, with j - N ≤ i < j. 
    Let's call this the optimal i for the j-th candidate answer. We can use a monoqueue to manage this.

    Algorithm

    Iterate forwards through jj, computing the jj-th candidate answer at each step. We'll maintain a queue of potentially optimal ii's.

    The main idea is that if i(1) < i(2) and P(i1) ≥ P(i2), then we don't need to remember i(1) anymore.

    Please see the inline comments for more algorithmic details about managing the queue.

    Complexity Analysis
    Time Complexity: O(N), where NN is the length of A.
    Space Complexity: O(N).
    """

    def doit_monoque(self, A):
        from collections import deque
        N = len(A)

        # Compute P[j] = sum(B[:j]) for the fixed array B = A+A
        P = [0]
        for _ in range(2):
            for x in A:
                P.append(P[-1] + x)

        # Want largest P[j] - P[i] with 1 <= j-i <= N
        # For each j, want smallest P[i] with i >= j-N
        ans = A[0]
        deque = deque([0])  # i's, increasing by P[i]
        for j in range(1, len(P)):
            # If the smallest i is too small, remove it.
            if deque[0] < j-N:
                deque.popleft()

            # The optimal i is deque[0], for cand. answer P[j] - P[i].
            ans = max(ans, P[j] - P[deque[0]])

            # Remove any i1's with P[i2] <= P[i1].
            while deque and P[j] <= P[deque[-1]]:
                deque.pop()

            deque.append(j)

        return ans

    """
    Approach 3: Kadane's (Sign Variant)
    Intuition and Algorithm

    As in Approach 1, subarrays of circular arrays can be classified as either as one-interval subarrays, or two-interval subarrays.

    Using Kadane's algorithm kadane for finding the maximum sum of non-empty subarrays, the answer for one-interval subarrays is kadane(A).

    Now, let N = A\text{.length}N=A.length. For a two-interval subarray like:

    (A_0 + A_1 + ... + A_i) + (A_j + A_{j+1} + ... + A_{N - 1})
    we can write this as

    (∑k=0, N−1 A[k])−(A[i+1] + A[i+2] + ⋯ + A[j−1])

    For two-interval subarrays, let BB be the array AA with each element multiplied by -1−1.
    Then the answer for two-interval subarrays is \text{sum}(A) + \text{kadane}(B)sum(A)+kadane(B).

    Except, this isn't quite true, as if the subarray of BB we choose is the entire array, the resulting two interval subarray [0, i] + [j, N-1][0,i]+[j,N−1] would be empty.

    We can remedy this problem by doing Kadane twice: once on BB with the first element removed, and once on BB with the last element removed.

    Complexity Analysis

    Time Complexity: O(N), where N is the length of A.

    Space Complexity: O(1) in additional space complexity.

    """

    def doit(self, A):
        def kadane(gen):
            # Maximum non-empty subarray sum
            ans = cur = None
            for x in gen:
                cur = x + max(cur, 0)
                ans = max(ans, cur)
            return ans

        S = sum(A)
        ans1 = kadane(iter(A))
        ans2 = S + kadane(-A[i] for i in range(1, len(A)))
        ans3 = S + kadane(-A[i] for i in range(len(A) - 1))
        return max(ans1, ans2, ans3)

    """
    Approach 4: Kadane's (Min Variant)
    Intuition and Algorithm

    As in Approach 3, subarrays of circular arrays can be classified as either as one-interval subarrays (which we can use Kadane's algorithm), or two-interval subarrays.

    We can modify Kadane's algorithm to use min instead of max. All the math in our explanation of Kadane's algorithm remains the same, but the algorithm lets us find the minimum sum of a subarray instead.

    For a two interval subarray written as (∑ A[k] (k=0, N−1))−(∑ A[k], (k=i+1, j−1)),
    we can use our kadane-min algorithm to minimize the "interior" (∑ A[k] (j−1, k=i+1)) part of the sum.

    Again, because the interior [i+1, j-1] must be non-empty, we can break up our search into a search on A[1:] and on A[:-1].
    """
    def doit(self, A):
        # ans1: answer for one-interval subarray
        ans1 = cur = None
        for x in A:
            cur = x + max(cur, 0)
            ans1 = max(ans1, cur)

        # ans2: answer for two-interval subarray, interior in A[1:]
        ans2 = cur = float('inf')
        for i in range(1, len(A)):
            cur = A[i] + min(cur, 0)
            ans2 = min(ans2, cur)
        ans2 = sum(A) - ans2

        # ans3: answer for two-interval subarray, interior in A[:-1]
        ans3 = cur = float('inf')
        for i in range(len(A)-1):
            cur = A[i] + min(cur, 0)
            ans3 = min(ans3, cur)
        ans3 = sum(A) - ans3

        return max(ans1, ans2, ans3)


if __name__ == '__main__':

    res = MaxSubarraySumCircular().doit_cycle([1, -2, 3, -2])  # 3

    res = MaxSubarraySumCircular().doit_cycle([5, -3, 5])  # 10

    res = MaxSubarraySumCircular().doit_cycle([3, -1, 2, -1])  # 4

    res = MaxSubarraySumCircular().doit_cycle([3, -2, 2, -3])  # 3

    res = MaxSubarraySumCircular().doit_cycle([-2, -3, -1])  # -1

    pass

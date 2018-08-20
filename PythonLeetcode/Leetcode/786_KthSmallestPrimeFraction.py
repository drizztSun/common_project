
# 786. K-th Smallest Prime Fraction

# A sorted list A contains 1, plus some number of primes.  Then, for every p < q in the list, we consider the fraction p/q.

# What is the K-th smallest fraction considered?  Return your answer as an array of ints, where answer[0] = p and answer[1] = q.

# Examples:
# Input: A = [1, 2, 3, 5], K = 3
# Output: [2, 5]
# Explanation:
# The fractions to be considered in sorted order are:
# 1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
# The third fraction is 2/5.

# Input: A = [1, 7], K = 1
# Output: [1, 7]
# Note:

# A will have length between 2 and 2000.
# Each A[i] will be between 1 and 30000.
# K will be between 1 and A.length * (A.length - 1) / 2.

import heapq


class KthSmallestPrimeFraction:

    def doit1(self, A, K):
        """
        :type A: List[int]
        :type K: int
        :rtype: List[int]
        """
        ans, N = [], len(A)
        for i in range(N):
            heapq.heappush(ans, (A[i] / A[N-1], i, N-1))

        while K > 0:
            s, i, j = heapq.heappop(ans)
            if i != j-1:
                heapq.heappush(ans, (A[i]/A[j-1], i, j - 1))
            K -= 1
        
        return [A[i], A[j]]

    def doit(self, A, K):
        """
        :type A: List[int]
        :type K: int
        :rtype: List[int]
        """
        import bisect
        l, r, N = 0, 1, len(A)

        while True:
            m = (l + r) / 2
            border = [bisect.bisect(A, A[i] / m) for i in range(N)]

            cur = sum(N - i for i in border)

            if cur > K:
                r = m
            elif cur < K:
                l = m
            else:
                return max([(A[i], A[j]) for i, j in enumerate(border) if j < N], key=lambda x: x[0] / x[1])

    def doi2(self, A, K):
        """
        :type A: List[int]
        :type K: int
        :rtype: List[int]
        """
        st = []
        for i in range(len(A)):
            for j in range(i+1, len(A)):
                heapq.heappush(st, (i / j, i, j))

        i, j = 0, 0
        while K > 0:
            r, i, j = heapq.heappop(st)
            K -= 1

        return [i, j]


if __name__ == "__main__":

    res = KthSmallestPrimeFraction().doit([1, 2, 3, 5], 3)

    res = KthSmallestPrimeFraction().doit([1, 7], 1)

    pass
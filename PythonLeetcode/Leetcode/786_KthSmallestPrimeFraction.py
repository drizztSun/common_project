"""
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
"""


import heapq


class KthSmallestPrimeFraction:

    """
    Heap
    The minimum number is A[0] / A[-1], and the second minimum could be A[1] / A[-1], the third one could be A[2] / A[-1] or A[0] / A[-2]...,
    What problem does this make you think this problem can be transformed to? Merging Kth sorted list. The head of each list could be A[0] / A[-1], A[1] / A[-1],
    A[2] / A[-1], ... A[-2] / A[-1]. The lastt thing is quite easy, to push each head to heap, and popup one by one until we reach the K while pushing updated head to heap by A[i] / A[ j - 1] if j - 1 > i.

    Time Complexity = (klgn)
    Space Complexity = (n)
    """
    def doit_heap(self, A, K):
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

    def doi_heap_2(self, A, K):
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

    """
    Binary Search
    The sorted array of fractions can make us think of using binary search as sorted always goes along with binary search. 
    So we can try to insert a number to find out the index of position in the sorted order, where the index means the count of fractions that are smaller than the inserted number.
    By doing this, the inserted number can be picked by binary search. The low is 0 and the high is 1, and then try to insert mid = low + (high - low) / 2.But how to insert it?
    Take a look at how fraction is generated. If we have numerator at i, and denominator at j, whose fraction is smaller than mid, then all numbers after j must be smaller than mid. 
    Is that all of numbers that are smallers than mid? No, there are more by moving i to be i`, but the j` for the i` must be larger than or equal to j as i` is larger than i and we must pick smaller or same j` 
    so that the fraction can be smaller than mid. So, we don't need reset j to i + 1 for each i and know we are finished counting the number when j reaches to the end.
    While we finished the counting, we need track the maximum number that is less than mid as for different i and j, different numbers that are smaller than mid are generated.
    At last, we compare the count with K, return the maximum number if equals, otherwise update either low or high to mid as mid might be the target number.
    
    Time Complexity = O(nlgx), where x denotes how fraction is contributed, but the choices of mid is 2^-x (0.5, 0.25, 0.125..), there might be a formula...
    Space Complexity = (1)
    """
    def doit_binary_search(self, A, K):
        l, r, n = 0, 1, len(A)
        while l < r:
            mid = l + (r - l) / 2
            i = count = max_val = p = q = 0
            j = 1
            while i < n and j < n:
                while j < n and A[i] / A[j] > mid:
                    j += 1
                count += n - j
                if j < n:
                    val = A[i] / A[j]
                    if val > max_val:
                        max_val = val
                        p, q = A[i], A[j]
                i += 1
            if count == K:
                return [p, q]
            elif count < K:
                l = mid
            else:
                r = mid
        return []

    def doit_binary_search(self, A, K):
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


if __name__ == "__main__":

    res = KthSmallestPrimeFraction().doit_heap([1, 2, 3, 5], 3)

    res = KthSmallestPrimeFraction().doit_binary_search([1, 7], 1)

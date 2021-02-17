"""
1492. The kth Factor of n

Given two positive integers n and k.

A factor of an integer n is defined as an integer i where n % i == 0.

Consider a list of all factors of n sorted in ascending order, return the kth factor in this list or return -1 if n has less than k factors.



Example 1:

Input: n = 12, k = 3
Output: 3
Explanation: Factors list is [1, 2, 3, 4, 6, 12], the 3rd factor is 3.
Example 2:

Input: n = 7, k = 2
Output: 7
Explanation: Factors list is [1, 7], the 2nd factor is 7.
Example 3:

Input: n = 4, k = 4
Output: -1
Explanation: Factors list is [1, 2, 4], there is only 3 factors. We should return -1.
Example 4:

Input: n = 1, k = 1
Output: 1
Explanation: Factors list is [1], the 1st factor is 1.
Example 5:

Input: n = 1000, k = 3
Output: 4
Explanation: Factors list is [1, 2, 4, 5, 8, 10, 20, 25, 40, 50, 100, 125, 200, 250, 500, 1000].


Constraints:

1 <= k <= n <= 1000


"""


class KthFactor:

    """
    Overview
    In this article, we consider three solutions.

    Approach 1: Brute Force, O(N). One could iterate from 11 to NN, figure out all divisors in a linear time, and then return the kth one.
    """
    def doit_on(self, n, k):
        for i in range(1, n):
            if n % i == 0:
                k -= 1
                if k == 0:
                    return i

    """
    Algorithm

    Initialize max heap. Use PriorityQueue in Java and heap in Python. heap is a min-heap. Hence, to implement max heap, change the sign of divisor before pushing it into the heap.
    
    Iterate by xx from 11 to N**0.5
    If xx is a divisor of NN, push xx and its pair divisor n / xn/x into the heap of size kk.
    Return the head of the heap if its size is equal to kk and -1−1 otherwise.
    
    Implementation
    """
    def doit_heap(self, n: int, k: int) -> int:
        from heapq import heappush, heappop
        # push into heap
        # by limiting size of heap to k

        def heappush_k(num):
            heappush(heap, - num)
            if len(heap) > k:
                heappop(heap)

        # Python heap is min heap
        # -> to keep max element always on top,
        # one has to push negative values
        heap = []
        for x in range(1, int(n ** 0.5) + 1):
            if n % x == 0:
                heappush_k(x)
                if x != n // x:
                    heappush_k(n // x)

        return -heappop(heap) if k == len(heap) else -1


    """
    Approach 3: Math, O(Nlog(k))
    Algorithm

    Initialize a list divisors to store the divisors.
    
    Iterate by xx from 11 to \sqrt{N} 

    If x is a divisor of NN, decrease kk by one. Return x if k == 0.
    We're here because the kth divisor is not yet found. Although divisors already contains all "independent" divisors. 
    All other divisors are "paired" ones, i.e, the kth divisor could be computed as N / divisors[len(divisors) - k].
    
    But before that, we need a small correction for the case when NN is a perfect square. In that case, the divisor list contains a duplicate because \sqrt{N} appears two times. 
    To skip it, we have to increase k by one.
    
    Return N / divisors[len(divisors) - k] if k <= len(divisors) and -1 otherwise.

    O(n**0.5)
    """
    def doit_math(self, n: int, k: int) -> int:
        divisors, sqrt_n = [], int(n ** 0.5)
        for x in range(1, sqrt_n + 1):
            if n % x == 0:
                k -= 1
                divisors.append(x)
                if k == 0:
                    return x

        # If n is a perfect square
        # we have to skip the duplicate
        # in the divisor list
        if (sqrt_n * sqrt_n == n):
            k += 1

        n_div = len(divisors)
        return n // divisors[n_div - k] if k <= n_div else -1



"""
# 857. Minimum Cost to Hire K Workers

# There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].

# Now we want to hire exactly K workers to form a paid group.
# When hiring a group of K workers, we must pay them according to the following rules:

# Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
# Every worker in the paid group must be paid at least their minimum wage expectation.
# Return the least amount of money needed to form a paid group satisfying the above conditions.



# Example 1:

# Input: quality = [10,20,5], wage = [70,50,30], K = 2
# Output: 105.00000
# Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
# Example 2:

# Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
# Output: 30.66667
# Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately.


# Note:

# 1 <= K <= N <= 10000, where N = quality.length = wage.length
# 1 <= quality[i] <= 10000
# 1 <= wage[i] <= 10000
# Answers within 10^-5 of the correct answer will be considered correct.

"""


class MincostToHireWorkers:

    """
    Approach 1: Greedy
    Intuition

    At least one worker will be paid their minimum wage expectation. If not, we could scale all payments down by some factor and still keep everyone earning more than their wage expectation.

    Algorithm

    For each captain worker that will be paid their minimum wage expectation, let's calculate the cost of hiring K workers where each point of quality is worth
    wage[captain] / quality[captain] dollars. With this approach, the remaining implementation is straightforward.

    Note that this algorithm would not be efficient enough to pass larger test cases.
    """
    def doit_greedy(self, quality, wage, K):
        from fractions import Fraction
        ans = float('inf')
        N = len(quality)

        for captain in range(N):
            # Must pay at least wage[captain] / quality[captain] per qual
            factor = Fraction(wage[captain], quality[captain])
            prices = []
            for worker in range(N):
                price = factor * quality[worker]
                if price < wage[worker]:
                    continue
                prices.append(price)

            if len(prices) < K:
                continue
            prices.sort()
            ans = min(ans, sum(prices[:K]))

        return float(ans)

    """
    Approach 2: Heap
    Intuition

    As in Approach #1, at least one worker is paid their minimum wage expectation.

    Additionally, every worker has some minimum ratio of dollars to quality that they demand. For example, if wage[0] = 100 and quality[0] = 20, then the ratio for worker 0 is 5.0.

    The key insight is to iterate over the ratio. Let's say we hire workers with a ratio R or lower. Then, we would want to know the K workers with the lowest quality,
    and the sum of that quality. We can use a heap to maintain these variables.

    Algorithm

    Maintain a max heap of quality. (We're using a minheap, with negative values.) We'll also maintain sumq, the sum of this heap.

    For each worker in order of ratio, we know all currently considered workers have lower ratio. (This worker will be the 'captain', as described in Approach #1.)
    We calculate the candidate answer as this ratio times the sum of the smallest K workers in quality.
    """
    def doit_heap(self, quality, wage, K):
        """
        :type quality: List[int]
        :type wage: List[int]
        :type K: int
        :rtype: float
        """
        import heapq
        workers = [(w/q, w, q) for w, q in zip(wage, quality)]
        workers.sort()
        heap = [-q for r, w, q in workers[:K]]
        total_q = -sum(heap)
        res = workers[K-1][0] * total_q
        heapq.heapify(heap)

        for i in range(K, len(workers)):
            r, w, q = workers[i]
            total_q += heapq.heappop(heap) + q
            heapq.heappush(heap, -q)
            res = min(res, r*total_q)
        return res


if __name__ == '__main__':

    MincostToHireWorkers().doit_heap([3, 1, 10, 10, 1], [4, 8, 2, 2, 7], 3)
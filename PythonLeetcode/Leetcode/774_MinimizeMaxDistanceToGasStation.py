"""
774. Minimize Max Distance to Gas Station


On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.

Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.

Return the smallest possible value of D.

Example:

Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
Output: 0.500000
Note:

stations.length will be an integer in range [10, 2000].
stations[i] will be an integer in range [0, 10^8].
K will be an integer in range [1, 10^6].
Answers within 10^-6 of the true value will be accepted as correct.


"""


class MinmaxGasDist:


    """
        Approach #3: Heap [Time Limit Exceeded]
        Intuition

        Following the intuition of Approach #2, if we are taking a repeated maximum, we can replace this with a heap data structure, which performs repeated maximum more efficiently.

        Algorithm

        As in Approach #2, let's repeatedly add a gas station to the next larget interval K times. We use a heap to know which interval is largest. In Python, we use a negative priority to simulate a max heap with a min heap.


        Complexity Analysis

        Let NN be the length of stations, and KK be the number of gas stations to add.

        Time Complexity: O(N + K \log N)O(N+KlogN)

        First of all, we scan the stations to obtain a list of intervals between each adjacent stations.

        Then it takes another O(N)O(N) to build a heap out of the list of intervals.

        Finally, we repeatedly pop out an element and push in a new element into the heap, which takes O(\log N)O(logN) respectively. In total, we repeat this step for KK times (i.e. to add KK gas stations).

        To sum up, the overall time complexity of the algorithm is O(N) + O(N) + O(K \cdot \log N) = O(N + K\cdot \log N)O(N)+O(N)+O(K⋅logN)=O(N+K⋅logN).

        Space Complexity: O(N)O(N), the size of deltas and count.

    """
    def minmaxGasDist(self, stations, K):
        import heapq
        pq = [] #(-part_length, original_length, num_parts)
        for i in range(len(stations) - 1):
            x, y = stations[i], stations[i+1]
            pq.append((x-y, y-x, 1))

        heapq.heapify(pq)

        for _ in range(K):
            negnext, orig, parts = heapq.heappop(pq)
            parts += 1
            heapq.heappush(pq, (-(orig / float(parts)), orig, parts))

        return -pq[0][0]

    """
    Approach #4: Binary Search [Accepted]
    Intuition

    Let's ask possible(D): with K (or less) gas stations, can we make every adjacent distance between gas stations at most D? This function is monotone, so we can apply a binary search to find D^{\text{*}}D
    *
     .

    Algorithm

    More specifically, there exists some D* (the answer) for which possible(d) = False when d < D* and possible(d) = True when d > D*. Binary searching a monotone function is a typical technique, so let's focus on the function possible(D).

    When we have some interval like X = stations[i+1] - stations[i], we'll need to use (X/D) gas stations to ensure every subinterval has size less than D. This is independent of other intervals, so in total we'll need to use 
    
    gas stations. If this is at most K, then it is possible to make every adjacent distance between gas stations at most D.

    Complexity Analysis

    Time Complexity: O(NlogW), where N is the length of stations, and W = 10^{14} is the range of possible answers (10^8), divided by the acceptable level of precision (10^{-6}).

    Space Complexity: O(1) in additional space complexity.

    """

    def doit_binary_search(self, stations, K):
        def possible(D):
            return sum(int((stations[i+1] - stations[i]) / D) for i in range(len(stations) - 1)) <= K

        lo, hi = 0, 10**8
        while hi - lo > 1e-6:
            mi = (lo + hi) / 2.0
            if possible(mi):
                hi = mi
            else:
                lo = mi
        return lo

    def doit_binary_search_1(self, stations: list, K: int) -> float:

        lo, hi = 0, 10**8

        def calculate(m, stations):
            count = 0
            for i in range(1, len(stations)):
                count += int((stations[i+1] - stations[i]) / m)
            return count

        while hi - lo > 1e-6:
            mid = (lo + hi) / 2.0

            if calculate(mid, stations) <= K:
                hi = mid
            else:
                lo = mid

        return lo
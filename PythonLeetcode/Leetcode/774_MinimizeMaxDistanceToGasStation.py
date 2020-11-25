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
    Approach #4: Binary Search [Accepted]
    Intuition

    Let's ask possible(D): with K (or less) gas stations, can we make every adjacent distance between gas stations at most D? This function is monotone, so we can apply a binary search to find D^{\text{*}}D
    *
     .

    Algorithm

    More specifically, there exists some D* (the answer) for which possible(d) = False when d < D* and possible(d) = True when d > D*. Binary searching a monotone function is a typical technique, so let's focus on the function possible(D).

    When we have some interval like X = stations[i+1] - stations[i], we'll need to use \lfloor \frac{X}{D} \rfloor⌊
    D
    X
    ​
     ⌋ gas stations to ensure every subinterval has size less than D. This is independent of other intervals, so in total we'll need to use \sum_i \lfloor \frac{X_i}{D} \rfloor∑
    i
    ​
     ⌊
    D
    X
    i
    ​

    ​
     ⌋ gas stations. If this is at most K, then it is possible to make every adjacent distance between gas stations at most D.

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

        lo, hi = 0, 10**8;

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


if __name__ == '__main__':

    MinmaxGasDist().doit_search(stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9)

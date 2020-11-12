"""
683. K Empty Slots


You have n bulbs in a row numbered from 1 to n. Initially, all the bulbs are turned off. We turn on exactly one bulb every day until all bulbs are on after n days.

You are given an array bulbs of length n where bulbs[i] = x means that on the (i+1)th day, we will turn on the bulb at position x where i is 0-indexed and x is 1-indexed.

Given an integer k, return the minimum day number such that there exists two turned on bulbs that have exactly k bulbs between them that are all turned off. If there isn't such day, return -1.



Example 1:

Input: bulbs = [1,3,2], k = 1
Output: 2
Explanation:
On the first day: bulbs[0] = 1, first bulb is turned on: [1,0,0]
On the second day: bulbs[1] = 3, third bulb is turned on: [1,0,1]
On the third day: bulbs[2] = 2, second bulb is turned on: [1,1,1]
We return 2 because on the second day, there were two on bulbs with one off bulb between them.
Example 2:

Input: bulbs = [1,2,3], k = 1
Output: -1


Constraints:

n == bulbs.length
1 <= n <= 2 * 104
1 <= bulbs[i] <= n
bulbs is a permutation of numbers from 1 to n.
0 <= k <= 2 * 104

"""


class kEmptySlots:

    """
    Approach #1: Insert Into Sorted Structure [Accepted]
    Intuition

    Let's add flowers in the order they bloom. When each flower blooms, we check it's neighbors to see if they can satisfy the condition with the current flower.

    Algorithm

    We'll maintain active, a sorted data structure containing every flower that has currently bloomed. When we add a flower to active, we should check it's lower and higher neighbors.
    If some neighbor satisfies the condition, we know the condition occurred first on this day.


    Complexity Analysis

    Time Complexity (Java): O(N \log N)O(NlogN), where NN is the length of flowers. Every insertion and search is O(\log N)O(logN).

    Time Complexity (Python): O(N^2)O(N
    2
     ). As above, except list.insert is O(N)O(N).

    Space Complexity: O(N)O(N), the size of active.

    """
    def doit_(self, bulbs: list, k: int) -> int:
        import bisect
        active = []
        for day, c in enumerate(bulbs, 1):
            i = bisect.bisect(active, c)
            for neighbor in active[i-(i>0): i+1]:
                if abs(neighbor - c) == k + 1:
                    return day
            active.insert(i, c)
        return -1

    """
    Approach #2: Min Queue [Accepted]
    Intuition
    
    For each contiguous block ("window") of k positions in the flower bed, we know it satisfies the condition in the problem statement 
    if the minimum blooming date of this window is larger than the blooming date of the left and right neighbors.
    
    Because these windows overlap, we can calculate these minimum queries more efficiently using a sliding window structure.
    
    Algorithm
    
    Let days[x] = i be the time that the flower at position x blooms. For each window of k days, let's query the minimum of this window in (amortized) constant time using a MinQueue, 
    a data structure built just for this task. If this minimum is larger than it's two neighbors, then we know this is a place where "k empty slots" occurs, and we record this candidate answer.
    
    To operate a MinQueue, the key invariant is that mins will be an increasing list of candidate answers to the query MinQueue.min.
    
    For example, if our queue is [1, 3, 6, 2, 4, 8], then mins will be [1, 2, 4, 8]. As we MinQueue.popleft, mins will become [2, 4, 8], 
    then after 3 more popleft's will become [4, 8], then after 1 more popleft will become [8].
    
    As we MinQueue.append, we should maintain this invariant. We do it by popping any elements larger than the one we are inserting. 
    For example, if we appended 5 to [1, 3, 6, 2, 4, 8], then mins which was [1, 2, 4, 8] becomes [1, 2, 4, 5].
    
    Note that we used a simpler variant of MinQueue that requires every inserted element to be unique to ensure correctness. 
    Also, the operations are amortized constant time because every element will be inserted and removed exactly once from each queue.
    
    Complexity Analysis

    Time Complexity: O(N), where NN is the length of flowers. In enumerating through the O(N)O(N) outer loop, we do constant work as MinQueue.popleft and MinQueue.min operations are (amortized) constant time.
    
    Space Complexity: O(N), the size of our window.
    """

    def doit_divide_conquer(self, flowers: list, k: int) -> int:

        from collections import deque

        class MinQueue(deque):
            def __init__(self):
                deque.__init__(self)
                self.mins = deque()

            def append(self, x):
                deque.append(self, x)
                while self.mins and x < self.mins[-1]:
                    self.mins.pop()
                self.mins.append(x)

            def popleft(self):
                x = deque.popleft(self)
                if self.mins[0] == x:
                    self.mins.popleft()
                return x

            def min(self):
                return self.mins[0]

        days = [0] * len(flowers)
        for day, position in enumerate(flowers, 1):
            days[position - 1] = day

        window = MinQueue()
        ans = len(days)

        for i, day in enumerate(days):
            window.append(day)
            if k <= i < len(days) - 1:
                window.popleft()
                if k == 0 or days[i - k] < window.min() > days[i + 1]:
                    ans = min(ans, max(days[i - k], days[i + 1]))

        return ans if ans <= len(days) else -1

    """"
    Approach #3: Sliding Window [Accepted]
    Intuition
    
    As in Approach #2, we have days[x] = i for the time that the flower at position x blooms. We wanted to find candidate intervals [left, right] where days[left], 
    days[right] are the two smallest values in [days[left], days[left+1], ..., days[right]], and right - left = k + 1.
    
    Notice that these candidate intervals cannot intersect: for example, if the candidate intervals are [left1, right1] and [left2, right2] with left1 < left2 < right1 < right2, 
    then for the first interval to be a candidate, days[left2] > days[right1]; and for the second interval to be a candidate, days[right1] > days[left2], a contradiction.
    
    That means whenever whether some interval can be a candidate and it fails first at i, indices j < i can't be the start of a candidate interval. This motivates a sliding window approach.
    
    Algorithm
    
    As in Approach #2, we construct days.
    
    Then, for each interval [left, right] (starting with the first available one), we'll check whether it is a candidate: whether days[i] > days[left] and days[i] > days[right] for left < i < right.
    
    If we fail, then we've found some new minimum days[i] and we should check the new interval [i, i+k+1]. If we succeed, then it's a candidate answer, and we'll check the new interval [right, right+k+1].
    
    Complexity Analysis
    Time and Space Complexity: O(N). The analysis is the same as in Approach #2.
    """
    def doit_1(self, flowers: list, k: int) -> int:
        days = [0] * len(flowers)
        for day, position in enumerate(flowers, 1):
            days[position - 1] = day
        ans = float('inf')
        left, right = 0, k + 1
        while right < len(days):
            for i in range(left + 1, right):
                if days[i] < days[left] or days[i] < days[right]:
                    left, right = i, i + k + 1
                    break
            else:
                ans = min(ans, max(days[left], days[right]))
                left, right = right, right + k + 1

        return ans if ans < float('inf') else -1

    def kEmptySlots(self, bulbs: list, K: int) -> int:
        import math
        N = len(bulbs)
        P = K + 1
        M = N // P + 1
        maxs = [-math.inf] * M
        mins = [math.inf] * M
        for day, pos in enumerate(bulbs, 1):
            bucket = pos // P
            if maxs[bucket] < pos:
                maxs[bucket] = pos
                if bucket + 1 < M and mins[bucket + 1] == pos + P:
                    return day
            if pos < mins[bucket]:
                mins[bucket] = pos
                if bucket - 1 >= 0 and maxs[bucket - 1] == pos - P:
                    return day
        return -1
    

if __name__ == '__main__':

    kEmptySlots().doit(bulbs=[1,3,2], k=1)

    kEmptySlots().doit(bulbs=[1,2,3], k=1)



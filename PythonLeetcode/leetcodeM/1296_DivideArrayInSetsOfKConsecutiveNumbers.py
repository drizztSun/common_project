"""
1296. Divide Array in Sets of K Consecutive Numbers


Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into sets of k consecutive numbers
Return True if its possible otherwise return False.

 

Example 1:

Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
Example 2:

Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].
Example 3:

Input: nums = [3,3,2,2,1,1], k = 3
Output: true
Example 4:

Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= nums.length
Note: This question is the same as 846: https://leetcode.com/problems/hand-of-straights/

"""


class DivideArrayInSetsOfKConsecutiveNumbers:

    """ 
        Intuition
        Exactly same as 846. Hand of Straights


        Solution 1
        Count number of different cards to a map c
        Loop from the smallest card number.
        Everytime we meet a new card i, we cut off i - i + k - 1 from the counter.

        Complexity:
        Time O(MlogM + MK), where M is the number of different cards.
        In Cpp and Java it's O(NlogM), which can also be improved.
    """
    def doit_hashtable(self, A, k):
        import collections
        c = collections.Counter(A)
        for i in sorted(c):
            if c[i] > 0:
                for j in range(k)[::-1]:
                    c[i + j] -= c[i]
                    if c[i + j] < 0:
                        return False
        return True

    """
        Follow Up
        We just got lucky AC solution. Because k <= 10000.
        What if k is huge, should we cut off card on by one?


        Solution 2
        Count number of different cards to a map c
        Cur represent current open straight groups.
        In a deque start, we record the number of opened a straight group.
        Loop from the smallest card number.
        For example, A = [1,2,3,2,3,4], k = 3
        We meet one 1:
        opened = 0, we open a new straight groups starting at 1, push (1,1) to start.
        We meet two 2:
        opened = 1, we need open another straight groups starting at 1, push (2,1) to start.
        We meet two 3:
        opened = 2, it match current opened groups.
        We open one group at 1, now we close it. opened = opened - 1 = 1
        We meet one 4:
        opened = 1, it match current opened groups.
        We open one group at 2, now we close it. opened = opened - 1 = 0

        return if no more open groups.

        Complexity
        O(N+MlogM), where M is the number of different cards.
        Because I count and sort cards.
        In Cpp and Java it's O(NlogM), which can also be improved.
    """
    def doit_hashtable(self, A, k):
        from collections import Counter, deque

        c = Counter(A)
        start = deque()
        last_checked, opened = -1, 0

        for i in sorted(c):
            if opened > c[i] or opened > 0 and i > last_checked + 1: return False
            start.append(c[i] - opened)
            last_checked, opened = i, c[i]
            if len(start) == k: opened -= start.popleft()
        
        return opened == 0

    def doit_heap(self, hand: list, k: int) -> bool:
        from collections import Counter
        from heapq import heapify, heappush, heappop

        if len(hand) % k != 0: return False

        heap = list(Counter(hand).items())
        heapify(heap)

        for _ in range(len(hand) // k):

            lastval = None
            duplicates = []

            for _ in range(k):
                if not heap:
                    return False
                
                nextval = heappop(heap)
                if lastval and nextval[0] != lastval + 1:
                    return False

                if nextval[1] > 1:
                    duplicates.append((nextval[0], nextval[1]-1))

                lastval = nextval[0]

            for d in duplicates:
                heappush(heap, d)

        return True 


    def doit_hashtable(self, nums: list, k: int) -> bool:
        d = {}
        nums.sort()
        for i in nums:
            d[i] = d.get(i,0) + 1
        
        for key,v in d.items():
            
            if v > 0:
                for i in range(key,key+k):
                    if i in d:
                        d[i] -= v
                    else:
                        return False
        
        return sum(d.values()) == 0


    def doit_hashtable(self, nums: list, k: int) -> bool:
        from collections import Counter
        
        cnt = Counter(nums)
        keys = sorted(cnt.keys())
        for c in keys:
            
            if c not in cnt:
                continue
            base = cnt[c]
            for s in range(c, c+k):
                
                if s not in keys or cnt[s] < base:
                    return False
                
                cnt[s] -= base
                if cnt[s] == 0:
                    del cnt[s]
                    
        return not cnt

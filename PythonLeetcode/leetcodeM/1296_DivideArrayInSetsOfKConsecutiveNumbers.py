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

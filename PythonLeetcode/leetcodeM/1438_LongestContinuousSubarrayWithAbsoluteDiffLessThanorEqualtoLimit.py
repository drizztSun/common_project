"""
1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit


Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.

 

Example 1:

Input: nums = [8,2,4,7], limit = 4
Output: 2 
Explanation: All subarrays are: 
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4. 
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4. 
Therefore, the size of the longest subarray is 2.
Example 2:

Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4 
Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.
Example 3:

Input: nums = [4,2,2,2,4,4,2,2], limit = 0
Output: 3
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
0 <= limit <= 10^9


"""


class LongestSubarray:

    """
        Intuition
        Last week we learned,
        in 1425. Constrained Subsequence Sum
        how to get minimum in a subarray when sliding.

        This week, we need to get both the maximum and the minimum,
        at the same time.

        So I opened my post last week,
        and copy some my own codes.


        Solution 0: Binary insert and remove
        Keep an increasing list L.
        Binary insert the current element.
        If the L[L.size() - 1] - L[0] > limit,
        binary search the position of A[i] and remove it from the list.


        More Similar Sliding Window Problems
        Here are some similar sliding window problems.
        Also find more explanations.
        If you have question about the complexity and if/while clause,
        pick an easier one first.

        1425. Constrained Subsequence Sum
        1358. Number of Substrings Containing All Three Characters
        1248. Count Number of Nice Subarrays
        1234. Replace the Substring for Balanced String
        1004. Max Consecutive Ones III
        930. Binary Subarrays With Sum
        992. Subarrays with K Different Integers
        904. Fruit Into Baskets
        862. Shortest Subarray with Sum at Least K
        209. Minimum Size Subarray Sum

        More Good Stack Problems
        Here are some stack problems that impressed me.

        1425. Constrained Subsequence Sum
        1130. Minimum Cost Tree From Leaf Values
        907. Sum of Subarray Minimums
        901. Online Stock Span
        856. Score of Parentheses
        503. Next Greater Element II
        496. Next Greater Element I
        84. Largest Rectangle in Histogram
        42. Trapping Rain Water

        FAQ
        Q: Why doest the return value work? Why use if instead of while
        A: Please refer to the discussion of @hzfmer
        (Maybe I should summary up an explanation)

        Q: Is your first thought compared with what @hzfmer suggests?
        A: If you follow my posts, you'll know that I use them everywhere.

        Time O(N^2)
        Space O(N)
    """
    def doit_(self, A, limit):
        import bisect
        i, L = 0, []
        for j in range(len(A)):
            bisect.insort(L, A[j])
            if L[-1] - L[0] > limit:
                L.pop(bisect.bisect(L, A[i]) - 1)
                i += 1
        return j - i + 1

    """
        Solution 1: Use two heaps
        Time O(NogN)
        Space O(N)
    """
    def doit_(self, A, limit):
        import heapq
        maxq, minq = [], []
        res = i = 0
        for j, a in enumerate(A):
            heapq.heappush(maxq, [-a, j])
            heapq.heappush(minq, [a, j])
            while -maxq[0][0] - minq[0][0] > limit:
                i = min(maxq[0][1], minq[0][1]) + 1
                while maxq[0][1] < i: heapq.heappop(maxq)
                while minq[0][1] < i: heapq.heappop(minq)
            res = max(res, j - i + 1)
        return res

    """
        Solution 3: Use two deques
        Time O(N)
        Space O(N)
        Monotonic queue
    """
    def doit_slidingwindow(self, A, limit):
        import collections
        maxd = collections.deque()
        mind = collections.deque()
        i = 0

        for a in A:
            while len(maxd) and a > maxd[-1]: maxd.pop()
            while len(mind) and a < mind[-1]: mind.pop()
            maxd.append(a)
            mind.append(a)
            if maxd[0] - mind[0] > limit:
                if maxd[0] == A[i]: maxd.popleft()
                if mind[0] == A[i]: mind.popleft()
                i += 1
        return len(A) - i
   
    """
        Monotonic queue
    """
    def doit_monotonic_queue(self, nums: list, limit: int) -> int:

        from collections import deque

        l, r, ans = 0, 0, 0

        minv, maxv = deque([float('inf')]), deque([float('-inf')])

        while r < len(nums):

            while minv and minv[-1] > nums[r]:
                minv.pop()

            while maxv and maxv[-1] < nums[r]:
                maxv.pop()

            minv.append(nums[r])
            maxv.append(nums[r])

            if abs(maxv[0] - minv[0]) <= limit:
                ans = max(ans, r - l + 1)

            while l < r and abs(maxv[0] - minv[0]) > limit:

                if maxv[0] == nums[l]: 
                    maxv.popleft()

                if minv[0] == nums[l]:
                    minv.popleft()

                l += 1

            r += 1

        return ans

    def doit_monotonic_queue(self, nums: list, limit: int) -> int:

        from collections import deque

        min_vals = deque()
        max_vals = deque()
        idx = 0
        
        for num in nums:
            while min_vals and num < min_vals[-1]:
                min_vals.pop()
            
            while max_vals and num > max_vals[-1]:
                max_vals.pop()
            
            min_vals.append(num)
            max_vals.append(num)
            
            if max_vals[0] - min_vals[0] > limit:
                if nums[idx] == min_vals[0]:
                    min_vals.popleft()
                
                elif nums[idx] == max_vals[0]:
                    max_vals.popleft()
                    
                idx += 1
        
        return len(nums) - idx



            



        
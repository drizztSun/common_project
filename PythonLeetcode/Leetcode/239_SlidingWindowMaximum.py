"""
# leetcode 239 Sliding Window Maximum

# Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right.
# You can only see the k numbers in the window. Each time the sliding window moves right by one position.

# For example,
# Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.


# Window position                Max
# ---------------               -----
# [1  3  -1] -3  5  3  6  7       3
#  1 [3  -1  -3] 5  3  6  7       3
#  1  3 [-1  -3  5] 3  6  7       5
#  1  3  -1 [-3  5  3] 6  7       5
#  1  3  -1  -3 [5  3  6] 7       6
#  1  3  -1  -3  5 [3  6  7]      7

# Therefore, return the max sliding window as [3,3,5,5,6,7].

# Note:
# You may assume k is always valid, ie: 1 ? k ? input array's size for non-empty array.


# Keep indexes of good candidates in deque d. The indexes in d are from the current window,
# they’re increasing, and their corresponding nums are decreasing.
# Then the first deque element is the index of the largest window value.

# For each index i:

# Pop (from the end) indexes of smaller elements (they’ll be useless).
# Append the current index.
# Pop (from the front) the index i - k, if it’s still in the deque (it falls out of the window).
# If our window has reached size k, append the current window maximum to the output.
"""

from collections import deque


class MaxSlidingWindow:

    def doit_queue(self, nums, k: int):
        if len(nums) * k == 0:
            return []
        if k == 1:
            return nums
        deq = deque()
        for i, num in enumerate(nums[:k]):
            while deq and nums[deq[-1]] < num:
                deq.pop()
            deq.append(i)
        results = [nums[deq[0]]]
        for i, num in enumerate(nums[k:]):
            if deq and deq[0] == i:
                deq.popleft()
            while deq and nums[deq[-1]] < num:
                deq.pop()
            deq.append(i + k)
            results.append(nums[deq[0]])
        return results

    def doit_queue(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        from collections import deque
        d = deque()
        out = []

        for i, n in enumerate(nums):
            while d and nums[d[-1]] < n:
                d.pop()

            d.append(i)
            if d[0] == i - k:
                d.popleft()

            if i >= k - 1:
                out.append(nums[d[0]])
        return out


if __name__ == "__main__":

    res = MaxSlidingWindow().doit_queue([1, -1], 1)

    # [3, 3, 5, 5, 6, 7]
    res = MaxSlidingWindow().doit_queue([1,3,-1,-3,5,3,6,7], 3)

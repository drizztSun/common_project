import os


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

class maxSlidingWindow:


# Keep indexes of good candidates in deque d. The indexes in d are from the current window,
# they’re increasing, and their corresponding nums are decreasing.
# Then the first deque element is the index of the largest window value.

# For each index i:

# Pop (from the end) indexes of smaller elements (they’ll be useless).
# Append the current index.
# Pop (from the front) the index i - k, if it’s still in the deque (it falls out of the window).
# If our window has reached size k, append the current window maximum to the output.

    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        import collections
        d = collections.deque()
        out = []

        for i, n in enumerate(nums):
            while d and nums[d[-1]] < n:
                d.pop()
            d += i,
            if d[0] == i - k:
                d.popleft()
            if i >= k - 1:
                out += nums[d[0]],
        return out

    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        if not nums or len(nums) < k:
            return nums
        
        d = deque(nums[0:k])
        m = max(d)
        ans = [m]
        for i in range(k, len(nums)):
            n = nums[i]
            popped = float('-inf')
            if len(d) >= k:
                popped = d.popleft()
            d.append(n)
            if popped == m:
                m = max(d)
            elif n > m:
                m = n
            ans.append(m)
            
        return ans

    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        if not nums or k == 0:
            return []

        p, windows, maxv = 0, [], float('-inf')
        ans = []
        for c in nums:
            windows.append(c)
            if c >= maxv:
                maxv = c
                p = len(windows) - 1

            if len(windows) >= k:
                if len(windows) > k:
                    windows.pop(0)
                    if p != 0:
                        p -= 1
                    else:
                        maxv = float('-inf')
                        for i, w in enumerate(windows):
                            if w >= maxv:
                                p, maxv = i, w

                ans.append(maxv)

        return ans
                
    # O(k*n)
    def doit1(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        if not nums or k == 0:
            return []

        times = len(nums) - k + 1
        ans = []
        for i in range(times):
            ans.append(max(nums[i : i + k]))

        return ans
            



if __name__=="__main__":

    res = maxSlidingWindow().doit([1, -1], 1)

    # [3, 3, 5, 5, 6, 7]
    res = maxSlidingWindow().doit([1,3,-1,-3,5,3,6,7], 3)


    
    pass
        
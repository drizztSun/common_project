"""
487. Max Consecutive Ones II

Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.

Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
Follow up:
What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?

"""


class MaxConsecutiveOnesII:


    """
        Approach 2: Sliding Window
        Intuition

        The naive approach works but our interviewer is not convinced. Let's see how we can optimize the code we just wrote.

        The brute force solution had a time complexity of O(n^2)O(n 
        2
        ). What was the bottleneck? Checking every single consecutive sequence. Intuitively, we know we're doing repeated work because sequences overlap. We are checking consecutive sequence blindly. We need to establish some rules on how to move our sequence forward.

        If our sequence is valid, let's continue expanding our sequence (because our goal is to get the largest sequence possible).
        If our sequence is invalid, let's stop expanding and contract our sequence (because an invalid sequence will never count towards our largest sequence).
        The pattern that comes to mind for expanding/contracting sequences is the sliding window. Let's define valid and invalid states.

        Valid State = one or fewer 0's in our current sequence
        Invalid State = two 0's in our current sequence
        Algorithm

        Great. How do we apply all this to the sliding window?

        Let's use left and right pointers to keep track of the current sequence a.k.a. our window. Let's expand our window by moving the right pointer forward until we reach a point where we have more than one 0 in our window. When we reach this invalid state, let's contract our window by moving the left pointer forward until we have a valid window again. By expanding and contracting our window from valid and invalid states, we are able to traverse the array efficiently without repeated overlapping work.

        Now we can break this approach down into a few actionable steps:

        While our window is in bounds of the array...

        Add the rightmost element to our window
        Check if our window is invalid. If so, contract the window until valid.
        Update our the longest sequence we've seen so far
        Continue to expand our window

        Complexity Analysis

        Let nn be equal to the length of the input nums array.

        Time complexity : O(n). Since both the pointers only move forward, each of the left and right pointer traverse a maximum of n steps. Therefore, the timecomplexity is O(n)O(n).

        Space complexity : O(1). Same as the previous approach. We don't store anything other than variables. Thus, the space we use is constant because it is not correlated to the length of the input array.
    """
    def doit_slidingwindow(self, nums: list) -> int:
        longest_sequence = 0
        left, right = 0, 0
        num_zeroes = 0

        while right < len(nums):   # while our window is in bounds
            if nums[right] == 0:    # add the right most element into our window
                num_zeroes += 1

            while num_zeroes == 2:   # if our window is invalid, contract our window
                if nums[left] == 0:    
                    num_zeroes -= 1
                left += 1

            longest_sequence = max(longest_sequence, right - left + 1)   # update our longest sequence answer
            right += 1   # expand our window

        return longest_sequence


    def doit_greedy(self, nums: list) -> int:

        cur, prev = 0, 0
        ans = 0
        plus = 0

        for n in nums:

            if n == 0:
                ans = max(ans, cur + prev)
                prev = cur
                cur = 0
                plus = 1
            else:
                cur += 1

        ans = max(ans, cur + prev)

        return ans + plus

    def doit_dp(self, nums: list) -> list:

        flip = nonflip = 0
        ans = 0

        for n in nums:

            if n == 0:
                flip = nonflip + 1
                nonflip = 0
            else:
                flip += 1
                nonflip += 1

            ans = max(ans, flip, nonflip)

        return ans





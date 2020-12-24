"""
376. Wiggle Subsequence

A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between positive and negative.
The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a wiggle sequence.

For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative.
In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first because its first two differences are positive and the second because its last difference is zero.

Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence.
A subsequence is obtained by deleting some number of elements (eventually, also zero) from the original sequence, leaving the remaining elements in their original order.

Example 1:

Input: [1,7,4,9,2,5]
Output: 6
Explanation: The entire sequence is a wiggle sequence.
Example 2:

Input: [1,17,5,10,13,15,10,5,16,8]
Output: 7
Explanation: There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].
Example 3:

Input: [1,2,3,4,5,6,7,8,9]
Output: 2
Follow up:
Can you do it in O(n) time?


"""


class WiggleSequenceMaxLength:

    """
    Approach #2 Dynamic Programming
    Algorithm

    To understand this approach, take two arrays for dp named upup and downdown.

    Whenever we pick up any element of the array to be a part of the wiggle subsequence, that element could be a part of a rising wiggle or a falling wiggle depending upon which element we have taken prior to it.

    up[i]up[i] refers to the length of the longest wiggle subsequence obtained so far considering i^{th}i
    th
      element as the last element of the wiggle subsequence and ending with a rising wiggle.

    Similarly, down[i]down[i] refers to the length of the longest wiggle subsequence obtained so far considering i^{th}i
    th
      element as the last element of the wiggle subsequence and ending with a falling wiggle.

    up[i]up[i] will be updated every time we find a rising wiggle ending with the i^{th}i
    th
      element. Now, to find up[i]up[i], we need to consider the maximum out of all the previous wiggle subsequences ending with a falling wiggle i.e. down[j]down[j], for every j<i and nums[i]>nums[j]. Similarly, down[i]down[i] will be updated.


    **Complexity Analysis**
    Time complexity : O(n^2). Loop inside a loop.
    Space complexity : O(n). Two arrays of the same length are used for dp.
    """

    def doit_dp_slow(self, nums: list) -> int:

        if len(nums) < 2:
            return 1

        dp = [[0] * 2 for _ in range(len(nums))]

        for i in range(1, len(nums)):

            for j in range(i):

                if nums[i] > nums[j]:
                    dp[i][0] = max(dp[i][0], dp[j][1]+1)

                if nums[i] < nums[j]:
                    dp[i][1] = max(dp[i][1], dp[j][0]+1)

        return max(dp[len(nums)-1][0], dp[len(nums)-1][1])

    """
    Approach #3 Linear Dynamic Programming
    Algorithm
    
    Any element in the array could correspond to only one of the three possible states:
    
    up position, it means nums[i] > nums[i-1]
    down position, it means nums[i] < nums[i-1]
    equals to position, nums[i] == nums[i-1]
    
    The updates are done as:
    
    If nums[i] > nums[i-1], that means it wiggles up. The element before it must be a down position. 
    So up[i] = down[i-1] + 1 and down[i] remains the same as down[i−1]. 
    
    If nums[i] < nums[i-1], that means it wiggles down. 
    The element before it must be a up position. So down[i] = up[i-1] + 1, up[i] remains the same as up[i-1]. 
    
    If nums[i] == nums[i-1], that means it will not change anything because it didn't wiggle at all. 
    So both down[i] and up[i] remain the same as down[i-1] and up[i−1].
    
    At the end, we can find the larger out of up[length-1] and down[length-1] to find the max. 
    wiggle subsequence length, where length refers to the number of elements in the given array.
    
    The process can be illustrated with the following example:
    """
    def doit_dp(self, nums: list) -> int:

        if not nums:
            return 0

        dp = [[0] * 2 for _ in range(len(nums))]
        dp[0][0] = dp[0][1] = 1

        for i in range(1, len(nums)):

            if nums[i] > nums[i - 1]:
                dp[i][0] = dp[i - 1][1] + 1
                dp[i][1] = dp[i - 1][1]

            elif nums[i] < nums[i - 1]:
                dp[i][0] = dp[i - 1][0]
                dp[i][1] = dp[i - 1][0] + 1

            else:
                dp[i][0] = dp[i - 1][0]
                dp[i][1] = dp[i - 1][1]

        return max(dp[-1][0], dp[-1][1])

    """
    memory optimization
    """
    def doit_dp(self, nums):

        if not nums:
            return 0

        down = up = 1

        for i in range(1, len(nums)):

            if nums[i] > nums[i-1]:
                up = down + 1
            if nums[i] < nums[i-1]:
                down = up + 1

        return max(down, up)





if __name__ == '__main__':

    WiggleSequenceMaxLength().doit_dp([1,7,4,9,2,5])

    WiggleSequenceMaxLength().doit_dp([1,17,5,10,13,15,10,5,16,8])

    WiggleSequenceMaxLength().doit_dp([1,2,3,4,5,6,7,8,9])

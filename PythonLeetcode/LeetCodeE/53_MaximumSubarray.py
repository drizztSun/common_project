"""
53. Maximum Subarray

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.



Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
Example 2:

Input: nums = [1]
Output: 1
Example 3:

Input: nums = [0]
Output: 0
Example 4:

Input: nums = [-1]
Output: -1
Example 5:

Input: nums = [-2147483647]
Output: -2147483647

"""


class MaxSubArray:

    def doit_dp(self, nums):

        res, total = 0, 0
        for c in nums:
            total = max(c, total + c)
            res = max(res, total)
        return res

    """
    Divide and Conquer

    This problem is better done using the normal single pass approach.
    But for those interested in Divide an Conquer, the logic is as follows:
    
    the divide step divides the array into left and right halves and recursively solves for both of them
    Each subproblem takes the following parameters as input
    maximum_sub_array_sum_rec(arr, st, end)
    (arr, st, end) => represents, the portion of the array corresponding to the subproblem.
    and returns the following tuple.
    left_sum, left_index, right_sum, right_index, max_sum
    left_sum = maximum sum of subarray starting from leftmost index.
    left_index = the index where the left_sum ends
    right_sum = maximum sum of subarray starting from rightmost index.
    right_index = the index where the right_sum ends
    max_sum = the result value, indicating the maximum sub array sum
    
    The merge step:
    the result for the combination of the 2 sub arrays, is the maximum of the following :
    a) solution for left sub array,
    b) solution for right sub array,
    c) sub array formed by combining the right_sum portion of left sub array + left_sum portion of the right sub array
    
    Once we have the solution, we need to recalculate the left_sum, left_index, right_sum, right_index portions for the merged array, 
    for which we will reuse the left_sum, left_index and right_sum, right_index values that we obtained from both the left and right halves.
    """

    def doit_divide_and_conquer(self, nums):

        def search(arr, s, e):

            if s > e:
                return float('-inf')

            if e == s:
                return nums[s]

            m = (s + e) // 2

            l = search(arr, s, m)
            r = search(arr, m+1, e)

            ml, tml = float('-inf'), 0
            for i in reversed(range(s, m+1)):
                tml += nums[i]
                ml = max(ml, tml)

            mr, tmr = float('-inf'), 0
            for j in range(m+1, e+1):
                tmr += nums[j]
                mr = max(mr, tmr)

            return max(l, r, ml + mr)

        return search(nums, 0, len(nums)-1)


if __name__ == '__main__':

    print(MaxSubArray().doit_divide_and_conquer([-2,1,-3,4,-1,2,1,-5,4]))

    print(MaxSubArray().doit_divide_and_conquer([-1, -2]))




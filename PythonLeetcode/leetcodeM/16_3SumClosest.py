"""
16. 3Sum Closest

Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target.
Return the sum of the three integers. You may assume that each input would have exactly one solution.



Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

"""
"""
Solution
This problem is a variation of 3Sum. The main difference is that the sum of a triplet is not necessarily equal to the target. 
Instead, the sum is in some relation with the target, which is closest to the target for this problem. In that sense, this problem shares similarities with 3Sum Smaller.

Before jumping in, let's check solutions for the similar problems:

3Sum fixes one number and uses either the two pointers pattern or a hash set to find complementary pairs. Thus, the time complexity is \mathcal{O}(n^2)O(n 
2
 ).

3Sum Smaller, similarly to 3Sum, uses the two pointers pattern to enumerate smaller pairs. Note that we cannot use a hash set here because we do not have a specific value to look up.

For the same reason as for 3Sum Smaller, we cannot use a hash set approach here. So, we will focus on the two pointers pattern and shoot for \mathcal{O}(n^2)O(n 
2
 ) time complexity as the best conceivable runtime (BCR).


"""


class ThreeSumClosest:

    """
        Approach 1: Two Pointers
        The two pointers pattern requires the array to be sorted, so we do that first. As our BCR is \mathcal{O}(n^2), the sort operation would not change the overall time complexity.

        In the sorted array, we process each value from left to right. For value v, we need to find a pair which sum, ideally,
        is equal to target - v. We will follow the same two pointers approach as for 3Sum, however, since this 'ideal' pair may not exist,
        we will track the smallest absolute difference between the sum and the target.
        The two pointers approach naturally enumerates pairs so that the sum moves toward the target.

        Algorithm

        Initialize the minimum difference diff with a large value.
        Sort the input array nums.
        Iterate through the array:
        For the current position i, set lo to i + 1, and hi to the last index.
        While the lo pointer is smaller than hi:
        Set sum to nums[i] + nums[lo] + nums[hi].
        If the absolute difference between sum and target is smaller than the absolute value of diff:
        Set diff to target - sum.
        If sum is less than target, increment lo.
        Else, decrement hi.
        If diff is zero, break from the loop.
        Return the value of the closest triplet, which is target - diff.
    """

    def doit_twopointerss(self, nums, target):

        diff = float('inf')
        nums.sort()
        
        for i in range(len(nums)):
            lo, hi = i + 1, len(nums) - 1
        
            while (lo < hi):
        
                sum = nums[i] + nums[lo] + nums[hi]
        
                if abs(target - sum) < abs(diff):
                    diff = target - sum
        
                if sum < target:
                    lo += 1
                else:
                    hi -= 1
        
            if diff == 0:
                break
        
        return target - diff
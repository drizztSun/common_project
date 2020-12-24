"""
280. Wiggle Sort

Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

Example:

Input: nums = [3,5,2,1,6,4]
Output: One possible answer is [3,5,1,6,2,4]


"""


class WiggleSort:

    """
    Approach #1 (Sorting) [Accepted]
    The obvious solution is to just sort the array first, then swap elements pair-wise starting from the second element. For example:

       [1, 2, 3, 4, 5, 6]
           ↑  ↑  ↑  ↑
           swap  swap

    => [1, 3, 2, 5, 4, 6]

    Complexity analysis

    Time complexity : O(nlogn). The entire algorithm is dominated by the sorting step, which costs O(n \log n)O(nlogn) time to sort nn elements.

    Space complexity : O(1). Space depends on the sorting implementation which, usually, costs O(1)O(1) auxiliary space if heapsort is used.

    """
    def doit_(self, nums: list) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        nums.sort()
        for i in range(1, len(nums)):
            if i + 1 < len(nums):
                nums[i], nums[i+1] = nums[i+1], nums[i]



    """
    Approach #2 (One-pass Swap) [Accepted]
    Intuitively, we should be able to reorder it in one-pass. As we iterate through the array, we compare the current element to its next element and if the order is incorrect, we swap them
    
    Complexity analysis

    Time complexity : O(n). In the worst case we swap at most n/2 times. An example input is [2,1,3,1,4,1].
    
    Space complexity : O(1).
    """
    def doit_1(self, nums: list) -> None:

        less = True

        for i in range(len(nums) - 1):

            if less:
                if nums[i] > nums[i+1]:
                    nums[i], nums[i+1] = nums[i+1], nums[i]
            else:
                if nums[i] < nums[i+1]:
                    nums[i], nums[i+1] = nums[i+1], nums[i]

            less = not less

    def doit_2(self, nums: list) -> None:

        for i in range(len(nums) - 1):
            if i % 2 == 0 and nums[i] > nums[i+1] or i % 2 == 1 and nums[i] < nums[i+1]:
                nums[i], nums[i+1] = nums[i+1], nums[i]

    def doit_3(self, nums: list) -> None:

        for i in range(len(nums)-1):
            if (i % 2 == 0) == (nums[i] > nums[i+1]):
                nums[i], nums[i+1] = nums[i+1], nums[i]
"""
33. Search in Rotated Sorted Array

You are given an integer array nums sorted in ascending order, and an integer target.

Suppose that nums is rotated at some pivot unknown to you beforehand (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

If target is found in the array return its index, otherwise, return -1.



Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1


Constraints:

1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
All values of nums are unique.
nums is guranteed to be rotated at some pivot.
-10^4 <= target <= 10^4

"""


class Search:

    """
    Approach 2: One-pass Binary Search
    Instead of going through the input array in two passes, we could achieve the goal in one pass with an revised binary search.

    The idea is that we add some additional condition checks in the normal binary search in order to better narrow down the scope of the search.

    Algorithm

    As in the normal binary search, we keep two pointers (i.e. start and end) to track the search scope. At each iteration, we reduce the search scope into half, by moving either the start or end pointer to the middle (i.e. mid) of the previous search scope.

    Here are the detailed breakdowns of the algorithm:

    Initiate the pointer start to 0, and the pointer end to n - 1.

    Perform standard binary search. While start <= end:

    Take an index in the middle mid as a pivot.

    If nums[mid] == target, the job is done, return mid.

    Now there could be two situations:

    Pivot element is larger than the first element in the array, i.e. the subarray from the first element to the pivot is non-rotated, as shown in the following graph.

    Complexity Analysis

    Time complexity: \mathcal{O}(\log{N})O(logN).
    Space complexity: \mathcal{O}(1)O(1).
    """


    def doit(self, nums, target):

        start, end = 0, len(nums) - 1
        while start <= end:
            mid = start + (end - start) // 2
            if nums[mid] == target:
                return mid
            elif nums[mid] >= nums[start]:
                if target >= nums[start] and target < nums[mid]:
                    end = mid - 1
                else:
                    start = mid + 1
            else:
                if target <= nums[end] and target > nums[mid]:
                    start = mid + 1
                else:
                    end = mid - 1
        return -1
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

    def doit_(self, nums: List[int], target: int) -> int:
                
        low, high = 0, len(nums)-1
        
        while low <= high:
            
            mid = (low + high) // 2
            
            if target == nums[mid]:
                return mid
            
            elif nums[mid] >= nums[low]:
                
                if target >= nums[low] and target < nums[mid]:
                    high = mid - 1
                else:
                    low = mid + 1
                    
            else:
                
                if target > nums[mid] and target <= nums[high]:
                    low = mid + 1
                else:
                    high = mid - 1
                    
        return -1

    """
    Approach 1: Binary search
    The problem is to implement a search in O(logN) time that gives an idea to use a binary search.

    The algorithm is quite straightforward :

    Find a rotation index rotation_index, i.e. index of the smallest element in the array. Binary search works just perfect here.

    rotation_index splits array in two parts. Compare nums[0] and target to identify in which part one has to look for target.

    Perform a binary search in the chosen part of the array.

    """
    def search(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        def find_rotate_index(left, right):
            if nums[left] < nums[right]:
                return 0

            while left <= right:
                pivot = (left + right) // 2
                if nums[pivot] > nums[pivot + 1]:
                    return pivot + 1
                else:
                    if nums[pivot] < nums[left]:
                        right = pivot - 1
                    else:
                        left = pivot + 1

        def search(left, right):
            """
            Binary search
            """
            while left <= right:
                pivot = (left + right) // 2
                if nums[pivot] == target:
                    return pivot
                else:
                    if target < nums[pivot]:
                        right = pivot - 1
                    else:
                        left = pivot + 1
            return -1

        n = len(nums)

        if n == 1:
            return 0 if nums[0] == target else -1

        rotate_index = find_rotate_index(0, n - 1)

        # if target is the smallest element
        if nums[rotate_index] == target:
            return rotate_index
        # if array is not rotated, search in the entire array
        if rotate_index == 0:
            return search(0, n - 1)
        if target < nums[0]:
            # search on the right side
            return search(rotate_index, n - 1)
        # search on the left side
        return search(0, rotate_index)

    """
    Approach 2: One-pass Binary Search
    Instead of going through the input array in two passes, we could achieve the goal in one pass with an revised binary search.

    The idea is that we add some additional condition checks in the normal binary search in order to better narrow down the scope of the search.

    Algorithm

    As in the normal binary search, we keep two pointers (i.e. start and end) to track the search scope. At each iteration, we reduce the search scope into half, 
    by moving either the start or end pointer to the middle (i.e. mid) of the previous search scope.

    Here are the detailed breakdowns of the algorithm:

    Initiate the pointer start to 0, and the pointer end to n - 1.

    Perform standard binary search. While start <= end:

    Take an index in the middle mid as a pivot.

    If nums[mid] == target, the job is done, return mid.

    Now there could be two situations:

    Pivot element is larger than the first element in the array, i.e. the subarray from the first element to the pivot is non-rotated, as shown in the following graph.

    Complexity Analysis

    Time complexity: O(logN).
    Space complexity: O(1).
    """
    def doit_binary_search(self, nums, target):

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
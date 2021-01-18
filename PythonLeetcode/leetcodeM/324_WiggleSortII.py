"""
324. Wiggle Sort II

Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:

Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].
Example 2:

Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].
Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?


"""


class WiggleSort:

    # O(nlogn)
    def doit_sort(self, nums: list) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        nums.sort()
        half = len(nums[::2]) - 1
        nums[::2], nums[1::2] = nums[half::-1], nums[:half:-1]

    # O(n)
    def doit(self, nums: list) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        import random
        mid = len(nums) // 2

        def quickselect(arr, lo, hi, k):
            pivot = random.randint(lo, hi)
            arr[pivot], arr[hi] = arr[hi], arr[pivot]
            pivot = lo
            for i in range(lo, hi):
                if arr[i] < arr[hi]:
                    arr[i], arr[pivot] = arr[pivot], arr[i]
                    pivot += 1
            arr[pivot], arr[hi] = arr[hi], arr[pivot]
            if k == pivot:
                return arr[pivot]
            elif k < pivot:
                return quickselect(arr, lo, pivot - 1, k)
            else:
                return quickselect(arr, pivot + 1, hi, k)

        median = quickselect(nums, 0, len(nums) - 1, mid)

        # virtual index
        vi = lambda x: x * 2 + 1 if x < mid else (x - mid) * 2
        i, j, k = 0, 0, len(nums) - 1
        while j <= k:
            if nums[vi(j)] < median:
                nums[vi(j)], nums[vi(k)] = nums[vi(k)], nums[vi(j)]
                k -= 1
            elif nums[vi(j)] > median:
                nums[vi(j)], nums[vi(i)] = nums[vi(i)], nums[vi(j)]
                i += 1
                j += 1
            else:
                j += 1


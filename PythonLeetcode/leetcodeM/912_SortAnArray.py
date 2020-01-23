# 912. Sort an Array

# Given an array of integers nums, sort the array in ascending order.

# Example 1:

# Input: nums = [5,2,3,1]
# Output: [1,2,3,5]

# Example 2:

# Input: nums = [5,1,1,2,0,0]
# Output: [0,0,1,1,2,5]


# Constraints:

# 1 <= nums.length <= 50000
# -50000 <= nums[i] <= 50000

class SortArray:
    def doit(self, nums):

        def quick_sort(A, s, e):
            if e - s < 2:
                return s

            base = A[s]
            i, j = s, s + 1
            while i < e:
                if A[i] < base:
                    A[i], A[j] = A[j], A[i]
                    j += 1
                i += 1

            A[s], A[j-1] = A[j-1], A[s]
            return j-1

        def sort(A, s, e):
            if e - s < 2:
                return

            k = quick_sort(A, s, e)
            sort(A, s, k)
            sort(A, k+1, e)

        sort(nums, 0, len(nums))
        return nums


if __name__ == '__main__':

    res = SortArray().doit(nums=[5, 2, 3, 1])  # [1,2,3,5]

    res = SortArray().doit(nums=[5, 1, 1, 2, 0, 0])  # [0,0,1,1,2,5]

    pass

"""
611. Valid Triangle Number


Given an array consists of non-negative integers, your task is to count the number of triplets chosen
from the array that can make triangles if we take them as side lengths of a triangle.

Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are:
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
Note:
The length of the given array won't exceed 1000.
The integers in the given array are in the range of [0, 1000].

"""


class TriangleNumber:

    def doit_(self, nums: list) -> int:
        n = len(nums)
        if n < 3:
            return 0

        ans = 0
        nums.sort()
        for k in range(n - 1, 1, -1):
            target = nums[k]
            i, j = 0, k - 1

            while i < j:
                if nums[i] + nums[j] > target:
                    ans += j - i
                    j -= 1
                else:
                    i += 1

        return ans


if __name__ == '__main__':

    TriangleNumber().doit_([2, 2, 3, 4])


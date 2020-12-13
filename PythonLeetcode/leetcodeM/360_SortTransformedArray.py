"""
360. Sort Transformed Array

Given a sorted array of integers nums and integer values a, b and c.
Apply a quadratic function of the form f(x) = ax2 + bx + c to each element x in the array.

The returned array must be in sorted order.

Expected time complexity: O(n)

Example 1:

Input: nums = [-4,-2,2,4], a = 1, b = 3, c = 5
Output: [3,9,15,33]
Example 2:

Input: nums = [-4,-2,2,4], a = -1, b = 3, c = 5
Output: [-23,-5,1,7]


"""


class SortTransformedArray:

    def doit_(self, nums: list, a: int, b: int, c: int) -> list:

        def getvalue(v):
            return a * v ** 2 + b * v + c

        if a == 0:
            ans = [getvalue(c) for c in nums]
            return ans if b > 0 else ans[::-1]

        base = -b / (2.0 * a)
        left, right = 0, len(nums) - 1
        ans = []

        while left <= right:

            if abs(nums[left] - base) > abs(nums[right] - base):
                ans.append(getvalue(nums[left]))
                left += 1
            else:
                ans.append(getvalue(nums[right]))
                right -= 1

        return ans if a < 0 else ans[::-1]


if __name__ == '__main__':

    SortTransformedArray().doit_([-4,-2,2,4], -1, 3, 5)






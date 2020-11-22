"""
1664. Ways to Make a Fair Array

You are given an integer array nums. You can choose exactly one index (0-indexed) and remove the element. Notice that the index of the elements may change after the removal.

For example, if nums = [6,1,7,4,1]:

Choosing to remove index 1 results in nums = [6,7,4,1].
Choosing to remove index 2 results in nums = [6,1,4,1].
Choosing to remove index 4 results in nums = [6,1,7,4].
An array is fair if the sum of the odd-indexed values equals the sum of the even-indexed values.

Return the number of indices that you could choose such that after the removal, nums is fair.



Example 1:

Input: nums = [2,1,6,4]
Output: 1
Explanation:
Remove index 0: [1,6,4] -> Even sum: 1 + 4 = 5. Odd sum: 6. Not fair.
Remove index 1: [2,6,4] -> Even sum: 2 + 4 = 6. Odd sum: 6. Fair.
Remove index 2: [2,1,4] -> Even sum: 2 + 4 = 6. Odd sum: 1. Not fair.
Remove index 3: [2,1,6] -> Even sum: 2 + 6 = 8. Odd sum: 1. Not fair.
There is 1 index that you can remove to make nums fair.
Example 2:

Input: nums = [1,1,1]
Output: 3
Explanation: You can remove any index and the remaining array is fair.
Example 3:

Input: nums = [1,2,3]
Output: 0
Explanation: You cannot make a fair array after removing any index.


Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 104

"""


class WaysToFairArray:

    def doit_twopointer(self, nums: list) -> int:
        def waysToBalance(self, nums: list) -> int:
            n = len(nums)
            evens = [nums[0]] * n
            odds = [0] * n
            for i in range(1, n):
                if i % 2:
                    odds[i] = nums[i] + odds[i - 1]
                    evens[i] = evens[i - 1]
                else:
                    odds[i] = odds[i - 1]
                    evens[i] = nums[i] + evens[i - 1]
            ans = 0

            for i in range(n):
                if i % 2:
                    odd = odds[i - 1] + evens[-1] - evens[i]
                    even = evens[i] + odds[-1] - odds[i]
                else:
                    if i == 0:
                        even = odds[-1]
                        odd = evens[-1] - evens[0]
                    else:
                        even = evens[i - 1] + odds[-1] - odds[i]
                        odd = odds[i] + evens[-1] - evens[i]
                if odd == even:
                    ans += 1
            return ans

    def doit_(self, nums: list) -> int:
        from collections import deque

        right = deque()
        for i in range(len(nums) - 1, -1, -1):
            if 1 % 2 == 1:
                right.appendleft([nums[i], 0])
            else:
                right.appendleft([0, nums[i]])

            if len(right) > 1:
                right[0][0] += right[1][0]
                right[0][1] += right[1][1]

        left = deque()
        for i in range(len(nums)):
            left.append([nums[i], 0] if 1 % 2 == 1 else [0, nums[i]])
            if len(left) > 1:
                left[i][0] += left[i - 1][0]
                left[i][1] += left[i - 1][1]

        print(right)
        print(left)

        res = 0
        for i in range(len(nums)):

            if i == 0 and right[i + 1][0] == right[i + 1][1]:
                res += 1
                continue

            if i == len(nums) - 1 and left[i - 1][0] == left[i - 1][1]:
                res += 1
                continue

            if 0 < i < len(nums) - 1 and left[i - 1][0] + right[i + 1][1] == left[i - 1][1] + right[i + 1][0]:
                res += 1

        return res


if __name__ == '__main__':

    WaysToFairArray().waysToMakeFair([2, 1, 6, 4])
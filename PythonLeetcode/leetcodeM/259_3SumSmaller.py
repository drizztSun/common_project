"""
259. 3Sum Smaller

Given an array of n integers nums and an integer target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

Follow up: Could you solve it in O(n2) runtime?



Example 1:

Input: nums = [-2,0,1,3], target = 2
Output: 2
Explanation: Because there are two triplets which sums are less than 2:
[-2,0,1]
[-2,0,3]
Example 2:

Input: nums = [], target = 0
Output: 0
Example 3:

Input: nums = [0], target = 0
Output: 0

"""


class ThreeSumSmaller:

    """
    Approach #3 (Two Pointers) [Accepted]
    Let us try sorting the array first. For example, nums = [3,5,2,8,1]nums=[3,5,2,8,1] becomes [1,2,3,5,8][1,2,3,5,8].

    Let us look at an example nums = [1,2,3,5,8]nums=[1,2,3,5,8], and target = 7target=7.

    [1, 2, 3, 5, 8]
     ↑           ↑
    left       right
    Let us initialize two indices, leftleft and rightright pointing to the first and last element respectively.

    When we look at the sum of first and last element, it is 1 + 8 = 91+8=9, which is \geq target≥target. That tells us no index pair will ever contain the index rightright. So the next logical step is to move the right pointer one step to its left.

    [1, 2, 3, 5, 8]
     ↑        ↑
    left    right
    Now the pair sum is 1 + 5 = 61+5=6, which is < target<target. How many pairs with one of the index = leftindex=left that satisfy the condition?
    You can tell by the difference between rightright and leftleft which is 33, namely (1,2), (1,3),(1,2),(1,3), and (1,5)(1,5).
    Therefore, we move leftleft one step to its right.

    Complexity analysis

    Time complexity : O(n^2). The twoSumSmaller function takes O(n)O(n) time because both left and right traverse at most n steps.
    Therefore, the overall time complexity is O(n^2).

    Space complexity : O(1).
    """
    def doit_twopointer(self, nums, target):

        nums.sort()
        res = 0

        for i in range(len(nums)-2):

            subTarget = target - nums[i]

            low, high = i+1, len(nums-1)

            while low < high:

                if nums[low] + nums[high] < subTarget:
                    res += high - low
                    low += 1
                else:
                    high -= 1
        return res

    def doit_twopointer(self, nums: list, target: int) -> int:
        from bisect import bisect_right, insort
        if len(nums) < 3:
            return 0
        ans = 0
        sorted_left = [nums[0]]
        for i in range(1, len(nums) - 1):
            for j in range(i + 1, len(nums)):
                ans += bisect_right(sorted_left, target - nums[i] - nums[j] - 1)
                print(ans)

            insort(sorted_left, nums[i])

        return ans
"""

448. Find All Numbers Disappeared in an Array


Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]



"""


class FindDisappearedNumbers:

    def doit_(self, nums: list) -> list:

        i = 0
        while i < len(nums):
            while nums[i] != i + 1 and nums[i] != nums[nums[i] - 1]:
                # python date swap issue. have to use a tmp variable.
                tmp = nums[i]
                nums[i], nums[tmp - 1] = nums[tmp - 1], tmp
            i += 1

        return [i + 1 for i in range(len(nums)) if nums[i] != i + 1]


if __name__ == '__main__':

    FindDisappearedNumbers().doit_([4,3,2,7,8,2,3,1])
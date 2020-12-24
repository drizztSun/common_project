"""
90. Subsets II

Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]


"""


class SubsetII:

    def doit_1(self, nums: list) -> list:
        res, last, temp = [[]], None, [[]]
        for num in sorted(nums):
            if num == last:
                temp = [[num] + target for target in temp]
            else:
                temp = [[num] + target for target in res]

            res += temp
            last = num
        return res

    def doit_2(self, nums: list) -> list:
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        def dfs(nums, index, path, rv):
            rv.append(path)
            last = None
            for i in range(index, len(nums)):
                if last != nums[i]:
                    dfs(nums, i+1, path+[nums[i]], rv)
                last = nums[i]

        rv = []
        dfs(sorted(nums), 0, [], rv)
        return rv






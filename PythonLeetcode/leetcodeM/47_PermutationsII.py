"""
46. Permutations

Given a collection of distinct integers, return all possible permutations.

Example:

Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

"""


class Permute:

    """
    Approach 1: Backtracking
    Backtracking is an algorithm for finding all solutions by exploring all potential candidates.
    If the solution candidate turns to be not a solution (or at least not the last one), backtracking algorithm discards it
    by making some changes on the previous step, i.e. backtracks and then try again.

    Here is a backtrack function which takes the index of the first integer to consider as an argument backtrack(first).

    If the first integer to consider has index n that means that the current permutation is done.
    Iterate over the integers from index first to index n - 1.
    Place i-th integer first in the permutation, i.e. swap(nums[first], nums[i]).
    Proceed to create all permutations which starts from i-th integer : backtrack(first + 1).
    Now backtrack, i.e. swap(nums[first], nums[i]) back.
    """

    def doit(self, nums):

        def helper(nums, cur, results):
            if cur == len(nums):
                results.append(nums.copy())

            for i in range(cur, len(nums)):
                nums[cur], nums[i] = nums[i], nums[cur]
                helper(nums, cur + 1, results)
                nums[cur], nums[i] = nums[i], nums[cur]

        results = []
        helper(nums, 0, results)
        return results

    def doit(self, nums):

        def dfs(numbers):

            if not numbers:
                return [[]]

            res = []
            for i in range(len(numbers)):

                for c in dfs(numbers[:i] + numbers[i + 1:]):
                    res.append([numbers[i]] + c)

            return res

        return dfs(nums)


"""

47. Permutations II


Given a collection of numbers that might contain duplicates, return all possible unique permutations.

Example:

Input: [1,1,2]
Output:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
"""


class PermuteUnique:

    def doit(self, nums):
        nums.sort()

        def helper(a):

            if len(a) == 1:
                return [a]

            res = []
            for i in range(len(a)):
                if i != len(a) - 1 and a[i] == a[i + 1]:
                    continue

                for c in helper(a[:i] + a[i + 1:]):
                    res.append([a[i]] + c)

            return res

        return helper(nums)

    def doit(self, nums):

        from collections import Counter

        results = []
        def backtrack(comb, counter):
            if len(comb) == len(nums):
                # make a deep copy of the resulting permutation,
                # since the permutation would be backtracked later.
                results.append(list(comb))
                return

            for num in counter:
                if counter[num] > 0:
                    # add this number into the current combination
                    comb.append(num)
                    counter[num] -= 1
                    # continue the exploration
                    backtrack(comb, counter)
                    # revert the choice for the next exploration
                    comb.pop()
                    counter[num] += 1

        backtrack([], Counter(nums))

        return results
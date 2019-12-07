

# Given a collection of distinct integers, return all possible permutations.

# Example:

# Input: [1,2,3]
# Output:
# [
#  [1,2,3],
#  [1,3,2],
#  [2,1,3],
#  [2,3,1],
#  [3,1,2],
#  [3,2,1]
# ]


class Permute46:

    def doit(self, nums):

        def helper(a):
            if len(a) <= 1:
                return [a]

            res = []
            for i in range(0, len(a)):
                for c in helper(a[:i] + a[i+1:]):
                    res.append([a[i]] + c)

            return res

        return helper(nums)

    def doit1(self, nums):

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


if __name__ == "__main__":

    print(Permute46().doit([1, 2, 3]))

    print(Permute46().doit1([1, 2, 3]))

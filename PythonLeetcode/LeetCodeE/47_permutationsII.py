
# 47. Permutations II

# Given a collection of numbers that might contain duplicates, return all possible unique permutations.

# Example:

# Input: [1,1,2]
# Output:
# [
#  [1,1,2],
#  [1,2,1],
#  [2,1,1]
# ]


class PermuteUnique:

    def doit(self, nums):

        def helper(a):

            nums.sort()

            if len(a) == 1:
                return [a]

            res = []
            for i in range(len(a)):
                if i != len(a) - 1 and a[i] == a[i+1]:
                    continue

                for c in helper(a[:i] + a[i+1:]):
                    res.append([a[i]] + c)

            return res

        return helper(nums)

    def doit1(self, nums):
        nums = sorted(nums)

        def permute(i, ret):
            if i == len(nums):
                return ret
            # print('here', i, ret)
            temp = []

            for x in ret:
                for j in range(len(x) + 1):
                    t = x.copy()
                    # print(a[j-1], a[i])
                    if j-1 >= 0 and x[j-1] == nums[i]:
                        break
                    t.insert(j, nums[i])
                    temp.append(t)
            return permute(i+1, temp)

        return permute(0, [[]])


if __name__ == "__main__":

    print(PermuteUnique().doit([1, 1, 2]))

    print(PermuteUnique().doit([1, 2, 2, 3, 3, 4, 5]))

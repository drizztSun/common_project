"""
564 backpack VI

# Given a array, nums, all element are positive. and there are no same ones.
# we need to find out all possible combination


# Sample
# when nums = [1, 2, 4], target = 4
# all composition is
# [1, 1, 1, 1]
# [1, 1, 2]
# [1, 2, 1]
# [2, 1, 1]
# [2, 2]
# [4]

# return 6

"""


class BackPackVI:
    """
    @param nums: an integer array and all positive numbers, no duplicates
    @param target: An integer
    @return: An integer
    """
    def doit(self, nums, target):
        # write your code here
        cnt = [0 for _ in range(target+1)]
        cnt[0] = 1

        for i in range(1, target+1):
            for j in range(len(nums)):
                if i >= nums[j]:
                    cnt[i] += cnt[i - nums[j]]
        return cnt[-1]

    """
    @param nums: an integer array and all positive numbers, no duplicates
    @param target: An integer
    @return: An integer
    """
    def doit1(self, nums, target):
        # write your code here
        nums.sort()
        cnt = [0 for _ in range(target+1)]
        cnt[0] = 1

        for i in range(1, target+1):
            for j in range(len(nums)):
                if i >= nums[j]:
                    cnt[i] += cnt[i - nums[j]]
                else:
                    break
        return cnt[-1]


if __name__ == "__main__":

    res = BackPackVI().doit([1, 2, 4], 4)
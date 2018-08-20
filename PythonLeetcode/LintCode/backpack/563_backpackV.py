

# 563 backpack V

# Given n items with size nums[i] which an integer array and all positive numbers.
# An integer target denotes the size of a backpack. Find the number of possible fill the backpack.

# Each item may only be used once

# Example
# Given candidate items [1,2,3,3,7] and target 7,

# A solution set is:
# [7]
# [1, 3, 3]
# return 2



class BackPackV:

    """
    @param nums: an integer array and all positive numbers
    @param target: An integer
    @return: An integer
    """
    def doit1(self, nums, target):

        if target > sum(nums):
            return 0

        dp = {V: None for V in range(target + 1)}
        dp[0] = []

        for c in nums:

            for i in reversed(range(1, target + 1)):

                if i >= c and (dp[i-c] or dp[i-c] == []):
                    if not dp[i]:
                        dp[i] = []

                    if not dp[i-c]:
                        dp[i].append([c])
                    else:
                        for k in dp[i-c]:
                            dp[i].append(k + [c])

        return dp[target]

    """
    @param nums: an integer array and all positive numbers
    @param target: An integer
    @return: An integer
    """
    def doit(self, nums, target):
        # write your code here
        dp = [0 for _ in range(target + 1)]
        dp[0] = 1

        for c in nums:
            for i in reversed(range(target + 1)):
                if i >= c:
                    dp[i] += dp[i - c]

        return dp[-1]

    """
    @param nums: an integer array and all positive numbers
    @param target: An integer
    @return: An integer
    """
    def doit(self, nums, target):
        # write your code here
        dp = [0 for _ in range(target + 1)]
        dp[0] = 1

        for c in nums:
            for i in reversed(c, range(target + 1)):
                dp[i] += dp[i - c]

        return dp[-1]



    """
    @param nums: an integer array and all positive numbers
    @param target: An integer
    @return: An integer
    """
    def doit(self, nums, target):
        nums.sort()
        dp = [0 for _ in range(target + 1)]
        dp[0] = 1

        for c in nums:
            for i in reversed(range(target + 1)):
                if i >= c:
                    dp[i] += dp[i - c]
                else:
                    break

        return dp[-1]


if __name__ == "__main__":

    res = BackPackV().doit1([1, 2, 3, 3, 7], 7)

    pass




# 562 Backpack IV

class BackPackIV:
    """
    @param nums: an integer array and all positive numbers, no duplicates
    @param target: An integer
    @return: An integer
    """
    def doit(self, nums, target):
        # write your code here
        dp = [0 for _ in range(target+1)]
        dp[0] = 1

        for c in nums:

            for i in range(c, target + 1):

                dp[i] += dp[i-c]

        return dp[-1]


if __name__ == "__main__":

    res = BackPackIV().doit([2, 3, 6, 7], 7)

    pass
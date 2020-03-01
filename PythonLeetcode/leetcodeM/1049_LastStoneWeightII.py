# 1049. Last Stone Weight II

# We have a collection of rocks, each rock has a positive integer weight.

# Each turn, we choose any two rocks and smash them together.  Suppose the stones have weights x and y with x <= y.
# The result of this smash is:

# If x == y, both stones are totally destroyed;
# If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
# At the end, there is at most 1 stone left.
# Return the smallest possible weight of this stone (the weight is 0 if there are no stones left.)

# Example 1:

# Input: [2,7,4,1,8,1]
# Output: 1
# Explanation:
# We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
# we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
# we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
# we can combine 1 and 1 to get 0 so the array converts to [1] then that's the optimal value.


class LastStoneWeightII:

    """
    the goal is to check if partial sums can be reached range from [min(stones), sum(stones)//2]
    then to find the last possible partial sums and return abs(2*psum - total_sum)
    """

    def doit(self, stones):

        total = sum(stones)
        start = min(stones)

        # every possible weight value, if dp[i] == true, i is a sum of partial weight of sub array
        dp = [False] * (total // 2 + 1)
        dp[0] = True

        for s in stones:
            # From partial array max to min val
            for i in range(total // 2, start - 1, -1):
                # i is possible weight, s is a element weight,
                # i - s is true, i could be a weight of sub array (i-s) + s
                # dp[s] will be true, because of just one element
                if s <= i and dp[i-s]:
                    dp[i] = True

        for i in range(len(dp) - 1, -1, -1):
            if dp[i]:
                # the most weight of paritial sum will be the answer
                return abs(2 * i - total)


if __name__ == '__main__':

    res = LastStoneWeightII().doit([2, 7, 4, 1, 8, 1])

    pass

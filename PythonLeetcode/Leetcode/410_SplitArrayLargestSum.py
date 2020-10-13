"""
# 410. Split Array Largest Sum

# Given an array which consists of non-negative integers and an integer m,
# you can split the array into m non-empty continuous subarrays.
# Write an algorithm to 'minimize' the largest sum among of these m subarrays.

# Note:
# If n is the length of array, assume the following constraints are satisfied:

# 1 <= n <= 1000
# 1 <= m <= min(50, n)

# Examples:

# Input:
# nums = [7,2,5,10,8]
# m = 2

# Output:
# 18

# Explanation:
# There are four ways to split nums into two subarrays.
# The best way is to split it into [7,2,5] and [10,8],
# where the largest sum among the two subarrays is only 18.

"""


class SplitArray:

    """
    # The answer is between maximum value of input array numbers and sum of those numbers.
    # Use binary search to approach the correct answer.
    # We have l = max number of array; r = sum of all numbers in the array;
    # Every time we do mid = (l + r) / 2;
    # Use greedy to narrow down left and right boundaries in binary search.

    # 3.1 Cut the array from left.
    # 3.2 Try our best to make sure that the sum of numbers between each two cuts (inclusive) is large enough but still less than mid.
    # 3.3 We’ll end up with two results: either we can divide the array into more than m subarrays or we cannot.

    # If we can, it means that the mid value we pick is too small because we’ve already tried our best
    # to make sure each part holds as many non-negative numbers as we can but we still have numbers left.
    # So, it is impossible to cut the array into m parts and make sure each parts is no larger than mid. We should increase m. This leads to l = mid + 1;

    # If we can’t, it is either we successfully divide the array into m parts and the sum of each part is less than mid,
    # or we used up all numbers before we reach m.
    # Both of them mean that we should lower mid because we need to find the minimum one. This leads to r = mid - 1;
    """
    def doit_binary_search(self, nums, m):
        """
        :type nums: List[int]
        :type m: int
        :rtype: int
        """
        def validate(target, nums, m):
            total, count = 0, 1
            for c in nums:
                total += c

                if total > target:
                    total = c
                    count += 1

                    if count > m:
                        return False
            return True

        # #####
        sums, maxS = 0, 0
        for c in nums:
            sums += c
            maxS = max(maxS, c)

        if m == 1:
            return sums
        if m == len(nums):
            return maxS

        l, r = maxS, sums

        while l <= r:
            mid = (l + r) // 2
            if validate(mid, nums, m):
                r = mid - 1
            else:
                l = mid + 1

        return l

    """
    # DP solution. This is obviously not as good as the binary search solutions; but it did pass OJ.

    # dp[s,j] is the solution for splitting subarray n[j]...n[L-1] into s parts.
    
    # dp[s+1,i] = min{ max(dp[s,j], n[i]+...+n[j-1]) }, i+1 <= j <= L-s
    
    # This solution does not take advantage of the fact that the numbers are non-negative (except to break the inner loop early). 
    That is a loss. (On the other hand, it can be used for the problem containing arbitrary numbers)
    """
    def doit_dp(self, nums, m):
        """
        :type nums: List[int]
        :type m: int
        :rtype: int
        """
        dp = [[float('inf')] * (m) for _ in range(len(nums) + 1)]
        acc = 0
        dp[0][0] = 0

        for i in range(1, len(nums) + 1):
            acc += nums[i - 1]
            dp[i][0] = acc

        for j in range(m):
            dp[0][j] = 0

        for i in range(1, len(nums) + 1):
            for i_ in range(i):
                for j in range(1, m):
                    dp[i][j] = min(dp[i][j], max(dp[i_][j - 1], dp[i][0] - dp[i_][0]))
        # print dp
        return dp[len(nums)][m - 1]


if __name__ == "__main__":

    res = SplitArray().doit([7,2,5,10,8], 2)

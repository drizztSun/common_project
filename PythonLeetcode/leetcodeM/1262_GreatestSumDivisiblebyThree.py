"""
1262. Greatest Sum Divisible by Three


Given an array nums of integers, we need to find the maximum possible sum of elements of the array such that it is divisible by three.



Example 1:

Input: nums = [3,6,5,1,8]
Output: 18
Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
Example 2:

Input: nums = [4]
Output: 0
Explanation: Since 4 is not divisible by 3, do not pick any number.
Example 3:

Input: nums = [1,2,3,4,4]
Output: 12
Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).


Constraints:

1 <= nums.length <= 4 * 10^4
1 <= nums[i] <= 10^4


"""


class GreatestSumDivisibleByThree:

    def doit_dp(self, nums: list) -> int:
        n = len(nums)
        dp = [[0] * 3 for _ in range(n + 1)]
        dp[0] = [0, float('-inf'), float('-inf')]

        for i in range(1, n + 1):
            c = nums[i - 1]
            dp[i][0] = max(dp[i - 1][0], c + dp[i - 1][(3 - c % 3) % 3])
            dp[i][1] = max(dp[i - 1][1], c + dp[i - 1][(3 - c % 3 + 1) % 3])
            dp[i][2] = max(dp[i - 1][2], c + dp[i - 1][(3 - c % 3 + 2) % 3])

        return dp[n][0]

    """
    # Idea:
    # Each number can be either remainder 0, 1, 2
    # Find max sum of numbers
    
    # If sum % 3 == 0: return
    # Find the smallest subset that mod 3 = 1 and mod 3 = 2
    # If sum % 3 == 1: return sum - m1 if m1 exists
    # Else if sum % 3 == 2: return sum - m2 if m2 exists    
    """
    def doit_math(self, nums: list) -> int:
        sums = sum(nums)

        if sums % 3 == 0:
            return sums

        m1, n1, m2, n2 = 0, 0, 0, 0

        nums.sort()
        for n in nums:
            if n % 3 == 1 and m1 == 0:
                m1 = n
            elif n % 3 == 2 and m2 == 0:
                m2 = n
            elif n % 3 == 1 and n1 == 0:
                n1 = n
            elif n % 3 == 2 and n2 == 0:
                n2 = n

            if m1 != 0 and m2 != 0 and n1 != 0 and n2 != 0:
                break

        smallest_mod_1 = min(m1, m2 + n2) if m2 != 0 and n2 != 0 else m1
        smallest_mod_2 = min(m2, m1 + n1) if m1 != 0 and n1 != 0 else m2

        #print(sums)
        #print(m1, n1, m2, n2)
        #print(smallest_mod_1, smallest_mod_2)

        if sums % 3 == 1:
            return sums - smallest_mod_1
        elif sums % 3 == 2:
            return sums - smallest_mod_2
        else:
            return 0
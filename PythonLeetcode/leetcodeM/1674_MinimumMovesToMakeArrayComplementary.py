"""
1674. Minimum Moves to Make Array Complementary


You are given an integer array nums of even length n and an integer limit. In one move, you can replace any integer
from nums with another integer between 1 and limit, inclusive.

The array nums is complementary if for all indices i (0-indexed), nums[i] + nums[n - 1 - i] equals the same number.
For example, the array [1,2,3,4] is complementary because for all indices i, nums[i] + nums[n - 1 - i] = 5.

Return the minimum number of moves required to make nums complementary.



Example 1:

Input: nums = [1,2,4,3], limit = 4
Output: 1
Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
nums[0] + nums[3] = 1 + 3 = 4.
nums[1] + nums[2] = 2 + 2 = 4.
nums[2] + nums[1] = 2 + 2 = 4.
nums[3] + nums[0] = 3 + 1 = 4.
Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.
Example 2:

Input: nums = [1,2,2,1], limit = 2
Output: 2
Explanation: In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to 3 since 3 > limit.
Example 3:

Input: nums = [1,2,1,2], limit = 2
Output: 0
Explanation: nums is already complementary.


Constraints:

n == nums.length
2 <= n <= 105
1 <= nums[i] <= limit <= 105
n is even.

"""


class MinimumMovesToArrayComplementary:

    def doit_(self, nums: list, limit: int) -> int:

        N = len(nums)
        delta = [0 for _ in range(2 * limit + 2)]
        res = N #maximum move

        for i in range(N//2):
            # calclulate we don't need to move
            a, b = nums[i], nums[N - i - 1]
            delta[a + b] -= 1 # no change
            delta[a + b + 1] += 1 # no change end
            delta[min(a+1, b+1)] -= 1 # change one to 1 start
            delta[max(a + limit, b + limit) + 1] += 1 # change one to limit end

        for i in range(2, 2 * limit + 2):
            N += delta[i]
            res = min(res, N)
        return res

    def doit_(self, nums: list, T: int) -> int:
        n = len(nums)

        acc_sum = [0] * (2 * T + 10)
        bit = [0] * (2 * T + 10)

        ans = n
        for i in range(n // 2):
            a, b = nums[i], nums[n - i - 1]
            m = min(1 + a, 1 + b)
            M = max(T + a, T + b)

            acc_sum[2] += 2
            acc_sum[m] -= 2

            acc_sum[m] += 1
            acc_sum[a + b] -= 1

            acc_sum[a + b + 1] += 1
            acc_sum[M + 1] -= 1

            acc_sum[M + 1] += 2
            acc_sum[2 * T + 1] -= 2

        ans = n
        s = 0
        for i in range(2, 2 * T + 1):
            s += acc_sum[i]
            ans = min(ans, s)

        return ans


if __name__ == '__main__':

    MinimumMovesToArrayComplementary().doit_([1, 2, 4, 3], 4)
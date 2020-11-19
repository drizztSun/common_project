"""
487. Max Consecutive Ones II

Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.

Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
Follow up:
What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?

"""


class MaxConsecutiveOnesII:

    def doit_greedy(self, nums: list) -> int:

        cur, prev = 0, 0
        ans = 0
        plus = 0

        for n in nums:

            if n == 0:
                ans = max(ans, cur + prev)
                prev = cur
                cur = 0
                plus = 1
            else:
                cur += 1

        ans = max(ans, cur + prev)

        return ans + plus

    def doit_dp(self, nums: list) -> list:

        flip = nonflip = 0
        ans = 0

        for n in nums:

            if n == 0:
                flip = nonflip + 1
                nonflip = 0
            else:
                flip += 1
                nonflip += 1

            ans = max(ans, flip, nonflip)

        return ans





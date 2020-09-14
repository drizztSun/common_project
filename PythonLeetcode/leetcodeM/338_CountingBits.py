"""
338. Counting Bits

Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

Example 1:

Input: 2
Output: [0,1,1]
Example 2:

Input: 5
Output: [0,1,1,2,1,2]
Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.

"""


class CountBits:

    def doit_dp(self, num):

        dp = [0 for _ in range(num+1)]

        for i in range(1, num+1):
            # every num is 2 * k + {1, 0}. so D[i] has same 1 or 0 as D[k]
            dp[i] = dp[i//2] + i % 2

        return dp[num]

    def doit_dp_1(self, num):
        if num == 0:
            return [0]
        elif num == 1:
            return [0, 1]

        out = [0, 1]
        k = 2
        while num >= pow(2, k) - 1:
            out += [1 + _ for _ in out]
            k += 1

        rem = num - pow(2, k - 1) + 1
        if rem > 0:
            out += [1 + _ for _ in out[0: rem]]
        return out

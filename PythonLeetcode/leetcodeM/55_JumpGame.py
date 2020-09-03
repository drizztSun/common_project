"""
55. Jump Game

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.



Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.


Constraints:

1 <= nums.length <= 3 * 10^4
0 <= nums[i][j] <= 10^5

Approach 4: Greedy
Once we have our code in the bottom-up state, we can make one final, important observation. From a given position, when we try to see if we can jump to a GOOD position,
we only ever use one - the first one (see the break statement). In other words, the left-most one. If we keep track of this left-most GOOD position as a separate variable,
we can avoid searching for it in the array. Not only that, but we can stop using the array altogether.

Iterating right-to-left, for each position we check if there is a potential jump that reaches a GOOD index (currPosition + nums[currPosition] >= leftmostGoodIndex).
If we can reach a GOOD index, then our position is itself GOOD. Also, this new GOOD position will be the new leftmost GOOD index. Iteration continues until the beginning of the array.
If first position is a GOOD index then we can reach the last index from the first position.

To illustrate this scenario, we will use the diagram below, for input array nums = [9, 4, 2, 1, 0, 2, 0]. We write G for GOOD, B for BAD and U for UNKNOWN.
Let's assume we have iterated all the way to position 0 and we need to decide if index 0 is GOOD. Since index 1 was determined to be GOOD,
it is enough to jump there and then be sure we can eventually reach index 6. It does not matter that nums[0] is big enough to jump all the way to the last index. All we need is one way.

Index	0	1	2	3	4	5	6
nums	9	4	2	1	0	2	0
memo	U	G	B	B	B	G	G

"""


class CanJump:

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        i, curMax = 0, 0
        while i < len(nums) and i <= curMax:
            curMax = max(i + nums[i], curMax)
            i += 1

        return i >= len(nums)


    def doit1(self, nums):

        dp = [False for _ in range(len(nums))]
        dp[0] = True

        for i in range(1, len(nums)):

            for j in reversed(range(0, i)):

                if dp[j] and j + nums[j] >= i:
                    dp[i] = True
                    break

        return dp[len(nums) - 1]

    def doit2(self, nums):

        lastpos = len(nums) - 1
        i = len(nums) - 1
        while i >= 0:
            if i + nums[i] >= lastpos:
                lastpos = i
            i -= 1

        return lastpos == 0


if __name__ == '__main__':

    res = CanJump().doit([2,3,1,1,4])

    res = CanJump().doit([3,2,1,0,4])


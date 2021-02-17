"""
1493. Longest Subarray of 1's After Deleting One Element

Given a binary array nums, you should delete one element from it.

Return the size of the longest non-empty subarray containing only 1's in the resulting array.

Return 0 if there is no such subarray.



Example 1:

Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.
Example 2:

Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray with value of 1's is [1,1,1,1,1].
Example 3:

Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.
Example 4:

Input: nums = [1,1,0,0,1,1,1,0,1]
Output: 4
Example 5:

Input: nums = [0,0,0]
Output: 0


Constraints:

1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
"""


class LongestSubarray:

    def doit_dp(self, nums: list) -> int:
        ans = 0
        nodel, delete = 0, 0

        for c in nums:
            if c == 1:
                nodel += 1
                delete += 1
            else:
                nodel, delete = 0, nodel

            ans = max(ans, nodel, delete)

        return ans if ans != len(nums) else ans - 1

    """
        Intuition
        Almost exactly same as 1004. Max Consecutive Ones III
        Given an array A of 0s and 1s,
        we may change up to k = 1 values from 0 to 1.
        Return the length - 1 of the longest (contiguous) subarray that contains only 1s.

        I felt we discuss the same sliding window solution every two weeks..
        And I continue to receive complaints that I didn't give explantion again and again.


        Complexity
        Time O(N)
        Space O(1)


        Solution 1:
        Sliding window with at most one 0 inside.


        Solution 2
        Sliding window that size doesn't shrink.
    """
    def doit_slidingwindow(self, nums: int) -> int:

        k, ans, j = 1, 0, 0

        for i in range(len(nums)):

            if nums[i] == 0:
                k -= 1

            while k < 0:
                if nums[j] == 0:
                    k += 1
                j += 1

            ans = max(ans, i - j)
        
        return ans

    def doit_slidingwindow(self, A):
        k, i = 1, 0
        
        for j in range(len(A)):
            k -= A[j] == 0
            if k < 0:
                k += A[i] == 0
                i += 1
        return j - i


if __name__ == '__main__':

    LongestSubarray().doit_slidingwindow([1, 1, 0, 1])

"""
1696. Jump Game VI


You are given a 0-indexed integer array nums and an integer k.

You are initially standing at index 0. In one move, you can jump at most k steps forward without going outside the boundaries of the array. 
That is, you can jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive.

You want to reach the last index of the array (index n - 1). Your score is the sum of all nums[j] for each index j you visited in the array.

Return the maximum score you can get.

 

Example 1:

Input: nums = [1,-1,-2,4,-7,3], k = 2
Output: 7
Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (underlined above). The sum is 7.
Example 2:

Input: nums = [10,-5,-2,4,0,3], k = 3
Output: 17
Explanation: You can choose your jumps forming the subsequence [10,4,3] (underlined above). The sum is 17.
Example 3:

Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
Output: 0
 

Constraints:

 1 <= nums.length, k <= 105
-104 <= nums[i] <= 104


"""

class JumpGameVI:

    """
        Solution 0: Recursive w/ memorized / dp 

        Definition DP(i) := max score we can get at position i
        Base case: dp(0) = nums[0]
        Transition: dp(1) = nums[i] + max(dp(j)  max(0, i-k) < j < i)
        Answer: dp(n-1)

        Time complexity:O(n^k) => TLE
        Space complexity: O(n)
    """
    def doit_dp(self, nums: list, k: int) -> int:
        from functools import lru_cache
        
        @lru_cache(None)
        def dp(i: int) -> int:
            return nums[0] if i == 0 else nums[i] + max(dp(j) for j in range(max(0, i - k), i))
        return dp(len(nums) - 1)
    
    """
        Solution 1: DP + Monotonic Queue

        max(dp(j)), (max(0, i - k) <= j < i) find a "Maximum sliding window of size k"

        leetcode 239 Sliding window maximum

        Method          Time            Space
        Brute Force     (n-k)*k         1
        BST/Multimap    (n-k)*log(k)    k
        Monotonic Queue   n             k
    """
    def doit_dp_1(self, nums: list, k: int) -> int:

        from collections import deque
        
        n = len(nums)

        dp = [0] * (n)
        dp[0] = nums[0]
        
        st = deque([0])

        for i in range(1, n):

            dp[i] = nums[i] + dp[st[0]]

            while st and dp[st[-1]] < dp[i]:
                st.pop()

            while st and i - st[0] >= k:
                st.popleft()

            st.append(i)

        return dp[n-1]


    def doit_dp_best(self, nums: list) -> list:

        from collections import deque
        
        st = deque([(0, nums[0])])

        for i in range(1, len(nums)):

            while st and st[0][0] < i - k:
                st.popleft()

            res = st[0][1] + nums[i]

            while st and st[-1][1] < res:
                st.pop()

            st.append((i, res))

        return st[-1][1]



            










    
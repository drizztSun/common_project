"""
698. Partition to K Equal Sum Subsets

Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.

 

Example 1:

Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
 

Note:

1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.


"""


class PartitionKEqualSumSubsets:

    def doit_(self, nums: list, k: int) -> bool:
        
        if k == 1:
            return True

        if k > len(nums):
            return False

        A = sum(nums)
        if A % k != 0:
            return False
        A = A // k

        visited = [0] * len(nums)
        nums.sort(reverse=1)
        
        def dfs(amount, idx, sums, cnt):

            if amount == 0:
                return True

            if sums == A and cnt > 0:
                return dfs(amount-1, 0, 0, 0)
                

            for i in range(idx, len(nums)):
                if not visited[i] and sums + nums[i] <= A:
                    visited[i] = 1
                    if dfs(amount, i+1, sums + nums[i], cnt + 1):
                        return True
                    visited[i] = 0

            return False

        return dfs(k, 0, 0, 0)



# 698. Partition to K Equal Sum Subsets

# Given an array of integers nums and a positive integer k,
# find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.

# Example 1:
# Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
# Output: True
# Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
# Note:

# 1 <= k <= len(nums) <= 16.
# 0 < nums[i] < 10000.


# <important>
class canPartitionKSubsets:

    # <DP>
    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        total = sum(nums)
        if k > len(nums):
            return False

        if total % k != 0:
            return False

        ave = total // k
        D = [[0 for _ in range(ave + 1)] for x in range(len(nums) + 1)]

        for x in range(1, len(nums) + 1):
            
            wi = nums[x-1]

            for weight in range(1, ave + 1):

                if weight >= wi:
                    D[x][weight] = max(D[x-1][weight], D[x-1][weight-wi] + nums[x-1])

        
        return D[len(nums)][ave] == ave

            


    # <dfs>
    def doit1(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
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
            
                

if __name__=="__main__":

    res = canPartitionKSubsets().doit([4, 3, 2, 3, 5, 2, 1], 4)

    res = canPartitionKSubsets().doit([2, 2, 2, 2, 3, 4, 5], 4)

    pass



        
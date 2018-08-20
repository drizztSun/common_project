

# 416. Partition Equal Subset Sum

# <Medium>

# Given a non-empty array containing only positive integers,
# find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

# Note:
# Each of the array element will not exceed 100.
# The array size will not exceed 200.

# Example 1:
# Input: [1, 5, 11, 5]
# Output: true
# Explanation: The array can be partitioned as [1, 5, 5] and [11].

# Example 2:
# Input: [1, 2, 3, 5]
# Output: false
# Explanation: The array cannot be partitioned into equal sum subsets.

class canPartition:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        total = sum(nums)
        if total % 2 != 0:
            return False

        HalfAmount = total // 2
        nums.sort()

        def search(nums, amount, i, buff):

            if i == len(nums):
                return False

            if (amount, i) in buff:
                return False

            if amount - nums[i] <= 0:
                return amount - nums[i] == 0

            res = search(nums, amount - nums[i], i + 1, buff)
            if res:
                return True
            else:
                buff.add((amount-nums[i], i))

            res =  search(nums, amount, i + 1, buff) 
            if not res:
                buff.add((amount-nums[i], i))
 
            return res
            

        return search(nums, HalfAmount, 0, set())


    def doit1(self, nums, ):
        """
        :type nums: List[int]
        :rtype: bool
        """
        # get sum
        val_sum = sum(nums)
        
        if val_sum % 2 == 1:
            # odd sum
            return False
        
        val_half = val_sum//2
        
        # Search for a sum of val_half
        #   Similar to Combinatorial Sum
        
        # sort it (reverse)
        nums.sort(reverse = True)
    
        # DFS
        def dfs(i, target):
            # in nums[i:] look for subset of sum of target
            if target == 0:
                return True
            if i == len(nums) or target < 0:
                return False
            
            # prune
            if nums[i] > target:
                return False
            
            # i < len(nums), target > 0
            return dfs(i+1, target - nums[i]) or dfs(i+1, target)
        
        return dfs(0, val_half)
        


if __name__=="__main__":

    res = canPartition().doit([1, 5, 11, 5])

    res = canPartition().doit([1, 2, 3, 5])

    pass 
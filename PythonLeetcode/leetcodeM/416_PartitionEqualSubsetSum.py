"""
416. Partition Equal Subset Sum

Given a non-empty array nums containing only positive integers, 
find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

 

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
 

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 100


"""

class PartitionEqualSum:

    def doit_dp_topdown(self, nums):
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

            #add 
            if search(nums, amount - nums[i], i + 1, buff):
                return True
                
            buff.add((amount-nums[i], i))

            res =  search(nums, amount, i + 1, buff)
            if not res:
                buff.add((amount-nums[i], i))
 
            return res

        return search(nums, HalfAmount, 0, set())
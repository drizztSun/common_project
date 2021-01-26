"""
1567. Maximum Length of Subarray With Positive Product


Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.

A subarray of an array is a consecutive sequence of zero or more values taken out of that array.

Return the maximum length of a subarray with positive product.

 

Example 1:

Input: nums = [1,-2,-3,4]
Output: 4
Explanation: The array nums already has a positive product of 24.
Example 2:

Input: nums = [0,1,-2,-3,-4]
Output: 3
Explanation: The longest subarray with positive product is [1,-2,-3] which has a product of 6.
Notice that we cannot include 0 in the subarray since that'll make the product 0 which is not positive.
Example 3:

Input: nums = [-1,-2,-3,0,1]
Output: 2
Explanation: The longest subarray with positive product is [-1,-2] or [-2,-3].
Example 4:

Input: nums = [-1,2]
Output: 1
Example 5:

Input: nums = [1,2,3,5,-6,4,0,10]
Output: 4
 

Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

"""



class GetMaxLen:
    
    """

    """
    def doit_(self, nums: list) -> int:
        import math
        nums.append(0) # This will initiate a calculation of max sub array length
        res = 0 # Store subarray lengths
        start = 0 # Marking begining of a candidate sub array 
        sign = 1 # Indicating if the total product is positive or negative
        start_neg = math.inf # Index following first negative number

        for i, n in enumerate(nums): 
            if n == 0: 
                if sign == 1: # Then the whole sub array is valid
                    res = max(res, i - start)
                else: # Then we record the whole array after the first negative
                    res = max(res, i - start_neg)
                start = i + 1
                sign = 1
                start_neg = math.inf
            if n < 0: 
                sign *= -1
                if sign == -1: # Record the result of the firt part of the array
                    res = max(res, i - start)
                    start_neg = min(start_neg, i + 1)
                    
        return res

    def doit_dp(self, nums: list) -> int:
        
        pos = neg = res = 0
        
        for n in nums:
            if n ==0: # 是值为0，那么全部重置。在dp 中有一种情况叫做重置，之前的都不算了，重头开始
                pos , neg =0, 0
            elif n >0:
                pos, neg = pos +1, neg + (1 if neg > 0 else 0)
            else:
                neg, pos = pos +1, neg + (1 if neg > 0 else 0)
            res = max(res, pos)
        return res

    """

    """
    def doit_(self, nums: list) -> int:

        fpos, fneg = -1, None
        cur, ans = 1, 0
        for i in range(len(nums)):
            
            if nums[i] == 0:
                fneg, fpos = None, i
                cur = 1
                continue
            
            # cur *= nums[i] Here is a big performance issue, it does increase the performance by multiple in Python, not sure in C++
            cur = -cur if nums[i] < 0 else cur
            
            if cur > 0:
                if fpos == None:
                    fpos = i
                
                ans = max(ans, i - fpos)
            else:
                if fneg == None:
                    fneg = i
                else:
                    ans = max(ans, i - fneg)
                
        return ans
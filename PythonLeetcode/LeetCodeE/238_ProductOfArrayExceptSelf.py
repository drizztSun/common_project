import os



# leetcode 238. Product of Array Except Self

# Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
# Solve it without division and in O(n).

# For example, given [1,2,3,4], return [24,12,8,6].
# Follow up:
# Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)


class productExceptSelf:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        ZeroNum, total = 0, 1
        for n in nums:
            if n == 0:
                ZeroNum += 1
            else:
                total *= n
                
        D = [0 for _ in range(len(nums))]
        
        if ZeroNum <= 1:
            for i, n in enumerate(nums):
                if n == 0:
                    D[i] = total
                else:
                    D[i] = total//n if ZeroNum == 0 else 0
                    
        return D
    
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        totalprod=1
        zero=0
            
        for x in nums:
            if x!=0:
                totalprod*=x
            else:
                zero+=1  
            
        result=[]
        
        for y in nums:
            if zero>1:
                result.append(0)
            elif zero==1:
                if y==0:
                    result.append(totalprod)
                else:
                    result.append(0)
            else:
                result.append(totalprod//y)

        return result
                     

if __name__=="__main__":


    pass
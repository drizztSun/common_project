# 503. Next Greater Element II

# Given a circular array (the next element of the last element is the first element of the array), 
# print the Next Greater Number for every element. 
# The Next Greater Number of a number x is the first greater number to its traversing-order next in the array,
# which means you could search circularly to find its next greater number. If it doesn't exist, output -1 for this number.

# Example 1:
# Input: [1,2,1]
# Output: [2,-1,2]
# Explanation: The first 1's next greater number is 2; 
# The number 2 can't find next greater number; 
# The second 1's next greater number needs to search circularly, which is also 2.
# Note: The length of given array won't exceed 10000.

class NextGreaterElementsII(object):


    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        N = len(nums)
        nums = nums * 2
        st, res = [], [-1 for _ in range(N)]
        
        for n in range(len(nums)):
        
            while st and nums[n] > nums[st[-1]]:
                res[st.pop()] = nums[n]
            
            if n < N:
                st.append(n)
               
        return res



    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        ans=[]
        n=len(nums)
        if n==0: 
            return []
        
        i = 1
        s = [0]
        ans = [-1] * n

        for i in range(1,n):
            while s and nums[i] > nums[s[-1]]:
                ans[s[-1]] = nums[i]
                s.pop()
            s.append(i)

        #print s
        for i in range(n):
            while nums[i]> nums[s[-1]]:
                ans[s[-1]] = nums[i]
                s.pop()                                         

        return ans
        

if __name__ == "__main__":

    res = NextGreaterElementsII().doit()
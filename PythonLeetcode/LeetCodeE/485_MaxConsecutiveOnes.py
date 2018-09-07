# 485. Max Consecutive Ones

# Given a binary array, find the maximum number of consecutive 1s in this array.

# Example 1:
# Input: [1,1,0,1,1,1]
# Output: 3
# Explanation: The first two digits or the last three digits are consecutive 1s.
#    The maximum number of consecutive 1s is 3.
# Note:

# The input array will only contain 0 and 1.
# The length of input array is a positive integer and will not exceed 10,000


class MaxConsecutiveOnes:
    
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        currMax = 0
        numb1s = 0
        
        for n in nums:
            if n:
                numb1s+=1
            else:
                currMax = max(currMax,numb1s)
                numb1s = 0
        
        return max(currMax, numb1s)

    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n, res = 0, 0
        for c in nums + [0]:
            if c == 0:
                res = max(n, res)

            else:
                n += 1

        return res


if __name__ == "__main__":

    res = MaxConsecutiveOnes().doit()     
            

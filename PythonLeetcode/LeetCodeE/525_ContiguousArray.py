# 525. Contiguous Array

#Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

#Example 1:
#Input: [0,1]
#Output: 2
#Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.

#Example 2:
#Input: [0,1,0]
#Output: 2
#Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.


class MaxLengthArray:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """      
        pos = [0 for _ in range(len(nums))]
        profix = {0:-1}
        maxv = 0

        for i in range(len(nums)):
            pos[i] = 1 if nums[i] == 1 else -1
            if i > 0:
                pos[i] += pos[i-1]

            if pos[i] not in profix:
                profix[pos[i]] = i
            else:
                maxv = max(maxv, i - profix[pos[i]])
                
        return maxv


    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        left = {0: -1}
        right = {}
        total = 0

        for idx, num in enumerate(nums):
            total += (num * 2) - 1
            if total not in left:
                left[total] = idx
            else:
                right[total] = idx

        longest = 0

        for idx in left:
            if idx in right:
                longest = max(longest, right[idx] - left[idx])

        return longest


if __name__ == "__main__":

    res = MaxLengthArray().doit([0,0,1,0,0,0,1,1])

    res = MaxLengthArray().doit([0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1])

    res = MaxLengthArray().doit([0, 1])

    

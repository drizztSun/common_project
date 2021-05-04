import os
import numbers
import math



class maximumGap(object):
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) <= 1:
           return len(nums)

        maxV, minV = nums[0], nums[0]
        for n in nums:
            maxV = max(maxV, n)
            minV = min(minV, n)

        
        delta = int(math.ceil((maxV - minV) / (len(nums) - 1))) + 1
        D = [[]  for _ in range(len(nums))]
        if not delta:
            return 0

        for n in nums:
            D [(n-minV)//delta].append(n)

        gap, last = 0, minV-1
        for num in D:
            if num == 0:
                continue
            gap = max(gap, num - last)
            last = num

        return gap


    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) <= 1:
            return 0

        intMax, intMin = sys.maxint, -sys.maxint
        maxV, minV = nums[0], nums[0]
        for i in nums:
            maxV = max(maxV, i)
            minV = min(minV, i)

        gap = int((maxV-minV)/(len(nums)-1)) + 1
        bucketMax = [intMin] * (len(num)-1)
        bucketMin = [intMax] * (len(num)-1)

        for num in nums:
            if num == minV or num == maxV:
                continue
            index = (num - minV) / gap
            bucketMax[index] = max(bucketMax[index], num)
            bucketMin[index] = min(bucketMin[index], num)

        maxGap = intMin
        previous = minV

        for i in range(len(num)-1):
            if bucketMax[i] == intMin and bucketMin[i] == intMax:
                continue

            maxGap = max(maxGap, bucketMin[i] - previous)
            previous = bucketMax[i]


        maxGap = max(maxGap, maxV - previous)

        return maxGap


    def doit3(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) < 2:
            return 0

        nums.sort()

        # print nums
        temp_max = 0
        prev = nums[0]
        for i in range(len(nums)):
            current = nums[i]
            gap = current - prev

            if temp_max < gap:
                temp_max = gap

            prev = current

        return temp_max


import os

# 228. Summary Ranges
# Given a sorted integer array without duplicates, return the summary of its ranges.

# Example 1:
# Input: [0,1,2,4,5,7]
# Output: ["0->2","4->5","7"]

# Example 2:
# Input: [0,2,3,4,6,8,9]
# Output: ["0","2->4","6","8->9"]



class summaryRanges:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[str]
        """
        if not nums:
            return []

        res = []
        s , e = nums[0], nums[0]


        for i in range(1, len(nums)):
            
            if nums[i] != e + 1:

                if nums[i] != e + 1:
                    item = str(s)   
                    if s != e:
                        item += "->" + str(e)

                    res.append(item)

                    if i == len(nums)-1:
                        res.append(str(nums[i]))
                
                    s, e = nums[i], nums[i]

            elif i == len(nums)-1:
                    item = str(s)   
                    if s != nums[i]:
                        item += "->" + str(nums[i])

                    res.append(item)
            else:
                e = nums[i]

        if not res:
            res.append(str(s))


        return res

    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[str]
        """
        range = []
        for c in nums:

            if not range or range[-1][-1] + 1 != c:
                range += []

            range[-1][1:] = c

        return ['->'.join(map(str, c)) for c in range]


    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: List[str]
        """
        if len(nums)==0:
            return []

        summary=[]
        cur = 0
        for i in range(1,len(nums)):
            if nums[i] != nums[i-1] +1:
                #Append
                if cur != i-1:
                    summary.append(str(nums[cur])+"->"+str(nums[i-1]))
                else:
                    summary.append(str(nums[cur]))
                cur= i

        if cur == len(nums)-1:
            summary.append(str(nums[-1]))
        else:
            summary.append(str(nums[cur])+"->"+str(nums[-1]))
            
        return summary            
                    



    
        



if __name__ == "__main__":


    res = summaryRanges().doit([0,1,2,4,5,7])

    res = summaryRanges().doit([0,2,3,4,6,8,9])

    pass
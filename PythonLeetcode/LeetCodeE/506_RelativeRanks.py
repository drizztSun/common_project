# 506. Relative Ranksc

# Given scores of N athletes, find their relative ranks and the people with the top three highest scores,
# who will be awarded medals: "Gold Medal", "Silver Medal" and "Bronze Medal".

# Example 1:
# Input: [5, 4, 3, 2, 1]
# Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
# Explanation: The first three athletes got the top three highest scores, so they got "Gold Medal", "Silver Medal" and "Bronze Medal". 
# For the left two athletes, you just need to output their relative ranks according to their scores.
# Note:
# N is a positive integer and won't exceed 10,000.
# All the scores of athletes are guaranteed to be unique.
# Seen this question in a real interview before?  

import heapq

class RelativeRanks(object):

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[str]
        """
        rank = ['' for _ in range(len(nums))]
        buff = []

        for i in range(len(nums)):
            heapq.heappush(buff, (-nums[i], i))

        for i in range(len(nums)):
            n, c = heapq.heappop(buff)
            if i == 0:
                rank[c] = 'Gold Medal'
            elif i == 1:
                rank[c] = 'Silver Medal'
            elif i == 2:
                rank[c] = 'Bronze Medal'

            else:
                rank[c] = str(i + 1)
        
        return rank

    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[str]
        """
        sort = sorted(nums, reverse=True)

        rank = ["Gold Medal","Silver Medal","Bronze Medal"] + map(str,range(4, len(nums)+1))

        return map(dict(zip(sort, rank)).get, nums)


    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: List[str]
        """
        n = sorted(nums, reverse = True)
        d = {}
        l = len(nums)

        d[n[0]] = ("Gold Medal")

        if l > 1:
            d[n[1]] = ("Silver Medal")

        if l > 2:
            d[n[2]] = ("Bronze Medal")

        for i in range(3,l):
            d[n[i]] = (str(i+1))

        result = [d[k] for k in nums]

        return result


if __name__ == "__main__":

    res = RelativeRanks().doit([5, 4, 3, 2, 1])
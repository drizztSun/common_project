import collections

class MajorityElement(object):

    def doit_1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        buffer = {}
        for i in nums:
            buffer[i] = buffer.get(i, 0) + 1
            if buffer[i] > len(nums) / 2:
                return i

    def doit_2(self, nums):
        counts = collections.Counter(nums)
        return max(counts.keys(), key=counts.get)

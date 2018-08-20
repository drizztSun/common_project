

# 697. Degree of an Array

# Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.

# Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

# Example 1:
# Input: [1, 2, 2, 3, 1]
# Output: 2

# Explanation: 
# The input array has a degree of 2 because both elements 1 and 2 appear twice.
# Of the subarrays that have the same degree:

# [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
# The shortest length is 2. So return 2.


class findShortestSubArray(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        import collections
       
        D = collections.defaultdict(list)
        maxS = 0
        for i, c in enumerate(nums):
            D[c].append(i)
            if len(D[c]) > len(D[maxS]):
                maxS = c
            elif len(D[c]) == len(D[maxS]) and (D[maxS][-1] - D[maxS][0]) > (D[c][-1] - D[c][0]):
                maxS = c

        return D[maxS][-1] - D[maxS][0] + 1 if len(D[maxS]) else 0



    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(set(nums)) == len(nums) :
            return 1
        else :
            nums1 = list()
            cnt = list()

            for n in set(nums) :
                nums1.append(n)
                cnt.append(nums.count(n))

            degree = max(cnt)
            short_subarr = list()

            for k in range(cnt.count(degree)) :
                print(nums1, cnt)
                p = cnt.index(degree)
                i = nums.index(nums1[p])
                j = nums[::-1].index(nums[i])
                short_subarr.append(len(nums)-j-i)

                cnt = cnt[p:]
                nums1 = nums1[p:]

                del(cnt[0])
                del(nums1[0])

            return min(short_subarr)

if __name__=="__main__":

    
    res = findShortestSubArray().doit([2,1,1,2,1,3,3,3,1,3,1,3,2])

    pass
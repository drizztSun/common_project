# 496. Next Greater Element I

# You are given two arrays (without duplicates) nums1 and nums2 where nums1�s elements are subset of nums2. 
# Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

# The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. 
# If it does not exist, output -1 for this number.

# Example 1:
# Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
# Output: [-1,3,-1]
# Explanation:
#    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
#    For number 1 in the first array, the next greater number for it in the second array is 3.
#    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.

# Example 2:
# Input: nums1 = [2,4], nums2 = [1,2,3,4].
# Output: [3,-1]
# Explanation:
#    For number 2 in the first array, the next greater number for it in the second array is 3.
#    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
# Note:
# All elements in nums1 and nums2 are unique.
# The length of both nums1 and nums2 would not exceed 1000.


class NextGreaterElement(object):


    def doit(self, nums1, nums2):
        """
        :type findNums: List[int]
        :type nums: List[int]
        :rtype: List[int]
        """
        k = -1
        greater = {}
        stack = []

        for n in nums2:
            while stack and n > stack[-1]:
                greater[stack.pop()] = n
            stack.append(n)

        while stack:
            greater[stack.pop()] = -1

        return [greater.get(n, -1) for n in nums1]

    def doit1(self, findNums, nums):
        """
        :type findNums: List[int]
        :type nums: List[int]
        :rtype: List[int]
        """
        pos = { nums[i] : i for i in range(len(nums)) }
        res = []

        for c in findNums:
            i = pos[c] + 1
            while i < len(nums):
                if nums[i] > c:
                    break
                i += 1

            res.append( -1 if i == len(nums) else nums[i])
            
        return res
        


if __name__ == "__main__":

    res = NextGreaterElement().doit([4,1,2], [1,3,4,2])

    rea = NextGreaterElement().doit([2,4], [1,2,3,4])
        

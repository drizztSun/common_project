
# 540. Single Element in a Sorted Array


# Given a sorted array consisting of only integers where every element appears twice except for one element which appears once. Find this single element that appears only once.

# Example 1:
# Input: [1,1,2,3,3,4,4,8,8]
# Output: 2
# Example 2:
# Input: [3,3,7,7,10,11,11]
# Output: 10
# Note: Your solution should run in O(log n) time and O(1) space.


class SingleNonDuplicate:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = nums[0]
        for i in range(1, len(nums)):
            n ^= nums[i]
            
        return n
        

if __name__ == "__main__":

    res = SingleNonDuplicate().doit([1,1,2,3,3,4,4,8,8])

    res = SingleNonDuplicate().doit([3,3,7,7,10,11,11])

    pass
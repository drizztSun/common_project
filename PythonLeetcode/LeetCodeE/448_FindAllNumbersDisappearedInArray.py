



# 448. Find All Numbers Disappeared in an Array

# Given an array of integers where 1 ? a[i] ? n (n = size of array), some elements appear twice and others appear once.

# Find all the elements of [1, n] inclusive that do not appear in this array.

# Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

# Example:

# Input:
# [4,3,2,7,8,2,3,1]

# Output:
# [5,6]


class findDisappearedNumbers:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        n = len(nums)
        target = [i+1 for i in range(n)]

        for c in nums:
            target[c-1] = -1

        return [i for i in target if i != -1]



if __name__=="__main__":

    res = findDisappearedNumbers().doit([4,3,2,7,8,2,3,1])


    pass

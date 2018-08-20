
# 334 Increasing Triplet Subsequence

# Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

# Formally the function should:
# Return true if there exists i, j, k 
# such that arr[i] < arr[j] < arr[k] given 0 ? i < j < k ? n-1 else return false.
# Your algorithm should run in O(n) time complexity and O(1) space complexity.

# Examples:
# Given [1, 2, 3, 4, 5],
# return true.

# Given [5, 4, 3, 2, 1],
# return false.


class increasingTriplet:

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        if len(nums) < 3:
            return False

        A = [nums[0]]

        for i in range(1, len(nums)):

            if nums[i] > A[-1]:
                A.append(nums[i])
                if len(A) == 3:
                    return True
            elif nums[i] == A[-1]:
                continue
            else:
                if len(A) == 2 and A[0] >= nums[i]:
                    A[0] = nums[i]
                else:
                    A[-1] = nums[i]

        return False

    
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        if len(nums) < 3:
            return False

        first = float('inf')
        second = first

        for c in nums:

            if c < first:
                first = c
    
            elif c > first and c < second :
                second = c
            
            elif c > first and c > second :
                
                return True

        return False        
                



if __name__=="__main__":


    res = increasingTriplet().doit([1, 2, 3, 4, 5])

    res = increasingTriplet().doit([5, 4, 3, 2, 1])

    pass
        
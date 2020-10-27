"""
# 41. First Missing Positive

# Given an unsorted integer array, find the first missing positive integer.

# For example,
# Given [1,2,0] return 3,
# and [3,4,-1,1] return 2.

#Your algorithm should run in O(n) time and uses constant space.


# The basic idea is for any k positive numbers (duplicates allowed), the first missing positive number must be within [1,k+1].
# The reason is like you put k balls into k+1 bins, there must be a bin empty, the empty bin can be viewed as the missing number.

Follow up:

Your algorithm should run in O(n) time and uses constant extra space.
"""


class FirstMissingPositive:

    def doit(self, nums):
        # space requirement
        buf = set(nums)
        for i in range(1, len(nums) + 1):
            if i not in buf:
                return i
        else:
            return len(nums) + 1


    def doit_array(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i, length = 0, len(nums)

        while i < length:
            while 0 < nums[i] <= length and nums[i] != nums[nums[i]-1]:
                nums[nums[i]-1], nums[i] = nums[i], nums[nums[i]-1]
                # nums[i], nums[nums[i] - 1] = nums[nums[i] - 1], nums[i]
                # incorrect, Here is the tricky sting. the first assignment, nums[i] = nums[nums[i] - 1] already changed the nums[i]
                # and then second assignment will be affect, nums[nums[i] - 1], using the new value.
                # it seems it get all right value first, then assign to the left one by one.
            i += 1

        i = 0
        while i < length and nums[i] == i+1:
            i += 1

        return i + 1

# 1. Unfortunately, there are 0 and negative numbers in the array, so firstly I think of using partition technique (used in quick sort) 
# to put all positive numbers together in one side. This can be finished in O(n) time, O(1) space.

# 2. After partition step, you get all the positive numbers lying within A[0,k-1]. 
# Now, According to the basic idea, I infer the first missing number must be within [1,k+1]. 
# I decide to use A[i] (0<=i<=k-1) to indicate whether the number (i+1) exists. But here I still have to main the original information A[i] holds. 
# Fortunately, A[i] are all positive numbers, so I can set them to negative to indicate the existence of (i+1) and I can still use abs(A[i]) to get the original information A[i] holds.

# 3. After step 2, I can again scan all elements between A[0,k-1] to find the first positive element A[i], that means (i+1) doesn't exist, which is what I want.

    def doit1(self, A):
        """
        :type nums: List[int]
        :rtype: int
        """
        def swap(A, i, j):
            if i != j:
                A[i] ^= A[j]
                A[j] ^= A[i]
                A[i] ^= A[j]

        def partition(A):
            n, q = len(A), -1
            i = 0
            while i < n:
                if A[i] > 0:
                    q += 1
                    swap(A, q, i)
                i += 1

            return q

        if not A:
            return 1

        k = partition(A) + 1
        
        first_missing_Index = k
        i, temp = 0, 0

        while i < k:
            temp = math.fabs(A[i])
            if temp <= k:
                A[temp-1] = A[temp-1] if A[temp-1] < 0 else -A[temp-1]
            i += 1

        for i in range(k):
            if A[i] > 0:
                first_missing_Index = i
                break

        return first_missing_Index + 1
             
            


if __name__ == "__main__":

    res = FirstMissingPositive().doit_array([3, 4, -1, -1])

    res = FirstMissingPositive().doit([1, 1])

    res = FirstMissingPositive().doit([1, 2, 0])

    res = FirstMissingPositive().doit([3, 4, -1, 1])

    res = FirstMissingPositive().doit([-3,9,16,4,5,16,-4,9,26,2,1,19,-1,25,7,22,2,-7,14,2,5,-6,1,17,3,24,-4,17,15])




    pass






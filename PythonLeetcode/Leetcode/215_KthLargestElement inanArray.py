# 215. Kth Largest Element in an Array

#Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, 
#not the kth distinct element.

#Example 1:

#Input: [3,2,1,5,6,4] and k = 2
#Output: 5
#Example 2:

#Input: [3,2,3,1,2,4,5,5,6] and k = 4
#Output: 4
#Note: 
#You may assume k is always valid, 1 ≤ k ≤ array's length.
import heapq

class FindKthLargest:

    def doit(self, nums: 'List[int]', k: 'int') -> 'int':
        return heapq.nlargest(k,nums)[-1]
        
    def doit1(self, nums: 'List[int]', k: 'int') -> 'int':
        A, B, k = nums[0], 0, k - 1
        min, max = 0, len(nums)
        while True:
            A, i, j = nums[min], min, min
            while i < max:
                if nums[i] > A:
                    j += 1
                    nums[i], nums[j] = nums[j], nums[i]
                i += 1
            
            if j != min :
                nums[j], nums[min] = nums[min], nums[j]
            
            if k == j:
                B = nums[k]
                break
            elif k > j :
                min = j + 1
            else:
                max = j

        return B

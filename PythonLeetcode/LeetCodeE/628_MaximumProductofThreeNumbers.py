# 628. Maximum Product of Three Numbers

# Given an integer array, find three numbers whose product is maximum and output the maximum product.

# Example 1:
# Input: [1,2,3]
# Output: 6

# Example 2:
# Input: [1,2,3,4]
# Output: 24

# Note:
# The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
# Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.


class MaximumProduct:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_v = [float("-inf")] * 3
        min_v = [float("inf")] * 3
        
        for c in nums:
            
            if c > min(max_v):
                s = min(max_v)
                for i in range(3):
                    if s == max_v[i]:
                        max_v[i] = c
                        break
                        
            if c < max(min_v):
                s = max(min_v)
                for i in range(3):
                    if s == min_v[i]:
                        min_v[i] = c
                        break

        max_v.sort()
        min_v.sort()
        return max(max_v[0] * max_v[1] * max_v[2], min_v[0] * min_v[1] * max_v[2])


    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        a, b = heapq.nlargest(3, nums), heapq.nsmallest(2, nums)
        return max(a[1]*a[2], b[0]*b[1]) * a[0]   
        
        
if __name__ == "__main__":

    res = MaximumProduct().doit([1, 2, 3])

    res = MaximumProduct().doit([1, 2, 3, 4])

    res = 1
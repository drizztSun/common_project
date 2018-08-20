
# 611. Valid Triangle Number

# Given an array consists of non-negative integers, your task is to count
# the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.

# Example 1:
# Input: [2,2,3,4]
# Output: 3

# Explanation:
# Valid combinations are: 
# 2,3,4 (using the first 2)
# 2,3,4 (using the second 2)
# 2,2,3
# Note:
# The length of the given array won't exceed 1000.
# The integers in the given array are in the range of [0, 1000].


class triangleNumber(object):

    # O()
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort(reverse=1)
        count = 0
        for i in range(len(nums)):
            j, k = i + 1, len(nums)-1
            
            while j < k:
                if nums[k] + nums[j] > nums[i]:
                    k -= 1
                else:
                    count += len(nums) - k
                    j += 1

        return count
                
                

                

    # O(n**3)
    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        res = 0
        for i in range(len(nums)-2):
            for j in range(i+1, len(nums)-1):
                for k in range(j+1, len(nums)):
                    if nums[i] + nums[j] + nums[k] > 2 * max(nums[i], nums[j], nums[k]):
                        res += 1

        return res                    
            
            
        

    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def triangle(a, b, c):
            if 0 in (a, b, c):
                return False

            longestSide = max(a, b, c)
            return a + b + c > 2 * longestSide

        nums.sort()
        d = {}
        for i, c in enumerate(nums):
            d[c] = d.get(c, 0) + 1

        res = 0
        items = list(d.keys())
        for i in range(len(items)):
            if i + 2 < len(items):
                a, b, c = d[items[i]], d[items[i+1]], d[items[i+2]]
                if triangle(items[i], items[i+1], items[i+2]) :
                    res += a * b * c

            if i + 1 < len(items):
                a, b = d[items[i]], d[items[i+1]]
                if b > 1 and triangle(items[i], items[i+1], items[i+1]):
                    res += a * b * (b - 1) // 2 
                if a > 1 and triangle(items[i], items[i], items[i+1]):
                    res += b * a * (a-1) // 2

            if i < len(items):
                a = d[items[i]]
                if a > 2 and triangle(items[i], items[i], items[i]):
                    res += a * (a-1) * (a-2) // 6

        return res
                    

            

            

            

        



if __name__=="__main__":


    res = triangleNumber().doit([2, 2, 3, 4])

    res = triangleNumber().doit([0,1,1,1])

    res = triangleNumber().doit([1,2,3,4,5,6])

    a = [86,27,76,72,44,86,51,72,77,85,88,43,1,11,98,7,17,8,13,6,17,88,100,22,7,88,6,11,63,24,8,72,33,79,13,49,54,36,39,27,31,25,23,76,40,36,8,60,59,80,98,6,8,58,55,73,20,7,59,17,100,1,52,97,68,27,84,75,6,28,55,30,4,90,33,97,10,11,90,16,72,31,31,95,59,46,35,59,91,60,6,88,55,2,10,48,84,56,44,73]

    res = triangleNumber().doit(a)

    pass
        
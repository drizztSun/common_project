
import os

# leetcode 42. Trapping Rain Water
# Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

# For example, 
# Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.




class trap:

    # O(3n)
    def doit(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        
        i, left, maxl = 1, [0 for _ in range(len(height))], 0
        while i < len(height):
            maxl = max(maxl, height[i-1])
            left[i] = maxl
            i += 1

        j, right, maxr = len(height)-2, [0 for _ in range(len(height))], 0
        while j >= 0:
            maxr = max(maxr, height[j+1])
            right[j] = maxr
            j -= 1

        i, res = 0, 0
        while i < len(height):
            res += (min(left[i], right[i]) - height[i]) if (min(left[i], right[i]) - height[i]) > 0 else 0 
            i += 1

        return res

    # O(n)
    def doit(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        if len(height)<=2:
            return 0

        l=0
        r=len(height)-1
        ans=0

        while l<r and height[l]<=height[l+1]:
            l+=1

        while l<r and height[r]<=height[r-1]:
            r-=1

        while l<r:
            left=height[l]
            right=height[r]

            if left<=right:
                while l<r and height[l]<=left:
                    
                    ans += left-height[l]
                    l=l+1
            else:
                while l<r and height[r]<=right:
                    
                    ans += right-height[r]
                    r=r-1
        
        return ans




# 407. Trapping Rain Water II
# Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, 
# compute the volume of water it is able to trap after raining.

# Note:
# Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.

# Example 
# Given the following 3x6 height map:
# [
#  [1,4,3,1,3,2],
#  [3,2,1,3,2,4],
#  [2,3,3,2,3,1]
# ]
# Return 4.

class trapRainWater:

    def doit(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        pass
        





if __name__=="__main__":


    res = trap().doit([2,0,2])

    res = trap().doit([0,1,0,2,1,0,1,3,2,1,2,1])

    pass
        

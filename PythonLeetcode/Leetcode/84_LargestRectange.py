
import os

# 84. Largest Rectangle in Histogram
# Given n non-negative integers representing the histogram's bar height where the width of each bar is 1,
# find the area of largest rectangle in the histogram.
# For example,
# Given heights = [2,1,5,6,2,3],
# return 10.

class largestRectangleArea(object):
    def doit1(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        leftLess = [-1] * len(heights)
        rightLess = [len(heights)] * len(heights)
        
        for i in range(1, len(heights)):
            p = i-1
            while p >= 0 and heights[p] >= heights[i]:
                p = leftLess[p]
            leftLess[i] = p

        for i in reversed(range(len(heights)-1)):
            p = i+1
            while p < len(heights) and heights[p] >= heights[i]:
                p = rightLess[p]
            rightLess[i] = p
        
        MAX = 0
        for i in range(len(heights)):
            val = heights[i] * (rightLess[i] - leftLess[i] - 1)        
            MAX = max(MAX, val)

        return MAX

    # fatest one
    def doit(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        maxArea = 0
        stackHeight = []
        stackIndex = []
        
        for i in range(len(heights)):
            if stackHeight == [] or heights[i] > stackHeight[len(stackHeight)-1]:
                stackHeight.append(heights[i]) 
                stackIndex.append(i)
                
            elif heights[i] < stackHeight[len(stackHeight)-1]:
                lastIndex = 0
                
                while stackHeight and heights[i] < stackHeight[len(stackHeight)-1]:
                    lastIndex = stackIndex.pop()
                    
                    tempArea = stackHeight.pop() * (i-lastIndex)
                    
                    if maxArea < tempArea: 
                        maxArea = tempArea
                        
                stackHeight.append(heights[i])
                stackIndex.append(lastIndex)
                
        while stackHeight:
            tempArea = stackHeight.pop() * (len(heights) - stackIndex.pop())
            if tempArea > maxArea:
                maxArea = tempArea
                
        return maxArea

    def doit2(self, height):
        """
        :type heights: List[int]
        :rtype: int
        """
        height.append(0)
        stack = [-1]
        ans = 0
        for i in range(len(height)):
            while height[i] < height[stack[-1]]:
                h = height[stack.pop()]
                w = i - stack[-1] - 1
                ans = max(ans, h * w)
            stack.append(i)
        height.pop()
        return ans


if __name__=="__main__":
     
   res = largestRectangleArea().doit([2,1,5,6,2,3])

   res = largestRectangleArea().doit([1,1])

   res = largestRectangleArea().doit([2,1,2])

   print
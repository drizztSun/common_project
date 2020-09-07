"""
# 84. Largest Rectangle in Histogram
# Given n non-negative integers representing the histogram's bar height where the width of each bar is 1,
# find the area of largest rectangle in the histogram.
# For example,
# Given heights = [2,1,5,6,2,3],
# return 10.
"""

class LargestRectangleArea(object):

    # O(n2)
    def doit1(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        maxv , p = 0, 0
        for i in range(len(heights)):
            if i == len(heights) - 1 or heights[i] > heights[i+1]:
                high = heights[i]
                for j in reversed(range(i+1)):
                    if heights[j] <= high:
                        high = heights[j]
                    maxv = max(maxv, (i - j + 1) * high)
        return maxv

    """
    idea: Each value of Heights has a potential Area, by its heights. 
    We need find the index of its first, left and right height, which is less than its heights.
    They are the left board and right board
    """
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
            if stackHeight == [] or heights[i] > stackHeight[-1]:
                stackHeight.append(heights[i]) 
                stackIndex.append(i)
                
            elif heights[i] < stackHeight[-1]:
                lastIndex = 0
                
                while stackHeight and heights[i] < stackHeight[-1]:
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
                # if cur high less than first stack high, that means it is the right board,
                h = height[stack.pop()]
                w = i - stack[-1] - 1 # i is right board, stack[-1] is left board
                ans = max(ans, h * w)
            # if high[i] > the first stack high, it means that is the left board
            stack.append(i)
        height.pop()
        return ans


if __name__=="__main__":
     
   res = LargestRectangleArea().doit([2,1,5,6,2,3])

   res = LargestRectangleArea().doit([1,1])

   res = LargestRectangleArea().doit([2,1,2])

   print
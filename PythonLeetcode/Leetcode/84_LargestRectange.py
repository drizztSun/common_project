"""
# 84. Largest Rectangle in Histogram
# Given n non-negative integers representing the histogram's bar height where the width of each bar is 1,
# find the area of largest rectangle in the histogram.
# For example,
# Given heights = [2,1,5,6,2,3],
# return 10.
"""


class LargestRectangleArea(object):

    """
    Approach 5: Using Stack
    Algorithm

    In this approach, we maintain a stack. Initially, we push a -1 onto the stack to mark the end.
    We start with the leftmost bar and keep pushing the current bar's index onto the stack until we get two successive numbers in descending order, i.e.
    until we get a[i]<a[i-1]. Now, we start popping the numbers from the stack until we hit a number stack[j] on the stack such that
    a[stack[j]] ≤ a[i].

    Every time we pop, we find out the area of rectangle formed using the current element as the height of the rectangle and the difference
    between the the current element's index pointed to in the original array and the element stack[top-1] -1stack[top−1]−1 as the width i.e.
    if we pop an element stack[top]stack[top] and i is the current index to which we are pointing in the original array, the current area of the rectangle will be considered as:

    (i-stack[top-1]-1) \times a\big[stack[top]\big].(i−stack[top−1]−1)×a[stack[top]].

    Further, if we reach the end of the array, we pop all the elements of the stack and at every pop, this time we use the following equation to find the area: (stack[top]-stack[top-1]) \times a\big[stack[top]\big](stack[top]−stack[top−1])×a[stack[top]], where stack[top]stack[top] refers to the element just popped. Thus, we can get the area of the of the largest rectangle by comparing the new area found everytime.

    The following example will clarify the process further:
    """
    def doit_stack(self, height):
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
                w = i - stack[-1] - 1  # i is right board, stack[-1] is left board
                ans = max(ans, h * w)
            # if high[i] > the first stack high, it means that is the left board
            stack.append(i)
        height.pop()
        return ans


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




if __name__=="__main__":
     
   res = LargestRectangleArea().doit([2,1,5,6,2,3])

   res = LargestRectangleArea().doit([1,1])

   res = LargestRectangleArea().doit([2,1,2])
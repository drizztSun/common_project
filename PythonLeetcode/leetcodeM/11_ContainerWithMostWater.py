"""
Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai).
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0).
Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49

"""


class MaxAreaByRect:

    def doit_brute_force(self, height):

        area = 0

        for l in range(len(height)):

            for r in range(l+1, len(height)):

                area = max(area, min(height[r], height[l]) * (r - l))

        return area

    """
    Approach 2: Two Pointer Approach
    Algorithm

    The intuition behind this approach is that the area formed between the lines will always be limited by the height of the shorter line. Further, the farther the lines, the more will be the area obtained.

    We take two pointers, one at the beginning and one at the end of the array constituting the length of the lines. Futher, we maintain a variable \text
    {maxarea}maxarea to store the maximum area obtained till now. At every step, we find out the area formed between them, update \text{maxarea}maxarea
    and move the pointer pointing to the shorter line towards the other end by one step.

    The algorithm can be better understood by looking at the example below:

    How this approach works?

    Initially we consider the area constituting the exterior most lines. Now, to maximize the area, we need to consider the area between the lines of larger lengths.
    If we try to move the pointer at the longer line inwards, we won't gain any increase in area, since it is limited by the shorter line. But moving the shorter
    line's pointer could turn out to be beneficial, as per the same argument, despite the reduction in the width. This is done since a relatively longer line obtained by moving the shorter
    line's pointer might overcome the reduction in area caused by the width reduction.

    For further clarification click here and for the proof click here.
    """
    def doit_twopointer(self, height: list[int]):

        left, right = 0, len(height) - 1
        area = 0

        while left <= right:

            area = max(area, min(height[left], height[right]) * (right-left))

            if height[left] < height[right]:
                left += 1
            else:
                right -= 1

        return area
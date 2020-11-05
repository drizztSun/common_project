"""
42. Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
Example 1:

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9


Constraints:

n == height.length
0 <= n <= 3 * 104
0 <= height[i] <= 105
"""


class TrapRainWater:

    # O(n)
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

    def doit_1(self, height):

        left = [0]
        for i in range(1, len(height)):
            left.append(max(left[-1], height[i - 1]))

        right = [0]
        for i in range(len(height) - 1, 0, -1):
            right.append(max(right[-1], height[i]))

        res = 0
        for i in range(len(height)):
            res += max(0, min(left[i], right[len(right) - 1 - i]) - height[i])

        return res

    # O(n)
    def doit(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        if len(height)<=2:
            return 0

        l = 0
        r = len(height)-1
        ans = 0

        while l < r and height[l] <= height[l+1]:
            l += 1

        while l < r and height[r] <= height[r-1]:
            r -= 1

        while l < r:
            left = height[l]
            right = height[r]

            if left <= right:
                while l < r and height[l] <= left:
                    ans += left-height[l]
                    l += 1
            else:
                while l < r and height[r] <= right:
                    ans += right-height[r]
                    r -= 1
        
        return ans


if __name__ == "__main__":

    res = TrapRainWater().doit([2,0,2])

    res = TrapRainWater().doit([0,1,0,2,1,0,1,3,2,1,2,1])

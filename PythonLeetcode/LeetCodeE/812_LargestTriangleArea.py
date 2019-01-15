# 812. Largest Triangle Area

# You have a list of points in the plane. Return the area of the largest triangle that can be formed by any 3 of the points.

# Example:
# Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
# Output: 2
# Explanation: 
# The five points are show in the figure below. The red triangle is the largest.

import itertools

class LargestTriangleArea:
    def doit(self, points):
        """
        :type points: List[List[int]]
        :rtype: float
        """
        ans = 0.0
        for item in itertools.combinations(points, 3):
            ans = max(ans, abs(item[0][0] * (item[1][1] - item[2][1]) + 
                                    item[1][0] * (item[2][1] - item[0][1]) +
                                    item[2][0] * (item[0][1] - item[1][1])))            

        return ans * 0.5


if __name__ == "__main__":

    res = LargestTriangleArea().doit([[0,0],[0,1],[1,0],[0,2],[2,0]])
        
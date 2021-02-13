"""
1739. Building Boxes


You have a cubic storeroom where the width, length, and height of the room are all equal to n units.
You are asked to place n boxes in this room where each box is a cube of unit side length. There are however some rules to placing the boxes:

You can place the boxes anywhere on the floor.
If box x is placed on top of the box y, then each side of the four vertical sides of the box y must either be adjacent to another box or to a wall.
Given an integer n, return the minimum possible number of boxes touching the floor.



Example 1:



Input: n = 3
Output: 3
Explanation: The figure above is for the placement of the three boxes.
These boxes are placed in the corner of the room, where the corner is on the left side.
Example 2:



Input: n = 4
Output: 3
Explanation: The figure above is for the placement of the four boxes.
These boxes are placed in the corner of the room, where the corner is on the left side.
Example 3:



Input: n = 10
Output: 6
Explanation: The figure above is for the placement of the ten boxes.
These boxes are placed in the corner of the room, where the corner is on the back side.


Constraints:

1 <= n <= 10^9



"""


class MinimumBoxes:

    """
        imagine the bottom is a triangle with same yao.
                 1
               1   1
              1  1   1
            1   1   1  1

        Per row increment 1, then the whole n could be incremented (row + 1) * row / 2.
        We are seeking the biggest row, make total just less than n

        Then rest of them, we can continue to fill cube on the ground to the top, on row + 1.
        if we can fill r on groud, the total increnment is r * (r+1) / 2.
    """
    def doit_math(self, n: int) -> int:

        if n == 1: return 1

        row_idx = 1
        total_n_boxes = 1
        while total_n_boxes < n:
            row_idx += 1
            increment = row_idx * (row_idx + 1) // 2
            total_n_boxes += increment

        total_n_boxes -= increment
        row_idx -= 1

        for r in range(row_idx + 2):
            if n <= r * (r + 1) // 2 + total_n_boxes:
                return r + row_idx * (row_idx + 1) // 2

        return 1

    def doit_binary_search(self, n: int) -> int:

        """
            4 3 3 2 1
            3 2 2 1
            2 1 1
            1

            so edge will be d, then d^2 < (1+d) * d <= 2 * area
            => d < sqrt(2*area) is upperbound, go d-- find smaller d.

            diff is more to fill ground

            n => area = 13 => d= 4 + 3 => n`

            5 4 3 1
            4 3 1
            3 1
            1

            # calculate the suffix total, of 5, 4, 3, 1
        """
        def calculate(area):
            from math import sqrt
            d = int(sqrt(2 * area))

            while (1 + d) * d // 2 > area:
                d -= 1

            diff = area - (1 + d) * d // 2

            triangle = [0] * d

            for i in range(d):
                triangle[i] = d - i

            for i in range(diff):
                triangle[i] += 1

            total, sufsum = 0, 0
            for i in range(d-1, -1, -1):
                sufsum += triangle[i]
                total += sufsum

            return total

        left, right = 1, n+1

        while left < right:

            mid = (left + right) // 2

            if calculate(mid) >= n:
                right = mid
            else:
                left = mid + 1

        return left


if __name__ == '__main__':

    MinimumBoxes().doit_binary_search(15)
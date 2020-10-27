"""
296. Best Meeting Point

A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group.
The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

Example:

Input:

1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

Output: 6

Explanation: Given three people living at (0,0), (0,4), and (2,2):
             The point (0,2) is an ideal meeting point, as the total travel distance
             of 2+2+2=6 is minimal. So return 6.

"""


class MinTotalDistance:

    """
    Approach #3 (Sorting) [Accepted]
    Finding the best meeting point in a 2D grid seems difficult. Let us take a step back and solve the 1D case which is much simpler.
    Notice that the Manhattan distance is the sum of two independent variables. Therefore, once we solve the 1D case, we can solve the 2D case as two independent 1D problems.

    Let us look at some 1D examples below:

    Case #1: 1-0-0-0-1

    Case #2: 0-1-0-1-0
    We know the best meeting point must locate somewhere between the left-most and right-most point. For the above two cases,
    we would select the center point at x = 2x=2 as the best meeting point. How about choosing the mean of all points as the meeting point?

    Consider this case:

    Case #3: 1-0-0-0-0-0-0-1-1
    Using the mean gives us avg(x) = (0 + 7 + 8) / 3, as the meeting point. The total distance is 10.

    But the best meeting point should be at x = 7 and the total distance is 8.

    You may argue that the mean is close to the optimal point. But imagine a larger case with many 1's congregating on the right side and just a single 1 on the left-most side. Using the mean as the meeting point would be far from optimal.

    Besides mean, what is a better way to represent the distribution of points? Would median be a better representation? Indeed. In fact, the median must be the optimal meeting point.

    Case #4: 1-1-0-0-1
    To see why this is so, let us look at case #4 above and choose the median x = 1x=1 as our initial meeting point.
    Assume that the total distance traveled is d. Note that we have equal number of points distributed to its left and to its right.
    Now let us move one step to its right where x = 2x=2 and notice how the distance changes accordingly.

    Since there are two points to the left of x = 2x=2, we add 2 * (+1)2∗(+1) to d. And d is offset by –1 since there is one point to the right.
    This means the distance had overall increased by 1.

    Therefore, it is clear that:

    As long as there is equal number of points to the left and right of the meeting point, the total distance is minimized.

    Case #5: 1-1-0-0-1-1
    One may think that the optimal meeting point must fall on one of the 1's. This is true for cases with odd number of 1's, but not necessarily true when there are even number of 1's, just like case #5 does. You can choose any of the x = 1x=1 to x = 4x=4 points and the total distance is minimized. Why?

    The implementation is direct. First we collect both the row and column coordinates, sort them and select their middle elements. Then we calculate the total distance as the sum of two independent 1D problems.

    Note that in the code above we do not need to sort rows, why?

    Complexity analysis

    Time complexity : O(mnlogmn). Since there could be at most m \times nm×n points, therefore the time complexity is O(mn \log mn)O(mnlogmn) due to sorting.

    Space complexity : O(mn).
    """
    def doit_sorting(self, grid):

        def distance1D(nums, c):
            return sum(abs(x - c) for x in nums)

        rows, cols = [], []
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    rows.append(i)
                    cols.append(j)

        rows.sort()
        cols.sort()

        return distance1D(rows, rows[len(rows) // 2]) + distance1D(cols, cols[len(cols) // 2])


    """
    Approach #4 (Collect Coordinates in Sorted Order) [Accepted]
    We could use the Selection algorithm to select the median in O(mn)O(mn) time, but there is an easier way. 
    Notice that we can collect both the row and column coordinates in sorted order.
    """
    def doit_sorting_1(self, grid):

        def distance1D(nums, c):
            return sum(abs(x - c) for x in nums)

        rows = []
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == 1:
                    rows.append(i)

        cols = []
        for i in range(len(grid[0])):
            for j in range(len(grid)):
                if grid[j][i] == 1:
                    cols.append(i)

        return distance1D(rows, rows[len(rows)//2]) + distance1D(cols, cols[len(cols)//2])

    def doit_sorting(self, grid):

        Xs = []
        for i, row in enumerate(grid):
            t = sum(row)
            if t:
                Xs.append([i, t])
        Ys = []
        for y in range(len(grid[0])):
            t = sum(grid[r][y] for r in range(len(grid)))
            if t:
                Ys.append([y, t])

        res = 0
        for XY in [Xs, Ys]:
            l, r = 0, len(XY) - 1
            while l < r:
                m = min(XY[l][1], XY[r][1])
                res += m * (XY[r][0] - XY[l][0])
                XY[r][1] -= m
                XY[l][1] -= m
                if XY[l][1] == 0:
                    l += 1
                if XY[r][1] == 0:
                    r -= 1
        return res


if __name__ == '__main__':

    MinTotalDistance().doit_sorting_1([[1, 1]])
"""
554. Brick Wall


There is a brick wall in front of you. The wall is rectangular and has several rows of bricks. The bricks have the same height but different width. You want to draw a vertical line from the top to the bottom and cross the least bricks.

The brick wall is represented by a list of rows. Each row is a list of integers representing the width of each brick in this row from left to right.

If your line go through the edge of a brick, then the brick is not considered as crossed. You need to find out how to draw the line to cross the least bricks and return the number of crossed bricks.

You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.

 

Example:

Input: [[1,2,2,1],
        [3,1,2],
        [1,3,2],
        [2,4],
        [3,1,2],
        [1,3,1,1]]

Output: 2

Explanation: 

 

Note:

The width sum of bricks in different rows are the same and won't exceed INT_MAX.
The number of bricks in each row is in range [1,10,000]. The height of wall is in range [1,10,000]. Total number of bricks of the wall won't

""""


class BrickWalls:

    """
        Approach #3 Using HashMap [Accepted]
        Algorithm

        In this approach, we make use of a HashMap mapmap which is used to store entries in the form: (sum, count)(sum,count). Here, sumsum refers to the cumulative sum of the bricks' widths encountered in the current row, and countcount refers to the number of times the corresponding sum is obtained. Thus, sumsum in a way, represents the positions of the bricks's boundaries relative to the leftmost boundary.

        Let's look at the process first. We traverse over every row of the given wall. For every brick considered, we find the sumsum corresponding to the sum of the bricks' widths encountered so far in the current row. If this sumsum's entry doesn't exist in the mapmap, we create a corresponding entry with an initial countcount of 1. If the sumsum already exists as a key, we increment its corresponding countcount value.

        This is done based on the following observation. We will never obtain the same value of sumsum twice while traversing over a particular row. Thus, if the sumsum value is repeated while traversing over the rows, it means some row's brick boundary coincides with some previous row's brick boundary. This fact is accounted for by incrementing the corresponding countcount value.

        But, for every row, we consider the sum only upto the second last brick, since the last boundary isn't a valid boundary for the solution.

        At the end, we can obtain the maximum countcount value to determine the minimum number of bricks that need to be cut to draw a vetical line through them.

        The following animation makes the process clear:

    """

    def doit_hashtable(self, wall):
        """
        :type wall: List[List[int]]
        :rtype: int
        """
        from collections import Counter
        rows = Counter()
        maxv = 0

        for i in range(len(wall)):
            accum = 0
            for c in range(len(wall[i]) - 1):
                accum += wall[i][c]
                rows[accum] += 1
                maxv = max(rows[accum], maxv)

        return len(wall) - maxv
# 218 The Skyline Problem


# A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. 
# Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), 
# write a program to output the skyline formed by these buildings collectively (Figure B).


# The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], 
# where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, 
# and Hi is its height. It is guaranteed that 0 ? Li, Ri ? INT_MAX, 0 < Hi ? INT_MAX, and Ri - Li > 0. 
# You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

# For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .
# The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. 
# A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

# For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

# Notes:

# The number of buildings in any input list is guaranteed to be in the range [0, 10000].
# The input list is already sorted in ascending order by the left x position Li.
# The output list must be sorted by the x position.
# There must be no consecutive horizontal lines of equal height in the output skyline. 
# For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: 
# [...[2 3], [4 5], [12 7], ...]

import heapq

class getSkyline:


# This is a Python version of my modification of dong.wang.1694’s brilliant C++ solution.
# It sweeps from left to right. But it doesn’t only keep heights of “alive buildings” in the priority queue
# and it doesn’t remove them as soon as their building is left behind.
# Instead, (height, right) pairs are kept in the priority queue and they stay in there as long as there’s a larger height in there,
# not just until their building is left behind.

# In each loop, we first check what has the smaller x-coordinate: adding the next building from the input,
# or removing the next building from the queue. In case of a tie, adding buildings wins, as that guarantees correctness (think about it :-).
# We then either add all input buildings starting at that x-coordinate or we remove all queued buildings ending at that x-coordinate or earlier
# (remember we keep buildings in the queue as long as they’re “under the roof” of a larger actually alive building).
# And then, if the current maximum height in the queue differs from the last in the skyline, we add it to the skyline.

    def doit(self, buildings):

        stack = []
        skylines = []
        i = 0
        
        while i < len(buildings) or stack:
            
            if not stack or i < len(buildings) and -stack[0][1] >= buildings[i][0]:
                # uphill
                # if top one's 'right' is larger then stack top's 'left',
                # new one 'i' is crossing with current top rect                
                x = buildings[i][0]
                while i < len(buildings) and buildings[i][0] <= x:
                    heapq.heappush(stack, (-buildings[i][2], -buildings[i][1]))
                    i += 1
            else:
                # downhill (The left of current 'i' is larger than the right of the top one in stack)
                # We looking for a shorter one, which 'right' is larger then current one's 'right'.
                # There must be a corssing between them. 
                # so hight will generate for the finally top one.
                x = -stack[0][1]
                while stack and -stack[0][1] <= x:
                    heapq.heappop(stack)

            # 0 or current top one's height                    
            height = len(stack) and -stack[0][0]
            
            # if height == to Top one in skylines, then we skip 
            if not skylines or height != skylines[-1][1]:
                skylines.append([x, height])

        return skylines


 



if __name__=="__main__":

    # [ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]
    res1 = getSkyline().doit([ [3, 7, 15], [2, 9, 10], [5, 12, 12], [15, 20, 10], [19, 24, 8] ])

    res2 = getSkyline().doit([ [2, 9, 10], [3, 7, 15],  [5, 12, 12], [15, 20, 10], [19, 24, 8] ])
    
    res = 1

    pass
        



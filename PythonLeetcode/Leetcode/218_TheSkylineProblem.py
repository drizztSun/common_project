"""
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
# A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height.
Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

# For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

# Notes:

# The number of buildings in any input list is guaranteed to be in the range [0, 10000].
# The input list is already sorted in ascending order by the left x position Li.
# The output list must be sorted by the x position.
# There must be no consecutive horizontal lines of equal height in the output skyline.
# For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such:
# [...[2 3], [4 5], [12 7], ...]

"""
import heapq


class GetSkyline:

    """
    I came up with a conceptually easy to understand solution, but I can't think of how to simplify my code further.

    The idea is this:

    We use a priority queue and order it by when the buildings begin to appear (i.e. their left side) and greatest height. When we encounter a new building, there can be one of three cases:

    The new building appears after the current one ends. In this case, we create a new key point at the end of our current building at height 0 and another at the beginning of the new building at its height.

    The new building appears exactly when the current one ends. In this case, we should create a new point only if the height has changed.

    The last case is the most interesting one. If the new building begins before the current one ends, we want to compare their heights. If the new one is greater,
    then we want to create a new point, otherwise we don't. Now this is where the main idea of the algorithm comes in. Suppose the new building's height is greater,
    but our current building ends after the new one. Then we effectively can create a new building, one that starts when the new building ends and ends when the current one ends.

    Obviously if the current building ends before the new one does, it is completely covered and we can just get rid of it.
    We can apply the same logic when the current buildings height is greater, just create a new building that starts from when current building ends and ends when new building ends, if possible.

    I think the idea is quite clear, but my code is not. Any ideas on how to simplify the logic?

    """
    def doit_heap(self, buildings):

        from heapq import heappush, heappop, heapify

        if not buildings:
            return []

        heap = [(l, -h, r, h) for l, r, h in buildings]
        heapify(heap)

        left, _, end, current = heappop(heap)
        result = [[left, current]]
        while heap:
            left, _, right, height = heappop(heap)

            # new building begins when current one ends, add key point if height changes
            if end == left and current != height:
                result.append([left, height])
            # new building begins after current one ends, add key point
            # at end of current building at height 0 and another at
            # beginning of new building at its height
            elif end < left:
                result.append([end, 0])
                result.append([left, height])
            # there is overlap in buildings
            elif left < end:
                # create new key point if height increased
                if height > current:
                    result.append([left, height])
                    # create a new building starting at right and ending at end
                    # with height current
                    if right < end:
                        heappush(heap, (right, -current, end, current))
                else:
                    # create a new building starting at end and ending at right
                    # with height height
                    if end < right:
                        heappush(heap, (end, -height, right, height))
                    # we dont want to update end and current here, so continue
                    continue

            end = right
            current = height

        result.append([end, 0])
        return result

    """
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

    """
    def doit_heap(self, buildings):

        stack = []
        skylines = []
        i = 0
        buildings.sort(key=lambda a: a[0])
        
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


if __name__ == "__main__":

    # [ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]
    res1 = GetSkyline().doit_heap([ [3, 7, 15], [2, 9, 10], [5, 12, 12], [15, 20, 10], [19, 24, 8] ])

    res2 = GetSkyline().doit_heap([ [2, 9, 10], [3, 7, 15],  [5, 12, 12], [15, 20, 10], [19, 24, 8] ])

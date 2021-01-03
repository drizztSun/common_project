"""
# 391. Perfect Rectangle

# Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.

# Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2].
# (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).

# Example 1:

# rectangles = [
#  [1,1,3,3],
#  [3,1,4,2],
#  [3,2,4,4],
#  [1,3,2,4],
#  [2,3,3,4]
# ]

# Example 2:

# rectangles = [
#  [1,1,2,3],
#  [1,3,2,4],
#  [3,1,4,2],
#  [3,2,4,4]
# ]
"""


class PerfectRectangle:

    # Save area and all FOUR corners for each sub-rectangle:
    # sum of area of all sub-rectangle == area of maximum rectangle.
    # each corner should only appear either TWO or FOUR times, except four corners of big rectangle.
    # if area == maxarea, but there are some overlapping, it means corners are not in 2 or 4 times
    def doit_hashtable(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        minX, maxX, minY, maxY = float('inf'), 0, float('inf'), 0
        area = 0
        D = {}

        for rect in rectangles:
            B, L, T, R = rect[:]
            minX, maxX = min(minX, L), max(maxX, R)
            minY, maxY = min(minY, B), max(maxY, T)

            area += (T - B) * (R - L)

            for i in [(L, B), (L, T), (R, B), (R, T)]:
                D[i] = D.get(i, 0) + 1

        if area != (maxX - minX) * (maxY - minY):
            return False
        
        bigCorner = [(minX, minY), (minX, maxY), (maxX, minY), (maxX, maxY)]

        for k in bigCorner:
            if k not in D or D[k] != 1:
                return False

        for k in D:
            # each corner should only appear either TWO or FOUR times, except four corners of big rectangle.
            if D[k] not in (2, 4) and k not in bigCorner:
                return False

        return True


    # https://leetcode.com/problems/perfect-rectangle/discuss/87180/O(n)-solution-by-counting-corners-with-detailed-explaination
    #    Algorithm
    #    Step1: Based on the above idea we maintain a mapping from (x, y)->mask by scanning the sub-rectangles from beginning to end.

    #   (x, y) corresponds to corners of sub-rectangles
    #   mask is a 4-bit binary mask. Each bit indicates whether there have been a sub-rectangle with a top-left/top-right/bottom-left/bottom-right corner at (x, y). If we see a conflict while updating mask, it suffice to return a false during the scan.
    #   In the meantime we obtain the bounding box of all rectangles (which potentially be the rectangle cover) by getting the upper/lower bound of x/y values.

    #   Step 2: Once the scan is done, we can just browse through the unordered_map to check the whether the mask corresponds to a T junction / cross, or corner if it is indeed a bounding box corner.
    #   (note: my earlier implementation uses counts of bits in mask to justify corners, and this would not work with certain cases as @StefanPochmann points out).

    #   Complexity
    #   The scan in step 1 is O(n) because it loop through rectangles and inside the loop it updates bounding box and unordered_map in O(1) time.

    #   Step2 
    #   visits 1 corner at a time with O(1) computations for at most 4n corners (actually much less because either corner overlap or early stopping occurs). So it’s also O(n).
    def doit_hashtable_1(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        import collections

        def insertCorner(D, x, y, pos):
            if D[(x, y)] & pos:
                return False
            D[(x, y)] |= pos
            return True

        # step 1
        bigRect = [float('inf'), float('inf'), 0, 0]
        D = collections.defaultdict(int)
        for c in rectangles:
            bigRect[0] = min(bigRect[0], c[0])
            bigRect[1] = min(bigRect[1], c[1])
            bigRect[2] = max(bigRect[2], c[2])
            bigRect[3] = max(bigRect[3], c[3])

            if not insertCorner(D, c[0], c[1], 1):
                return False
        
            if not insertCorner(D, c[2], c[1], 2):
                return False

            if not insertCorner(D, c[0], c[3], 4):
                return False
        
            if not insertCorner(D, c[2], c[3], 8):
                return False

        
        # step 2
        valid_corner = [False for _ in range(16)]
        valid_interior = [False for _ in range(16)]

        valid_corner[1] = valid_corner[2] = valid_corner[4] = valid_corner[8] = True
        valid_interior[3] = valid_interior[5] = valid_interior[10] = valid_interior[12] = valid_interior[15] = True

        for x in D.keys():
            if ((x != bigRect[1] and x != bigRect[3]) or (y != bigRect[0] and y != bigRect[2])) and not valid_interior[D[x]]:
                return False

        return True


    def doit(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        # Find bottom left and top right points:
        b = rectangles[0][0]
        l = rectangles[0][1]
        t = rectangles[0][2]
        r = rectangles[0][3]
        area = 0
        for rect in rectangles:
            if rect[0] < b: b=rect[0]
            if rect[1] < l: l=rect[1]
            if rect[2] > t: t=rect[2]
            if rect[3] > r: r=rect[3]
        
        # Shift all rectangles into positive-definite regime
        new_rectangles = []
        for rect in rectangles:
            rect[0] += 1-b
            rect[2] += 1-b
            rect[1] += 1-l
            rect[3] += 1-l

            new_rectangles.append(rect)

        rectangles = new_rectangles

        t += 1-b
        r += 1-l
        b = 1
        l = 1
        
        # Calculate running sums of the X and Y indices cleverly
        running_sum_x = 0
        running_sum_y = 0
        running_sum_xy = 0
        area = 0

        for rect in rectangles:

            running_sum_x += ((rect[2]*(rect[2]-1)) - (rect[0])*(rect[0]-1)) * (rect[3]-rect[1])

            running_sum_y += ((rect[3]*(rect[3]-1)) - (rect[1])*(rect[1]-1)) * (rect[2]-rect[0])

            running_sum_xy += ((rect[3]*(rect[3]-1)) - (rect[1])*(rect[1]-1)) * ((rect[2]*(rect[2]-1)) - (rect[0])*(rect[0]-1))

            area += (rect[2]-rect[0]) * (rect[3]-rect[1])

        if (running_sum_x == (t)*(t-1)*(r-l) and running_sum_y == (r)*(r-1)*(t-b) and 
            area == (t-b)*(r-l) and running_sum_xy == (r)*(r-1)*(t)*(t-1)):
            return True
        else:
            return False

    # O(n**3)
    def doit3(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        #bigRect = [max([ a[i][j] for i in range(len(rectangles)) ]) for j in range(4)]
        #minB, minL, minT, minR = float('inf'), float('inf'), 0, 0
        #bigRect = [float('inf'), float('inf'), 0, 0 for c in rectangles]

        bigRect = [float('inf'), float('inf'), 0, 0]
        for c in rectangles:
            bigRect[0] = min(bigRect[0], c[0])
            bigRect[1] = min(bigRect[1], c[1])
            bigRect[2] = max(bigRect[2], c[2])
            bigRect[3] = max(bigRect[3], c[3])


        rects = set()
        for j in range(bigRect[0], bigRect[2]):
            for i in range(bigRect[1], bigRect[3]):
                rects.add((i, j, i+1, j+1))

        for c in rectangles:
            for j in range(c[0], c[2]):
                for i in range(c[1], c[3]):
                    if (i, j, i+1, j+1) in rects:
                        rects.remove((i, j, i+1, j+1))
                    else :
                        return False

        
        return len(rects) == 0


if __name__=="__main__":

    rectangles = [
      [1,1,3,3],
      [3,1,4,2],
      [3,2,4,4],
      [1,3,2,4],
      [2,3,3,4]
    ]

    res = PerfectRectangle().doit(rectangles)

    rect = [
     [1,1,3,3],
     [3,1,4,2],
     [1,3,2,4],
     [2,2,4,4]
    ]

    res = PerfectRectangle().doit(rect)


    rect = [
        [0,0,1,1],
        [0,1,3,2],
        [1,0,2,2]
    ]

    res = PerfectRectangle().doit(rect)

    pass

    

    


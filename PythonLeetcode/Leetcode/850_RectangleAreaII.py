# 850. Rectangle Area II

# We are given a list of (axis-aligned) rectangles.  Each rectangle[i] = [x1, y1, x2, y2] , 
# where (x1, y1) are the coordinates of the bottom-left corner, 
# and (x2, y2) are the coordinates of the top-right corner of the ith rectangle.

# Find the total area covered by all rectangles in the plane.  
# Since the answer may be too large, return it modulo 10^9 + 7.


# Example 1:

# Input: [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
# Output: 6
# Explanation: As illustrated in the picture.
# Example 2:

# Input: [[0,0,1000000000,1000000000]]
# Output: 49
# Explanation: The answer is 10^18 modulo (10^9 + 7), which is (10^9)^2 = (-7)^2 = 49.
# Note:

# 1 <= rectangles.length <= 200
# rectanges[i].length = 4
# 0 <= rectangles[i][j] <= 10^9
# The total area covered by all rectangles will never exceed 2^63 - 1 and thus will fit in a 64-bit signed integer.


class RectangleArea:


# Main steps:

# Construct a rectangle that subsumes all input rectangles as the inital available rectangle;

# For each available rectangle and a input rectangle, cut the available rectangle into 0~4 new available rectangles. 
# Recursively check the next rectangle and its relationship with new available rectangles.

    def doit(self, rectangles):
        """
        :type rectangles: List[List[int]]  [l, b, r, t]
        :rtype: int
        """
        MOD = 10 ** 9 + 7

        def getIntersectArea(r1, c1, r2, c2, x1, y1, x2, y2):
            return  max(0, min(r2, x2) - max(r1, x1)) * max(0, min(c2, y2) - max(c1, y1));       

        def cutRectangle(now, rects, r1, c1, r2, c2):
            if now >= len(rects) or r1 >= r2 or c1 >= c2:
                return 0

            x1, y1, x2, y2 = rects[now]

            if x1 >= r2 or y1 >= c2 or x2 <= r1 or y2 <= c1:
                return cutRectangle(now + 1, rects, r1, c1, r2, c2)

            s1 = cutRectangle(now + 1, rects, r1, c1, min(x1, r2), c2) if x1 > r1 else 0
            s2 = cutRectangle(now + 1, rects, max(r1, x2), c1, r2, c2 ) if x2 < r2 else 0
            s3 = cutRectangle(now + 1, rects, max(r1, x1), c1, min(r2, x2), y1) if y1 > c1 else 0
            s4 = cutRectangle(now + 1, rects, max(r1, x1), y2, min(r2, x2), c2) if y2 < c2 else 0
          
            return s1 + s2 + s3 + s4 + getIntersectArea(x1, y1, x2, y2, r1, c1, r2, c2)

        trp = list(zip(*rectangles))
        return cutRectangle(0, rectangles, min(trp[0]), min(trp[1]), max(trp[2]), max(trp[3])) % MOD



    def doit1(self, rectangels):

        from bisect import insort_left, bisect_left

        events=[]
        for x1, y1, x2, y2 in rectangles:
            events.append((y1,"add",x1,x2))
            events.append((y2,"remove",x1,x2))

        events.sort()
        print(events)

        def cur_length(active):
            ret=0
            cur_x1=cur_x2=-1
            for x1,x2 in active:
                if x1<=cur_x2:
                    cur_x2=max(cur_x2,x2)
                else:
                    ret+=cur_x2-cur_x1
                    cur_x1,cur_x2=x1,x2
            ret+=cur_x2-cur_x1
            return ret

        active=[]
        cur_y=events[0][0]
        ans=0
        for y,typ,x1,x2 in events:
            ans+=(y-cur_y)*cur_length(active)
            if typ=="add":
                insort_left(active,(x1,x2))
            else:
                active.remove((x1,x2))
            cur_y=y

        return ans % (10**9 + 7)


if __name__ == "__main__":

    res = RectangleArea().doit([[0,0,2,2],[1,0,2,3],[1,0,3,1]])
    
    res = RectangleArea().doit([[0,0,1000000000,1000000000]])

    pass
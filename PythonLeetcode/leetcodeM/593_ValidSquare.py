"""
593. Valid Square

Given the coordinates of four points in 2D space p1, p2, p3 and p4, return true if the four points construct a square.

The coordinate of a point pi is represented as [xi, yi]. The input is not given in any order.

A valid square has four equal sides with positive length and four equal angles (90-degree angles).

 

Example 1:

Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: true
Example 2:

Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,12]
Output: false
Example 3:

Input: p1 = [1,0], p2 = [-1,0], p3 = [0,1], p4 = [0,-1]
Output: true
 

Constraints:

p1.length == p2.length == p3.length == p4.length == 2
-10^4 <= xi, yi <= 10^4


"""


class ValidSquare:

    def doit_(self, p1: list, p2: list, p3: list, p4: list) -> bool:
        
        if not (p1 != p2 and p1 != p3 and p2 != p4 and p3 != p4):
            return False
        
        num = sorted([p1, p2, p3, p4], key = lambda x: (x[0], x[1]))
        p1, p2, p3, p4 = num[0], num[1], num[2], num[3]
        
        diff = lambda x, y: (x[0] - y[0], x[1] - y[1])
        
        length = lambda x : x[0] ** 2 + x[1] ** 2

        ortho = lambda x, y: x[0] * y[0] + x[1] * y[1] == 0

        l12 = diff(p1, p2)
        l13 = diff(p1, p3)
        l24 = diff(p2, p4)
        l34 = diff(p3, p4)

        return length(l12) == length(l13) and length(l24) == length(l34) and length(l13) == length(l24) and ortho(l12, l13)


    """
        Approach #2 Using Sorting [Accepted]
        Instead of considering all the permutations of arrangements possible, we can make use of maths to simplify this problem a bit. 
        If we sort the given set of points based on their x-coordinate values, and in the case of a tie, based on their y-coordinate value, we can obtain an arrangement, 
        which directly reflects the arrangement of points on a valid square boundary possible.

        Consider the only possible cases as shown in the figure below:

        Valid_Square

        In each case, after sorting, we obtain the following conclusion regarding the connections of the points:

        1. P0P1, P1P3, P3P2, P2P0  form the four sides of any valid square.
    ​	
        2. P0P3, P1P2 form the diagonals of the square.

        Thus, once the sorting of the points is done, based on the above knowledge, we can directly compare P0P1, P1P3, P3P2, P2P0 for equality of lengths(corresponding to the sides); and P0P3 and P1P2 for equality of lengths(corresponding to the diagonals).


        Complexity Analysis

        Time complexity : O(1). Sorting 4 points takes constant time.

        Space complexity : O(1). Constant space is required.

    """
    def doit_(self, p1: list, p2: list, p3: list, p4: list) -> bool:

        def distance(a, b):
            return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2

        p1, p2, p3, p4 = sorted([p1, p2, p3, p4], key= lambda x: x)
        
        return distance(p1, p2) != 0 and distance(p1, p2) == distance(p1, p3) == distance(p2, p4) == distance(p3, p4) and distance(p1, p4) == distance(p2, p3)
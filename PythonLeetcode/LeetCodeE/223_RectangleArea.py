import os






# leetcode 223 Rectangle Area

# Find the total area covered by two rectilinear rectangles in a 2D plane.

# Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

# Assume that the total area is never beyond the maximum possible value of int.

# (A, B, C, D) (Bottom, left, top, right)


class RectangleArea:
    def doit(self, A, B, C, D, E, F, G, H):
        """
        :type A: int
        :type B: int
        :type C: int
        :type D: int
        :type E: int
        :type F: int
        :type G: int
        :type H: int
        :rtype: int
        """
        Area1 = (D - B) * (C - A)
        Area2 = (G - E) * (H - F)
 
        # length (B, D) or (F, H)
        if (B > H or D < F) or (C < E or A > G):
            return Area1 + Area2

        length = 0
        if F <= B <= H and F <= D <= H:
            length = D - B
        elif B <= F <= D and B <= H <= D:
            length = H - F
        elif F <= B <= H:
            length = H - B
        elif F <= D <= H:
            length = D - F


        width = 0
        if E <= A <= G and E <= C <= G:
            width = C - A
        elif A <= E <= C and A <= G <= C:
            width = G- E 
        elif E <= A <= G:
            width = G- A
        elif E <= C <= G:
            width = C- E 
        
        return Area1 + Area2 - length * width


    def doit1(self, A, B, C, D, E, F, G, H):
        """
        :type A: int
        :type B: int
        :type C: int
        :type D: int
        :type E: int
        :type F: int
        :type G: int
        :type H: int
        :rtype: int
        """
        area1 = (C - A) * (D - B)
        area2 = (G - E) * (H - F)
        if area1 == 0:
            return area2
        if area2 == 0:
            return area1

        cover_l, cover_b, cover_r, cover_t, = max(A, E), max(B, F), min(C, G), min(D, H)

        cover_area = 0
        if cover_l < cover_r and cover_b < cover_t:
            cover_area = (cover_r - cover_l) * (cover_t - cover_b)

        return area1 + area2 - cover_area




if __name__=="__main__":


    res = RectangleArea().doit(-2, -2, 2, 2, -1, -1, 1, 1)


    pass
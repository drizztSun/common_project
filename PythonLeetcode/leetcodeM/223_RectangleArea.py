"""
223. Rectangle Area

Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

Rectangle Area

Example:

Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
Output: 45
Note:

Assume that the total area is never beyond the maximum possible value of int.

"""


class RectangleArea:

    def doit_(self, A: int, B: int, C: int, D: int, E: int, F: int, G: int, H: int) -> int:

        Area1 = (C-A) * (D-B)
        Area2 = (G-E) * (H-F)
        
        if Area1 == 0:
            return Area2
        if Area2 == 0:
            return Area1
        
        cl, cr = max(A, E), min(C, G)
        cb, ct = max(B, F), min(D, H)
        
        AreaCommon = 0
        if cl < cr and cb < ct:
            AreaCommon = (cr-cl) * (ct-cb)
        
        return Area1 + Area2 - AreaCommon
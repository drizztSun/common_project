

class Solution:

    def calculate_area_of_rectange_(self, A: int, B: int, C: int, D: int, E: int, F: int, G: int, H: int) -> int:
        
        Area1 = (C-A) * (D-B)
        Area2 = (G-E) * (H-F)
        
        if Area1 == 0: return Area2
        if Area2 == 0: return Area1

        # Two rectangle common area    
        cl, cr = max(A, E), min(C, G)
        cb, ct = max(B, F), min(D, H)
        
        AreaCommon = 0
        if cl < cr and cb < ct: # if two rectangle has common areas.
            AreaCommon = (cr-cl) * (ct-cb)
        
        return Area1 + Area2 - AreaCommon



    def validate_square(self, p1: list, p2: list, p3: list, p4: list) -> bool:
        
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



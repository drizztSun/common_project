

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
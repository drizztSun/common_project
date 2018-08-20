# 780. Reaching Points

# A move consists of taking a point (x, y) and transforming it to either (x, x+y) or (x+y, y).

# Given a starting point (sx, sy) and a target point (tx, ty), return True if and only if a sequence of
# moves exists to transform the point (sx, sy) to (tx, ty). Otherwise, return False.

# Examples:
# Input: sx = 1, sy = 1, tx = 3, ty = 5
# Output: True
# Explanation:
# One series of moves that transforms the starting point to the target is:
# (1, 1) -> (1, 2)
# (1, 2) -> (3, 2)
# (3, 2) -> (3, 5)

# Input: sx = 1, sy = 1, tx = 2, ty = 2
# Output: False

# Input: sx = 1, sy = 1, tx = 1, ty = 1
# Output: True

# Note:

# sx, sy, tx, ty will all be integers in the range [1, 10^9].


class ReachingPoints:

    # <BFS> 
    def doit1(self, sx, sy, tx, ty):
        """
        :type sx: int
        :type sy: int
        :type tx: int
        :type ty: int
        :rtype: bool
        """
        stack = [(sx, sy)]
        visited = set()

        while stack:

            x, y = stack.pop(0)

            visited.add((x, y))

            if x == tx and y == ty:
                return True
            
            if (x, x + y) not in visited and x <= tx and x + y <= ty:
                stack.append((x, x + y))
            
            if (x + y, y) not in visited and x + y <= tx and y <= ty:
                stack.append((x + y, y))

        return False

    def doit2(self, sx, sy, tx, ty):
        """
        :type sx: int
        :type sy: int
        :type tx: int
        :type ty: int
        :rtype: bool
        """
        def search(sx, sy, tx, ty):
            if sx == tx and sy == ty:
                return True
            elif tx == ty or tx < sx or ty < sy:
                return False
            elif tx > ty:
                index = max(1, int((tx - sx) / ty))
                return search(sx, sy, tx - index * ty, ty)
            else :
                index = max(1, int((ty - sy) / tx))
                return search(sx, sy, tx, ty - index * tx)

        return search(sx, sy, tx, ty)

    def doit(self, sx, sy, tx, ty):
        """
        :type sx: int
        :type sy: int
        :type tx: int
        :type ty: int
        :rtype: bool
        """
        while tx >= sx and ty >= sy:
            if tx == ty:
                break
            elif tx > ty:
                if ty > sy:
                    tx %= ty
                else:
                    return (tx - sx) % ty == 0
            else:
                if tx > sx:
                    ty %= tx
                else:
                    return (ty - sy) % tx == 0

        return tx == sx and ty == sy


        # Basic idea:
        # If we start from sx,sy, it will be hard to find tx, ty.
        # If we start from tx,ty, we can find only one path to go back to sx, sy.
        # I cut down one by one at first and I got TLE. So I came up with remainder.

        # First line:
        # if 2 target points are still bigger than 2 starting point, we reduce target points.
        # Second line:
        # check if we reduce target points to (x, y+kx) or (x+ky, y)

        # Time complexity
        # I will say O(logN) where N = max(tx,ty).
    def doit3(self, sx, sy, tx, ty):
        """
        :type sx: int
        :type sy: int
        :type tx: int
        :type ty: int
        :rtype: bool
        """
        while sx < tx and sy < ty:
            tx, ty = tx % ty, ty % tx
        
        return sx == tx and (ty - sy) % sx == 0 or sy == ty and (tx - sx) % sy == 0


if __name__ == "__main__":

    res = ReachingPoints().doit(sx = 1, sy = 1, tx = 3, ty = 5)

    res = ReachingPoints().doit(sx = 1, sy = 1, tx = 2, ty = 2)

    res = ReachingPoints().doit(sx = 1, sy = 1, tx = 1, ty = 1)

    res = ReachingPoints().doit(35, 13, 455955547, 420098884)

    pass

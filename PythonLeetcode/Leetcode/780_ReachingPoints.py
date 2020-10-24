"""

780. Reaching Points

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

"""


class ReachingPoints:

    """
    Approach #3: Work Backwards (Naive Variant) [Time Limit Exceeded]
    Intuition

    Every parent point (x, y) has two children, (x, x+y) and (x+y, y). However, every point (x, y) only has one parent candidate (x-y, y) if x >= y, else (x, y-x). This is because we never have points with negative coordinates.
    Looking at previous successive parents of the target point, we can find whether the starting point was an ancestor.
    For example, if the target point is (19, 12), the successive parents must have been (7, 12), (7, 5), and (2, 5); so (2, 5) is a starting point of (19, 12).

    Algorithm

    Repeatedly subtract the smaller of {tx, ty} from the larger of {tx, ty}. The answer is true if and only if we eventually reach sx, sy.

    Complexity Analysis

    Time Complexity: O(\max(tx, ty))O(max(tx,ty)). If say ty = 1, we could be subtracting tx times.

    Space Complexity: O(1)O(1).
    """
    def doit_backward_tle(self, sx, sy, tx, ty):
        while tx >= sx and ty >= sy:
            if sx == tx and sy == ty: return True
            if tx > ty:
                tx -= ty
            else:
                ty -= tx
        return False

    """
    Approach #4: Work Backwards (Modulo Variant) [Accepted]
    Intuition

    As in Approach #3, we work backwards to find the answer, trying to transform the target point to the starting point
    via applying the parent operation (x, y) -> (x-y, y) or (x, y-x) [depending on which one doesn't have negative coordinates.]

    We can speed up this transformation by bundling together parent operations.

    Algorithm

    Say tx > ty. We know that the next parent operations will be to subtract ty from tx, until such time that tx = tx % ty.
    When both tx > ty and ty > sy, we can perform all these parent operations in one step,
    replacing while tx > ty: tx -= ty with tx %= ty.

    Otherwise, if say tx > ty and ty <= sy, then we know ty will not be changing (it can only decrease).
    Thus, only tx will change, and it can only change by subtracting by ty.
    Hence, (tx - sx) % ty == 0 is a necessary and sufficient condition for the problem's answer to be True.

    The analysis above was for the case tx > ty, but the case ty > tx is similar. When tx == ty, no more moves can be made.
    Complexity Analysis
    
    Time Complexity: O(log(max(tx,ty))). The analysis is similar to the analysis of the Euclidean algorithm, 
    and we assume that the modulo operation can be done in O(1) time.
    Space Complexity: O(1).
    """
    def doit_backward(self, sx, sy, tx, ty):

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

    """
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
    """
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




    # <BFS>
    def doit_tle(self, sx, sy, tx, ty):
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




if __name__ == "__main__":

    res = ReachingPoints().doit(sx = 1, sy = 1, tx = 3, ty = 5)

    res = ReachingPoints().doit(sx = 1, sy = 1, tx = 2, ty = 2)

    res = ReachingPoints().doit(sx = 1, sy = 1, tx = 1, ty = 1)

    res = ReachingPoints().doit(35, 13, 455955547, 420098884)

    pass

"""
1197. Minimum Knight Moves


n an infinite chess board with coordinates from -infinity to +infinity, you have a knight at square [0, 0].

A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.



Return the minimum number of steps needed to move the knight to the square [x, y].  It is guaranteed the answer exists.

 

Example 1:

Input: x = 2, y = 1
Output: 1
Explanation: [0, 0] → [2, 1]
Example 2:

Input: x = 5, y = 5
Output: 4
Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]
 

Constraints:

|x| + |y| <= 300

"""


class MinKnightMoves:

    """
    1. Firstly, the nature of this problem is symmetric with respect to the coordinates being positive/negative and with the axes themselves (x can be swapped with y). Because of this, I took the absolute value of each coordinate and worked with the maximum and minimum coordinates (all the logic is based around this, it simplifies the problem a bit).
    2. This is a special case that will throw a wrench in the gears of the logic below, this is the only special case of concern.
    3. When cmin is less than half of cmax, the bulk of our moves will be spent getting cmax to zero. Each time we reduce it, we will do so by 2 (which will consequently reduce cmin by 1). Because cmin is less than half of cmax, reducing cmax in this manner will afford us enough moves to reduce cmin to zero as well. The caveat here being (1) when cmax is odd it requires another move and (2) when there is a discrepency between cmin being odd and the number of times we shifted it being even (or vice versa), which also requires another move to correct. (cmax + 1) // 2 gets the number of times it takes to shift cmax down to zero (which accounts for the extra odd move), int((cmax//2 + 2*(cmax % 2)) % 2 != cmin % 2) will be 1 when there is a discrepency between cmin and the number of times it was shifted (see above).
    4. In this case, we want to determine the number of moves it takes to reduce cmax and cmin so that cmin*2 == cmax. If we can reduce both coordinates down in this manner, then we will have exactly cmin moves left to reduce them both to zero. The code is weird, but it is less weird when you realize it is the result of solving the following equation: (cmax - moves)/2 = cmin - 2*moves. Why that equation? Because it's an equality that tells us the number of moves to set cmax == 2*cmin, it's also worth noting that we will be reducing cmin by 2 each time to arrive at cmax == 2*cmin as quickly as possible. If we solve for moves here, we get moves = (2*cmin - cmax)/3. Of course, we need to use integer division, and if there is a remainder there will be another move required. So in the end we get the result of moves + cmin + int(bool(rem)), moves represents the number of moves it took to get cmax == 2*cmin, cmin was reduced down appropriately based on our initial moves (but should be reduced by 1 more if the previous remainder was 2, see below), and int(bool(rem)) is another way of converting a positive integer to 1 (or 0 if it started at 0).
    I tried to explain it all, there is a bit here. This is actually a kinda cool problem, though if I'm being honest, I can't say exactly why (2*cmin - cmax) % 3 == 2 requires cmin to be reduced an additional time. It was just the result of failing specific test cases, noticing a pattern, then developing some logic to avoid that case. Any ideas?
    """    
    def doit_math_1(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        # (1) The nature of this problem is symmetric.
        x, y = -x if x < 0 else x, -y if y < 0 else y
        cmax, cmin = max(x, y), min(x, y)
        # (2) Special case that falls outside of the constant time solution.
        if (cmax, cmin) == (1, 0): return 3
        # (3) cmin is less than half of cmax: see post.
        if 2*cmin < cmax: 
            return (cmax + 1) // 2 + int((cmax//2 + 2*(cmax % 2)) % 2 != cmin % 2)
        # (4) cmin is in [cmax//2, cmax]: see post.
        moves, rem = ((2*cmin - cmax)//3), (2*cmin - cmax) % 3
        cmin -= 2*moves + (1 if rem == 2 else 0)
        return moves + cmin + int(bool(rem))

    def doit_math(self, x: int, y: int) -> int:
        x, y = abs(x), abs(y)
        if x < y:
            x, y = y, x

        if x == 1 and y == 0:
            return 3
        
        if x == 2 and y == 2:
            return 4
        
        delta = x - y
        if y > delta:
            return delta - 2 * int((delta - y) // 3)
        
        return delta - 2 * int((delta - y) // 4)
    
    def doit_bfs(self, tx: int, ty: int) -> int:

        from collections import deque

        qu = deque([(0, 0, 0)])
        visited = set([0, 0])

        def neighbours(x, y):
            return [(x+2, y+1), (x+2, y-1), (x+1, y-2), (x+1, y+2), (x-2, y+1), (x-2, y-1), (x-1, y+2), (x-1, y-2)]

        while qu:

            x, y, s = qu.popleft()

            if x == tx and y == ty:
                return s

            for x1, y1 in neighbours(x, y):
                
                if abs(x1-tx) > abs(tx)+2 or abs(y1-ty) > abs(ty)+2:
                    continue
                
                if (x1, y1) not in visited:
                    qu.append((x1, y1, s+1))
                    visited.add((x1, y1))

        return -1


if __name__ == '__main__':

    MinKnightMoves().doit_math_1(4, 1)
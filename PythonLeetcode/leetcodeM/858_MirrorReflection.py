# 858. Mirror Reflection

# There is a special square room with mirrors on each of the four walls.
# Except for the southwest corner, there are receptors on each of the remaining corners, numbered 0, 1, and 2.

# The square room has walls of length p, and a laser ray from the southwest corner first meets the east wall at a distance q from the 0th receptor.

# Return the number of the receptor that the ray meets first.  (It is guaranteed that the ray will meet a receptor eventually.)


# Example 1:

# Input: p = 2, q = 1
# Output: 2
# Explanation: The ray meets receptor 2 the first time it gets reflected back to the left wall.

# Note:

# 1 <= p <= 1000
# 0 <= q <= p

class MirrorReflection:

    """
    Approach 1: Simulation
    Intuition

    The initial ray can be described as going from an origin (x, y) = (0, 0) in the direction (rx, ry) = (p, q).
    From this, we can figure out which wall it will meet and where, and what the appropriate new ray will be (based on reflection.)
    We keep simulating the ray until it finds it's destination.

    Algorithm
    The parameterized position of the laser after time t will be (x + rx * t, y + ry * t).
    From there, we know when it will meet the east wall (if x + rx * t == p), and so on.
    For a positive (and nonnegligible) time t, it meets the next wall.

    We can then calculate how the ray reflects. If it hits an east or west wall, then rx *= -1, else ry *= -1.
    In Java, care must be taken with floating point operations.

    Complexity Analysis

    Time Complexity: O(p). We can prove (using Approach #2) that the number of bounces is bounded by this.
    Space Complexity: O(1).
    """

    def doit_(self, p, q):
        from fractions import Fraction as F
        x = y = 0
        rx, ry = p, q
        targets = [(p, 0), (p, p), (0, p)]

        while (x, y) not in targets:
            # Want smallest t so that some x + rx, y + ry is 0 or p
            # x + rxt = 0, then t = -x/rx etc.
            t = float('inf')
            for v in [F(-x, rx), F(-y, ry), F(p-x, rx), F(p-y, ry)]:
                if v > 0:
                    t = min(t, v)

            x += rx * t
            y += ry * t

            # update rx, ry
            if x == p or x == 0:  # bounced from east/west wall, so reflect on y axis
                rx *= -1
            if y == p or y == 0:
                ry *= -1

        return 1 if x == y == p else 0 if x == p else 2

    """
    Approach 2: Mathematical
    Intuition and Algorithm

    Instead of modelling the ray as a bouncing line, model it as a straight line through reflections of the room.

    For example, if p = 2, q = 1, then we can reflect the room horizontally, and draw a straight line from (0, 0) to (4, 2).
    The ray meets the receptor 2, which was reflected from (0, 2) to (4, 2).

    In general, the ray goes to the first integer point (kp, kq) where k is an integer, and kp and kq are multiples of p.
    Thus, the goal is just to find the smallest k for which kq is a multiple of p.

    The mathematical answer is k = p / gcd(p, q).

    Complexity Analysis

    Time Complexity: O(logP), the complexity of the gcd operation.

    Space Complexity: O(1).

    """
    def doit(self, p, q):
        from fractions import gcd
        g = gcd(p, q)
        p = (p / g) % 2
        q = (q / g) % 2

        return 1 if p and q else 0 if p else 2


if __name__ == '__main__':

    res = MirrorReflection().doit_(p=2, q=1)  # 2

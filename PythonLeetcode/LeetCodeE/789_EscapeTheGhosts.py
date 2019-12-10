# 789. Escape The Ghosts

# You are playing a simplified Pacman game. You start at the point (0, 0), and your destination is (target[0], target[1]).
# There are several ghosts on the map, the i-th ghost starts at (ghosts[i][0], ghosts[i][1]).

# Each turn, you and all ghosts simultaneously *may* move in one of 4 cardinal directions: north, east, west, or south,
# going from the previous point to a new point 1 unit of distance away.

# You escape if and only if you can reach the target before any ghost reaches you (for any given moves the ghosts may take.)
# If you reach any square (including the target) at the same time as a ghost, it doesn't count as an escape.

# Return True if and only if it is possible to escape.

# Example 1:
# Input:
# ghosts = [[1, 0], [0, 3]]
# target = [0, 1]
# Output: true
# Explanation:
# You can directly reach the destination (0, 1) at time 1, while the ghosts located at (1, 0) or (0, 3) have no way to catch up with you.

# Example 2:
# Input:
# ghosts = [[1, 0]]
# target = [2, 0]
# Output: false
# Explanation:
# You need to reach the destination (2, 0), but the ghost at (1, 0) lies between you and the destination.
#
# Example 3:
# Input:
# ghosts = [[2, 0]]
# target = [1, 0]
# Output: false
# Explanation:
# The ghost can reach the target at the same time as you.
# Note:

# All points have coordinates with absolute value <= 10000.
# The number of ghosts will not exceed 100.


class EscapeGhosts:

    # if Ghost reach to the target first, Escape will be failed.


    def doit1(self, ghostsPos, target):
        # BFS will bring unknown and impossible move.
        escaper = set([(0, 0)])
        ghosts = set()
        for c in ghostsPos:
            ghosts.add((c[0], c[1]))
        direct = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        target = (target[0], target[1])

        while True:

            catchednode = set()
            for c in escaper:

                if c == target:
                    return target not in ghosts

                if c in ghosts:
                    catchednode.add(c)

            for c in catchednode:
                escaper.remove(c)

            if len(escaper) == 0:
                return False

            nextescaper = set()
            for c in escaper:
                for d in direct:
                    nextescaper.add((c[0] + d[0], c[1] + d[1]))

            nextghost = set()
            for c in ghosts:
                for d in direct:
                    nextghost.add((c[0] + d[0], c[1] + d[1]))
                nextghost.add(c)

            if target in nextescaper:
                return False

            ghosts = nextghost
            escaper = nextescaper


    def doit(self, ghosts, target):
        # A player can reach the target if and only if his Manhattan distance to the target is below any Manhattan distances between a ghost and the target.

        escaper_distance = abs(0 - target[0]) + abs(0 - target[1])

        for c in ghosts:
            if abs(c[0] - target[0]) + abs(c[1] - target[1]) <= escaper_distance:
                return False

        return True


if __name__ == "__main__":

    res = EscapeGhosts().doit([[1, 0], [0, 3]], [0, 1])

    res = EscapeGhosts().doit([[1, 0]], [2, 0])

    res = EscapeGhosts().doit([[2, 0]], [1, 0])
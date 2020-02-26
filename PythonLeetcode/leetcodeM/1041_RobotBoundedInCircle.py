# 1041. Robot Bounded In Circle

# On an infinite plane, a robot initially stands at (0, 0) and faces north.
# The robot can receive one of three instructions:

# "G": go straight 1 unit;
# "L": turn 90 degrees to the left;
# "R": turn 90 degress to the right.
# The robot performs the instructions given in order, and repeats them forever.

# Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.


# Example 1:

# Input: "GGLLGG"
# Output: true
# Explanation:
# The robot moves from (0,0) to (0,2), turns 180 degrees, and then returns to (0,0).
# When repeating these instructions, the robot remains in the circle of radius 2 centered at the origin.

# Example 2:

# Input: "GG"
# Output: false
# Explanation:
# The robot moves north indefinitely.

# Example 3:

# Input: "GL"
# Output: true
# Explanation:
# The robot moves from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ...

# Note:

# 1 <= instructions.length <= 100
# instructions[i] is in {'G', 'L', 'R'}

class IsRobotBounded:

    def doit(self, instructions):

        def delta():
            s = [0, 0]
            direct = 0

            for c in instructions:
                steps = [(0, 1), (1, 0), (0, -1), (-1, 0)]
                if c == 'G':
                    s[0] += steps[direct][0]
                    s[1] += steps[direct][1]
                else:
                    direct += -1 if c == 'L' else 1
                    if direct > 3:
                        direct -= 4
                    elif direct < -3:
                        direct += 4

            return (s[0], s[1], (0 - direct) % 4)

        delta_change = delta()
        s, ang = [delta_change[0], delta_change[1]], delta_change[2]
        steps = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        while s == [0, 0] or ang != 0:
            s[0] += steps[ang][0]
            s[1] += steps[ang][1]
            ang += ang
            if ang > 3:
                ang -= 4
            elif ang < -3:
                ang

        return s == [0, 0]

    def doit(self, instructions):
        import collections
        # short cuts based on simple counts
        c = collections.Counter(instructions)

        if (c['L'] - c['R']) % 4:
            return True  # not facing north -> goes back and forth or in square

        if c['G'] % 2:
            return False  # still facing north and cannot be back to origin

        # follow actual path
        pos = [0, 0]
        face = 0  # 0: north, 1: east, 2: south, 3: west

        for i in instructions:
            if i == 'G':  # marching changes position based on current face direction
                pos[face % 2] += (1, -1)[face > 1]
            else:  # turning changes face direction
                face = (face + (1, 3)[i == 'L']) % 4

        return pos == [0, 0]


if __name__ == '__main__':

    res = IsRobotBounded().doit("GL")

    res = IsRobotBounded().doit("GGLLGG")

    res = IsRobotBounded().doit("GG")

    pass

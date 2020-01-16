# 874. Walking Robot Simulation

# A robot on an infinite grid starts at point (0, 0) and faces north.
# The robot can receive one of three possible types of commands:

# -2: turn left 90 degrees
# -1: turn right 90 degrees
# 1 <= x <= 9: move forward x units
# Some of the grid squares are obstacles.

# The i-th obstacle is at grid point (obstacles[i][0], obstacles[i][1])

# If the robot would try to move onto them, the robot stays on the previous grid square instead (but still continues following the rest of the route.)

# Return the square of the maximum Euclidean distance that the robot will be from the origin.


# Example 1:

# Input: commands = [4,-1,3], obstacles = []
# Output: 25
# Explanation: robot will go to (3, 4)

# Example 2:

# Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
# Output: 65
# Explanation: robot will be stuck at (1, 4) before turning left and going to (1, 8)


# Note:

# 0 <= commands.length <= 10000
# 0 <= obstacles.length <= 10000
# -30000 <= obstacle[i][0] <= 30000
# -30000 <= obstacle[i][1] <= 30000
# The answer is guaranteed to be less than 2 ^ 31.

class RobotSimution:

    def doit(self, commands, obstacles):
        X, Y = {}, {}
        for x, y in obstacles:
            if x in X:
                bisect.insort(X[x], y)

            else:
                X[x] = [y]

            if y in Y:
                bisect.insort(Y[y], x)

            else:
                Y[y] = [x]

        d, x, y, mx = 0, 0, 0, 0
        for z in commands:
            if z == -2:
                d = 3 if d == 0 else d - 1

            elif z == -1:
                d = 0 if d == 3 else d + 1

            else:
                if d == 0:
                    if x not in X or X[x][-1] <= y:
                        y += z

                    else:
                        i = bisect.bisect(X[x], y)
                        y = y + z if X[x][i] > y + z else X[x][i] - 1

                elif d == 1:
                    if y not in Y or Y[y][-1] <= x:
                        x += z

                    else:
                        i = bisect.bisect(Y[y], x)
                        x = x + z if Y[y][i] > x + z else Y[y][i] - 1

                elif d == 2:
                    if x not in X or X[x][0] >= y:
                        y -= z

                    else:
                        i = bisect.bisect(X[x], y) - 1
                        y = y - z if X[x][i] < y - z else X[x][i] + 1

                else:
                    if y not in Y or Y[y][0] >= x:
                        x -= z

                    else:
                        i = bisect.bisect(Y[y], x) - 1
                        x = x - z if Y[y][i] < x - z else Y[y][i] + 1

                mx = max(mx, x ** 2 + y ** 2)

        return mx

    def doit(self, commands, obstacles):
        x, y, cur, ans = 0, 0, 0, 0
        d = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        obs = set(map(tuple, obstacles))

        for c in commands:
            if c == -1:
                cur = (cur + 1) % 4
            elif c == -2:
                cur = (cur - 1) % 4
            else:
                for _ in range(c):
                    if (x + d[cur][0], y + d[cur][1]) in obs:
                        break
                    x += d[cur][0]
                    y += d[cur][1]
                    ans = max(ans, x * x + y * y)

        return ans

    """
    Approach 1: Simulation
    Intuition

    We simulate the path of the robot step by step. Since there are at most 90000 steps, this is efficient enough to pass the given input limits.

    Algorithm

    We store the robot's position and direction. If we get a turning command, we update the direction; otherwise we walk the specified number of steps in the given direction.

    Care must be made to use a Set data structure for the obstacles, so that we can check efficiently if our next step is obstructed. If we don't, our check is point in obstacles could be ~10,000 times slower.

    In some languages, we need to encode the coordinates of each obstacle as a long integer so that it is a hashable key that we can put into a Set data structure. Alternatively, we could also encode the coordinates as a string.
    """

    def doit1(self, commands, obstacles):
        dx = [0, 1, 0, -1]
        dy = [1, 0, -1, 0]
        x = y = di = 0
        obstacleSet = set(map(tuple, obstacles))
        ans = 0

        for cmd in commands:
            if cmd == -2:  # left
                di = (di - 1) % 4
            elif cmd == -1:  # right
                di = (di + 1) % 4
            else:
                for k in range(cmd):
                    if (x+dx[di], y+dy[di]) not in obstacleSet:
                        x += dx[di]
                        y += dy[di]
                        ans = max(ans, x*x + y*y)

        return ans


if __name__ == '__main__':

    res = RobotSimution().doit(commands=[4, -1, 3], obstacles=[])

    res = RobotSimution().doit(
        commands=[4, -1, 4, -2, 4], obstacles=[[2, 4]])  # 65

    pass

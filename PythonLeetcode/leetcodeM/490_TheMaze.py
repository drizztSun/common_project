"""
490. The Maze

There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The ball can go through the empty spaces by rolling up, down, left or right,
but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the maze, the ball's start position and the destination, where start = [startrow, startcol] and destination = [destinationrow, destinationcol],
return true if the ball can stop at the destination, otherwise return false.

You may assume that the borders of the maze are all walls (see examples).



Example 1:


Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [4,4]
Output: true
Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.
Example 2:


Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [3,2]
Output: false
Explanation: There is no way for the ball to stop at the destination. Notice that you can pass through the destination but you cannot stop there.
Example 3:

Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], start = [4,3], destination = [0,1]
Output: false


Constraints:

1 <= maze.length, maze[i].length <= 100
maze[i][j] is 0 or 1.
start.length == 2
destination.length == 2
0 <= startrow, destinationrow <= maze.length
0 <= startcol, destinationcol <= maze[i].length
Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
The maze contains at least 2 empty spaces.


"""


class MazehasPath:

    def doit(self, maze, start, destination):

        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        visited = set()

        def dfs(s):

            if s in visited:
                return False

            if s[0] == destination[0] and s[1] == destination[1]:
                return True

            visited.add(s)

            for deltax, deltay in directions:

                x1, y1 = s[0] + deltax, s[1] + deltay
                while 0 <= x1 < len(maze) and 0 <= y1 < len(maze[0]) and maze[x1][y1] == 0:
                    x1 += deltax
                    y1 += deltay

                x1 -= deltax
                y1 -= deltay

                if dfs((x1, y1)):
                    return True

            return False

        return dfs((start[0], start[1]))


    def doit_bfs(self, maze, start, destination):

        from collections import deque
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        bfsque = deque([(start[0], start[1])])
        visited = set([(start[0], start[1])])

        while bfsque:

            x, y = bfsque.popleft()
            if x == destination[0] and y == destination[0]:
                return True

            for delx, dely in directions:

                x1, y1 = x + delx, y + dely
                while 0 <= x1 < len(maze) and 0 <= y1 < len(maze[0]) and maze[x1][y1] == 0:
                    x1 += delx
                    y1 += dely

                x1 -= delx
                y1 -= dely
                if (x1, y1) in visited:
                    continue
                bfsque.appendleft((x1, y1))
                visited.add((x1, y1))

        return False















if __name__ == '__main__':

    MazehasPath().doit_bfs(maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [4,4])

    MazehasPath().doit(maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [3,2])

    MazehasPath().doit(maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], start = [4,3], destination = [0,1])

# 773. Sliding Puzzle


# On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.

# A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

# The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

# Given a puzzle board, return the least number of moves required so that the state of the board is solved. 
# If it is impossible for the state of the board to be solved, return -1.

# Examples:

# Input: board = [[1,2,3],[4,0,5]]
# Output: 1
# Explanation: Swap the 0 and the 5 in one move.

# Input: board = [[1,2,3],[5,4,0]]
# Output: -1
# Explanation: No number of moves will make the board solved.

# Input: board = [[4,1,2],[5,0,3]]
# Output: 5
# Explanation: 5 is the smallest number of moves that solves the board.

# An example path:

# After move 0: [[4,1,2],[5,0,3]]
# After move 1: [[4,1,2],[0,5,3]]
# After move 2: [[0,1,2],[4,5,3]]
# After move 3: [[1,0,2],[4,5,3]]
# After move 4: [[1,2,0],[4,5,3]]
# After move 5: [[1,2,3],[4,5,0]]

# Input: board = [[3,2,4],[1,5,0]]
# Output: 14
# Note:

# board will be a 2 x 3 array as described above.
# board[i][j] will be a permutation of [0, 1, 2, 3, 4, 5].


class SlidingPuzzle:

    # <DFS>
    def doit1(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        def getCord(n):
            for i in range(2):
                for j in range(3):
                    if board[i][j] == n:
                        return i, j

        def isvalid():
            return board == [[1, 2, 3], [4, 5, 0]]

        def search(s, x, y):
            
            if isvalid():
                self.step = min(step, s)
                return

            if s > min(step, 18):
                return

            for c in direct:
                x1, y1 = x + c[0], y + c[1]
                if x1 in (0, 1) and y1 in (0, 1, 2):
                    board[x1][y1], board[x][y] = board[x][y], board[x1][y1] 
                    search(s+1, x1, y1)
                    board[x][y], board[x1][y1] = board[x1][y1], board[x][y] 

        direct = [(0, -1), (0, 1), (1, 0), (-1, 0)]
        x, y = getCord(0)
        self.step = float('inf')

        search(0, x, y)

        return step if step < 20 else -1

    # <BFS>
    def doit1(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        goal = '123450'
        cur = ''.join(map(str, board[0])) + ''.join(map(str, board[1]))
        stack = [(cur, 0, [])] # or deque
        visited = set()

        while stack:
            cur, step, past = stack.pop(0)
            # 0 is the most import, it means it is BFS not DFS
            if cur == goal:
                print(past)
                return step

            visited.add(cur)
            index = cur.index('0')
            x, y = int(index/3), index % 3

            for c in [(0, -1), (0, 1), (1, 0), (-1, 0)]:
                xx, yy = x + c[0], y + c[1]

                if xx in (0, 1) and yy in (0, 1, 2):
                    n = xx * 3 + yy
                    next = ''.join([cur[index] if i == n else cur[n] if i == index else cur[i] for i in range(len(cur))])
                    if next not in visited:
                        stack.append((next, step+1, past+[cur]))

        return -1


# <BFS>
class Solution:
    def doit(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        goal = "123450"
        cur = "".join(map(str, board[0])) + "".join(map(str, board[1]))
        visited = set()
        stack = []
        stack.append((cur, 0, []))

        while stack:
            cur, cnt, past = stack.pop(0)
            if cur == goal:
                return cnt

            visited.add(cur)
            loc = cur.index('0')
            r, c = int(loc / 3), loc % 3

            for x, y in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
                rr, cc = r + x, c + y
                if 0 <= rr < 2 and 0 <= cc < 3:
                    idxx = rr * 3 + cc
                    next = "".join(cur[loc] if i == idxx else cur[idxx] if i == loc else cur[i] for i in range(6))

                    if next not in visited:
                        stack.append((next, cnt + 1, past + [cur]))

        return -1


if __name__ == "__main__":

    res = SlidingPuzzle().doit([[1,2,3], [4,0,5]])

    res = SlidingPuzzle().doit([[1,2,3], [5,4,0]])

    res = SlidingPuzzle().doit([[4,1,2], [5,0,3]])

    res = SlidingPuzzle().doit([[3,2,4],[1,5,0]])

    pass
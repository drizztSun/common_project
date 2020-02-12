# 999. Available Captures for Rook

# On an 8 x 8 chessboard, there is one white rook.  There also may be empty squares, white bishops, and black pawns.
# These are given as characters 'R', '.', 'B', and 'p' respectively. Uppercase characters represent white pieces,
# and lowercase characters represent black pieces.

# The rook moves as in the rules of Chess: it chooses one of four cardinal directions (north, east, west, and south),
# then moves in that direction until it chooses to stop, reaches the edge of the board,
# or captures an opposite colored pawn by moving to the same square it occupies.
# Also, rooks cannot move into the same square as other friendly bishops.

# Return the number of pawns the rook can capture in one move.


class NumRookCaptures:

    def doit(self, board):

        x, y = -1, -1
        for i in range(len(board)):
            for j in range(len(board[0])):
                if board[i][j] == 'R':
                    x, y = i, j
                    break

        if x == -1 or y == -1:
            return 0

        ans = 0
        for z in range(y+1, 8):
            if board[x][z] != '.':
                ans += 1 if board[x][z] == 'p' else 0
                break

        for z in range(y-1, -1, -1):
            if board[x][z] != '.':
                ans += 1 if board[x][z] == 'p' else 0
                break

        for z in range(x+1, 8):
            if board[z][y] != '.':
                ans += 1 if board[z][y] == 'p' else 0
                break

        for z in range(x-1, -1, -1):
            if board[z][y] != '.':
                ans += 1 if board[z][y] == 'p' else 0
                break

        return ans


if __name__ == '__main__':

    res = NumRookCaptures().doit([[".", ".", ".", ".", ".", ".", ".", "."],
                                  [".", ".", ".", "p", ".", ".", ".", "."],
                                  [".", ".", ".", "R", ".", ".", ".", "p"],
                                  [".", ".", ".", ".", ".", ".", ".", "."],
                                  [".", ".", ".", ".", ".", ".", ".", "."],
                                  [".", ".", ".", "p", ".", ".", ".", "."],
                                  [".", ".", ".", ".", ".", ".", ".", "."],
                                  [".", ".", ".", ".", ".", ".", ".", "."]])

    res = NumRookCaptures().doit([[".", ".", ".", ".", ".", ".", ".", "."],
                                  [".", "p", "p", "p", "p", "p", ".", "."],
                                  [".", "p", "p", "B", "p", "p", ".", "."],
                                  [".", "p", "B", "R", "B", "p", ".", "."],
                                  [".", "p", "p", "B", "p", "p", ".", "."],
                                  [".", "p", "p", "p", "p", "p", ".", "."],
                                  [".", ".", ".", ".", ".", ".", ".", "."],
                                  [".", ".", ".", ".", ".", ".", ".", "."]])

    res = NumRookCaptures().doit([[".", ".", ".", ".", ".", ".", ".", "."],
                                  [".", ".", ".", "p", ".", ".", ".", "."],
                                  [".", ".", ".", "p", ".", ".", ".", "."],
                                  ["p", "p", ".", "R", ".", "p", "B", "."],
                                  [".", ".", ".", ".", ".", ".", ".", "."],
                                  [".", ".", ".", "B", ".", ".", ".", "."],
                                  [".", ".", ".", "p", ".", ".", ".", "."],
                                  [".", ".", ".", ".", ".", ".", ".", "."]])

    pass

# 794. Valid Tic-Tac-Toe State

# A Tic-Tac-Toe board is given as a string array board. Return True if and only if
# it is possible to reach this board position during the course of a valid tic-tac-toe game.

# The board is a 3 x 3 array, and consists of characters " ", "X", and "O".  The " " character represents an empty square.

# Here are the rules of Tic-Tac-Toe:

# Players take turns placing characters into empty squares (" ").
# The first player always places "X" characters, while the second player always places "O" characters.
# "X" and "O" characters are always placed into empty squares, never filled ones.
# The game ends when there are 3 of the same (non-empty) character filling any row, column, or diagonal.
# The game also ends if all squares are non-empty.
# No more moves can be played if the game is over.

# Example 1:
# Input: board = ["O  ", "   ", "   "]
# Output: false
# Explanation: The first player always plays "X".

# Example 2:
# Input: board = ["XOX", " X ", "   "]
# Output: false
# Explanation: Players take turns making moves.

# Example 3:
# Input: board = ["XXX", "   ", "OOO"]
# Output: false

# Example 4:
# Input: board = ["XOX", "O O", "XOX"]
# Output: true


class ValidTicTacToe:

    def doit(self, board):
        """
        :type board: List[str]
        :rtype: bool
        """
        x_o_cnt = 0
        for i in range(len(board)):
            for j in range(3):
                if board[i][j] == ' ':
                    continue
                x_o_cnt += 1 if board[i][j] == 'X' else -1

        if x_o_cnt not in (0, 1):
            return False

        lines = [board[0], board[1], board[2]]
        lines.append(''.join([board[i][i] for i in range(3)]))
        lines.append(''.join([board[i][2-i] for i in range(3)]))
        lines.extend([''.join([board[j][i] for j in range(3)])
                      for i in range(3)])

        x_done = False
        o_done = False
        for c in lines:
            if c == 'XXX':
                x_done = True

            if c == 'OOO':
                o_done = True

        if x_done:
            return x_o_cnt == 1 and not o_done

        if o_done:
            return x_o_cnt == 0 and not x_done

        return True

    def doit(self, board):
        X, Y = "XO"
        size = 3

        x_count = sum(r.count('X') for r in board)
        o_count = sum(r.count('O') for r in board)

        def winner(char):
            for i in range(size):
                if all(board[i][j] == char for j in range(3)):
                    return True
                if all(board[j][i] == char for j in range(3)):
                    return True

            if all(board[i][i] == char for i in range(3)):
                return True
            if all(board[i][size - i - 1] == char for i in range(3)):
                return True

            return False

        if o_count not in {x_count, x_count - 1}:
            return False

        if winner("X") and x_count != o_count + 1:
            return False
        if winner("O") and o_count != x_count:
            return False

        return True


if __name__ == '__main__':

    res = ValidTicTacToe().doit(["O  ", "   ", "   "])

    res = ValidTicTacToe().doit(["XOX", " X ", "   "])

    res = ValidTicTacToe().doit(["XXX", "   ", "OOO"])

    res = ValidTicTacToe().doit(["XOX", "O O", "XOX"])

    res = ValidTicTacToe().doit(["XXX", "OOX", "OOX"])

    pass

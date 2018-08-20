

# 782. Transform to Chessboard

# An N x N board contains only 0s and 1s. In each move, you can swap any 2 rows with each other,
# or any 2 columns with each other.

# What is the minimum number of moves to transform the board into a "chessboard" - a board
# where no 0s and no 1s are 4-directionally adjacent? If the task is impossible, return -1.

# Examples:
# Input: board = [[0,1,1,0],
#                 [0,1,1,0],
#                 [1,0,0,1],
#                 [1,0,0,1]]
# Output: 2
# Explanation:
# One potential sequence of moves is shown below, from left to right:

# 0110     1010     1010
# 0110 --> 1010 --> 0101
# 1001     0101     1010
# 1001     0101     0101

# The first move swaps the first and second column.
# The second move swaps the second and third row.


# Input: board = [[0, 1], [1, 0]]
# Output: 0
# Explanation:
# Also note that the board with 0 in the top left corner,
# 01
# 10

# is also a valid chessboard.

# Input: board = [[1, 0], [1, 0]]
# Output: -1
# Explanation:
# No matter what sequence of moves you make, you cannot end with a valid chessboard.
# Note:

# board will have the same number of rows and columns, a number in the range [2, 30].
# board[i][j] will be only 0s or 1s.


class MovesToChessboard:

    # Two conditions to help solve this problem:

    # In a valid chess board, there are 2 and only 2 kinds of rows and one is inverse to the other.
    # For example if there is a row 01010011 in the board, any other row must be either 01010011 or 10101100.

    # The same for columns

    # A corollary is that, any rectangle inside the board with corners top left, top right, bottom left,
    # bottom right must be 4 zeros or 2 ones 2 zeros or 4 zeros.

    # Another important property is that every row and column has half ones. Assume the board is N * N:
    # If N = 2*K, every row and every column has K ones and K zeros.
    # If N = 2*K + 1, every row and every column has K ones and K + 1 zeros or K + 1 ones and K zeros.

    # Since the swap process does not break this property, for a given board to be valid, this property must hold.
    # These two conditions are necessary and sufficient condition for a valid chessboard.

    # Once we know it is a valid cheese board, we start to count swaps.
    # Basic on the property above, when we arrange the first row, we are actually moving all columns.

    # I try to arrange one row into 01010 and 10101 and I count the number of swaps.

    # In case of N even, I take the minimum swaps, because both are possible.
    # In case of N odd, I take the even swaps.
    # Because when we make a swap, we move 2 columns or 2 rows at the same time.
    # So col swaps and row swaps should be even here.

    def doit(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        N = len(board)
        if any(board[0][0] ^ board[i][0] ^ board[0][j] ^ board[i][j] for i in range(N) for j in range(N)):
            return -1

        if not N // 2 <= sum(board[0]) <= (N + 1) // 2:
            return -1

        if not N // 2 <= sum(board[i][0] for i in range(N)) <= (N + 1) // 2:
            return -1

        col = sum(board[0][i] == i % 2 for i in range(N))
        row = sum(board[i][0] == i % 2 for i in range(N))

        if N % 2:
            
            if col % 2:
                col = [col, N-col][col % 2]
            
            if row % 2:
                row = N - row
        else:
            
            col = min(N - col, col)
            row = min(N - row, row)

        return (col + row) // 2


    def doit1(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        N = len(board)
        
        if any(board[0][0] ^ board[0][i] ^ board[j][0] ^ board[j][i] for i in range(N) for j in range(N)):
            return -1
        
        if not N // 2 <= sum(board[0]) <= (N + 1) // 2:
            return -1
        
        if not N // 2 <= sum(board[0][i] for i in range(N)) <= (N + 1) // 2:
            return -1
        
        col = sum(board[0][i] == i % 2 for i in range(N))
        row = sum(board[i][0] == i % 2 for i in range(N))
        

        if N % 2:
            if col % 2:
                col = N - col
            if row % 2:
                row = N - row
        else:
            col = min(col, N - col)
            row = min(row, N - row)
        
        return (col + row) // 2


if __name__ == "__main__":

    res = MovesToChessboard().doit([[0,1,1,0],
                                    [0,1,1,0],
                                    [1,0,0,1],
                                    [1,0,0,1]]) # 2

    res = MovesToChessboard().doit([[0, 1], 
                                    [1, 0]]) # 0
        
    res = MovesToChessboard().doit([[1, 0], 
                                    [1, 0]]) # -1

    res = MovesToChessboard().doit([[1,1,0],
                                    [0,0,1],
                                    [0,0,1]]) # 2

    pass
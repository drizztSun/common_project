# 529. Minesweeper

# Let's play the minesweeper game (Wikipedia, online game)!

# You are given a 2D char matrix representing the game board. 'M' represents an unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally 'X' represents a revealed mine.

# Now given the next click position (row and column indices) among all the unrevealed squares ('M' or 'E'), return the board after revealing this position according to the following rules:

# If a mine ('M') is revealed, then the game is over - change it to 'X'.
# If an empty square ('E') with no adjacent mines is revealed, then change it to revealed blank ('B') and all of its adjacent unrevealed squares should be revealed recursively.
# If an empty square ('E') with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
# Return the board when no more squares will be revealed.

# Example 1:

# Input: 

# [['E', 'E', 'E', 'E', 'E'],
#  ['E', 'E', 'M', 'E', 'E'],
#  ['E', 'E', 'E', 'E', 'E'],
#  ['E', 'E', 'E', 'E', 'E']]

# Click : [3,0]

# Output: 

# [['B', '1', 'E', '1', 'B'],
#  ['B', '1', 'M', '1', 'B'],
#  ['B', '1', '1', '1', 'B'],
#  ['B', 'B', 'B', 'B', 'B']]


# Example 2:
# Input: 

# [['B', '1', 'E', '1', 'B'],
#  ['B', '1', 'M', '1', 'B'],
#  ['B', '1', '1', '1', 'B'],
#  ['B', 'B', 'B', 'B', 'B']]

# Click : [1,2]

# Output: 

# [['B', '1', 'E', '1', 'B'],
#  ['B', '1', 'X', '1', 'B'],
#  ['B', '1', '1', '1', 'B'],
#  ['B', 'B', 'B', 'B', 'B']]

# Note:
# The range of the input matrix's height and width is [1,50].
# The click position will only be an unrevealed square ('M' or 'E'), which also means the input board contains at least one clickable square.
# The input board won't be a stage when game is over (some mines have been revealed).
# For simplicity, not mentioned rules should be ignored in this problem. For example, you don't need to reveal all the unrevealed mines when the game is over, consider any cases that you will win the game or flag any squares.


class MinesweeperBoard:

    def doit(self, board, click):
        """
        :type board: List[List[str]]
        :type click: List[int]
        :rtype: List[List[str]]
        """
        m, n = len(board), len(board[0])
        x, y = click

        if board[x][y] == 'M':
            board[x][y] = 'X'
            return board

        buff = [(x, y)]
        
        while buff:

            x, y = buff.pop(0)

            if board[x][y] == 'E':

                count = 0
                directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]

                for c in directions:
                    if 0 <= x + c[0] < m and 0 <= y + c[1] < n and board[x + c[0]][y + c[1]] == 'M':
                        count += 1

                if count > 0:
                    board[x][y] = str(count)
                else:
                    board[x][y] = 'B'
                    for c in directions:
                        if 0 <= x + c[0] < m and 0 <= y + c[1] < n and board[x + c[0]][y + c[1]] == 'E':
                            buff.append((x + c[0], y + c[1]))

        return board



    def doit1(self, board, click):
        """
        :type board: List[List[str]]
        :type click: List[int]
        :rtype: List[List[str]]
        """
        def checkM(board, x,y):
            # x,y = click
            m = 0
            if x>0 and y>0 and (board[x-1][y-1]=='M' or board[x-1][y-1]=='X'):
                m += 1
            if x<len(board)-1 and y<len(board[0])-1 and (board[x+1][y+1]=='M' or board[x+1][y+1]=='X'):
                m += 1
            if x>0 and y<len(board[0])-1 and (board[x-1][y+1]=='M' or board[x-1][y+1]=='X'):
                m += 1
            if y>0 and x<len(board)-1 and (board[x+1][y-1]=='M' or board[x+1][y-1]=='X'):
                m += 1
            if x>0 and (board[x-1][y]=='M' or board[x-1][y]=='X'):
                m += 1
            if x<len(board)-1 and (board[x+1][y]=='M' or board[x+1][y]=='X'):
                m += 1
            if y>0 and (board[x][y-1]=='M' or board[x][y-1]=='X'):
                m += 1
            if y<len(board[0])-1 and (board[x][y+1]=='M' or board[x][y+1]=='X'):
                m += 1

            return m
        
        def helper(board, x,y):
            if not (0<=x<len(board) and 0<=y<len(board[0])):
                return

            if board[x][y]=='M':
                board[x][y] = 'X'
                return

            if board[x][y]=='E':
                m = checkM(board,x,y)
                if m==0:
                    board[x][y] = 'B'
                    helper(board,x-1,y)
                    helper(board,x-1,y-1)
                    helper(board,x-1,y+1)
                    helper(board,x+1,y)
                    helper(board,x+1,y-1)
                    helper(board,x+1,y+1)
                    helper(board,x,y-1)
                    helper(board,x,y+1)
                else:
                    board[x][y] = str(m)

        
        helper(board, click[0], click[1])
        return board
                            
      
if __name__ == "__main__":

    input =  [['E', 'E', 'E', 'E', 'E'],
              ['E', 'E', 'M', 'E', 'E'],
              ['E', 'E', 'E', 'E', 'E'],
              ['E', 'E', 'E', 'E', 'E']]

    res = MinesweeperBoard().doit(input, [3, 0])

    res = 1
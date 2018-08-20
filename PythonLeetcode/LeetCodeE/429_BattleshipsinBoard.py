


# 419. Battleships in a Board

# Given an 2D board, count how many battleships are in it. 
# The battleships are represented with 'X's, empty slots are represented with '.'s. You may assume the following rules:

# You receive a valid board, made of only battleships or empty slots.
# Battleships can only be placed horizontally or vertically.
# In other words, they can only be made of the shape 1xN (1 row, N columns) or Nx1 (N rows, 1 column), where N can be of any size.

#At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
# Example:
# X..X
# ...X
# ...X
# In the above board there are 2 battleships.

# Invalid Example:
# ...X
# XXXX
# ...X
# This is an invalid board that you will not receive - as battleships will always have a cell separating between them.

# Follow up:
# Could you do it in one-pass, using only O(1) extra memory and without modifying the value of the board?

class countBattleships:
    def doit1(self, board):
        """
        :type board: List[List[str]]
        :rtype: int
        """
        # Will not working in "invalid case"
        if not board :
            return 0

        m, n = len(board), len(board[0])
        count = 0
        for i in range(m):
            for j in range(n):

                if board[i][j] == 'X' and (i == 0 or board[i-1][j] == '.') and (j == 0 or board[i][j-1] == '.'):
                    count += 1

        return count


    def doit(self, board):
        """
        :type board: List[List[str]]
        :rtype: int
        """
        if len(board) == 0:
            return 0;
        
        shipCount = 0;
        
        for y, row in enumerate(board):
            for x, cell in enumerate(row):
                if cell == "X" and checkShip(board, x, y):
                    shipCount += 1;
                
        return shipCount;
    
        def checkShip(board, x, y):

            if checkLeft(board, x, y) or checkTop(board, x, y):
                return False;
        
            if  checkRight(board, x, y):
                while  checkThis(board, x, y):
                    if  checkTop(board, x, y) or  checkBottom(board, x, y):
                        return False;
                    x += 1; 

            elif  checkBottom(board, x, y):
                while checkThis(board, x, y):
                    if checkLeft(board, x, y) or checkRight(board, x, y):
                        return False;
                    y += 1;
        
            return True;
        
        def checkLeft(self, board, x, y):
            return x > 0 and board[y][x - 1] == "X";
    
        def checkRight(self, board, x, y):
            return x < len(board[0]) - 1 and board[y][x + 1] == "X";
    
        def checkTop(self, board, x, y):
            return y > 0 and board[y - 1][x] == "X";
    
        def checkBottom(self, board, x, y):
            return y < len(board) - 1 and board[y + 1][x] == "X";
    
        def checkThis(self, board, x, y):
            return x >= 0 and x < len(board[0]) and y >= 0 and y < len(board) and board[y][x] == "X";



if __name__=="__main__":

    a = [
          ['X','.','.', 'X'],
          ['.','.','.', 'X'],
          ['.','.','.', 'X']
        ]

    res = countBattleships().doit(a)
    

    a = [
          ['.','.','.', 'X'],
          ['X','X','X', 'X'],
          ['.','.','.', 'X']
        ]

    res = countBattleships().doit(a)
    pass

        
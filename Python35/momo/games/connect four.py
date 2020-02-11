import numpy as np
import pygame 
RCOUNT = 6
CCOUNT = 7

def Cboard():
    board = np.zeros((6,7))
    return board
def drop(board,row,col,piece):
    board[row][col] = piece
    pass
def valid(board,col):
    return board[5][col] == 0
def gnor(board,col):
    for r in range(RCOUNT):
        if board[r][col] == 0:
            return r
def Pboard(board):
    print(np.flip(board,0))
def winning(board,piece):
    for c in range(CCOUNT-3):
        for r in range (RCOUNT):
            if (board[r][c] ==piece and board[r][c+1] == piece)and (board[r][c+2] == piece and board[r][c+3] == piece):
                return True
    for c in range(CCOUNT):
        for r in range (RCOUNT-3):
            if (board[r][c] ==piece and board[r+1][c] == piece)and (board[r+2][c] == piece and board[r+3][c] == piece):
                return True
    for c in range(CCOUNT-3):
        for r in range (RCOUNT-3):
            if (board[r][c] ==piece and board[r+1][c+1] == piece)and (board[r+2][c+2] == piece and board[r+3][c+3] == piece):
                return True
    for c in range(CCOUNT-3):
        for r in range (3,RCOUNT):
            if (board[r][c] ==piece and board[r-1][c+1] == piece)and (board[r-2][c+2] == piece and board[r-3][c+3] == piece):
                return True
def Dboard(board):
    for c in range(CCOUNT):
        for r in range (RCOUNT):
            pygame.draw.rect(screen,pygame.Color.b,(c*SQARESIZE,r*SQARESIZE,SQARESIZE,SQARESIZE))    
board = Cboard() 
Pboard(board)  
game_over = False
turn = 0
#pygame.init()

SQARESIZE = 500
w = CCOUNT*SQARESIZE
h = RCOUNT+1*SQARESIZE
size = (w,h)
screen = pygame.display.set_mode(size)
while not game_over:
    #p1 inp
    if turn == 0:
        
        col = int(input('PLESE MAKE YOUR CHOICE P1(clonmn 0-6)'))
        if valid(board,col):
            row = gnor(board,col)
            drop(board,row,col,1)
        Pboard(board)
        if winning(board,1):
            print('PLAYER 1 WINS!!!')
            game_over = True
    #p2 inp
    else:
        col = int(input('PLESE MAKE YOUR CHOICE P2(clonmn0-6)'))
        if valid(board,col):
            row = gnor(board,col)
            drop(board,row,col,2)
        Pboard(board) 
        if winning(board,2):
            print('PLAYER 2 WINS!!!')
            game_over = True
            break   
    turn +=1
    turn = turn%2         
piece = board[row][col]   
import os


# 289. Game of Life

# According to the Wikipedia's article: "The Game of Life, also known simply as Life, 
# is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

# Given a board with m by n cells, each cell has an initial state live (1) or dead (0).
# Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

# Any live cell with fewer than two live neighbors dies, as if caused by under-population.
# Any live cell with two or three live neighbors lives on to the next generation.
# Any live cell with more than three live neighbors dies, as if by over-population..
# Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
# Write a function to compute the next state (after one update) of the board given its current state.


class gameOfLife:
    def doit(self, board):
        """
        :type board: List[List[int]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        m, n = len(board), len(board[0])

        def search(A, i, j, m, n):
            sum = 0
            for a in range(i-1, i+2):
                for b in range(j-1, j+2):
                    if 0 <= a < m and 0 <= b < n and A[a][b] == 1:
                        sum += 1 

            return sum - A[i][j]

        next = [[0] * n for _ in range(m)]

        for i in range(m):
            for j in range(n):

                res = search(board, i, j, m, n)
                if res < 2 or res > 3:
                    next[i][j] = 0
                elif res == 3 and board[i][j] == 0:
                    next[i][j] = 1
                elif res in (2, 3):
                    next[i][j] = board[i][j]

        for i in range(m):
            for j in range(n):
                board[i][j] = next[i][j]
                    
                     

    def doit1(self, boards):
        """
        :type board: List[List[int]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        m = len(board)
        if m == 0: 
            return
        n = len(board[0])
        
        mask = 0b01
        neighbours = [(1, 0), (0, 1), (1, 1), (-1, 1), (-1, 0), (0, -1), (-1, -1), (1, -1)]
        
        for i in range(m):
            for j in range(n):
                adj = 0

                for e in neighbours:
                    x, y = e
                    if 0 <= i + x <= m - 1 and 0 <= j + y <= n - 1:
                        adj += board[i + x][j + y] & mask

                if adj == 3 or (board[i][j] == 1 and adj == 2):
                    board[i][j] += 2
    
        
        for i in range(m):
            for j in range(n):
                board[i][j] >>= 1


    def doit2(self, board):
        """
        :type board: List[List[int]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        if not board:
		    return

		m, n = len(board), len(board[0])

		for i in range(m):
			for j in range(n):
				lives = 0
				for inc_i in range(-1, 2, 1):
					for inc_j in range(-1, 2, 1):
						n_i, n_j = i + inc_i, j + inc_j
						if n_i == i and n_j == j:
							continue
						if 0 <= n_i < m and 0 <= n_j < n:
							if board[n_i][n_j] == 1 or board[n_i][n_j] == -1:
								lives += 1
				if board[i][j] == 1:
					if lives < 2 or lives > 3:
						board[i][j] = -1
				else:
					if lives == 3:
						board[i][j] = -2

		for i in range(m):
			for j in range(n):
				if board[i][j] == -1:
					board[i][j] = 0
				elif board[i][j] == -2:
					board[i][j] = 1



if __name__ == "__main__":


    A = [[0, 1]]

    gameOfLife().doit(A)


    pass
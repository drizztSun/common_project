import os



# leetcode 37. Sudoku Solver
# Write a program to solve a Sudoku puzzle by filling the empty cells.
# Empty cells are indicated by the character '.'.
# You may assume that there will be only one unique solution.

class solveSudoku(object):
    def doit(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        def isValid(board, num, row, col):
            #print(row, col)
            
            for i in range(9):

                if board[row][i] != '.' and board[row][i] == num:
                    return False

                if board[i][col] != '.' and board[i][col] == num:
                    return False

                c = board[3 * (row//3) + i//3][3 * (col//3) + i%3]
                if c != '.' and c == num:
                    return False

            return True
            

        m, n = len(board), len(board[0])
        buff = [(x, y) for x in range(m) for y in range(n) if board[x][y] == '.']
        itemV = dict()
        for item in buff:
            itemV[item] = '0'

        # print(len(itemV))
        i = 0
        while i < len(buff):
            
            row, col = buff[i]
            while '0' <= itemV[buff[i]] < '9':

                itemV[buff[i]] = chr(ord(itemV[buff[i]]) + 1)

                if isValid(board, itemV[buff[i]], row, col):
                    board[row][col] = itemV[buff[i]]
                    i += 1
                    if i == len(buff):
                        return
                    row, col = buff[i]

            itemV[buff[i]] = '0'
            board[row][col] = '.'
            i -= 1
            


    def doit1(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        def isValid(board, num, row, col):
            #print(row, col)
            for i in range(9):

                if board[row][i] != '.' and board[row][i] == num:
                    return False

                if board[i][col] != '.' and board[i][col] == num:
                    return False

                c = board[3 * (row//3) + i//3][3 * (col//3) + i%3]
                if c != '.' and c == num:
                    return False

            return True

            
        def search(board):
            m, n = len(board), len(board[0])

            for i in range(m):
                for j in range(n):
                    if board[i][j] == '.':
                        for c in range(1, 10):
                            if isValid(board, str(c), i, j):
                                board[i][j] = str(c)

                                if search(board):
                                    return True

                                board[i][j] = '.'     
                        return False

            return True

        if len(board) == 0 or len(board[0]) == 0:
            return

        search(board)


    def doit2(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        def isValid(board, num, row, col):
            print(row, col)
            for i in range(9):

                if board[row][i] != '.' and board[row][i] == num:
                    return False

                if board[i][col] != '.' and board[i][col] == num:
                    return False

                c = board[3 * (row//3) + i//3][3 * (col//3) + i%3]

                if c != '.' and c == num:
                    return False

            return True

        def search(board, buff, i):
            if i == len(buff):
                return True

            row, col = buff[i]
            if board[row][col] == '.':
                for c in range(1, 10):
                    if isValid(board, str(c), row, col):
                        board[row][col] = str(c)

                        if search(board, buff, i+1):
                            return True

                        board[i][j] = '.'     
            
            return False

        if len(board) == 0 or len(board[0]) == 0:
            return

        m, n = len(board), len(board[0])
        buff = [(x, y) for x in range(m) for y in range(n) if board[x][y] == '.']

        search(board, buff, 0)



    def doitBest(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        def checkIn(x, y, exists):
            if board[x][y] != '.':
                if board[x][y] not in exists:
                    exists.add(board[x][y])
                else:
                    return True
            return False

        def get_zone(x, y):
            return x, y, (y // 3) * 3 + x // 3

        def get_remain(x, y):
            col, row, blk = get_zone(x, y)
            return col_remains[col] & row_remains[row] & blk_remains[blk]
        
        def fill_in(x, y):
            values = get_remain(x, y)
            for value in values:
                board[x][y] = value
                for i, remain in zip(get_zone(x, y), remains):
                    remain[i].remove(value)
                while uncertain:
                    if not fill_in(*uncertain.pop()):
                        for i, remain in zip(get_zone(x, y), remains):
                            remain[i].add(value)
                        break
                    else:
                        return True
                else:
                    return True
            uncertain.append((x, y))
            return False
        
        col_remains = [{} for _ in range(9)]
        row_remains = [{} for _ in range(9)]
        blk_remains = [{} for _ in range(9)]
        all_digits = set(str(i) for i in range(1, 10))
        uncertain = []

        for x in range(9):
            for y in range(9):
                if board[x][y] == '.':
                    uncertain.append((x, y))
                    
        remains = [col_remains, row_remains, blk_remains]

        for remain in remains:
            for index in range(9):
                exist = set()
                for y in range(9):
                    checkIn(index, y, exist)
                col_remains[index] = all_digits - exist
                exist = set()
                for x in range(9):
                    checkIn(x, index, exist)
                row_remains[index] = all_digits - exist
                exist = set()
                x, y = index % 3, index // 3
                for dx in range(3):
                    for dy in range(3):
                        checkIn(3 * x + dx, 3 * y + dy, exist)
                blk_remains[index] = all_digits - exist
        
        fill_in(*uncertain.pop())

            

    # dfs
    def doit5(self, board):

        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        empty_list = []

        def find_available_numbers(y, x):

            def get_range(r):
                if 0 <= r <= 2:
                    return 0
                elif 3 <= r <= 5:
                    return 3
                else:
                    return 6
                
            flag = [True] * 10

            for j in range(0, 9):
                if board[y][j] != '.':
                    flag[int(board[y][j])] = False

            for i in range(0, 9):
                if board[i][x] != '.':
                    flag[int(board[i][x])] = False

            
            block_start_y = get_range(y) 
            block_start_x = get_range(x) 

            for i in range(block_start_y, block_start_y + 3):
                for j in range(block_start_x, block_start_x + 3):
                    if board[i][j] != '.':
                        flag[int(board[i][j])] = False

            numbers = []
            for i in range(1, 10):
                if flag[i]:
                    numbers.append(i)

            return numbers

        for i in range(9):
            for j in range(9):
                if board[i][j] == '.':
                    available_numbers = find_available_numbers(i, j)
                    heapq.heappush(empty_list, (len(available_numbers), [i,j]))


        def dfs():

            if len(empty_list) == 0:
                return True

            empty_space =  heapq.heappop(empty_list)
            empty_space = empty_space[1]

            y = empty_space[0]
            x = empty_space[1]
            available_numbers = find_available_numbers(y, x)

            for number in available_numbers:
                board[y][x] = str(number)
                result = dfs()
                if result:
                    return True
                board[y][x] = '.'

            heapq.heappush(empty_list, (len(available_numbers), [y, x]))
            return False

        dfs()











if __name__=="__main__":


    a = [[".",".","9","7","4","8",".",".","."],
         ["7",".",".",".",".",".",".",".","."],
         [".","2",".","1",".","9",".",".","."],
         [".",".","7",".",".",".","2","4","."],
         [".","6","4",".","1",".","5","9","."],
         [".","9","8",".",".",".","3",".","."],
         [".",".",".","8",".","3",".","2","."],
         [".",".",".",".",".",".",".",".","6"],
         [".",".",".","2","7","5","9",".","."]]

    #solveSudoku().doit1(a)

    solveSudoku().doit(a)

    #[["5","1","9","7","4","8","6","3","2"],
    #["7","8","3","6","5","2","4","1","9"],
    #["4","2","6","1","3","9","8","7","5"],
    #["3","5","7","9","8","6","2","4","1"],
    #["2","6","4","3","1","7","5","9","8"],
    #["1","9","8","5","2","4","3","6","7"],
    #["9","7","5","8","6","3","1","2","4"],
    #["8","3","2","4","9","1","7","5","6"],
    #["6","4","1","2","7","5","9","8","3"]]



    pass
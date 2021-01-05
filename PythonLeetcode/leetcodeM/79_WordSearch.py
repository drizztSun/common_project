"""
79. Word Search

Given an m x n board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where "adjacent" cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

Example 1:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
Example 2:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
Example 3:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
 

Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 200
1 <= word.length <= 103
board and word consists only of lowercase and uppercase English letters.

"""

class WordSearch:

    """
    Approach 1: Backtracking
    Intuition

    This problem is yet another 2D grid traversal problem, which is similar with another problem called 489. Robot Room Cleaner.

    Many people in the discussion forum claimed that the solution is of DFS (Depth-First Search). Although it is true that we would explore the 2D grid with the DFS strategy for this problem, it does not capture the entire nature of the solution.

    We argue that a more accurate term to summarize the solution would be backtracking, which is a methodology where we mark the current path of exploration, if the path does not lead to a solution, we then revert the change (i.e. backtracking) and try another path.

    As the general idea for the solution, we would walk around the 2D grid, at each step we mark our choice before jumping into the next step. And at the end of each step, we would also revert our marking, so that we could have a clean slate to try another direction. In addition, the exploration is done via the DFS strategy, where we go as further as possible before we try the next direction.

    Algorithm

    There is a certain code pattern for all the algorithms of backtracking. For example, one can find one template in our Explore card of Recursion II.

    The skeleton of the algorithm is a loop that iterates through each cell in the grid. For each cell, we invoke the backtracking function (i.e. backtrack()) to check if we would obtain a solution, starting from this very cell.

    For the backtracking function backtrack(row, col, suffix), as a DFS algorithm, it is often implemented as a recursive function. The function can be broke down into the following four steps:

    Step 1). At the beginning, first we check if we reach the bottom case of the recursion, where the word to be matched is empty, i.e. we have already found the match for each prefix of the word.

    Step 2). We then check if the current state is invalid, either the position of the cell is out of the boundary of the board or the letter in the current cell does not match with the first letter of the word.

    Step 3). If the current step is valid, we then start the exploration of backtracking with the strategy of DFS. First, we mark the current cell as visited, e.g. any non-alphabetic letter will do. Then we iterate through the four possible directions, namely up, right, down and left. The order of the directions can be altered, to one's preference.

    Step 4). At the end of the exploration, we revert the cell back to its original state. Finally we return the result of the exploration.

    We demonstrate how it works with an example in the following animation.


    """
    def doit_backtracking(self, board, word):
        """
        :type board: List[List[str]]
        :type word: str
        :rtype: bool
        """
        ROWS = len(board)
        COLS = len(board[0])
        board = board

        def backtrack(row, col, suffix):
            # bottom case: we find match for each letter in the word
            if len(suffix) == 0:
                return True

            # Check the current status, before jumping into backtracking
            if row < 0 or row == ROWS or col < 0 or col == COLS or board[row][col] != suffix[0]:
                return False

            ret = False
            # mark the choice before exploring further.
            board[row][col] = '#'
            # explore the 4 neighbor directions
            for rowOffset, colOffset in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                ret = backtrack(row + rowOffset, col + colOffset, suffix[1:])
                # break instead of return directly to do some cleanup afterwards
                if ret: break

            # revert the change, a clean slate and no side-effect
            board[row][col] = suffix[0]

            # Tried all directions,  and did not find any match
            return ret

        for row in range(ROWS):
            for col in range(COLS):
                if backtrack(row, col, word):
                    return True

        # no match found after all exploration
        return False






    def doit_dfs(self, board: 'list', word: str) -> bool:
        if not board:
            return False

        m, n = len(board), len(board[0])

        def search(i, j, s, path):
            if s == len(word):
                return True

            if i < 0 or i >= m or j < 0 or j >= n or board[i][j] != word[s]:
                return False
            
            if (i, j) in path:
                return False

            path.add((i, j))
            res = search(i+1, j, s+1, path) or search(i-1, j, s+1, path) or search(i, j+1, s+1, path) or search(i, j-1, s+1, path)
            path.remove((i, j))

            return res
        
        for i in range(m):
            for j in range(n):
                if board[i][j] != word[0]:
                    continue

                if search(i, j, 0, set()):
                    return True
                                    
        return False

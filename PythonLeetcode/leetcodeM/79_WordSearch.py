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

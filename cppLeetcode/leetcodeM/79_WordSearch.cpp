/*
79. Word Search

Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

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
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.
 

Follow up: Could you use search pruning to make your solution faster with a larger board?


*/
#include <functional>
#include <vector>
#include <string>
#include <unordered_set>

using std::unordered_set;
using std::string;
using std::vector;

class WordSearch {

public:

    // 
    bool doit_dfs(vector<vector<char>>& board, string word) {
        reverse(word.begin(), word.end());
        for (int m = 0; m < board.size(); m++) {
            for (int n = 0; n < board[m].size(); n++){
                if (board[m][n] == word[0] && existAround(m, n, board, word)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool existAround(int m, int n, vector<vector<char>> board, string word) {
        string oldWord = word;
        if (word == "") return true;
        if (m >= board.size() || n >= board[m].size() || m < 0 || n < 0 || board[m][n] != word[0]) return false;
        board[m][n] = '0'; // The same letter cell may not be used more than once.
        word.erase(0, 1);
        return existAround(m - 1, n, board, word)
            || existAround(m + 1, n, board, word)
            || existAround(m, n - 1, board, word)
            || existAround(m, n + 1, board, word);
    }


    
    bool doit_dfs(vector<vector<char>>& board, string word) {
        
        int m = board.size(), n = board[0].size();
        int dir[5] = {-1, 0, 1, 0, -1};
        
        std::function<bool(int, int, int, unordered_set<int>&)> dfs = [&](int i, int j, int idx, unordered_set<int>& visited) {
            
            if (idx == word.length()) return true;
            
            visited.insert(i*n+j);
            
            for (int d = 0; d < 4; d++) {    
                int x = i + dir[d], y = j + dir[d+1];
                if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != word[idx] || visited.count(x*n+y)) continue;
                if (dfs(x, y, idx+1, visited)) return true;
            }
            
            visited.erase(i*n+j);
            return false;
        };
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != word[0]) continue;
                
                unordered_set<int> visited;
                if (dfs(i, j, 1, visited)) return true;
            }
        }
        
        return false;
    }
};
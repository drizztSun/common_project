/*
 488. Zuma Game
 
 
 Think about Zuma Game. You have a row of balls on the table, colored red(R), yellow(Y), blue(B), green(G), and white(W). You also have several balls in your hand.

 Each time, you may choose a ball in your hand, and insert it into the row (including the leftmost place and rightmost place).
 Then, if there is a group of 3 or more balls in the same color touching, remove these balls. Keep doing this until no more balls can be removed.

 Find the minimal balls you have to insert to remove all the balls on the table. If you cannot remove all the balls, output -1.

  

 Example 1:

 Input: board = "WRRBBW", hand = "RB"
 Output: -1
 Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW
 Example 2:

 Input: board = "WWRRBBWW", hand = "WRBRW"
 Output: 2
 Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty
 Example 3:

 Input: board = "G", hand = "GGGGG"
 Output: 2
 Explanation: G -> G[G] -> GG[G] -> empty
 Example 4:

 Input: board = "RBYYBBRRB", hand = "YRBGB"
 Output: 3
 Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty
  

 Constraints:

 You may assume that the initial row of balls on the table won’t have any 3 or more consecutive balls with the same color.
 1 <= board.length <= 16
 1 <= hand.length <= 5
 Both input strings will be non-empty and only contain characters 'R','Y','B','G','W'.
 */
#include <string>
#include <vector>

using std::vector;
using std::string;


class ZumaGame {
    
    
public:
    int findMinStep(string board, string hand) {
        vector<int> h(128, 0);
        for (char color : hand) ++h[color];
        return dfs(board, h);
    }
    
private:
    // Return the min # of balls needed in hand to clear the board.
    // Returns -1 if not possible.
    int dfs(const string& board, vector<int>& hand) {
        if (board.empty()) return 0;
        
        int ans = INT_MAX;
        int i = 0;
        int j = 0;
        while (i < board.size()) {
            while (j < board.size() && board[i] == board[j]) ++j;
            // board[i] ~ board[j - 1] have the same color
            const char color = board[i];
            // Number of balls needed to clear board[i] ~ board[j - 1]
            const int b = 3 - (j - i);
            // Have sufficient balls in hand
            if (hand[color] >= b) {
                // Remove board[i] ~ board[j - 1] and update the board
                string nb = update(board.substr(0, i) + board.substr(j));
                // Find the solution on new board with updated hand
                hand[color] -= b;
                int r = dfs(nb, hand);
                if (r >= 0) ans = std::min(ans, r + b);
                // Recover the balls in hand
                hand[color] += b;
            }
            i = j;
        }
        return ans == INT_MAX ? -1 : ans;
    }
    
    // Update the board by removing all consecutive 3+ balls.
    // "YWWRRRWWYY" -> "YWWWWYY" -> "YYY" -> ""
    string update(string board) {
        int i = 0;
        while (i < board.size()) {
            int j = i;
            while (j < board.size() && board[i] == board[j]) ++j;
            if (j - i >= 3) {
                board = board.substr(0, i) + board.substr(j);
                i = 0;
            } else {
                ++i;
            }
        }
        return board;
    }
    
    
public:
    
    int doit_dfs(string board, string hand) {

        int cnt[26] = {0};
        char base = 'A';
        for (auto c : hand) {
            cnt[c-base]++;
        }
        
        std::function<int(string)> dfs = [&](string path) {
            
            if (path.size() == 0)
                return 0;
            
            int res = INT_MAX;
            
            for (auto i = 0; i < path.size(); i++){
                
                int j = i;
                while (j < path.size() && path[j] == path[i]) j++;
                
                int c = path[i]-base;
                int b = 3- (j - i);
                
                
                if (hand[c] >= b) {
                    
                    
                    string nexttarget = update(path.substr(0, i) + path.substr(j));
                    
                    hand[c] -= b;
                    
                    int ans = dfs(nexttarget);
                    if (ans > 0 )
                        res = std::min(res, ans + b);
                    
                    hand[c] += b;
                }
                i = j;
            }
            
            
            return res == INT_MAX ? -1 : res;
        };
        
        std::function<string(string)> update = [&](string path) {
            
            for (int i = 0; i < path.size(); i++) {
                
                int j = i;
                while (j < path.size() && path[j] == path[i]) j++;
                
                if (j - i >= 3) {
                    path = path.substr(0, i) + path.substr(j);
                    i = 0;
                } else
                    i++;
            }
            return path;
        };
        
        return dfs(board);
    }
};

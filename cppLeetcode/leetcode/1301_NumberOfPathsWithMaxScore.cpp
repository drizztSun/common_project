/*
 
 1301. Number of Paths with Max Score
 
 
 You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.

 You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'.
 In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

 Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.

 In case there is no path, return [0, 0].

  

 Example 1:

 Input: board = ["E23","2X2","12S"]
 Output: [7,1]
 Example 2:

 Input: board = ["E12","1X1","21S"]
 Output: [4,2]
 Example 3:

 Input: board = ["E11","XXX","11S"]
 Output: [0,0]
  

 Constraints:

 2 <= board.length == board[i].length <= 100
 
 */

#include <stdio.h>
#include <vector>
#include <string>

using std::string;
using std::vector;


class NumberOfPathWithMaxScore {
    
public:
    
    /*
     
     Solution DP

     Max Score only -> Medium

     dp[i][j] := max score when reach (j, i)
     count[i][j] := path to reach (j, i) with max score

     m = max(dp[i + 1][j], dp[i][j+1], dp[i+1][j+1])
     dp[i][j] = board[i][j] + m

     count[i][j] += count[i+1][j] if dp[i+1][j] == m
     count[i][j] += count[i][j+1] if dp[i][j+1] == m
     count[i][j] += count[i+1][j+1] if dp[i+1][j+1] == m

     Time complexity: O(n^2)
     Space complexity: O(n^2)
     
     */
    
    vector<int> doit_dp(vector<string>&& board) {
        
        const int kMod = 1e9 + 7;
        const int N = board.size();
        
        vector<vector<int>> dp(N+1, vector<int>(N+1, 0));
        vector<vector<int>> cc(N+1, vector<int>(N+1, 0));

        board[N-1][N-1] = board[0][0] = '0';
        cc[N-1][N-1] = 1;
        
        for (int i = N-1; i >= 0; i--) {
            for (int j = N-1; j >= 0; j--) {
                
                if (board[i][j] == 'X')
                    continue;
                
                int maxlength = std::max({dp[i+1][j+1], dp[i+1][j], dp[i][j+1]});
                dp[i][j] = maxlength + (board[i][j] - '0');

                if (maxlength == dp[i+1][j+1])
                    cc[i][j] = (cc[i][j] + cc[i+1][j+1]) % kMod;
                
                if (maxlength == dp[i+1][j])
                    cc[i][j] = (cc[i][j] + cc[i+1][j]) % kMod;
                
                if (maxlength == dp[i][j+1])
                    cc[i][j] = (cc[i][j] + cc[i][j+1]) % kMod;
            }
        }
        
        return {cc[0][0] ? dp[0][0] : 0, cc[0][0]};
    }
    
    
    int sum[100][100];
    int cases[100][100];

   vector<int> doit_dp_1(vector<string>& board) {
       int mod = 1e9 + 7;
       int n = board.size();
       cases[0][0] = 1;
       sum[0][0] = 1;
       board[n - 1][n - 1] = '0';
       
       for (int i = 1; i < n; i++) {
           if (board[0][i] == 'X') break;
           sum[0][i] = sum[0][i - 1] + board[0][i] - '0';
           cases[0][i] = 1;
       }
       for (int i = 1; i < n; i++) {
           if (board[i][0] == 'X') break;
           sum[i][0] = sum[i - 1][0] + board[i][0] - '0';
           cases[i][0] = 1;
       }
       
   
       for (int i = 1; i < n; i++) {
           for (int j = 1; j < n; j++) {
               if (board[i][j] == 'X') continue;
               int maxSum = std::max(sum[i - 1][j - 1], std::max(sum[i][j - 1], sum[i - 1][j]));
               if (!maxSum) continue;
               sum[i][j] = maxSum + (board[i][j] - '0');
               if (sum[i - 1][j - 1] == maxSum) cases[i][j] = cases[i - 1][j - 1];
               if (sum[i - 1][j] == maxSum) cases[i][j] = (cases[i][j] + cases[i - 1][j]) % mod;
               if (sum[i][j - 1] == maxSum) cases[i][j] = (cases[i][j] + cases[i][j - 1]) % mod;
           }
       }
       if (sum[n - 1][n - 1]) sum[n - 1][n - 1]--;
       return {sum[n - 1][n - 1], cases[n - 1][n - 1]};
   }
};


void test_1301_number_of_paths() {

    NumberOfPathWithMaxScore().doit_dp(vector<string>{"E23","2X2","12S"});
}

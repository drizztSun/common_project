/*
 1349. Maximum Students Taking Exam
 
 Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.

 Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible..

 Students must be placed in seats in good condition.

  

 Example 1:


 Input: seats = [["#",".","#","#",".","#"],
                 [".","#","#","#","#","."],
                 ["#",".","#","#",".","#"]]
 Output: 4
 Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam.
 Example 2:

 Input: seats = [[".","#"],
                 ["#","#"],
                 ["#","."],
                 ["#","#"],
                 [".","#"]]
 Output: 3
 Explanation: Place all students in available seats.

 Example 3:

 Input: seats = [["#",".",".",".","#"],
                 [".","#",".","#","."],
                 [".",".","#",".","."],
                 [".","#",".","#","."],
                 ["#",".",".",".","#"]]
 Output: 10
 Explanation: Place students in available seats in column 1, 3 and 5.
  

 Constraints:

 seats contains only characters '.' and'#'.
 m == seats.length
 n == seats[i].length
 1 <= m <= 8
 1 <= n <= 8
 
 */
#include <vector>


using std::vector;

class MaximumStudentsTaskingExam {
    
public:
    
    int n,m;
    int find(vector<vector<char>>& a,int y,int b)
    {
        static int d[6][2]={{-1,-1},{-1,1},{0,-1},{0,1},{1,-1},{1,1}};
        if(y>=n or y<0)
            return 0;
        int res=0;
        for(int i=0;i<m;i++)
        {
            if(a[i][y]=='#')
                continue;
            bool f=1;
            for(int j=0;j<6;j++)
            {
                int xx=i+d[j][0];
                int yy=y+d[j][1];
                if(xx<0 or xx>=m or yy<0 or yy>=n)
                    continue;
                if(a[xx][yy]=='S')
                {
                    f=0;
                    break;
                }
            }
            if(!f)
                continue;
            ++res;
            a[i][y]='S';
        }
        res+=find(a,y+b,b);
        for(int i=0;i<m;i++)
            if(a[i][y]=='S')
                a[i][y]='.';
        return std::max(res,find(a,y+b,b));
    }
    int doit_dfs(vector<vector<char>>& s) {
        n=s[0].size(),m=s.size();
        return std::max(find(s,0,1), find(s,n-1,-1));
    }
    
    int doit_dp(vector<vector<char>>& seats) {
    
        auto m = seats.size(), n = seats[0].size();
        vector<vector<int>> dp(m+1, vector<int>(1<<n));
        
        for (int i = 0; i < m; i++) { // row_i
            
            // enumerate status
            for (int l = 0; l < 1<<n; l++)  //row i-1
            for (int c = 0; c < 1<<n; c++) { // row i
                
                bool flag = true;
                for (auto j = 0; j < n && flag; j++) {
                    
                    if (!(c&(1<<j)))
                        continue;
                    
                    if (seats[i][j] == '#')
                        flag = false;
                    
                    bool cl = j == 0? false: (c & (1<<(j-1)));
                    bool cr = j == n-1 ? false: (c & (1<<(j+1)));
                    bool ll = (j == 0 || i == 0) ? false: (l & (1<<(j-1)));
                    bool lr = (j == n-1 || i == 0) ? false: (l & (1 << (j+1)));
                    
                    if (cl | cr | ll | lr)
                        flag = false;
                }
                
                if (flag)
                    dp[i+1][c] = std::max(dp[i+1][c], dp[i][l] + __builtin_popcount(c));
            }
        }
        
        return *max_element(dp[m].begin(), dp[m].end());
    }
    
    
    int doit_dp_1(vector<vector<char>>& seats) {
      const int m = seats.size();
      const int n = seats[0].size();
      vector<int> s(m + 1);
      for (int i = 1; i <= m; ++i)
        for (int j = 0; j < n; ++j)
          s[i] |= (seats[i - 1][j] == '.') << j;
      
      vector<vector<int>> dp(m + 1, vector<int>(1 << n));
      for (int i = 1; i <= m; ++i)
        for (int c = s[i];;c = (c - 1) & s[i]) {
          if (c & (c >> 1))
              continue;
          
          for (int l = s[i - 1];;l = (l - 1) & s[i - 1]) {
            if (!(l & (c >> 1)) && !((l >> 1) & c))
              dp[i][c] = std::max(dp[i][c], dp[i - 1][l] + __builtin_popcount(c));
            if (l == 0)
                break;
          }
          if (c == 0)
              break;
        }
      return *max_element(begin(dp[m]), end(dp[m]));
    }
};

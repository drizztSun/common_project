/*
351. Android Unlock Patterns



Android devices have a special lock screen with a 3 x 3 grid of dots. Users can set an "unlock pattern" by connecting the dots in a specific sequence, 
forming a series of joined line segments where each segment's endpoints are two consecutive dots in the sequence. A sequence of k dots is a valid unlock pattern if both of the following are true:

All the dots in the sequence are distinct.
If the line segment connecting two consecutive dots in the sequence passes through any other dot, the other dot must have previously appeared in the sequence. No jumps through non-selected dots are allowed.
Here are some example valid and invalid unlock patterns:



The 1st pattern [4,1,3,6] is invalid because the line connecting dots 1 and 3 pass through dot 2, but dot 2 did not previously appear in the sequence.
The 2nd pattern [4,1,9,2] is invalid because the line connecting dots 1 and 9 pass through dot 5, but dot 5 did not previously appear in the sequence.
The 3rd pattern [2,4,1,3,6] is valid because it follows the conditions. The line connecting dots 1 and 3 meets the condition because dot 2 previously appeared in the sequence.
The 4th pattern [6,5,4,1,9,2] is valid because it follows the conditions. The line connecting dots 1 and 9 meets the condition because dot 5 previously appeared in the sequence.
Given two integers m and n, return the number of unique and valid unlock patterns of the Android grid lock screen that consist of at least m keys and at most n keys.

Two unlock patterns are considered unique if there is a dot in one sequence that is not in the other, or the order of the dots is different.

 

Example 1:

Input: m = 1, n = 1
Output: 9
Example 2:

Input: m = 1, n = 2
Output: 65
 

Constraints:

1 <= m, n <= 9

*/

#include <vector>
#include <functional>

using std::vector;



class NumberOfPatterns {

    /*
        351.Android-Unlock-Patterns
        关于题意：如果走L形的move，我们不认为它经过任何其他的格子。

        本题是典型的DFS。我们从任意点开始，每个回合有16种移动的选择：上、下、左、右、左上、左下、右上、右下、左上上、右上上、左下下、右下下、左左上、左左下、右右上、右右下。

        特别地，对于前8种move而言，如果走一步遇到的格子是已经访问过的，根据规则，可以再朝同方向走一步（算作同一次操作）。如果走一步遇到的格子是没有访问过的，则不能这么做。
    */
    int count = 0;
    int m,n;

    int numberOfPatterns(int m, int n) 
    {
        this->m = m;
        this->n = n;        
        auto visited = vector<vector<int>>(3, vector<int>(3,0));
        
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
            {
                visited[i][j] = 1;
                dfs(i,j,1,visited);
                visited[i][j] = 0;
            }
        return count;        
    }
    
    void dfs(int x, int y, int r, vector<vector<int>>&visited)
    {        
        auto dir = vector<std::pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1},{-1,2},{1,2},{-2,1},{2,1},{-1,-2},{1,-2},{-2,-1},{2,-1}});
        if (r>=m && r<=n)
            count++;
        if (r>n) return;
        
        for (int k=0; k< dir.size(); k++)
        {
            int i = x+dir[k].first;
            int j = y+dir[k].second;
            if (i<0||i>=3||j<0||j>=3)
                continue;        
            if (visited[i][j] == 0)
            {
                visited[i][j] = 1;
                dfs(i,j,r+1,visited);
                visited[i][j] = 0;
            }                
            else
            {
                i = i+dir[k].first;
                j = j+dir[k].second;
                if (i<0||i>=3||j<0||j>=3)
                    continue;     
                if (visited[i][j]==1) continue;
                visited[i][j] = 1;
                dfs(i,j,r+1,visited);
                visited[i][j] = 0;
            }            
        }        
    }
public:
    
    int doit_dfs(int m, int n) {

        int ans = 0;

        vector<vector<int>> visited(3, vector<int>(3, 0));
        auto dir = vector<std::pair<int,int>>({{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1},{-1,2},{1,2},{-2,1},{2,1},{-1,-2},{1,-2},{-2,-1},{2,-1}});

        std::function<int(int, int, int)> dfs = [&](int i, int j, int r) {

            if (r >= m && r <= n) {
                ans++;
            }

            if (r > n) return;

            for (auto c: dir) {

                int x = i + c.first, y = j + c.second;

                if (x<0 || x>2 || y<0 || y>2 ) continue;

                if (visited[x][y] == 0) {
                    visited[x][y] = 1;
                    dfs(x, y, r+1);
                    visited[x][y] = 0;
                } else {

                    x = x + c.first, y = y + c.second;
                    if (x<0 || x>2 || y<0 || y>2 ) continue;

                    if (visited[x][y] == 0) {
                        visited[x][y] = 1;
                        dfs(x, y, r+1);
                        visited[x][y] = 0;
                    } 
                }
            }
        };

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                visited[i][j] = 1;
                dfs(i, j, 0);
                visited[i][j] = 0;
            }
        }

        return ans;
    }

public:

    vector<int> seen;
    int moves[10][10];
    int m, n;

    int dfs(int num, int len, int count) {
        if (len >= m) ++count;
        if (++len > n) return count;

        seen[num] = 1;

        for (int j = 1; j <= 9; ++j) {
            int jump = moves[num][j];
            if (!seen[j] && (jump == 0 || seen[jump])) {
                count = dfs(j, len, count);
            }
        }

        seen[num] = 0;
        return count;
    }

    int numberOfPatterns(int m, int n) {
        this->m = m;
        this->n = n;
        seen = vector<int>(10);

        memset(moves, 0, sizeof(int) * 100);
        moves[1][3] = moves[3][1] = 2;
        moves[4][6] = moves[6][4] = 5;
        moves[7][9] = moves[9][7] = 8;
        moves[1][7] = moves[7][1] = 4;
        moves[2][8] = moves[8][2] = 5;
        moves[3][9] = moves[9][3] = 6;
        moves[1][9] = moves[9][1] = 5;
        moves[3][7] = moves[7][3] = 5;

        return 4 * dfs(1, 1, 0) + 4 * dfs(2, 1, 0) + dfs(5, 1, 0);
    }
};
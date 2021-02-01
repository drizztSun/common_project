/*
1504. Count Submatrices With All Ones

Given a rows * columns matrix mat of ones and zeros, return how many submatrices have all ones.

 

Example 1:

Input: mat = [[1,0,1],
              [1,1,0],
              [1,1,0]]
Output: 13
Explanation:
There are 6 rectangles of side 1x1.
There are 2 rectangles of side 1x2.
There are 3 rectangles of side 2x1.
There is 1 rectangle of side 2x2. 
There is 1 rectangle of side 3x1.
Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.
Example 2:

Input: mat = [[0,1,1,0],
              [0,1,1,1],
              [1,1,1,0]]
Output: 24
Explanation:
There are 8 rectangles of side 1x1.
There are 5 rectangles of side 1x2.
There are 2 rectangles of side 1x3. 
There are 4 rectangles of side 2x1.
There are 2 rectangles of side 2x2. 
There are 2 rectangles of side 3x1. 
There is 1 rectangle of side 3x2. 
Total number of rectangles = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24.
Example 3:

Input: mat = [[1,1,1,1,1,1]]
Output: 21
Example 4:

Input: mat = [[1,0,1],[0,1,0],[1,0,1]]
Output: 5
 

Constraints:

1 <= rows <= 150
1 <= columns <= 150
0 <= mat[i][j] <= 1

*/
#include <vector>
#include <stack>

using std::vector;
using std::stack;


class SubmatricesAllOnes {

public:

    /*
        Algo
        In the first step, stack mat row by row to get the "histogram model". For example,
        
        mat = [[1,0,1],
               [1,1,0],
               [1,1,0]]
        becomes
        
        mat = [[1,0,1],
               [2,1,0],
               [3,2,0]]
        In the second step, traverse the stacked matrix row by row. At each position i, j, compute the number of all-1 submatrices like below.
        
        Define a stack to store indices of non-decreasing height, and a variable cnt for the number of all-1 submatrices at given position (i, j). 
        Take the height of row i as an example, say h = mat[i]. At column j, if h[j-1] <= h[j], it is apparent that cnt[j] = cnt[j-1] + h[j], 
        since every case that contributes to cnt[j-1] could be added a new column of 1's from the jth column to contribute to cnt[j].
        
        The tricky part is when h[j-1] > h[j]. In this case, we need to "hypothetically" lower h[j-1] to h[j] to get an updated cnt*[j-1] before adding h[j] to get cnt[j]. 
        Suppose that the histogram is like below to reflect 3,3,3,2. 
        To compute cnt[3], we have to adjust cnt[2] to a hypothetical height of 2 by removing top row before adding the new column to get cnt[3]. 
        The specific operation is done using a mono-stack which stores indices of non-decreasing height. 
        
        Whenever a new height comes in, pop out the heights in the stack that are higher than the new height while removing the quota contributed by the extra height (between poped height and new height).
        
        * * * 
        * * * * 
        * * * *
    
        O(m*n)
    */

    int doit_(vector<vector<int>>& mat) {
        
        int rows = mat.size(), cols = mat[0].size();
        int ans = 0;

        for (int i = 0; i < rows; i++) {    
            for (int j = 0; j < cols; j++) {
                if (mat[i][j] && i > 0)
                    mat[i][j] += mat[i-1][j];
            }
        }
            
        for (int i = 0; i < rows; i++) {
            
            int cnt = 0;
            stack<int> st;
            
            for (int j = 0; j < cols; j++) {
                
                while (!st.empty() && mat[i][st.top()] > mat[i][j]) {
                    int jj = st.top();
                    st.pop();
                    int kk = st.empty() ? -1 : st.top();
                    cnt -= (jj - kk) * (mat[i][jj] - mat[i][j]);
                }
                
                cnt += mat[i][j];
                ans += cnt;
                st.push(j);
            }
        }
        
        return ans;
    }
    
    int doit_(vector<vector<int>>& mat) {
        
        int rows = mat.size(), cols = mat[0].size();
        int ans = 0;
            
        for (int i = 0; i < rows; i++) {
            
            int cnt = 0;
            stack<int> st;
            
            for (int j = 0; j < cols; j++) {
                
                if (i > 0 && mat[i][j] == 1)
                    mat[i][j] = mat[i-1][j] + 1;
                
                while (!st.empty() && mat[i][st.top()] > mat[i][j]) {
                    int jj = st.top();
                    st.pop();
                    int kk = st.empty() ? -1 : st.top();
                    cnt -= (jj - kk) * (mat[i][jj] - mat[i][j]);
                }
                
                cnt += mat[i][j];
                ans += cnt;
                st.push(j);
            }
        }
        
        return ans;
    }
};
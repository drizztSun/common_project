/*
85. Maximal Rectangle

Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

 

Example 1:


Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
Example 2:

Input: matrix = []
Output: 0
Example 3:

Input: matrix = [["0"]]
Output: 0
Example 4:

Input: matrix = [["1"]]
Output: 1
Example 5:

Input: matrix = [["0","0"]]
Output: 0
 

Constraints:

rows == matrix.length
cols == matrix.length
0 <= row, cols <= 200
matrix[i][j] is '0' or '1'.
*/
#include <vector>
#include <stack>

using std::stack;
using std::vector;


class maximalRectangle {

    /*
        此题是leetcode第84题的二维扩展，转化为求maximal histgram.  

        for (int i=0; i<M; i++)  //遍历histgram的底行位置。注意：不需要遍历histgram的顶行位置！
        {
        for (int j=0; j<N; j++)
        {
            if (matrix[i][j]==0)
                q[j]=0;
            else
                q[j]=q[j]+1;
        }
        }
        注意：

        不要试图用预处理的DP算法（计算sum[i][j]），这样仍需要四重循环，时间复杂度太大。
        MaxHistgram时的小技巧：在数组首尾都加零。前者避免 i-s.top()-1 时遇到栈空，后者保证总会进行一次退栈。
    
    */
    int doit_(vector<vector<bool> > &matrix) 
    {
        int M=matrix.size();
        if (M==0) return 0;
        int N=matrix[0].size();
        
        auto q= vector<int>(N,0);
        int result = 0;
        
        for (int i=0; i<M; i++)
        {
            for (int j=0; j<N; j++)
            {
                if (matrix[i][j]==0) 
                    q[j]=0;
                else
                    q[j]=q[j]+1;
            }

            result = std::max(result, helper(q));   
        }
        
        return result;
    }
    
    int helper(vector<int>height)
    {
        if (height.size()==0) return 0;
        if (height.size()==1) return height[0];
        
        stack<int>s;
        height.push_back(0);
        height.insert(height.begin(),0);
        
        int result=0;
        
        for (int i=0; i<height.size(); i++)
        {
            if (s.empty() || height[i]>=height[s.top()])
            {
                s.push(i);
                continue;
            }
            
            if (height[i]<height[s.top()])
            {
                while (!s.empty() && height[i]<height[s.top()])
                {
                    int H = height[s.top()];
                    s.pop();
                    result = std::max(result, H*(i-s.top()-1));
                }
                s.push(i);
            }
        }
        
        return result;
    }

public:
    int doit_monotonic_stack(vector<vector<char>>& matrix) {
        
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        vector<int> height(n, 0);
        int res = 0;
        
        for (int i = 0; i < m; i++) {
            
            for (int j = 0; j < n; j++) 
                height[j] = matrix[i][j] == '1' ? height[j] + 1 : 0;    
            
            stack<int> st;
            for (int j = 0; j <= n; j++) {
                
                while (!st.empty() && (j == n  || height[st.top()] > height[j])) {
                    
                    int H = height[st.top()];
                    st.pop();
                    int last = st.empty() ? -1 : st.top();
                    int L = j - last - 1;
                    res = std::max(res, L * H);
                }
                st.push(j);
            }
        }
        
        return res;
    }
};
/*
221. Maximal Square


Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:

Input:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4
*/
#include <vector>
#include <stack>

using std::stack;
using std::vector;

class MaximalSquare {

public:

    /*
        Approach #2 (Dynamic Programming) [Accepted]
        Algorithm

        We will explain this approach with the help of an example.

        0 1 1 1 0
        1 1 1 1 1
        0 1 1 1 1
        0 1 1 1 1
        0 0 1 1 1
        We initialize another matrix (dp) with the same dimensions as the original one initialized with all 0’s.

        dp(i,j) represents the side length of the maximum square whose bottom right corner is the cell with index (i,j) in the original matrix.

        Starting from index (0,0), for every 1 found in the original matrix, we update the value of the current element as

        dp(i, j) = min(dp(i−1,j), dp(i−1,j−1), dp(i,j−1)) + 1.

        We also remember the size of the largest square found so far. In this way, we traverse the original matrix once and find out the required maximum size.
        This gives the side length of the square (say maxsqlenmaxsqlen). The required result is the area maxsqlen^2.

        To understand how this solution works, see the figure below.

        Max Square

        An entry 2 at (1, 3)(1,3) implies that we have a square of side 2 up to that index in the original matrix.
        Similarly, a 2 at (1, 2)(1,2) and (2, 2)(2,2) implies that a square of side 2 exists up to that index in the original matrix.
        Now to make a square of side 3, only a single entry of 1 is pending at (2, 3)(2,3). So, we enter a 3 corresponding to that position in the dp array.

        Now consider the case for the index (3, 4)(3,4). Here, the entries at index (3, 3)(3,3) and (2, 3)(2,3) imply that a square of side 3 is possible up to their indices.
        But, the entry 1 at index (2, 4)(2,4) indicates that a square of side 1 only can be formed up to its index.
        Therefore, while making an entry at the index (3, 4)(3,4), this element obstructs the formation of a square having a side larger than 2.
        Thus, the maximum sized square that can be formed up to this index is of size 2\times22×2.

        Complexity Analysis

        Time complexity : O(mn). Single pass.

        Space complexity : O(mn). Another matrix of same size is used for dp.
     
    */
    int doit_dp(vector<vector<char>>& matrix) {

        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        int ans = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (matrix[i-1][j-1] == '1') {
                    dp[i][j] = std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                    ans = std::max(ans, dp[i][j]);
                }
            }
        }
        
        return ans * ans;
    }

    /*
        Approach #3 (Better Dynamic Programming) [Accepted]
        Algorithm

        In the previous approach for calculating dp of i^{th} row we are using only the previous element and the (i-1)^{th} row. Therefore, we don't need 2D dp matrix as 1D dp array will be sufficient for this.

        Initially the dp array contains all 0's. As we scan the elements of the original matrix across a row, we keep on updating the dp array as per the equation 
        dp[j] = min(dp[j-1],dp[j],prev)dp[j] = min(dp[j−1],dp[j],prev), where prev refers to the old dp[j-1]dp[j−1]. For every row, we repeat the same process and update in the same dp array.

        Max Square 

        java

        public class Solution {
            public int maximalSquare(char[][] matrix) {
                int rows = matrix.length, cols = rows > 0 ? matrix[0].length : 0;
                int[] dp = new int[cols + 1];
                int maxsqlen = 0, prev = 0;
                for (int i = 1; i <= rows; i++) {
                    for (int j = 1; j <= cols; j++) {
                        int temp = dp[j];
                        if (matrix[i - 1][j - 1] == '1') {
                            dp[j] = Math.min(Math.min(dp[j - 1], prev), dp[j]) + 1;
                            maxsqlen = Math.max(maxsqlen, dp[j]);
                        } else {
                            dp[j] = 0;
                        }
                        prev = temp;
                    }
                }
                return maxsqlen * maxsqlen;
            }
        }
        Complexity Analysis

        Time complexity : O(mn). Single pass.

        Space complexity : O(n). Another array which stores elements in a row is used for dp.
    */
    int doit_dp(vector<vector<char>>& matrix) {

        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(2, vector<int>(n+1, 0));
        int ans = 0;

        for (int i = 1; i <= m; i++) {
            int index = i % 2;

            for (int j = 1; j <= n; j++) {
                
                dp[index][j] = 0;
                
                if (matrix[i-1][j-1] == '1') {
                    dp[index][j] = std::min({dp[1-index][j], dp[index][j-1], dp[1-index][j-1]}) + 1;
                    ans = std::max(ans, dp[index][j]);
                }
            }
        }
        
        return ans * ans;
    }

    /*
        leetcode-221-Maximal-Square  
        解法1：brutal search
        首先预处理得到矩阵sum[i][j]，表示从左上角(0,0)到(i,j)处的所有元素之和。注意技巧，sum在定义时两个维度大小都增1。

        对于每一个sum[i][j]，判断是否存在以(i,j)为右下角、边长为k的正方形，k的取值从1到不越界。判断表达式是：

        if (sum[i][j]-sum[i-1][j]-sum[i][j-1]+sum[i-1][j-1] == k*k) 
        73ms

        解法2：逐行判断，贪心法
        完全类似于 leetcode 85 maximal rectangular，变换成在一维上求最大正方形。

        核心思想：不断加入数组元素，维护一个非减的栈序列，注意栈元素是数组的index而不是数值本身。遇到下一个数组元素比栈顶元素小的时候，退栈，判断该栈顶元素能够围成的最大正方形空间。

        if （height[i]>=height[s.top()])  
        {push(i); continue;}
        else    
        { int H=height[s.top()];
            s.pop();
            result = max(result,min(H,i-s.top()-1);
        }  
        9ms

        解法3：动态规划  
        设计dp[i][j]表示右下角为(i,j)的最大正方形边长。则有动态转移方程：

        if (matrix[i][j]==1)
        dp[i][j]=min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1
        else
        dp[i][j]=0;
        可以这么理解上述的动态转移方程。假设matrix[i][j]==1，那么对于右下角为（i,j）的可能的最大正方形，主要取决于dp[i-1][j-1]有多大，其次还要考虑第i行和第j列分别有多少1与（i,j）连着。所以，这个最大正方形，其下边长由min(dp[i-1][j-1],dp[i][j-1])决定，有边长由min(dp[i-1][j-1],dp[i-1][j])决定。

        最后注意，输出的面积应该是最长边长的平方。
    */
    int doit_bruteforce(vector<vector<char>>& matrix) 
    {
        int M=matrix.size();
        if (M==0) return 0;
        int N=matrix[0].size();
        
        auto sum=vector<vector<int>>(M+1,vector<int>(N+1,0));
        
        for (int i=1; i<M+1; i++)
            for (int j=1; j<N+1; j++)
            {
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+matrix[i-1][j-1]-'0';
            }
            
        /*
        for (int i=1; i<M+1; i++)
        {
            for (int j=1; j<N+1; j++)
            {
                cout<<sum[i][j]<<" ";
            }
            cout<<endl;
        }
        */
        
        int result = 0;
        
        for (int i=1; i<M+1; i++)
            for (int j=1; j<N+1; j++)
            {
                int k=1;
                while (j-k>=0 && i-k>=0)
                {
                    int temp = sum[i][j]-sum[i-k][j]-sum[i][j-k]+sum[i-k][j-k];
                    if (temp == k*k)
                        result = std::max(result, temp);
                    k++;    
                }
            }
            
        return result;
    }

    int doit_dp(vector<vector<char>>& matrix) 
    {
        int M=matrix.size();
        if (M==0) return 0;
        int N=matrix[0].size();
        auto dp=vector<vector<int>>(M+1,vector<int>(N+1,0));
        int result=0;
        
        for (int i=1; i<=M; i++)
            for (int j=1; j<=N; j++)
            {
                if (matrix[i-1][j-1]=='0')
                    dp[i][j]=0;
                else
                {
                    int temp=std::min(dp[i-1][j],dp[i][j-1]);
                    temp = std::min(temp,dp[i-1][j-1]);
                    dp[i][j]=temp+1;
                    result=std::max(result,dp[i][j]*dp[i][j]);
                }
            }
        
        return result;
    }

    int doit_stack(vector<vector<char>>& matrix) 
    {
        int M=matrix.size();
        if (M==0) return 0;
        int N=matrix[0].size();
        
        vector<int>q(N,0);
        
        int result=0;
        for (int i=0; i<M; i++)
        {
            for (int j=0; j<N; j++)
            {
                if (matrix[i][j]=='0')
                    q[j]=0;
                else
                    q[j]=q[j]+1;
                    
            }

            result = std::max(result,helper(q));
        }
        
        return result;
        
    }
    
    int helper(vector<int>height)
    {
        if (height.size()==1) return (height[0]>0);
        height.push_back(0);
        height.insert(height.begin(),0);
        
        stack<int>s;
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
                    int H=height[s.top()];
                    
                    s.pop();
                    int d = std::min(H,i-s.top()-1);
                    result = std::max(result,d*d);
                }
                s.push(i);
            }
        }
    
        return result;
    }
};
/*
 
 1411. Number of Ways to Paint N × 3 Grid
 
 
 You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colours: Red, Yellow or Green
 while making sure that no two adjacent cells have the same colour (i.e no two cells that share vertical or horizontal sides have the same colour).

 You are given n the number of rows of the grid.

 Return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 10^9 + 7.

  

 Example 1:

 Input: n = 1
 Output: 12
 Explanation: There are 12 possible way to paint the grid as shown:

 Example 2:

 Input: n = 2
 Output: 54
 Example 3:

 Input: n = 3
 Output: 246
 Example 4:

 Input: n = 7
 Output: 106494
 Example 5:

 Input: n = 5000
 Output: 30228214
  

 Constraints:

 n == grid.length
 grid[i].length == 3
 1 <= n <= 5000

 
 */
#include <vector>


using std::vector;


class NumOfWays {

    /*
        1411.Number-of-Ways-to-Paint-N×3-Grid
        解法1：
        此题和1349.Maximum Students Taking Exam很相似。第i行的喷涂方法只受第i-1行喷涂方法的约束。所以是第I类基本型的DP问题。

        考虑到每一行的喷涂方法就只有3^3=27种，是可以枚举过来的。我们可以利用状态压缩的思想，用一个小于27的整数来代表一种喷涂方法。

        我们定义dp[i][p]表示当第i行喷涂p方案时，前i行整体的喷涂方案总数。于是

        dp[i][p] = sum(dp[i-1][q])
        其中q就是第i-1行的喷涂方案，要求q与p不冲突，且q和p都是合法的。

        最终的答案是最后一行所有合法喷涂方案p对应的dp值的总和。

        解法2：
        另外一种解法就要费神一些。设计状态color2表示第i行喷涂两种颜色时（整体）的方案总数；color3表示第i行喷涂三种颜色时（整体）的方案总数。

        假设某一行喷涂两种颜色，可以用ABA表示。那么如果下一行也是喷涂两种颜色，只可能是如下模式：BAB, BCB, CAC. 如果下一行喷涂三种颜色，只可能是如下模式：BAC, CAB.

        假设某一行喷涂三种颜色，可以用ABC表示。那么如果下一行也是喷涂两种颜色，只可能是如下模式：BAB, BAB. 如果下一行喷涂三种颜色，只可能是如下模式：BCA, CAB.

        于是我们可以得到行与行之间的状态转移方程：

        color2 = 3*color2' + 2*color3'
        color3 = 2*color2' + 2*color3'
    */
    int numOfWays(int n) 
    {
        long colors2 = 6, colors3 = 6;
        long M = 1e9+7;
        
        for (int i=1; i<n; i++)
        {
            long temp2 = colors2, temp3 = colors3;
            colors2 = ((3*temp2)%M + (2*temp3)%M)%M;
            colors3 = ((2*temp2)%M + (2*temp3)%M)%M;
        }
        
        return (colors2+colors3)%M;   
    }

public:
    
    vector<int>temp1, temp2;

    int numOfWays(int n) 
    {
        vector<int>dp(27,0);
        int M = 1e9+7;
        temp1.resize(3);
        temp2.resize(3);
        
        for (int p=0; p<27; p++)
        {
            if (selfOK(p))
                dp[p] = 1;
        }

        for (int i=1; i<n; i++)
        {
            auto dp_prev = dp;
            for (int p=0; p<27; p++)
            {
                dp[p] = 0;
                if (!selfOK(p)) continue;
                for (int q=0; q<27; q++)
                {
                    if (!selfOK(q)) continue;
                    if (crossOK(p,q))
                        dp[p] = (dp[p]+dp_prev[q])%M;
                }
            }
        }
        
        int sum = 0;
        for (int p=0; p<27; p++)
        {
            if (selfOK(p))
                sum = (sum+dp[p])%M;
        }
        return sum;
        
    }
    
    bool selfOK(int p)
    {
        for (int i=0; i<3; i++)
        {
            temp1[i] = (p%3);
            p/=3;
        }
        return (temp1[0]!=temp1[1] && temp1[1]!=temp1[2]);
    }
    
    bool crossOK(int p, int q)
    {
        
        for (int i=0; i<3; i++)
        {
            temp1[i] = (p%3);
            temp2[i] = (q%3);
            p/=3;
            q/=3;
        }
        return (temp1[0]!=temp2[0] && temp1[1]!=temp2[1] && temp1[2]!=temp2[2]);
    }
    
    
public:
    
    int doit_dp_1(int n) {
        
        int M = 1e9+7;
        int tmp1[3] = {0, 0, 0}, tmp2[3] = {0, 0, 0};
        
        auto self_dk = [](int p, int* tmp) ->bool {
            
            for (int i = 0; i < 3; i++) {
                tmp[i] = p%3;
                p /= 3;
            }
            
            return (tmp[0] != tmp[1] && tmp[1] != tmp[2]);
        };
        
        int dp[27] = {0};
        for (auto i = 0; i < 27; i++) {
            if (self_dk(i, tmp1))
                dp[i] = 1;
        }
            
        while (n > 1) {
            
            int nextdp[27];
            
            for (auto i = 0; i < 27; i++)
                nextdp[i] = dp[i];
            
            // each line, can has 27 possible result, but only 12 of them are valid.
            // last line can also have 27 possible result and 12 of them are valid.
            for (auto i = 0; i < 27; i++) {

                dp[i] = 0;
                if (!self_dk(i, tmp1))
                    continue;
                
                for (auto j = 0; j < 27; j++) {
                    
                    if (!self_dk(j, tmp2))
                        continue;
                    
                    if (tmp1[0] != tmp2[0] && tmp1[1] != tmp2[1] && tmp1[2] != tmp2[2])
                        dp[i] = (dp[i] + nextdp[j]) % M;
                }
            }
            
            n--;
        }
        
        int res = 0;
        for (auto i = 0; i < 27; i++) {
            res = (res + dp[i]) % M;
        }
        return res;
    }
    
    int doit_dp(int n) {
        
        /*
            i-1, 2 colors,   3 colors
            i,   2 colors,   3 colors
            
            ABA(2 colors) => CAC, BCB, BAB (2 colors) or BAC, CAB (3 colors)
            
            ABC(3 colors) => BAB, BCB, (2 colors) or BCA, CAB (3 colors)
            
            dp2[i] = 2 * dp3[i-1] + 3 * dp2[i-1]
            dp3[i] = 2 * dp2[i-1] + 2 * dp3[i-1]
        */
        
        int M = 1e9+7;
        int dp2 = 6, dp3 = 6;
        
        while (n > 1) {
            
            long last2 = dp2, last3 = dp3;
            
            dp2 = ((2 * last3) % M + (3 * last2) % M) % M;
            dp3 = ((2 * last2) % M + (2 * last3) % M) % M;
            
            n--;
        }
        
        return (dp2 + dp3) % M;
    }
    
    int doit_dp_fastpower(int n) {
        
        constexpr long kMod = 1e9 + 7;
        
        auto mul = [kMod] (const vector<vector<long>>& A, const vector<vector<long>>& B) {
            
            const auto m = A.size(), n = B.size();
            const auto p = B[0].size();
            
            vector<vector<long>> C(m, vector<long>(p));
            for (auto i = 0; i < m; i++) {
                for (auto j = 0; j < p; j++) {
                    for (auto k = 0; k < n; k++) {
                        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % kMod;
                    }
                }
            }
            return C;
        };
        
        vector<vector<long>> ans{{6, 6}};
        vector<vector<long>> M{{3, 2}, {2, 2}};
        
        --n;
        while (n) {
            
            if (n & 1)
                ans = mul(ans, M);
            M = mul(M, M);
            n >>= 1;
        }
        
        return (ans[0][0] + ans[0][1]) % kMod;
    }
};
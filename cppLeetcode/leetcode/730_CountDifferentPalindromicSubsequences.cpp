/*
 
 730. Count Different Palindromic Subsequences
 
 Given a string S, find the number of different non-empty palindromic subsequences in S, and return that number modulo 10^9 + 7.

 A subsequence of a string S is obtained by deleting 0 or more characters from S.

 A sequence is palindromic if it is equal to the sequence reversed.

 Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.

 Example 1:
 Input:
 S = 'bccb'
 Output: 6
 Explanation:
 The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
 Note that 'bcb' is counted only once, even though it occurs twice.
 Example 2:
 Input:
 S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
 Output: 104860361
 Explanation:
 There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.
 Note:

 The length of S will be in the range [1, 1000].
 Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.

 */
#include <string>
#include <vector>

using std::vector;
using std::string;


class CountPalindromicSubsequences {

    /*
        730.Count-Different-Palindromic-Subsequences
        我们定义dp[i][j]为区间[i,j]内的不同的回文序列的个数。那么怎么区分不同的回文序列呢？可以采用层层剥离的思想，也就是分别考虑回文序列的最外层配对是'a','b','c','d'的四种情况.按照这种思路去分类的话，不同类之间的回文序列肯定是不会有重复的。也就是说dp[i][j]，可以拆分为：[i,j]区间里以字符k为最外层配对的回文数的和，其中k分别为'a','b','c','d'.

        dp[i][j]里以'a'为最外层配对的回文数怎么找呢？显然我们要把这个最外层配对找到，这是一定可以确定下来的。如果我们要找到i后面第一个为'a'的位置m，以及j前面第一个为'a'的位置n，并且m<n，显然就有递推的关系dp[i][j] += dp[m+1][n-1]，可以这么理解：拔掉了最外层的配对'a'，里面还有多少个回文数，就说明dp[i][j]有多少以'a'为最外层配对的回文数。同理我们可以找其他最外层配对的情况，也就是'b','c','d'。所以递推关系是：

        for (int k=0; k<4; k++)
        {
        if (next[i][k]<prev[j][k])  //小于号保证了这个配对一定是成双的
            dp[i][j] += dp[next[i][k]+1][prev[j][k]-1];
        }
        其中next[i][k]定义了i位置之后第一个为字符k的位置（可以是i本身），prev[j][k]定义了j位置之前第一个为字符k的位置（可以是j本身）。这两个next和prev数组可以预处理得到。

        上面的递推关系还有一个疏漏。如果[i,j]区间内没有以字符k的配对，但是有单独的一个字符k存在。这种情况也需要加进dp[i][j]的统计中去。所以完整的递推关系：

        for (int k=0; k<4; k++)
        {
        if (next[i][k]<prev[j][k])  //小于号保证了这个配对一定是成双的
            dp[i][j] += dp[next[i][k]+1][prev[j][k]-1];
        if (next[i][k]<=j)
            dp[i][j] += 1;
        }
        以上的语句再加上最外层对于i,j的大循环，即是完整的代码。最终的答案是dp[0][N-1]。

        本题其实也可以通过定义dp[i][j][k]三维状态数组来实现这个算法，最终输出是sum{k=0,1,2,3} dp[0][N-1][k]。但是空间上可能无法通过。
    */
    int countPalindromicSubsequences(string S) 
    {
        int N = S.size();
        auto dp = vector<vector<int>>(N,vector<int>(N,0));
        
        auto first = vector<vector<int>>(N,vector<int>(4,-1));
        auto last = vector<vector<int>>(N,vector<int>(4,-1));
        
        int MOD = 1e9+7;
        
        for (int len = 1; len<=N; len++)
            for (int i=0; i+len<=N; i++)
            {
                int j = i+len-1;
                
                if (first[i][S[j]-'a']==-1)
                    first[i][S[j]-'a'] = j;
                else
                    last[i][S[j]-'a'] = j;
                
                for (int k=0; k<4; k++)
                {
                    if (last[i][k]>=0)                    
                        dp[i][j]+=dp[first[i][k]+1][last[i][k]-1]+1;                    
                    if (first[i][k]>=0)
                        dp[i][j]+=1;                    
                    dp[i][j]%=MOD;
                }
            }
        
        return dp[0][N-1];
    }

    int countPalindromicSubsequences(string S) 
    {
        int M = 1e9+7;
        int N = S.size();
        auto next = vector<vector<int>>(N,vector<int>(4,N));
        auto prev = vector<vector<int>>(N,vector<int>(4,-1));        
        auto dp = vector<vector<int>>(N,vector<int>(N,0));  
        
        for (int k=0; k<4; k++)
        {
            int i = 0;
            for (int j=0; j<N; j++)
            {
                if (S[j]!='a'+k) continue;
                while (i<=j)
                {
                    next[i][k] = j;
                    i++;
                }
            }
        }
        
        for (int k=0; k<4; k++)
        {
            int i = N-1;
            for (int j=N-1; j>=0; j--)
            {
                if (S[j]!='a'+k) continue;
                while (i>=j)
                {
                    prev[i][k] = j;
                    i--;
                }
            }
        }
        
        for (int i=0; i<N; i++) dp[i][i]=1;
        
        for (int len = 2; len<=N; len++)
            for (int i=0; i<=N-len; i++)
            {
                int j = i+len-1;
                for (int k=0; k<4; k++)
                {
                    if (next[i][k]<prev[j][k])
                        dp[i][j]+=dp[next[i][k]+1][prev[j][k]-1]+1;
                    if (next[i][k]<=j)
                        dp[i][j]+=1;
                    dp[i][j] = dp[i][j]%M;
                }
            }
        return dp[0][N-1];
    }

public:
    
    int doit_dp_bottomup_best(string S) {
        int N = S.size();
        long MOD = 1e9 + 7;
        
        vector<vector<int>> T(N, vector<int>(N, 0));
        
        for (int i = 0; i < N; ++i)
            T[i][i] = 1;
        
        for (int gap = 1; gap < N; ++gap) {
            for (int i = 0, j = i+gap; j < N; ++i, ++j) {
                //Fill in T[i][j]
                if (S[i] != S[j]) {
                    T[i][j] = T[i+1][j] + T[i][j-1] - T[i+1][j-1];
                } else {
                    // Si, Si+1, ..., Sj-1, Sj
                    // Si+1, ...., Sj-1
                    T[i][j] = 2 * T[i+1][j-1];
                    
                    int l = i+1, r = j-1;
                    while(l <= r && S[l] != S[i])
                        l++;
                    while(l <= r && S[r] != S[i])
                        r--;
                    
                    if (l < r) {
                        // S(i, j) = b # # b . . b # # b where # != b, b + s[l+1][r-1] + b, duplicate with two outside b.
                        T[i][j] -= T[l+1][r-1];
                    }
                    
                    if (l == r) {
                        // S(i, j) = b # # b # # b where # != b, plus bb
                        T[i][j] += 1;
                    }
                    
                    if (l > r) {
                        // S(i, j) = b # # # b where # != b, plus b, bb
                        T[i][j] += 2;
                    }
                }
                T[i][j] = (T[i][j] + MOD)%MOD;
            }
        }
        
        return T[0][N-1];
    }

    
    int search(const string& S, int s, int e, vector<vector<int>>& dp) {
        
        int mod = 1e9+7;
        
        if (dp[s][e] != -1)
            return dp[s][e];
        
        if (e - s <= 2) {
            dp[s][e] = e - s;
            return e - s;
        }
        
        int cnt = 0;
        for (auto c : string("abcd")) {
            
            auto s1 = S.find(c, s);
            auto e1 = S.rfind(c, e-1);
            
            if (s1 == -1 && e1 == -1)
                continue;
            
            cnt += (e1 != s1) ? search(S, s1+1, e1, dp) + 2: 1;
        }
        
        dp[s][e] = cnt % mod;
        return cnt;
    }
    
    
    int doit_dp_dfs(string S) {
        
        auto N = S.length();
        vector<vector<int>> dp(N+1, vector<int>(N+1, -1));
        return search(S, 0, N, dp);
    }
};


void test_730_count_different_palindorme_subsequence() {
    
    CountPalindromicSubsequences().doit_dp_dfs(string("bccb"));
    
    CountPalindromicSubsequences().doit_dp_dfs(string("abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba"));
}

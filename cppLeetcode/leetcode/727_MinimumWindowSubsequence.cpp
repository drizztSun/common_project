/*
 727. Minimum Window Subsequence
 
 Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.

 If there is no such window in S that covers all characters in T, return the empty string "". If there are multiple such minimum-length windows, return the one with the left-most starting index.

 Example 1:

 Input:
 S = "abcdebdde", T = "bde"
 Output: "bcde"
 Explanation:
 "bcde" is the answer because it occurs before "bdde" which has the same length.
 "deb" is not a smaller window because the elements of T in the window must occur in order.
  

 Note:

 All the strings in the input will only contain lowercase letters.
 The length of S will be in the range [1, 20000].
 The length of T will be in the range [1, 100].
 */
#include<vector>
#include<string>

using std::string;
using std::vector;

class MinWindow {

    /*
                727.Minimum-Window-Subsequence
        对于双字符串的DP题，如果没有其他思路，不妨就考虑dp[i][j]代表了字符串A的前i个、字符串B的前j个的子问题，很大概率上就可以成功。

        在本题中，我们令 dp[i][j] 表示字符串T[1:i]是字符串S[k:j]的subsequence时、最短的[k:j]的长度，注意这个长度必须包括S串的j位置往前算起。最终的答案是在dp[N][j] (j=1,2,...M)中找最小的。

        和很多字符串的DP题一样，动态转移方程很套路，根据 T[i]==S[j]分别考虑即可：

        for (int i=1; i<=N; i++)
        for (int j=1; j<=M; j++)
        {
            if (T[i]==S[j])
            dp[i][j]=dp[i-1][j-1]+1;
            else
            dp[i][j]=dp[i][j-1]+1; //说明S[j]没有帮助，还要依靠dp[i][j-1]
        }
        然后我们考虑边界条件。易知 dp[0][j] (i=0, j=1,2,...M) 都是要考虑的。长度为0的T子串肯定是任意S子串的subsequence。故这些初始值应该是0.

        另外可以看出 dp[i][0] (i=1,2,...,N, j=0)也是需要提前设置初始值。显然，长度不为0的T子串不是任何空字串的subsequence，故这些值应该是inf.

        最后在所有dp[N][j]中找到第一个最小值k，那么 S.substr(j-k+1,k)就是答案。
    */
    string minWindow(string S, string T) 
    {
        int m = S.size();
        int n = T.size();
        S = "#"+S;
        T = "#"+T;
        auto dp = vector<vector<int>>(m+1,vector<int>(n+1,0));
        
        for (int j=1; j<=n; j++)
            dp[0][j] = INT_MAX/2;

        for (int i=0; i<=m; i++)
            dp[i][0] = 0;
        
        for (int i=1; i<=m; i++)
            for (int j=1; j<=n; j++)
            {
                if (S[i]==T[j])
                    dp[i][j] = dp[i-1][j-1]+1;
                else
                    dp[i][j] = dp[i-1][j]+1;
            }
        
        int len  = INT_MAX/2;
        int pos;
        for (int i=1; i<=m; i++)
        {
            if (dp[i][n] < len)
            {
                len = dp[i][n];
                pos = i;
            }
        }
        
        return len >= INT_MAX/2 ? "" : S.substr(pos-len+1,len); 
    }

public:
    
    string doit_dp_str(string S, string T) {
        
        auto N = S.length();
        vector<int> cur(N, N);
        
        for (auto i = 0; i < N; i++) {
            if (S[i] == T[0])
                cur[i] = i;
        }
        
        for (auto i = 1; i < T.length(); i++) {
            
            vector<int> next(N, N);
            auto last = N;
            for (auto j = 0; j < N; j++) {
                
                if (T[i] == S[j] && last != N) {
                    next[j] = last;
                }
                
                if (cur[j] != N) {
                    last = cur[j];
                }
            }
            cur = next;
        }
        
        int s = -1, l = N+1;
        for (auto i = 0; i < N; i++) {
            if (cur[i] != N && i - cur[i] + 1 < l) {
                s = cur[i], l = i - cur[i] + 1;
            }
        }
        
        return l == N+1 ? "" : S.substr(s, l);
    }
    
    string doit_dp_it(string S, string T) {
        int minLen = -1;
        int start, end, ti = 0, st;
        
        for (int i = 0; i < S.length(); i++) {
            if (S[i] == T[ti]) {
                if (ti == 0) st = i;
                ti++;
            
                if (ti == T.length()) {
                    ti--;
                    
                    for (int j = i; j >= st; j--) {
                        
                        if (S[j] == T[ti]) {
                            ti--;
                            
                            if (ti < 0) {
                                if (minLen == -1 || minLen > i - j + 1) {
                                    start = j;
                                    end = i;
                                    minLen = i - j + 1;
                                }
                                ti = 0;
                                i = j + 1;
                                break;
                            }
                        }
                    }
                }
                
            }
        }
        
        if (minLen == -1) return "";
        
        return string(S, start, minLen);
    }
};
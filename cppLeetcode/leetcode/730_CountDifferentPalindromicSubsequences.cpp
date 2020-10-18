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
public:
    
    int doit_dp(string S) {
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

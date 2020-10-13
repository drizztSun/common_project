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
public:
    string doit_dp(string S, string T) {
        
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


void test_727_minimum_windows_subsequence() {
    
    MinWindow().doit_dp("abcdebdde", "bde");
}

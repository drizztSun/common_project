/*
 
 1531. String Compression II
 
 
 Run-length encoding is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times)
 with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "aabccc"
 we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes "a2bc3".

 Notice that in this problem, we are not adding '1' after single characters.

 Given a string s and an integer k. You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.

 Find the minimum length of the run-length encoded version of s after deleting at most k characters.

  

 Example 1:

 Input: s = "aaabcccd", k = 2
 Output: 4
 Explanation: Compressing s without deleting anything will give us "a3bc3d" of length 6. Deleting any of the characters 'a' or 'c' would at most decrease the length of the compressed string to 5, for instance delete 2 'a' then we will have s = "abcccd" which compressed is abc3d. Therefore, the optimal way is to delete 'b' and 'd', then the compressed version of s will be "a3c3" of length 4.
 Example 2:

 Input: s = "aabbaa", k = 2
 Output: 2
 Explanation: If we delete both 'b' characters, the resulting compressed string would be "a4" of length 2.
 Example 3:

 Input: s = "aaaaaaaaaaa", k = 0
 Output: 3
 Explanation: Since k is zero, we cannot delete anything. The compressed string is "a11" of length 3.
  

 Constraints:

 1 <= s.length <= 100
 0 <= k <= s.length
 s contains only lowercase English letters.

 
 */

#include <stdio.h>
#include <string>
#include <vector>


using std::vector;
using std::string;



class StringCompressionII {
    
public:
    
    /*
     
     Can we do beter? Do we really need a 4 dimensional state?
     
     We need last/running length because the unsolved subproblem rely on that.
     what if we remove the dependency by making one group if same characters at a time?
     
     dp(i, k) := min length to encode s[i:] with at most k deletions.
     
     Trasition: keep / delete
     
     delete: dp(i, k) = dp(i+1, k-1)
     
     keep:
     Use s[i] as an anchor, scan from i tp n, for s[i~j], we need to remove all other characters other then s[i] to form a group.
     
     dp(i, k) = encode_len(sum(s[i~j] == s[i]) + dp(j+1, k-(s[i~j] != s[i]))
     
     Subproblems: O(n*k), each takes O(n) time.
     
     dp[i][k] := min len of s[i:] encoded by deleting at most k charchters.

     dp[i][k] = min(dp[i+1][k-1] # delete s[i]
     encode_len(s[i~j] == s[i]) + dp(j+1, k – sum(s[i~j])) for j in range(i, n)) # keep

     Time complexity: O(n^2*k)
     Space complexity: O(n*k)
     */
    
    int doit_dp(string s, int k) {
        const int n = s.length();
        vector<vector<int>> cache(n, vector<int>(k + 1, -1));
        
        std::function<int(int, int)> dp = [&](int i, int k) -> int {
          if (k < 0)
              return n;
          
          if (i + k >= n)
              return 0;
          
          int& ans = cache[i][k];
          if (ans != -1)
              return ans;
          
          ans = dp(i + 1, k - 1); // delete
          int len = 0;
          int same = 0;
          int diff = 0;
            
          for (int j = i; j < n && diff <= k; ++j) {
            if (s[j] == s[i] && ++same) {
              if (same <= 2 || same == 10 || same == 100) ++len;
            } else {
              ++diff;
            }
            ans = std::min(ans, len + dp(j + 1, k - diff));
          }
          return ans;
        };
        return dp(0, k);
    }
        
        
    
    /*
     Run legnth encoding encode(aaabbc) +> a3b2c
     
     Observation 1: len(encode(s)) <+ len(s)
     encode(a) = a
     encode(aa) = a2
     encode(aaa) = a3
     encode(aaaaaaaaa) = a9
     encode(aaaaaaaaaa) = a10
     
     Observation 2: the more deletion the shorter the cnoded string.
     
     Solution 0. Brute Force
     Combination, choose k fro n to delete
     
     O(C(n, k)) = O(n!/k!/(n-k)!) TLE 12/132 passed
     
     */
    int doit_dfs_bruteforce(string s, int k) {
        const int n = s.length();
        auto encode = [&]()-> int {
            char p = '$';
            int count = 0;
            int len = 0;
            for (char c : s) {
                if (c == '.') continue;
                if (c != p) {
                    p = c;
                    count = 0;
                }
                ++count;
                if (count <= 2 || count == 10 || count == 100) ++len;
            }
            
            return len;
        };
        
        std::function<int(int, int)> dfs = [&](int start, int k) -> int {
            if (start == n || k == 0) return encode();
            
            int ans = n;
            for (int i = start; i < n; ++i) {
                char c = s[i];
                s[i] = '.'; //delete
                ans = std::min(ans, dfs(i+1, k-1));
                s[i] = c;
            }
            return ans;
        };
        
        return dfs(0, k);
    }
    
    /*
     Optimal decision problem => DP similar to LC 546. Remove Boxes State:
     
     1. i: current index
     2. k: # of chars to remove
     3. p: previous character
        l: Running legnth of the last character.
     
     dp(state) := min len of s[i:] encoded, given the current state.
     
     Transition for dp(i, k, p, l)
     
     1. Delete := dp(i+1, k-1, p, l)
     
     2. Keep:
        
        if s[i] == p
            carry + dp(i+1, k, p, l+1)
        else:
            dp(i+1, k, s[i], 1)
     
     State:
     i: the start index of the substring
     last: last char
     len: run-length
     k: # of chars that can be deleted.

     base case:
     1. k < 0: return inf # invalid
     2. i >= s.length(): return 0 # done

     Transition:
     1. if s[i] == last: return carry + dp(i + 1, last, len + 1, k)

     2. if s[i] != last:
     return min(1 + dp(i + 1, s[i], 1, k, # start a new group with s[i]
     dp(i + 1, last, len, k -1) # delete / skip s[i], keep it as is.

     Time complexity: O(n^3*26)
     Space complexity: O(n^3*26)


     */
    int doit_dp(string s, int k) {
          vector<vector<vector<vector<int>>>> cache(101, vector<vector<vector<int>>>(27, vector<vector<int>>(101, vector<int>(101, -1))));
          // Min length of compressioned string of s[i:]
          // 1. last char is |last|
          // 2. current run-length is len
          // 3. we can delete k chars.
          std::function<int(int, int, int, int)> dp = [&](int i, int last, int len, int k) {
            if (k < 0)
                return INT_MAX / 2;
            if (i >= s.length())
                return 0;
            
            int& ans = cache[i][last][len][k];
            if (ans != -1)
                return ans;
            
            if (s[i] - 'a' == last) {
              // same as the previous char, no need to delete.
              int carry = (len == 1 || len == 9 || len == 99);
              ans = carry + dp(i + 1, last, len + 1, k);
            } else {
              ans = std::min(1 + dp(i + 1, s[i] - 'a', 1, k),  // keep s[i]
                            dp(i + 1, last, len, k - 1)); // delete s[i]
            }
            return ans;
          };
        
          return dp(0, 26, 0, k);
    }
};

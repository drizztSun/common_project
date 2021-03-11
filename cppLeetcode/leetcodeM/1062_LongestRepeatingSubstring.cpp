/*
1062. Longest Repeating Substring

Given a string S, find out the length of the longest repeating substring(s). Return 0 if no repeating substring exists.

 

Example 1:

Input: S = "abcd"
Output: 0
Explanation: There is no repeating substring.
Example 2:

Input: S = "abbaba"
Output: 2
Explanation: The longest repeating substrings are "ab" and "ba", each of which occurs twice.
Example 3:

Input: S = "aabcaabdaab"
Output: 3
Explanation: The longest repeating substring is "aab", which occurs 3 times.
Example 4:

Input: S = "aaaaa"
Output: 4
Explanation: The longest repeating substring is "aaaa", which occurs twice.
 

Constraints:

The string S consists of only lowercase English letters from 'a' - 'z'.
1 <= S.length <= 1500



*/
#include <string>
#include <unordered_set>
#include <vector>


using std::vector;
using std::unordered_set;
using std::string;


class LongestRepeatingSubstring {

public:

    /*
        1062.Longest-Repeating-Substring
        解法1： DP
        此题和1044.Longest-Duplicate-Substring一模一样，唯一的区别是数据范围更小一些，因此可以用o(N^2)的DP算法。

        我们将S分别看做S1和S2，那么此题就变成求两个字符串的longest common substring. 我们令dp[i][j]表示以S1[i]结尾、S2[j]结尾的最长的字符串的长度。则有状态转移方程：

        if (S[i]==S[j]) dp[i][j] = dp[i-1][j-1] + 1;
        特别注意，还要加上限制条件if (i!=j)

        解法2： Rolling Hash
        High Level是二分搜值，猜测这个longest repeating substring的长度是多少。如果我们找不到任何长度为len的substring在S中出现过多次，那么就往下猜len；否则就往上猜len。

        对于上述的子问题，我们会考虑一个固定长度len的滑窗，掠过整个S。在每个位置上的滑窗，我们都将里面的字符串映射成一个26进制的数，当做hash key放入集合中。如果发现这个key已经在集合中出现过，
        就意味着存在两个完全相同的子串。注意这个hash key会很大，所以需要取一个大数的模。当然，这肯定会有collision的风险。
    */

    int doit_rolling_hash_binary_search(string S) 
    {
        int left = 1, right = S.size()-1;
        auto found = [&](int len)
        {
            long base = 26;
            long mod = 1e9+7;
            long hash = 0;
            long pow_base_len = 1;
            unordered_set<long>Set;
            for (int i = 0; i < len; i++)
                pow_base_len = pow_base_len*base % mod;
            
            for (int i = 0; i < S.size(); i++)
            {
                hash = (hash * base + S[i] - 'a') % mod;
                if (i >= len)
                    hash = (hash - pow_base_len * (S[i-len] - 'a') % mod + mod) % mod;
                
                if (i >= len-1)
                {
                    if (Set.find(hash)!=Set.end())
                        return true;
                    Set.insert(hash);
                }
            }
            return false;
        };

        while (left < right) {
            int mid = right-(right-left)/2; 
            // left + (right - left) / 2, but left = 0, right = 1. it is deadloop based on below left, rght.
            if (found(mid)) // [left, right] two closed range
                left = mid;  // including mid, it is a valid value
            else
                right = mid-1; // mid is not valid value.
        }

        return found(left) ? left : 0;
    }

    int doit_rolling_hash_binary_search_1(string S) 
    {
        int left = 1, right = S.size();
        auto found = [&](int len)
        {
            long base = 26;
            long mod = 1e9+7;
            long hash = 0;
            long pow_base_len = 1;
            unordered_set<long>Set;
            for (int i = 0; i < len; i++)
                pow_base_len = pow_base_len*base % mod;
            
            for (int i = 0; i < S.size(); i++)
            {
                hash = (hash * base + S[i] - 'a') % mod;
                if (i >= len)
                    hash = (hash - pow_base_len * (S[i-len] - 'a') % mod + mod) % mod;
                
                if (i >= len-1)
                {
                    if (Set.find(hash)!=Set.end())
                        return true;
                    Set.insert(hash);
                }
            }
            return false;
        };

        while (left <= right) {

            int mid = left + (right-left) / 2; 
            
            if (found(mid)) 
                left = mid + 1;
            else
                right = mid - 1;
        }

        return left - 1;
    }

    int doit_dp(string S) {
        
        int n = S.size();
        S = "#"+S;
        auto dp = vector<vector<int>>(n+1,vector<int>(n+1,0));
        int ret = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                if (i != j && S[i] == S[j]) {
                    dp[i][j] = dp[i-1][j-1]+1;
                    ret = std::max(ret, dp[i][j]);
                }
        }
        return ret;
    }
};
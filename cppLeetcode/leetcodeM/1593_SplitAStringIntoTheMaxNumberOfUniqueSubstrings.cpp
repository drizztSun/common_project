/*
 1593. Split a String Into the Max Number of Unique Substrings
 
 Given a string s, return the maximum number of unique substrings that the given string can be split into.

 You can split string s into any list of non-empty substrings, where the concatenation of the substrings forms the original string.
 However, you must split the substrings such that all of them are unique.

 A substring is a contiguous sequence of characters within a string.

  

 Example 1:

 Input: s = "ababccc"
 Output: 5
 Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.
 Example 2:

 Input: s = "aba"
 Output: 2
 Explanation: One way to split maximally is ['a', 'ba'].
 Example 3:

 Input: s = "aa"
 Output: 1
 Explanation: It is impossible to split the string any further.
  

 Constraints:

 1 <= s.length <= 16

 s contains only lower case English letters.
 
 */
#include <unordered_set>
#include <string>
#include <functional>

using std::string;
using std::unordered_set;


class SplitStringIntoUniqueSubstrings {

    /*
                1593.Split-a-String-Into-the-Max-Number-of-Unique-Substrings
        本题并没有巧解，只能暴力枚举判断。DFS来搜索分组的方案是比较可行的方法。如果遇到当前分组不满足条件时，就可以终止剩余字符的分组。

        注意，不要试图用状态压缩来暴力枚举判断。因为它无法实现DFS的提前剪枝。
    */
    int ret = 0;    
    unordered_set<string>Set;

    int maxUniqueSplit(string s) 
    {
        int n = s.size();
        dfs(s,0,0);
        return ret;
    }
    void dfs(string&s, int cur, int len)
    {
        if (cur==s.size())
        {
            ret = max(ret, len);
            return;
        }
        if (s.size()-cur + len <= ret)
            return;

        for (int i=cur; i<s.size(); i++)
        {
            if (Set.find(s.substr(cur, i-cur+1))==Set.end())
            {
                Set.insert(s.substr(cur, i-cur+1));
                dfs(s, i+1, len+1);
                Set.erase(s.substr(cur, i-cur+1));
            }            
        }
    }

public:
    
    int doit_dfs_backtracking(string s) {
        
        unordered_set<string> Set;
        int ans = 0;
        
        std::function<void(int, int)> dfs = [&](int cutidx, int length) {
            
            if (cutidx == s.length()) {
                ans = std::max(ans, length);
                return;
            }
            
            if (length + s.length() - cutidx < ans) return;

            for (int i = cutidx; i < s.length(); i++) {
                
                string cut = s.substr(cutidx, i - cutidx+1);
                if (Set.find(cut) == Set.end()) {
                    Set.insert(cut);
                    dfs(i+1, length+1);
                    Set.erase(cut);
                }
            }
        };
        
        dfs(0, 0);
        
        return ans;
    }
};
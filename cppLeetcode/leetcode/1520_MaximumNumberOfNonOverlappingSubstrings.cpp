/*
 1520. Maximum Number of Non-Overlapping Substrings
 
 Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:

 The substrings do not overlap, that is for any two substrings s[i..j] and s[k..l], either j < k or i > l is true.
 A substring that contains a certain character c must also contain all occurrences of c.
 Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings,
 return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.

 Notice that you can return the substrings in any order.



 Example 1:

 Input: s = "adefaddaccc"
 Output: ["e","f","ccc"]
 Explanation: The following are all the possible substrings that meet the conditions:
 [
   "adefaddaccc"
   "adefadda",
   "ef",
   "e",
   "f",
   "ccc",
 ]
 If we choose the first string, we cannot choose anything else and we'd get only 1.

 If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings.
 Notice also, that it's not optimal to choose "ef" since it can be split into two.
 Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
 Example 2:

 Input: s = "abbaccd"
 Output: ["d","bb","cc"]
 Explanation: Notice that while the set of substrings ["d","abba","cc"] also has length 3, it's considered incorrect since it has larger total length.


 Constraints:

 1 <= s.length <= 10^5
 s contains only lowercase English letters.
 
 */
#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;


class MaximumNumberNonOverlappingSubstrings {
    
public:
    
    vector<string> doit_gready(string s) {
        
        
        unordered_map<char, std::pair<int, int>> pos;
        for (auto i = 0; i < s.length(); i++) {
            if (pos.count(s[i]) == 0) {
                pos.insert({s[i], {i, i}});
            } else {
                pos[s[i]].second = i;
            }
        }
        
        auto extend = [&](int i) -> int {
            
            int j = i, p = pos[s[i]].second;
            
            while (j < p) {
                
                auto c = pos[s[j]];
                if (c.first < i)
                    return -1;
                if (c.second > p)
                    p = c.second;
                j++;
            }
            return p;
        };
        
        vector<string> res;
        int last = -1;
        
        for (auto i = 0; i < s.length(); i++) {
            
            if (i != pos[s[i]].first)
                continue;
            
            int r = extend(i);
            if (r == -1)
                continue;
            
            if (last < i)
                res.push_back(s.substr(i, r-i+1));
            else if (r-i+1 < res.back().length())
                res.back() = s.substr(i, r-i+1);
            
            last = r;
        }
        
        return res;
    }
    
    vector<string> maxNumOfSubstrings(string s) {
        int count[26] = {0};
        for (auto c : s) ++count[c-'a'];
        
        bool pre[26] = {false};
        bool visited[26] = {false};
        vector<std::pair<int, int>> v;
        
        for (int i = 0; i < s.size(); ++i) {
            if (pre[s[i]-'a']) continue;

            for (int j = i, c = 0; j < s.size(); ++j) {
                int index = s[j] - 'a';
                if (!visited[index] && pre[index]) break;
            
                if (!visited[index]) {
                    c += count[index];
                    visited[index] = true;
                }
            
                if (--c == 0) {
                    v.push_back({i, j});
                    break;
                }
            }
            
            pre[s[i]-'a'] = true;
            memset(visited, false, sizeof(visited));
        }
        
        
        std::sort(v.begin(), v.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second-a.first < b.second-b.first;
        });
        
        vector<string> ans;
        vector<std::pair<int, int>> res;
        
        for (auto& n : v) {
            bool skip = false;
            for (auto& r : res) {
                if (r.first <= n.second && r.second >= n.first) {
                    skip = true;
                    break;
                }
            }
            
            if (!skip) {
                res.push_back(n);
                ans.push_back(s.substr(n.first, n.second-n.first+1));
            }
        }
        
        return ans;
    }
};

/*
 1520. Maximum Number of Non-Overlapping Substrings
 
 Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:

  .The substrings do not overlap, that is for any two substrings s[i..j] and s[k..l], either j < k or i > l is true.
  .A substring that contains a certain character c must also contain all occurrences of c.

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
#include <vector>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;


class MaximumNumberNonOverlappingSubstrings {

    /*
        1520.Maximum-Number-of-Non-Overlapping-Substrings
        考虑一个substring里面，如果出现了字母a，那么所有字母a必须出现在这个substring中，一个直接的想法是，这个substring必然要跨越a出现的所有位置。也就是说起始点必然是start['a']，截止点必然至少是end['a']（可能更靠后，下面会解释）。于是我们的注意力就集中在了26个substring上，他们就是以每个字母最早和最晚出现的位置为跨度的字符串。

        但是显然并不是上面26种substring都是符合题目中第二个条件的。假设第一个a在第1个位置，最后一个a在第10个位置；但是同时有第一个b在第5个位置，最后一个b在第15个位置。所以当我们考虑以第一个a为起始的字符串时（left=1），此时[1,10]的区间内包含了字母b，所以我们不得不把区间的右端点后移，至少要移动到end['b']的位置。于是我们就一路往后遍历，不断拓展右边界，直到找到一个right，使得[left,right]所包含的所有字母的start/end都在这个区间内。

        我们重复利用这个策略，就可以得到26种符合第二个条件的substring，他们的起始点分别是第一个a、第一个b、第一个c...所谓“符合第二个条件”就是题意中的 A substring that contains a certain character c must also contain all occurrences of c。注意，实现这个的时间复杂度是o(26N).

        接下来特别注意，这（最多）26种substring，要么互斥，要么互相嵌套，不可能出现部分相交的情况。（Why？假设有两个按照上述规则生成的合法区间ABC和BCD，而之所以BCD成立是因为BC本身必定不是合法的必须延伸到D，那么这与ABC本身已经合法相互矛盾。）对于互相嵌套的区间，根据题意 If there are multiple solutions with the same number of substrings, return the one with minimum total length. 我们再两两比较一下每对区间，将互相嵌套的大区间都排除即可。
    */
    static bool cmp(vector<int>&a, vector<int>&b)
    {
        return a[1]-a[0] < b[1]-b[0];
    }
public:
    vector<string> maxNumOfSubstrings(string s) 
    {
        vector<int>start(26,-1);
        vector<int>end(26,-1);
        for (int i=0; i<s.size(); i++) 
            if (start[s[i]-'a']==-1) start[s[i]-'a'] = i;
        for (int i=s.size()-1; i>=0; i--) 
            if (end[s[i]-'a']==-1) end[s[i]-'a'] = i;
        
        vector<vector<int>>intervals;
        for (int i=0; i<26; i++)
        {
            if (start[i]==-1) continue;
            int left = start[i], right = end[i];
            bool valid = true;
            for (int k=left; k<=right; k++)
            {
                if (start[s[k]-'a']==-1) continue;
                if (start[s[k]-'a'] < left)
                {
                    valid = false;
                    break;
                }
                right = std::max(right, end[s[k]-'a']);
            }
            if (valid) intervals.push_back({left, right});
        }
        
        std::sort(intervals.begin(), intervals.end(), cmp); 
        vector<int>flags(intervals.size(),1);

        for (int i=0; i<intervals.size(); i++)
        {
            if (flags[i]==0) continue;
            for (int j=i+1; j<intervals.size(); j++)
            {                
                if (flags[j]!=0 && intervals[i][0]>intervals[j][0] && intervals[i][1]<intervals[j][1])                
                    flags[j] = 0;                
            }
        }

        vector<string> ret ;
        for (int i=0; i<intervals.size(); i++)
            if (flags[i]) ret.push_back(s.substr(intervals[i][0], intervals[i][1]-intervals[i][0]+1));

        return ret;
    }
    
public:
    
    vector<string> doit_greedy(string s) {
        
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

/*
 691. Stickers to Spell Word
 
 
 We are given N different types of stickers. Each sticker has a lowercase English word on it.

 You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them.

 You can use each sticker more than once if you want, and you have infinite quantities of each sticker.

 What is the minimum number of stickers that you need to spell out the target? If the task is impossible, return -1.

 Example 1:

 Input:

 ["with", "example", "science"], "thehat"
 Output:

 3
 Explanation:

 We can use 2 "with" stickers, and 1 "example" sticker.
 After cutting and rearrange the letters of those stickers, we can form the target "thehat".
 Also, this is the minimum number of stickers necessary to form the target string.
 Example 2:

 Input:

 ["notice", "possible"], "basicbasic"
 Output:

 -1
 Explanation:

 We can't form the target "basicbasic" from cutting letters from the given stickers.
 Note:

 stickers has length in the range [1, 50].
 stickers consists of lowercase English words (without apostrophes).
 target has length in the range [1, 15], and consists of lowercase English letters.
 In all test cases, all words were chosen randomly from the 1000 most common US English words, and the target was chosen as a concatenation of two random words.
 The time limit may be more challenging than usual. It is expected that a 50 sticker test case can be solved within 35ms on average.

 */
#include<vector>
#include<unordered_map>
#include<string>
#include<unordered_set>
#include<queue>

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::queue;

class MinStickers {
    
public:
    
    void dfs(const vector<string>& stickers, const string& target, unordered_map<char, int>& buff, int c, int p, unordered_map<char, int>& targetbuf, int& res) {
        
        if (p == target.length()) {
            if (res == -1 || res > c) {
                res = c;
            }
            return;
        }
        
        if (buff[target[p]] >= targetbuf[target[p]]) {
            dfs(stickers, target, buff, c, p+1, targetbuf, res);
            return;
        }
        
        if (res != -1 && c >= res)
            return;
            
        for(auto& stick : stickers) {
            if (stick.find(target[p]) != -1) {
                for (auto c : stick) {
                    buff[c]++;
                }
                
                dfs(stickers, target, buff, c+1, p+1, targetbuf, res);
                
                for (auto c : stick) {
                    buff[c]--;
                }
            }
        }
    }
    
    int doit_dfs(vector<string>&& stickers, string target) {
    
        unordered_map<char, int> buff, targetbuff;
        for (auto c: target) {
            targetbuff[c]++;
        }
        
        int res = -1;
        dfs(stickers, target, buff, 0, 0, targetbuff, res);
        return res;
    }
    
    
    
    int doit_bfs(vector<string>& stickers, string target) {
        
        int m = stickers.size(), n = target.size();
        vector<vector<int> > map(m, vector<int>(26));
        for (int i = 0; i < m; i++)
          for (char c : stickers[i])
              map[i][c - 'a']++;

        // check if cur_target has been visited
        unordered_set<int> vis;

        // BFS
        // store the bit representation of target string
        queue<int> q;
        
        // target at the beginning: all bits set to 1
        q.push((1 << n) - 1);
        int level = 0;
        
        while (!q.empty()) {
            
          ++level;
          for (int sz = q.size(); sz > 0; --sz) {
              
            int cur_target = q.front();
            q.pop();
            
            // check if cur_target has been visited
            if (vis.count(cur_target))
                continue;
            vis.insert(cur_target);
            
            // the starting point from the right that need to be eliminated
            // because we always try to remove the right most char first (heuristic,
            // see below)
            int start = 0;
            while (start < n) {
              if ((cur_target >> start) & 1)
                  break;
              ++start;
            }

            for (int i = 0; i < m; ++i) {  // try all stickers
              // heuristic (this is the key speedup, we try stickers with char
              // target[n-1-start] first, so we always can remove the right most
              // char in cur_target)
              if (map[i][target[n - 1 - start] - 'a'] == 0)
                  continue;
                
              int next_target = cur_target;
              
                // try every char in stickers[i], delete it from cur_target
              for (char c : stickers[i]) {
                for (int r = start; r < n; r++) {  // delete from right to left
                  if (target[n - 1 - r] == c && ((next_target >> r) & 1)) {
                    next_target ^= (1 << r);
                    break;
                  }
                }
              }
                
              if (next_target == 0)
                  return level;
              
               q.push(next_target);
            }
          }
        }
        return -1;
      }
    
    
    int minStickers(vector<string>& stickers, string target) {
        int m = stickers.size();
        vector<vector<int>> mp(m, vector<int>(26, 0)); // word count for each sticker
        unordered_map<string, int> dp;
        // count characters a-z for each sticker
        for (int i = 0; i < m; i++)
            for (char c:stickers[i]) mp[i][c-'a']++;
        dp[""] = 0;
        return helper(dp, mp, target);
    }
private:
    int helper(unordered_map<string, int>& dp, vector<vector<int>>& mp, string target) {
        if (dp.count(target))
            return dp[target];
        
        int ans = INT_MAX, n = mp.size();
        vector<int> tar(26, 0);
        
        for (char c : target)
            tar[c-'a']++;
        
        // try every sticker
        for (int i = 0; i < n; i++) {
            // optimization
            if (mp[i][target[0]-'a'] == 0)
                continue;
            
            string s;
            // figure out what characters left after applying i-th sticker
            for (int j = 0; j < 26; j++)
                if (tar[j]-mp[i][j] > 0)
                    // build sorted array after applying i-th sticker
                    s += string(tar[j]-mp[i][j], 'a'+j);
            
            int tmp = helper(dp, mp, s);
            if (tmp != -1)
                ans = std::min(ans, 1+tmp);
        }
        
        dp[target] = ans == INT_MAX? -1 : ans;
        return dp[target];
    }
};

void Test_691_StickersToSpellWord() {
    
    MinStickers().doit_dfs(vector<string>{"with", "example", "science"}, "thehat"); // 3
    
    MinStickers().doit_dfs(vector<string>{"notice", "possible"},  "basicbasic");
}

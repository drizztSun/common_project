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
#include <vector>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <queue>
#include <functional>

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::queue;

class MinStickers {

    /*
        691.Stickers-to-Spell-Word
        设置状态数组dp[i],dp的大小是 N = 2^n, 其中n是target的大小。怎么理解？将dp的索引i进行二进制拆解，i的每一个bit表示的是target对应位置的字符是否得到了满足。比如n=3时，dp数组的大小N=8，对应的状态有 000,001,010,011,100,101,110,111. 举个例子，i=3 (即011)表示target的末两位的字符得到了满足，但第一位的字符还没有得到满足。dp[i]表示在状态i下，需要的sticker的最少数目。

        注意：这种状态的排列有一个非常好的性质。任何状态，只可能由位于其前面的状态转移得到，不可能从后面的状态转移得到。比如i=3(即 011)这个状态，只可能从i=0,1,2转移过来（通过使用某些合适的sticker）；再比如i=4(即100)这个状态，只可能从i=0转移过来。这种状态转移的性质，非常适合dp根据i从前往后的遍历。

        所以，dp的大循环就是 for (state=0; state<(1<<n); state++). 对于该状态state，我们尝试每一个sticker[k]，计算状态i经过sticker[k]的帮助后得到的状态new_state（注意已经分析过new_state肯定是大于state的），那么dp[new_state]就可以得到更新dp[new_state]=min(dp[new_state], dp[state]+1)

        所有的状态i都遍历过之后，答案的输出就是 dp[N-1]
    */
    int minStickers(vector<string>& stickers, string target) 
    {
        int n = target.size();
        vector<int>dp(1<<n,INT_MAX);
        dp[0] = 0;

        for (int state=0; state<(1<<n); state++)
        {
            if (dp[state]==INT_MAX) continue;
            for (string str:stickers)
            {
                int new_state = findNextStatusByUsingStr(state,target,str);
                dp[new_state] = std::min(dp[new_state], dp[state]+1);
            }
        }
        return dp[(1<<n)-1]==INT_MAX?-1: dp[(1<<n)-1];
    }
    
    int findNextStatusByUsingStr(int status, string target, string s)
    {
        int n = target.size();
        for (auto ch:s)
        {
            // loop over each character in target, if equals to ch and not filled, then set as filled
            for (int k=0; k<n; k++)
            {
                if (((status>>k)&1)==0 && target[k]==ch)
                {
                    status = status+(1<<k);   
                    break;
                }
            }
        }
        return status;
    }
    
public:

    int doit_dfs_TLE(vector<string>&& stickers, string target) {
    
        unordered_map<char, int> buff, targetbuf;
        for (auto c: target) targetbuf[c]++;
        
        int res = -1;

        std::function<void(int, int)> dfs = [&](int c, int p){
            
            if (p == target.length()) {
                if (res == -1 || res > c) {
                    res = c;
                }
                return;
            }
            
            if (buff[target[p]] >= targetbuf[target[p]]) {
                dfs(c, p+1);
                return;
            }
            
            if (res != -1 && c >= res)
                return;
                
            for(auto& stick : stickers) {
                if (stick.find(target[p]) != -1) {
                    for (auto chr : stick) {
                        buff[chr]++;
                    }
                    
                    dfs(c+1, p+1);
                    
                    for (auto chr : stick) {
                        buff[chr]--;
                    }
                }
            }
        };

        dfs(0, 0);
        return res;
    }
    
public:
    
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
                if (vis.count(cur_target)) continue;
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
                
                if (next_target == 0) return level;
              
                q.push(next_target);
                }
            }
        }

        return -1;
    }
    
public:

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
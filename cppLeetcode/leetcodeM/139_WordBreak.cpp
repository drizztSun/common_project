/*
139. Word Break

Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 

Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.

*/

#include <vector>
#include <unordered_set>
#include <string>
#include <functional>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;
using std::unordered_set;


class Solution {

    /*
        139.Word-Break
        此题只要能想到用DP来做,就是成功的关键.

        解法1： DP
        本题和322.Coin Change很相似，令dp[i]表示前i个字符是否能够break成功。转移方法是找到一个小于i的序号j,使得s[j:i]恰是一个单词，并且dp[j-1]也能成功。所以遍历一下j即可。

        初始条件需要稍微注意一下.此题里,改成1-index更加方便,这样初始条件就是dp[0]需要设置为True即可.

        补充：相比于在内层循环中遍历j的位置，有一种更高效的方法。就是在内存循环中遍历wordDict，查看是否有任何一个单词word能够匹配s[0:i]的后缀。这种解法在s很长而wordDict很小的情况下，优势非常明显。

        解法2：DFS+Trie
        我们将所有的单词构建一棵字典树。我们从前往后遍历字符串，如果发现字符串的某段前缀[0:i]对应着Trie中的一个单词，那么我们就可以从对前缀之后的子串[i+1:n-1]进行递归处理。直至发现恰好递归到字符串尾部。

        注意DFS要配合记忆化使用，用memo[i]来标记[i:n-1]是否能够已经失败过。
    */
    bool wordBreak_dp(string s, vector<string>& wordDict) 
    {
        int N = s.size();
        s = "#"+s;
        vector<bool>dp(N+1,0);
        
        dp[0] = true;
        
        for (int i=1; i<=N; i++)
        {
            // updaet dp[i]
            for (auto x: wordDict)
            {
                if (i>=x.size() && s.substr(i-x.size()+1,x.size())==x && dp[i-x.size()])
                {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[N];
    }


public:

    class TrieNode
    {
        public:
        TrieNode* next[26];
        bool end;
        TrieNode()
        {
            end = false;
            for (int i=0;i<26;i++)
                next[i] = NULL;
        }
    };
    TrieNode* root;
    int memo[300];

    bool wordBreak(string s, vector<string>& wordDict) 
    {
        root = new TrieNode();
        for (auto word: wordDict)
        {
            TrieNode* node = root;
            for (auto ch: word)
            {
                if (node->next[ch-'a']==NULL)
                    node->next[ch-'a'] = new TrieNode();
                node = node->next[ch-'a'];
            }
            node->end = true;
        }
        
        return dfs(s,0);          
    }
    
    bool dfs(string&s, int cur)
    {
        if (memo[cur]==1) return false;
        
        if (cur==s.size())
            return true;
        
        TrieNode* node = root;
        for (int i=cur; i<s.size(); i++)
        {           
            if (node->next[s[i]-'a']!=NULL)
            {
                node = node->next[s[i]-'a'];
                if (node->end==true && dfs(s, i+1))
                    return true;
            } else
            {
                break;
            }
        }
        
        memo[cur] = 1;
        return false;
    }

public:
    bool doit_topdown_dp(string s, vector<string>& wordDict) {

        int maxl = 0;
        for (auto& c : wordDict) {
            maxl = std::max(maxl, int(c.length()));
        }

        unordered_set<string> wordSet(begin(wordDict), end(wordDict));
        vector<int> dp(s.length(), -1);

        std::function<bool(int)> dfs = [&](int cur) {

            if (cur == s.size()) return true;

            if (dp[cur] != -1) return static_cast<bool>(dp[cur]);

            for (int i = cur + 1; i <= std::min(int(s.size()), maxl + cur+1); i++) {
                if (wordSet.count(s.substr(cur, i - cur)) && dfs(i)) {
                    dp[cur] = 1;
                    return true;
                }
            }

            dp[cur] = 0;
            return false;
        };

        return dfs(0);
    }

    struct Trie {
        Trie* next[26];
        bool is_terminal;
        
        Trie() {
            memset(next, 0, sizeof(next));
            is_terminal = false;
        }
    };

    bool doit_trie(string s, vector<string>& wordDict) {

        Trie* root = new Trie();
        for (const string& word : wordDict) {
            Trie* cur = root;
            for (char w : word) {
                int c = w - 'a';
                if (!cur->next[c]) {
                    cur->next[c] = new Trie();
                }
                cur = cur->next[c];
            }
            
            cur->is_terminal = true;
        }
        
        unordered_set<Trie*> states;
        states.insert(root);
        for (char w : s) {
            char c = w - 'a';
            unordered_set<Trie*> tmp;
            for (Trie* s : states) {
                if(s->next[c]) {
                    tmp.insert(s->next[c]);
                    if (s->next[c]->is_terminal) {
                        tmp.insert(root);
                    }
                }
            }
            swap(states,tmp);
        }
        
        for (Trie* s : states) {
            if (s->is_terminal) return true;
        }
        
        return false;
    }


    class Trie {
    private:
        struct Elem {
          unordered_map<char, Elem*> elems;  
          bool isWord = false;  
        };
        Elem* trie;
    public:
        Trie() : trie(new Elem()){}
    
        void add(const string& s) {
            auto r = trie;
            for (auto c : s) {
                if (!r->elems[c]) {
                    r->elems[c] = new Elem();
                }
                r = r->elems[c];
            }
            r->isWord = true;
        }
    
        int wordLonger(const string& s, int len) {
            auto r = trie;
            int ret = 0;
            for (auto c : s) {
                if(!r)
                    break;
                r = r->elems[c];
                ret++;
                if(r && r->isWord) {
                    if (ret > len) {
                        return ret;
                    }
                }
            }
            return 0;
        }        
    };

    Trie trie;
    unordered_set<string> check;
public:
    bool nwordBreak(string s) {
        
        if (s.empty()) {
            return true;
        }
        
        if(check.find(s) != check.end()){
            return false;
        }
        
        int i = 0;
        while(i < s.size()) {
            int len = trie.wordLonger(s, i);
            if (len == 0) {
                return false;
            }

            if(nwordBreak(s.substr(len))){
                return true;
            } else {
                check.insert(s.substr(len));
            }
            
            i = len;
        }
        
        return false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        for(const auto& w:wordDict) {
            trie.add(w);
        }                
        return nwordBreak(s);
    }
};
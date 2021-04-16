/*
269. Alien Dictionary

There is a new alien language that uses the English alphabet. However, the order among the letters is unknown to you.

You are given a list of strings words from the alien language's dictionary, where the strings in words are sorted lexicographically by the rules of this new language.

Return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there is no solution, return "". If there are multiple solutions, return any of them.

A string s is lexicographically smaller than a string t if at the first letter where they differ, the letter in s comes before the letter in t in the alien language. 

If the first min(s.length, t.length) letters are the same, then s is smaller if and only if s.length < t.length.

 

Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Example 2:

Input: words = ["z","x"]
Output: "zx"
Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".
 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of only lowercase English letters.
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using std::queue;
using std::unordered_set;
using std::unordered_map;
using std::string;
using std::vector;

class AlienOrder {

    /*
        269.Alien-Dictionary
        我们比较任何两个相邻的单词，逐个对比每个字母，可以得到两个字母之间的字典序大小的关系。如果a<b，那么我们就定义一条有向边a->b。

        于是本题就转化为：有一系列的有向边，要求给出一个包括所有节点的顺序排列，使得任何一条边x->y的两个节点(x,y)在这个序列里的顺序都是满足x的位置在y之前。这是一个拓扑排序的问题，适合BFS来做。

        我们需要预处理所有的节点，得到所有节点的入度值。在队列的初始值里，加入所有的外围字母（即入度为零的节点）。因为这些字母的入度为0，说明没有任何字母比它们更小，所以可以安全地放在字典序中的最前面（它们彼此之间的顺序无所谓）。
        接着在BFS过程中，每弹出一个字母x，就找到对应的后续节点y（可能有多个），并将y的入度减一（因为我们已经处理完了字母x）。如果此时y的入度降至0，那么我们就可以将其加入队列中，做为下一批的外围节点。

        核心代码如下：

        while (!q.emtpy())
        {
            char current = q.front();
            q.pop();
            for (auto next: Next[current])
            {
                inDegree[next]--;
                if (inDegree[next]==0)
                    q.push(next);
            }
        }
    */
    string alienOrder(vector<string>& words) 
    {
        unordered_map<char,unordered_set<char>>Next;
        unordered_map<char,int>inDegree;
        
        for (int i=0; i<words.size(); i++)
            for (int j=0; j<words[i].size(); j++)
                inDegree[words[i][j]] = 0;
        
        for (int i=1; i<words.size(); i++)
        {
            string word1 = words[i-1];
            string word2 = words[i];
            
            if (word1.size()>word2.size() && word1.substr(0, word2.size())==word2) return "";
            
            for (int i=0; i<min(word1.size(),word2.size()); i++)
            {
                if (word1[i]==word2[i]) continue;                
                if (Next[word1[i]].find(word2[i])==Next[word1[i]].end())
                {
                    Next[word1[i]].insert(word2[i]);
                    inDegree[word2[i]]++;
                }
                break;
            }            
        }
                        
        queue<char>q;
        for (auto a:inDegree) 
            if (a.second==0) q.push(a.first);
        string result;
        
        while (!q.empty())
        {
            char current = q.front();
            q.pop();
            result+=current;
            
            for (auto a: Next[current])
            {
                inDegree[a]--;
                if (inDegree[a]==0)                
                    q.push(a);                
            }            
        }
               
        if (result.size()==inDegree.size())
            return result;
        else
            return "";
    }


public:
    
    string doit_topsort(vector<string>& words) {

        unordered_map<char, int> indegree;
        unordered_map<char, unordered_set<char>> graph;
        
        for (auto word: words)
            for (auto c: word)
                if (indegree.find(c) == end(indegree)) indegree[c] = 0;

        for (int i = 1; i < words.size(); i++) {

            bool done = true;
            for (int j = 0; j < std::min(words[i].size(), words[i-1].size()); j++) {
                char c = words[i][j], b = words[i-1][j];
                if (b != c) {
                    if (graph[b].count(c) == 0) {
                        indegree[c]++;
                        graph[b].insert(c);
                    }
                    done = false;
                    break;
                }
            }

            if (done && words[i-1].length() > words[i].length()) return "";
        }

        queue<char> buff;

        for (auto it: indegree) {
            if (indegree[it.first] == 0) buff.push(it.first);
        }

        string ans;

        while (!buff.empty()) {

            char cur = buff.front();
            buff.pop();

            ans.push_back(cur);

            for (auto child: graph[cur]) {
                
                if (--indegree[child] == 0) {
                    buff.push(child);
                }
            }
        }

        return ans.length() < indegree.size() ? "" : ans;
    }


    string alienOrder(vector<string>& ws) {
        unordered_map<char, unordered_set<char>> m;
        unordered_map<char, int> indeg;
        for(int k = 0; k < ws.size(); k++) {
            for (char c : ws[k]) if (!indeg.count(c)) indeg[c] = 0;
            if (k == 0) continue;
            auto& w1 = ws[k-1], &w2 = ws[k];
            int i = 0, j = 0;
            for(; i < w1.length() && j < w2.length() && w1[i] == w2[j]; i++, j++) {}
            if(i < w1.length() && j < w2.length()) {
                if(m[w1[i]].insert(w2[j]).second) {
                    // cout << w1[i] << " -> "<< w2[j] << endl;
                    indeg[w2[j]]++;
                }
            } else if (i < w1.length()) {
                return "";
            }
        }
        queue<char> q;
        for (const auto char_to_indeg : indeg) {
            if (char_to_indeg.second == 0) {
                q.push(char_to_indeg.first);
            }
        }
        string ans = "";
        while(!q.empty()) {
            char c = q.front();
            q.pop();
            ans.push_back(c);
            for (char nei : m[c]) {
                if (--indeg[nei] == 0) {
                    q.push(nei);
                }
            }
        }
        return ans.length() == indeg.size() ? ans : "";
    }
};
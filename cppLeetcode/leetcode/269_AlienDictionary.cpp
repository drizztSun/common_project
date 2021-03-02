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

        if (ans.length() < indegree.size()) return "";

        return ans;
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
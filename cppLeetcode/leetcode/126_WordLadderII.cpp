/*
 
 126. Word Ladder II
 
 Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

 Only one letter can be changed at a time
 Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
 Note:

 Return an empty list if there is no such transformation sequence.
 All words have the same length.
 All words contain only lowercase alphabetic characters.
 You may assume no duplicates in the word list.
 You may assume beginWord and endWord are non-empty and are not the same.
 Example 1:

 Input:
 beginWord = "hit",
 endWord = "cog",
 wordList = ["hot","dot","dog","lot","log","cog"]

 Output:
 [
   ["hit","hot","dot","dog","cog"],
   ["hit","hot","lot","log","cog"]
 ]
 Example 2:

 Input:
 beginWord = "hit"
 endWord = "cog"
 wordList = ["hot","dot","dog","lot","log"]

 Output: []

 Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
 
 
 */
#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>


using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;


class WordLaddersII {
    
public:
    
    vector<vector<string>> doit_bfs_bidirect(string beginWord, string endWord, vector<string>&& wordList) {
        
        unordered_set<string> begin{beginWord}, end{endWord};
        unordered_map<string, unordered_set<string>> tree;
        unordered_set<string> words(wordList.begin(), wordList.end());
        unordered_set<string> *pBegin = &begin;
        unordered_set<string> *pEnd = &end;
        bool found = false;
        bool reversed = false;
        
        if (words.find(endWord) == words.end())
            return {};
        
        // words.erase(endWord);
        // words.erase(beginWord);
        
        while (!pBegin->empty() && !found) {
            
            unordered_set<string> nextgroup;
            //words.erase(pBegin->begin(), pBegin->end());
            for (auto& c: *pBegin) {
                words.erase(c);
            }
            
            for (string word : *pBegin) {
                
                string parent = word;
                for (int i = 0; i < word.length(); i++) {
                    
                    for (char j = 0; j < 26; j++) {
                        
                        char c = word[i];
                        
                        word[i] = 'a' + j;
                                            
                        if (words.find(word) != words.end()) {
                            
                            if (pEnd->find(word) != pEnd->end()) {
                                found = true;
                            }
                            nextgroup.insert(word);
                            
                            if (reversed)
                                tree[word].insert(parent);
                            else
                                tree[parent].insert(word);
                        }
                        
                        word[i] = c;
                    }
                }
                
            }
            
            pBegin->swap(nextgroup);
            
            if (pBegin->size() > pEnd->size()) {
                auto* p = pEnd;
                pEnd = pBegin;
                pBegin = p;
                reversed = !reversed;
            }
        }
        
        std::function<vector<vector<string>>(const string)> build = [&](string node){
            
            if (node == endWord)
                return vector<vector<string>> {{endWord}};
            
            vector<vector<string>> res;
            
            for (auto& c : tree[node]) {
                
                for (auto& p : build(c)) {
                    vector<string> s{node};
                    s.insert(s.end(), p.begin(), p.end());
                    res.emplace_back(s);
                }
            }
            
            return res;
        };
        
        if (!found)
            return {};
        
        auto finalres = build(beginWord);
        return finalres;
        //return dfs(tree, beginWord, endWord);
    }
};


void test_126_wordladder() {
    
    WordLaddersII().doit_bfs_bidirect("ta", "if", vector<string>{"ts","sc","ph","ca","jr","hf","to","if","ha","is","io","cf","ta"});
    
    WordLaddersII().doit_bfs_bidirect("hit", "cog", vector<string>{"hot","dot","dog","lot","log","cog"});
    
    WordLaddersII().doit_bfs_bidirect("red", "tax", vector<string>{"ted","tex","red","tax","tad","den","rex","pee"});
}

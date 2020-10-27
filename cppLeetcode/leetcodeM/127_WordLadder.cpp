/*
 127. Word Ladder
 
 Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

 Only one letter can be changed at a time.
 Each transformed word must exist in the word list.
 Note:

 Return 0 if there is no such transformation sequence.
 All words have the same length.
 All words contain only lowercase alphabetic characters.
 You may assume no duplicates in the word list.
 You may assume beginWord and endWord are non-empty and are not the same.
 Example 1:

 Input:
 beginWord = "hit",
 endWord = "cog",
 wordList = ["hot","dot","dog","lot","log","cog"]

 Output: 5

 Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
 return its length 5.
 Example 2:

 Input:
 beginWord = "hit"
 endWord = "cog"
 wordList = ["hot","dot","dog","lot","log"]

 Output: 0

 Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
 
 */

#include <stdio.h>
#include <string>
#include <queue>
#include <vector>
#include <unordered_set>

using std::unordered_set;
using std::vector;
using std::queue;
using std::string;

class WordLadder {
public:
    
    int doit_bfs(string beginWord, string endWord, vector<string>& wordList) {
        
        unordered_set<string> dict(wordList.begin(), wordList.end());
        queue<string> todo;
        todo.push(beginWord);
        
        int ladder = 1;
        while (!todo.empty()) {
            auto n = todo.size();
            for (int i = 0; i < n; i++) {
                string word = todo.front();
                todo.pop();
                if (word == endWord) {
                    return ladder;
                }
                dict.erase(word);
                for (int j = 0; j < word.size(); j++) {
                    char c = word[j];
                    for (int k = 0; k < 26; k++) {
                        word[j] = 'a' + k;
                        if (dict.find(word) != dict.end()) {
                            todo.push(word);
                        }
                     }
                    word[j] = c;
                }
            }
            ladder++;
        }
        return 0;
    }
    
    int doit_bfs_bidirect(string beginWord, string endWord, vector<string>& wordList) {
        
            unordered_set<string> dict(wordList.begin(), wordList.end()), head, tail, *phead, *ptail;
            if (dict.find(endWord) == dict.end()) {
                return 0;
            }
        
            head.insert(beginWord);
            tail.insert(endWord);
            int ladder = 2;
        
            while (!head.empty() && !tail.empty()) {
                if (head.size() < tail.size()) {
                    phead = &head;
                    ptail = &tail;
                } else {
                    phead = &tail;
                    ptail = &head;
                }
                unordered_set<string> temp;
                for (auto it = phead -> begin(); it != phead -> end(); it++) {
                    string word = *it;
                    for (int i = 0; i < word.size(); i++) {
                        char t = word[i];
                        for (int j = 0; j < 26; j++) {
                            word[i] = 'a' + j;
                            if (ptail -> find(word) != ptail -> end()) {
                                return ladder;
                            }
                            if (dict.find(word) != dict.end()) {
                                temp.insert(word);
                                dict.erase(word);
                            }
                        }
                        word[i] = t;
                    }
                }
                ladder++;
                phead -> swap(temp);
            }
            return 0;
        }
};

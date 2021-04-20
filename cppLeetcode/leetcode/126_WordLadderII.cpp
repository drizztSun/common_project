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
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <queue>

using std::queue;
using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;


class WordLaddersII {

    /*
                
        126.Word-Ladder-II
        这是一道考点比较综合全面的ＢＦＳ题．需要注意的几点是：

        １．提前处理这个wordList，将其放入一个wordSet中．并且对于每个单词，我们都提前计算好它的next可能是哪些．

        ２．看清题意，这个wordSet必须包含endWord，否则直接返回空．另外，记得把beginWord也要放进去，否则就不会生成它的next.

        3.题目要求所有的最短路径．这就说明不仅仅是搜到endWord就停止，必须把同一个层级的都搜索完．所以建议用如下的trick

        while (!q.empty())
        {
        int len = q.size();
        for (int k=0; k<len; k++)
        {
            ...
            if (endWord) flag=1;
        }
        if (flag==1) break;
        }
        要保证一个for循环完整地执行完．

        4.要找到回溯的路径，就需要保存所有单词的prev．因为可能有多条最短路径都经过str，那么str的ｐｒｅｖ需要是一个集合．最后回溯的方法用DFS.
    */
    unordered_set<string>wordSet;
    unordered_map<string,vector<string>>next;
    unordered_map<string,unordered_set<string>>prev;
    vector<vector<string>>results;
    string beginWord;
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) 
    {   
        wordList.push_back(beginWord);        
        
        for (auto str:wordList)
            wordSet.insert(str);
        this->beginWord = beginWord;
        
        if (wordSet.find(endWord)==wordSet.end()) return {};
                
        for (int i=0; i<wordList.size(); i++)
        {
            string str = wordList[i];
            for (int k=0; k<str.size(); k++)
            {                
                for (char ch='a'; ch<='z'; ch++)
                {
                    string temp = str;
                    temp[k] = ch;
                    if (temp==str) continue;
                    if (wordSet.find(temp)!=wordSet.end())
                        next[str].push_back(temp);                    
                }
            }
        }
        
        unordered_set<string>visited;
        queue<string>q;
        int flag = 0;
        
        q.push(beginWord);
        visited.insert(beginWord);
        
        while (!q.empty())
        {
            int len = q.size();
            unordered_set<string>newVisited;
            
            for (int k=0; k<len; k++)
            {
                string str = q.front();
                q.pop();
                                
                for (auto nextStr: next[str])
                {                                        
                    if (visited.find(nextStr)!=visited.end())
                        continue;                                                                                
                    prev[nextStr].insert(str);
                    newVisited.insert(nextStr);
                    
                    if (nextStr==endWord) flag = 1;
                }
            }    
            
            for (auto x: newVisited)
            {
                visited.insert(x);                
                q.push(x);
            }                
            
            if (flag==1) break;
        }       
        
        if (flag==0) return {};
        
        DFS(endWord,{endWord});
        
        return results;
    }
    
    void DFS(string word, vector<string> path)
    {
        if (word==beginWord)
        {
            reverse(path.begin(),path.end());
            results.push_back(path);
            return;
        }
        
        for (auto preStr:prev[word])
        {
            vector<string>newPath=path;
            newPath.push_back(preStr);
            DFS(preStr, newPath);
        }
        return;
    }

    
public:
    
    vector<vector<string>> doit_bfs_bidirect_dfs(string beginWord, string endWord, vector<string>&& wordList) {
        
        unordered_set<string> begin{beginWord}, end{endWord};
        unordered_map<string, unordered_set<string>> tree;
        unordered_set<string> words(wordList.begin(), wordList.end());
        unordered_set<string> *pBegin = &begin;
        unordered_set<string> *pEnd = &end;
        bool found = false;
        bool reversed = false;
        
        if (words.find(endWord) == words.end()) return {};
        
        while (!pBegin->empty() && !found) {
            
            unordered_set<string> nextgroup;

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
                std::swap(pEnd, pBegin);
                reversed = !reversed;
            }
        }
        
        std::function<vector<vector<string>>(const string)> build = [&](string node){
            
            if (node == endWord) return vector<vector<string>> {{endWord}};
            
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
        
        if (!found) return {};
        
        return build(beginWord);
    }
};
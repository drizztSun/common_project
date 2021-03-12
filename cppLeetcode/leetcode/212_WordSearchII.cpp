/*
212. Word Search II

Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

Example 1:


Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
Example 2:


Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] is a lowercase English letter.
1 <= words.length <= 3 * 104
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.

*/

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <set>

using std::set;
using std::unordered_map;
using std::vector;
using std::string;


class WordSearch {

    /*
        212.Word-Search-II
        此题是用将常规的DFS算法与Trie的数据结构相结合。设计DFS函数

        void DFS(int i, int j, TrieNode* node, string word, vector<vector<int>>&visited, vector<vector<char>>& board)
        表示(i,j)为起点、node为Trie树的当前根、visited为已经经过的路径，求是否能在board里继续遍历出可以拼成完整单词的路径。拼出完整单词的依据是node->isEnd==true，无法继续的判据是node->next[board[i][j]-'a']==NULL
    */
    class TrieNode
    {
        public:
        TrieNode* next[26];
        bool isEnd;
        TrieNode()
        {
            for (int i=0; i<26; i++)
                next[i]=NULL;
            isEnd=false;
        }
    };
    TrieNode* root;
    set<string>Set;
    int M;
    int N;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) 
    {
        root=new TrieNode();
        
        for (int i=0; i<words.size(); i++)
            build(words[i]);
                
        M=board.size();
        N=board[0].size();            
        auto visited=vector<vector<int>>(M,vector<int>(N,0));
        
        string word;
        for (int i=0; i<M; i++)
         for (int j=0; j<N; j++)
         {             
             visited[i][j]=1;
             DFS(i,j,root,word,visited,board);
             visited[i][j]=0;
         }
        
        vector<string>results(Set.begin(),Set.end());
        return results;
    }
    
    void build(string word)
    {
        TrieNode* node=root;
        for (int i=0; i<word.size(); i++)
        {
            char ch=word[i];
            if (node->next[ch-'a']==NULL)
                node->next[ch-'a']=new TrieNode();
            node=node->next[ch-'a'];
        }
        node->isEnd=true;
    }
    
    void DFS(int i, int j, TrieNode* node, string word, vector<vector<int>>&visited, vector<vector<char>>& board)
    {
        if (node->next[board[i][j]-'a']==NULL) return;
        
        node = node->next[board[i][j]-'a'];
        word += board[i][j];
        
        if (node->isEnd==true) Set.insert(word);
        
        vector<std::pair<int,int>>dir={{1,0},{-1,0},{0,1},{0,-1}};        
        
        for (int k=0; k<4; k++)
        {
            int x=i+dir[k].first;
            int y=j+dir[k].second;
            if (x<0||x>=M||y<0||y>=N) continue;
            if (visited[x][y]==1) continue;
            
            visited[x][y]=1;
            DFS(x,y,node,word,visited,board);
            visited[x][y]=0;                            
        }        
    }


public:
    
    struct Trienode {
        bool done = false;
        unordered_map<char, Trienode*> children;
    };
    
    vector<string> doit_trie(vector<vector<char>>& board, vector<string>& words) {

        Trienode root;

        for (auto word : words) {
            Trienode* p = &root;
            for (auto c : word) {
                if (p->children.count(c) == 0)
                    p->children[c] = new Trienode();
                p = p->children[c];
            }
            p->done = true;
        }


        int m = board.size(), n = board[0].size();
        int direct[5] = { -1, 0 , 1, 0, -1 };
        set<string> ans;

        std::function<void(Trienode*, int, int, string&)> dfs = [&](Trienode* p, int i, int j, string& path) {

            //if (p->children.count(board[i][j]) == 0) return;

            if (p->done) ans.insert(path);
            char c = board[i][j];
            board[i][j] = 0;

            for (int k = 0; k < 4; k++) {

                int x = i + direct[k], y = j + direct[k + 1];

                if (x >= 0 && x < m && y >= 0 && y < n && board[x][y] != 0) {

                    if (p->children.count(board[x][y]) == 0) continue;
                    char c = board[x][y];
                    //board[x][y] = 0;
                    path.push_back(board[x][y]);
                    dfs(p->children[board[x][y]], x, y, path);
                    path.pop_back();
                    //board[x][y] = c;
                }
            }

            board[i][j] = c;
            return;
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                if (root.children.count(board[i][j]) != 0) {
                    string path{board[i][j]};
                    dfs(root.children[board[i][j]], i, j, path);
                }
            }
        }

        return { begin(ans), end(ans) };
    }
};




class Solution {

    class TrieNode {
        public:
            unordered_map<char, TrieNode*> next;//the TrieNode pointer each char corresponds to
            string word = "";
            TrieNode() {}
    };

    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        //can letter at the same position be re-used?
        //[fat, fanny, bed, bear, god]
        // f
        // /\
        // a
        TrieNode* root = new TrieNode();
        for (auto word : words) {
            TrieNode* node = root;
            for (auto c : word) {
                if (!node->next.count(c)) {
                    node->next[c] = new TrieNode();
                }
                node = node->next[c];
            }
            node->word = word;
            std::cout<<"Save the word: " << node->word<< "in the Trie"<<endl;
        }
        unordered_set<string> sol;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (root->next.count(board[i][j])) {
                    std::cout<<"The match is letter " << board[i][j] << endl;
                    dfs(i, j, root, board, sol);
                }
            }
        }
        vector<string> res;
        for (auto x : sol) {
            res.push_back(x);
        }
        return res;
    }
    
    void dfs(int row, int col, TrieNode* node, vector<vector<char>>& board, unordered_set<string>& sol) {
        // if (node->word != "") {
        //     std::cout<<"The word is: " << node->word<<endl;
        //     sol.push_back(node->word);
        // }
        TrieNode* next = node->next[board[row][col]];
        if (next->word != "") {
            std::cout<<"The word is: " << next->word<<endl;
            sol.insert(next->word);
        }
        char tmp = board[row][col];
        board[row][col] = '#';
        for (int k = 0; k < 4; ++k) {
            int x = row + dx[k], y = col + dy[k];
            if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size() || board[x][y] == '#') continue;
            if (next->next.count(board[x][y])) {
                dfs(x, y, next, board, sol);
            }
        }
        board[row][col] = tmp;
        if (next->next.empty()) {
            node->next.erase(tmp);
        }
    }
};
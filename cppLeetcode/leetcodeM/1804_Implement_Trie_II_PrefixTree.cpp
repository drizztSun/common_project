/*
1804. Implement Trie II (Prefix Tree)

A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
int countWordsEqualTo(String word) Returns the number of instances of the string word in the trie.
int countWordsStartingWith(String prefix) Returns the number of strings in the trie that have the string prefix as a prefix.
void erase(String word) Erases the string word from the trie.
 

Example 1:

Input
["Trie", "insert", "insert", "countWordsEqualTo", "countWordsStartingWith", "erase", "countWordsEqualTo", "countWordsStartingWith", "erase", "countWordsStartingWith"]
[[], ["apple"], ["apple"], ["apple"], ["app"], ["apple"], ["apple"], ["app"], ["apple"], ["app"]]
Output
[null, null, null, 2, 2, null, 1, 1, null, 0]

Explanation
Trie trie = new Trie();
trie.insert("apple");               // Inserts "apple".
trie.insert("apple");               // Inserts another "apple".
trie.countWordsEqualTo("apple");    // There are two instances of "apple" so return 2.
trie.countWordsStartingWith("app"); // "app" is a prefix of "apple" so return 2.
trie.erase("apple");                // Erases one "apple".
trie.countWordsEqualTo("apple");    // Now there is only one instance of "apple" so return 1.
trie.countWordsStartingWith("app"); // return 1
trie.erase("apple");                // Erases "apple". Now the trie is empty.
trie.countWordsStartingWith("app"); // return 0
 

Constraints:

1 <= word.length, prefix.length <= 2000
word and prefix consist only of lowercase English letters.
At most 3 * 104 calls in total will be made to insert, countWordsEqualTo, countWordsStartingWith, and erase.
It is guaranteed that for any function call to erase, the string word will exist in the trie.
*/
#include <map>
#include <string>

using std::map;
using std::string;

class Trie {
    
    
    struct node {
        
        int cnt;
        bool done;
        node* child[26];
        
        node() : cnt(0), done(false) {
            for (int i = 0; i < 26; i++) child[i] = nullptr;
        }
    };    
    
    node * root;
    
public:
    
    Trie() {
        root = new node;
    }
    
    void insert(string word) {
        
        node *p = root;
        
        for (auto c : word) {
            int base = c -'a';
            p->cnt++;
            if (p->child[base] == nullptr)
                p->child[base] = new node;
            
            p = p->child[base];
        }
        
        p->cnt++;
        p->done = true;
    }
    
    int countWordsEqualTo(string word) {
        
        node *p = root;
        
        for (auto c : word) {
            int base = c -'a';
            
            if (p->child[base] == nullptr || p->cnt == 0) return 0;
            
            p = p->child[base];
        }
        
        return p->done ? p->cnt : 0;
    }
    
    int countWordsStartingWith(string prefix) {
        node *p = root;
        
        for (auto c : prefix) {
            int base = c -'a';
            
            if (p->child[base] == nullptr || p->cnt == 0) return 0;
            
            p = p->child[base];
        }
        
        return p->cnt;
    }
    
    void erase(string word) {
        
        if (countWordsEqualTo(word) == 0) return;
        
        node *p = root;
        
        for (auto c : word) {
            p->cnt--;
            int base = c -'a';    
            p = p->child[base];
        }
        
        if (--p->cnt == 0) p->done = false;
    }
};




class TrieNode {
public:
    TrieNode(char c=0, bool end=false) {
        content = c;
        isEnd = end;
        cnt = 0;
    }
    char content;
    int cnt;
    bool isEnd;
    map<char, TrieNode*> branches;
};


class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node=root;
        int i;
        for(i=0;i<word.size();i++) {
            if(node->branches.find(word[i]) != node->branches.end()) { 
                node=node->branches[word[i]];
                if(i==word.size()-1) {
                    node->isEnd=true;
                    ++ node->cnt;
                }
            }else
                break;
        }
        for(;i<word.size();i++) {
            TrieNode* tmp= new TrieNode(word[i],i==word.size()-1?true:false);
            node->branches[word[i]] = tmp;
            node=tmp;
            if(i==word.size()-1) {
                ++ node->cnt;
            }
        }
    }
    
    int countWordsEqualTo(string word) {
        TrieNode* node=root;
        for(int i=0;i<word.size();i++) {
            if(node->branches.find(word[i]) != node->branches.end()) { 
                node=node->branches[word[i]];
            }else{
                return 0;
            }
        }
        if(node->isEnd)
            return node->cnt;
        return 0;
    }
    
    int countWordsStartingWith(string prefix) {
        int ans = 0;
        TrieNode* node=root;
        for(int i=0;i<prefix.size();i++) {
            if(node->branches.find(prefix[i]) != node->branches.end()) { 
                node=node->branches[prefix[i]];
            }else{
                return 0;
            }
        }
        dfs(node, ans);
        return ans;
    }
    
    void erase(string word) {
        TrieNode* node=root;
        for(int i=0;i<word.size();i++) {
            if(node->branches.find(word[i]) != node->branches.end()) { 
                node=node->branches[word[i]];
            }else{
                return ;
            }
        }
        if(node->isEnd && node->cnt > 0) {
            -- node->cnt;
        }
        return ;
    }
private:
    void dfs(TrieNode* root, int &ans) {
        if(root->isEnd) {
            ans += root->cnt;
        }
        
        for(auto it : root->branches) {
            dfs(it.second, ans);
        }
    }
};
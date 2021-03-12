/*
208. Implement Trie (Prefix Tree)


Trie (we pronounce "try") or prefix tree is a tree data structure used to retrieve a key in a strings dataset. 
There are various applications of this very efficient data structure, such as autocomplete and spellchecker.

Implement the Trie class:

Trie() initializes the trie object.
void insert(String word) inserts the string word to the trie.
boolean search(String word) returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix) returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.
 

Example 1:

Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True
 

Constraints:

1 <= word.length, prefix.length <= 2000
word and prefix consist of lowercase English letters.
At most 3 * 104 calls will be made to insert, search, and startsWith.

*/
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;


/*
    208.Implement-Trie--Prefix-Tree
    对于Trie类型的基本功操作包括：

    1. Trie类型的定义：包括两个成员变量，构造函数
    2. Trie的单词添加
    3. 在Trie树中找指定的完整单词（需要找到叶子节点）
    4. 在Trie树中找指定的前缀（不需要找到叶子节点）
*/
class Trie {
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
        
public:
    /** Initialize your data structure here. */
    Trie() 
    {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) 
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
    
    /** Returns if the word is in the trie. */
    bool search(string word) 
    {
        TrieNode* node=root;
        for (int i=0; i<word.size(); i++)
        {
            char ch=word[i];
            if (node->next[ch-'a']==NULL)
                return false;
            node=node->next[ch-'a'];
        }
        if (node->isEnd==false)
            return false;
        else
            return true;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) 
    {
        TrieNode* node=root;
        for (int i=0; i<prefix.size(); i++)
        {
            char ch=prefix[i];
            if (node->next[ch-'a']==NULL)
                return false;
            node=node->next[ch-'a'];
        }
        return true;        
    }
};


class Trie {

    struct TrieNode {
        unordered_map<char, TrieNode*> _node;
        bool end = false;
    };

    TrieNode _root;
public:
    /** Initialize your data structure here. */
    Trie() {}
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        
        TrieNode* node = &_root;
        for (auto c: word) {
            if (node->_node.count(c) == 0)
                node->_node[c] = new TrieNode();
            node = node->_node[c];
        }

        node->end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        
        TrieNode* node = &_root;
        for (auto c: word) {
            if (node->_node.count(c) == 0) return false;
            node = node->_node[c];
        }

        return node->end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        
        TrieNode* node = &_root;
        for (auto c: prefix) {
            if (node->_node.count(c) == 0) return false;
            node = node->_node[c];
        }

        return true;
    }
};
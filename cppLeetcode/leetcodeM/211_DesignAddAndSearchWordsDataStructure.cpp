/*
211. Design Add and Search Words Data Structure

Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the WordDictionary class:

WordDictionary() Initializes the object.
void addWord(word) Adds word to the data structure, it can be matched later.
bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word may contain dots '.' where dots can be matched with any letter.
 

Example:

Input
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output
[null,null,null,null,false,true,true,true]

Explanation
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True
 

Constraints:

1 <= word.length <= 500
word in addWord consists lower-case English letters.
word in search consist of  '.' or lower-case English letters.
At most 50000 calls will be made to addWord and search.

*/
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using std::vector;
using std::string;
using std::unordered_map;


/*
    
211.Add-and-Search-Word
这是字典树的典型题，考察了Trie的各种基本操作。

首先是TrieNode的类型及构造函数:

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
注意：1.类定义结束之后要加分号。2.构造函数必须显式地声明为public（否则默认为private）。

其次是字典树的数据添加:

    void addWord(string word) 
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
本质是不断开辟子树的过程，将原本是NULL的子节点new出一个实际的内存空间。

最后的字典树的查询，则是用到了DFS，根据索引下沉到相应的子节点，和二叉树的遍历类似。
*/
class WordDictionary {
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
    WordDictionary() 
    {
        root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) 
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
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) 
    {
        return DFS(word, 0, root);
    }
    
    bool DFS(string word, int i, TrieNode* node)
    {
        if (node==NULL)
            return false;
        if (i==word.size())
            return (node->isEnd);

        if (word[i]!='.')
            return DFS(word, i+1, node->next[ch=word[i]-'a']);
        else
        {
            bool flag=false;
            for (int k=0; k<26; k++)
            {
                if (DFS(word,i+1,node->next[k]))
                {
                    flag=true;
                    break;
                }    
            }
            return flag;
        }
    }
};

class WordDictionary_Trie {

    struct Trie {

        vector<Trie*> children;
        bool done;
        Trie(): children(26), done(false) {}

    };

    Trie _root;

public:

    /** Initialize your data structure here. */
    WordDictionary_Trie() {}

    void _build(const string& word) {
        
        Trie *node = &_root;

        for (auto w: word) {
            int index = w - 'a';
            if (node->children[index] == nullptr)
                node->children[index] = new Trie();
            node = node->children[index];
        }

        node->done = true;
    }

    bool _query(const string& word) {

        std::function<bool(int, Trie*)> dfs = [&](int i, Trie* node) {
            
            if (!node)
                return false;

            if (i == word.length())
                return node->done;

            if (word[i] == '.') {
                for (auto c : node->children)
                    if (c && dfs(i+1, c))
                        return true;
                return false;
            } else {
                return dfs(i+1, node->children[word[i]-'a']);
            }
        };

        return dfs(0, &_root);
    }
    
    void addWord(string word) {
        _build(word);
    }
    
    bool search(string word) {
        return _query(word);
    }
};

class WordDictionary {
    struct TrieNode {
        unordered_map<char, TrieNode*> _node;
        bool end = false;
    };

    TrieNode _root;

public:
    /** Initialize your data structure here. */
    WordDictionary() {}
    
    void addWord(string word) {
        TrieNode* node = &_root;
        for (auto c: word) {
            if (node->_node.count(c) == 0)
                node->_node[c] = new TrieNode();
            node = node->_node[c];
        }

        node->end = true;
    }
    
    bool search(string word) {
        
        std::function<bool(TrieNode*, int)> dfs = [&](TrieNode* p, int i) {
            if (i == word.length())
                return p->end;
            
            if (word[i] != '.') {
                return p->_node.count(word[i]) > 0 && dfs(p->_node[word[i]], i+1);
            } else {   
                for (auto c: p->_node) {
                    if (dfs(c.second, i+1)) return true;
                }
                
                return false;
            }
        };
        
        return dfs(&_root, 0);
    }
};
/*
676. Implement Magic Dictionary

Design a data structure that is initialized with a list of different words. Provided a string, you should determine if you can change exactly one character in this string to match any word in the data structure.

Implement the MagicDictionary class:

. MagicDictionary() Initializes the object.
. void buildDict(String[] dictionary) Sets the data structure with an array of distinct strings dictionary.
. bool search(String searchWord) Returns true if you can change exactly one character in searchWord to match any string in the data structure, otherwise returns false.
 

Example 1:

Input
["MagicDictionary", "buildDict", "search", "search", "search", "search"]
[[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
Output
[null, null, false, true, false, false]

Explanation
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // return False
magicDictionary.search("hhllo"); // We can change the second 'h' to 'e' to match "hello" so we return True
magicDictionary.search("hell"); // return False
magicDictionary.search("leetcoded"); // return False
 

Constraints:

1 <= dictionary.length <= 100
1 <= dictionary[i].length <= 100
dictionary[i] consists of only lower-case English letters.
All the strings in dictionary are distinct.
1 <= searchWord.length <= 100
searchWord consists of only lower-case English letters.
buildDict will be called only once before search.
At most 100 calls will be made to search.
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using std::unordered_map;
using std::vector;
using std::string;

class MagicDictionary {

    struct Trienode {
        bool done = false;
        unordered_map<char, Trienode*> _children;
    };

    Trienode _root;

public:
    /** Initialize your data structure here. */
    MagicDictionary() {}
    
    void buildDict(vector<string> dictionary) {

        for (auto word: dictionary) {

            Trienode* p = &_root;

            for (auto c : word) {

                if (p->_children.count(c) == 0)
                    p->_children[c] = new Trienode();

                p = p->_children[c];
            }

            p->done = true;
        }
    }
    
    bool search(string searchWord) {
        
        std::function<bool (Trienode*, int, bool)> dfs = [&](Trienode* p, int i, bool match) {
            
            if (i == searchWord.length())
                return match && p->done;

            bool res = false;
            for (auto it : p->_children) {
                if (it.first == searchWord[i])
                    res = dfs(it.second, i+1, match);
                else {
                    if (match) continue;
                    res = dfs(it.second, i+1, true);
                }

                if (res) break;
            }
            return res;
        };

        return dfs(&_root, 0, false);
    }
};


/*
    676.Implement-Magic-Dictionary
    此题特征就是用Trie树，实现高效的单词搜索。Trie树的一些基本操作应数量掌握，包括构建树 buildTree(string word, TrieNode* node)，搜索一个单词是否在此字典树内 inDictionary(string word, TrieNode* node).

    对于单词abcdefg，先考虑置换第一个字母a，换成其他字母后，考察bcdefg是否是在这个字典树node内，需要调用inDictionary。如果从a到z的置换都不成功，则将根节点下降一层node=node->next['a'-'a']，
    同时word=word.substr(1)，于是就将原问题转化为在新的字典树node理考察新的word（bcdefg），这样可以递归调用整个search的过程。
*/

class MagicDictionary {
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
    MagicDictionary() 
    {
        root = new TrieNode();
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) 
    {        
        for (int i=0; i<dict.size(); i++)
        {
            TrieNode* node=root;
            string str=dict[i];
            for (int j=0; j<str.size(); j++)
            {
                if (node->next[str[j]-'a']==NULL)
                    node->next[str[j]-'a']=new TrieNode();
                node=node->next[str[j]-'a'];
            }
            node->isEnd=true;
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) 
    {
         return DFS_search(word,root);
    }
    
    bool DFS_search(string word, TrieNode* node)
    {
        if (word=="") return false;
        if (node==NULL) return false;
        
        for (char ch='a'; ch<='z'; ch++)
        {
            if (ch==word[0]) continue;
            if (inDict(word.substr(1),node->next[ch-'a']))
                return true;            
        }
        return DFS_search(word.substr(1),node->next[word[0]-'a']);
    }
    
    bool inDict(string word, TrieNode* node)
    {
        if (node==NULL) return false;
        
        for (int i=0; i<word.size(); i++)
        {
            char ch=word[i];
            if (node->next[ch-'a']==NULL)
                return false;
            node=node->next[ch-'a'];
        }
        
        return (node->isEnd);            
    }
};

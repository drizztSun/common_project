/*
677. Map Sum Pairs

Implement the MapSum class:

MapSum() Initializes the MapSum object.
void insert(String key, int val) Inserts the key-val pair into the map. If the key already existed, the original key-value pair will be overridden to the new one.
int sum(string prefix) Returns the sum of all the pairs' value whose key starts with the prefix.
 

Example 1:

Input
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
Output
[null, null, 3, null, 5]

Explanation
MapSum mapSum = new MapSum();
mapSum.insert("apple", 3);  
mapSum.sum("ap");           // return 3 (apple = 3)
mapSum.insert("app", 2);    
mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)
 

Constraints:

. 1 <= key.length, prefix.length <= 50
. key and prefix consist of only lowercase English letters.
. 1 <= val <= 1000
. At most 50 calls will be made to insert and sum.

*/

#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class MapSum {
    struct Trienode {
        bool done = false;
        int current = 0;
        unordered_map<char, Trienode*> _children;
    };
    
    unordered_map<string, int> _base;

    Trienode _root;

public:
    /** Initialize your data structure here. */
    MapSum() {}
    
    void insert(string key, int val) {
        
        Trienode* p = &_root;
        int diff = val;
        if (_base.count(key) != 0) {
            diff -= _base[key];
        }

        for (auto c : key) {
            p->current += diff;

            if (p->_children.count(c) == 0)
                p->_children[c] = new Trienode();
            
            p = p->_children[c];
        }

        p->current += diff;
        _base[key] = val;
    }
    
    int sum(string prefix) {

        Trienode* p = &_root;

        for (auto c : prefix) {
            if (p->_children.count(c) == 0) return 0;
            p = p->_children[c];
        }

        return p->current;
    }
};

/*
    677.Map-Sum-Pairs-My-SubmissionsBack-to-Contest
    常规的Trie操作。

    注意，在类的公告区域里定义了TrieNode* root之后，在构造函数里就只需要直接root=TrieNode()即可，千万不能TrieNode* root=TrieNode()。否则会有意想不到的错误。
*/
class MapSum {
    class TrieNode
    {
        public:
        TrieNode* next[26];
        int val;
        TrieNode()
        {
            for (int i=0; i<26; i++)
                next[i]=NULL;
            val=0;
        }
    };
    TrieNode* root;
public:
    /** Initialize your data structure here. */
    MapSum() 
    {
        root=new TrieNode();
    }
    
    void insert(string key, int val) 
    {
        TrieNode* node=root;
        for (int i=0; i<key.size(); i++)
        {
            char ch=key[i];
            if (node->next[ch-'a']==NULL)
                node->next[ch-'a']=new TrieNode();
            node=node->next[ch-'a'];
        }
        node->val=val;
    }
    
    int sum(string prefix) 
    {
        TrieNode* node=root;
        for (int i=0; i<prefix.size(); i++)
        {
            char ch=prefix[i];
            if (node->next[ch-'a']==NULL)
                node->next[ch-'a']=new TrieNode();
            node=node->next[ch-'a'];
        }
        int SUM=0;
        DFS(node,SUM);
        return SUM;
    }
    
    void DFS(TrieNode* node, int & SUM)
    {
        if (node==NULL) return;
        
        SUM+=node->val;
        for (int i=0; i<26; i++)
            DFS(node->next[i],SUM);
    }
};
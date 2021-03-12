#include <vector>
#include <string>
#include <functional>

using std::string;
using std::vector;


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

    ~WordDictionary_Trie() {
        std::function<void(Trie*)> dfs = [](Trie* node) {
            if (!node) return;

            for (Trie* c: node->children) {
                if(c) {
                    dfs(c);
                    delete c;
                }
            }
        };
        dfs(&_root);
    }

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



/*


648.Replace-Words
此题显而易见，是用Trie来实现单词（词根）的查找。

对于Trie类型的基本功操作包括：

1. Trie类型的定义：包括两个成员变量，构造函数
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

2. Trie的单词添加
void addWord(TrieNode* root, string word)
{
    TrieNode* node=root;
    for (int i=0; i<word.size(); i++)
    {
        char ch=word[i];
        if (node->next[ch-'a']==NULL)
          node->next[ch-'a']==new TrieNode();
        node = node->next[ch-'a'];
    }
    node->isEnd=1;
}
3. Trie的单词查找。在本题中，只要能追踪到叶子节点 isEnd==true 即说明找到词根
bool flag = DFS(root,word,0); // 递归调用

bool DFS(TrieNode* root, string word, int k)
{
    if (root->isEnd==true)
      return true;
    if (k==word.size())
      return false;
    for (int i=0; i<26; i++)
    {
       if (DFS(root->next[word[i]-'a'],word,k+1))
          return true;
    }
    return false;
}

*/

class Solution {
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
    
    void addWord(TrieNode* root, string word)
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
    
    string replace(TrieNode* root, string word)
    {
        string result;
        string str;
        DFS(root,word,0,str,result);
        if (result!="")
            return result;
        else
            return word;
    }
    
    void DFS(TrieNode* root, string word, int k, string str, string &result)
    {
        if (root->isEnd==1)
        {
            if (result=="")
                result=str;
            else if (result.size()>str.size())
                result=str;
            return;
        }
        
        if (k==word.size())
            return;
                
        for (int i=0; i<26; i++)
        {
            if (root->next[word[k]-'a']!=NULL)
            {
                DFS(root->next[word[k]-'a'],word,k+1,str+word[k],result);
            }
        }
        return;
    }
    
public:
    string replaceWords(vector<string>& dict, string sentence) 
    {
        TrieNode* root=new TrieNode();
        for (int i=0; i<dict.size(); i++)
            addWord(root,dict[i]);
        
        int i=0;
        while (i<sentence.size() && sentence[i]==' ') i++;
        
        string result;
        while (i<sentence.size())
        {
            int i0=i;
            while (i<sentence.size() && sentence[i]!=' ') i++;
            string str=sentence.substr(i0,i-i0);
            string str2 = replace(root,str);
            
            result+=str2;
            result+=' ';
            i++;
        }
        result.pop_back();
        
        return result;
    }
};
/*
648. Replace Words

In English, we have a concept called root, which can be followed by some other word to form another longer word - let's call this word successor. 
For example, when the root "an" is followed by the successor word "other", we can form a new word "another".

Given a dictionary consisting of many roots and a sentence consisting of words separated by spaces, replace all the successors in the sentence with the root forming it. 
If a successor can be replaced by more than one root, replace it with the root that has the shortest length.

Return the sentence after the replacement.

 

Example 1:

Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
Example 2:

Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
Output: "a a b c"
Example 3:

Input: dictionary = ["a", "aa", "aaa", "aaaa"], sentence = "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa"
Output: "a a a a a a a a bbb baba a"
Example 4:

Input: dictionary = ["catt","cat","bat","rat"], sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
Example 5:

Input: dictionary = ["ac","ab"], sentence = "it is abnormal that this solution is accepted"
Output: "it is ab that this solution is ac"
 

Constraints:

1 <= dictionary.length <= 1000
1 <= dictionary[i].length <= 100
dictionary[i] consists of only lower-case letters.
1 <= sentence.length <= 10^6
sentence consists of only lower-case letters and spaces.
The number of words in sentence is in the range [1, 1000]
The length of each word in sentence is in the range [1, 1000]
Each two consecutive words in sentence will be separated by exactly one space.
sentence does not have leading or trailing spaces.
*/
#include <string>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;
using std::string;


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

class ReplaceWords {
    
    struct Trienode {
        unordered_map<char, Trienode*> node;
        bool done = false;
    };
    
public:
    
    string doit_trie(vector<string>& dictionary, string sentence) {
        
        Trienode root;
        
        auto build = [](Trienode* p, string word) {
            
            for (auto c : word) {
                if (p->node.count(c) == 0)
                    p->node[c] = new Trienode();
                p = p->node[c];
            }
            
            p->done = true;
        };
        
        for (auto word: dictionary) {
            
            build(&root, word);
        }
        
        string ans;
        
        for (int i = 0; i < sentence.length(); i++) {
            
            int j = i;
            while (j < sentence.length() && iswspace(sentence[j])) j++;
            
            int j1 = j;
            while (j1 < sentence.length() && !iswspace(sentence[j1])) j1++;
            
            if (j1 - j == 0) {
                i = j1;
                continue;
            }
            
            string word = sentence.substr(j, j1 - j);
            
            Trienode* p = &root;
            string key;
            for (auto c : word) {
                if (p->node.count(c) == 0) break;
                key.push_back(c);
                p = p->node[c];
                if (p->done) break;
            }
            
            if (!ans.empty())
                ans.push_back(' ');
            
            if (p->done) 
                ans.append(key);
            else
                ans.append(word);
            i = j1;
        }
        
        return ans;
    }
};
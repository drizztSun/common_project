/*
1268. Search Suggestions System

Given an array of strings products and a string searchWord. We want to design a system that suggests at most three product names from products after each character of searchWord is typed. 
Suggested products should have common prefix with the searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.

Return list of lists of the suggested products after each character of searchWord is typed. 

 

Example 1:

Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [
["mobile","moneypot","monitor"],
["mobile","moneypot","monitor"],
["mouse","mousepad"],
["mouse","mousepad"],
["mouse","mousepad"]
]
Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"]
After typing m and mo all products match and we show user ["mobile","moneypot","monitor"]
After typing mou, mous and mouse the system suggests ["mouse","mousepad"]
Example 2:

Input: products = ["havana"], searchWord = "havana"
Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
Example 3:

Input: products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
Output: [["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
Example 4:

Input: products = ["havana"], searchWord = "tatiana"
Output: [[],[],[],[],[],[],[]]
 

Constraints:

1 <= products.length <= 1000
There are no repeated elements in products.
1 <= Σ products[i].length <= 2 * 10^4
All characters of products[i] are lower-case English letters.
1 <= searchWord.length <= 1000
All characters of searchWord are lower-case English letters.

*/

#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

class SuggestedProducts {

    /*
        Approach 1: Binary Search
        Intuition

        Since the question asks for the result in a sorted order, let's start with sorting products. An advantage that comes with sorting is Binary Search, we can binary search for the prefix. 
        Once we locate the first match of prefix, all we need to do is to add the next 3 words into the result (if there are any), since we sorted the words beforehand.

        Algorithm

        Sort the input products.
        Iterate each character of the searchWord adding it to the prefix to search for.
        After adding the current character to the prefix binary search for the prefix in the input.
        Add next 3 strings from the current binary search start index till the prefix remains same.
        Another optimization that can be done is reducing the binary search space to current start index (This is due to the fact that adding more characters to the prefix will make the next search result's index be at least > current search's index).

        Complexity Analysis

        Time complexity : O(nlog(n)) + O(mlog(n))O(nlog(n))+O(mlog(n)). Where n is the length of products and m is the length of the search word. Here we treat string comparison in sorting as O(1)O(1). 
        O(nlog(n)) comes from the sorting and O(mlog(n))O(mlog(n)) comes from running binary search on products m times.

        In Java there is an additional complexity of O(m^2)O(m 
        2
        ) due to Strings being immutable, here m is the length of searchWord.
        Space complexity : Varies between O(1)O(1) and O(n)O(n) where n is the length of products, as it depends on the implementation used for sorting. We ignore the space required for output as it does not affect the algorithm's space complexity. 
        See Internal details of std::sort. Space required for output is O(m)O(m) where m is the length of the search word.
    */
    vector<vector<string>> suggestedProducts(vector<string> &products, string searchWord) {

        std::sort(products.begin(), products.end());
        vector<vector<string>> result;
        int start, bsStart = 0, n=products.size();
        string prefix;
        for (char &c : searchWord) {
            prefix += c;

            // Get the starting index of word starting with `prefix`.
            start = lower_bound(products.begin() + bsStart, products.end(), prefix) - products.begin();

            // Add empty vector to result.
            result.push_back({});

            // Add the words with the same prefix to the result.
            // Loop runs until `i` reaches the end of input or 3 times or till the
            // prefix is same for `products[i]` Whichever comes first.
            for (int i = start; i < std::min(start + 3, n) && !products[i].compare(0, prefix.length(), prefix); i++)
                result.back().push_back(products[i]);

            // Reduce the size of elements to binary search on since we know
            bsStart = start;
        }
        return result;
    }



public:    

    // Custom class Trie with function to get 3 words starting with given prefix
    class Trie
    {
        // Node definition of a trie
        struct Node {
            bool isWord = false;
            vector<Node *> children{vector<Node *>(26, NULL)};
        } * Root, *curr;

        // Runs a DFS on trie starting with given prefix and adds all the words in the result, limiting result size to 3
        void dfsWithPrefix(Node * curr, string & word, vector<string> & result) {
            if (result.size() == 3)
                return;
            if (curr->isWord)
                result.push_back(word);

            // Run DFS on all possible paths.
            for (char c = 'a'; c <= 'z'; c++)
                if (curr->children[c - 'a']) {
                    word += c;
                    dfsWithPrefix(curr->children[c - 'a'], word, result);
                    word.pop_back();
                }
        }

    public:
        Trie() {
            Root = new Node();
        }
        // Inserts the string in trie.
        void insert(string & s) {
            // Points curr to the root of trie.
            curr = Root;
            for (char &c : s) {
                if (!curr->children[c - 'a'])
                    curr->children[c - 'a'] = new Node();
                curr = curr->children[c - 'a'];
            }
            // Mark this node as a completed word.
            curr->isWord = true;
        }
        vector<string> getWordsStartingWith(string & prefix) {
            curr = Root;
            vector<string> result;

            // Move curr to the end of prefix in its trie representation.
            for (char &c : prefix) {
                if (!curr->children[c - 'a'])
                    return result;
                curr = curr->children[c - 'a'];
            }
            dfsWithPrefix(curr, prefix, result);
            return result;
        }
    };

public:

    vector<vector<string>> doit_trie(vector<string> &products, string searchWord) {
        Trie trie=Trie();
        vector<vector<string>> result;

        // Add all words to trie.
        for(string &w:products)
            trie.insert(w);
        string prefix;
        for (char &c : searchWord) {
            prefix += c;
            result.push_back(trie.getWordsStartingWith(prefix));
        }
        return result;
    }
};


/*
1268.Search-Suggestions-System
解法1：
比较严谨的做法是用Trie。根据searchWord的前缀（比如说前k个字母）在Trie中推进直至某个节点，然后以这个节点为根，用DFS的方法、根据先左后右的规则，找出最多三个合法的子路径（即能够拼成一个product）。

特别注意，此题中的product允许有重复，所以在TrieNode定义中，传统的bool isEnd需要改造为int count，并在构造整颗树的时候用它来计算有多少个重复（即共享完全相同的路径）的product。在DFS的过程中，如果推进到某个节点的count>1，说明会有多于1个product有着相同的名字，我们需要把它们都算上。

解法2：
有一种非常取巧的方法，那就是将所有product按照字典排序。然后查找searchWord在里面的位置（用lower_bound定位），得到的就是字典序恰好大于等于searchWord的那个单词。我们查看以这个单词开始的连续三个单词，是否与searchWord共享指定书目的前缀，是的话就相应收入囊中。

这种方法可以不必理会products中是否存在重复。但是第一步排序的过程其实比较耗时，不过题目给出了1 <= Σ products[i].length <= 2 * 10^4，这就是暗示了字符串排序的复杂度是可以接受的。

*/

class Solution {
    class TrieNode
    {
        public:
            TrieNode* next[26];
            int isEnd;
        TrieNode()
        {
            for (int i=0; i<26; i++)
                next[i]=NULL;
            isEnd=0;
        }
    };
    TrieNode* root;    
    
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) 
    {
        root = new TrieNode();
        for (auto word: products)
            insert(word);
        
        vector<vector<string>>rets;
        TrieNode* node=root;
        string word;
        for (int i=0; i<searchWord.size(); i++)
        {
            char ch = searchWord[i];            
            if (node->next[ch-'a']==NULL)
            {
                for (int j=i; j<searchWord.size(); j++)
                    rets.push_back({});
                break;
            }
            
            node = node->next[ch-'a'];
            word.push_back(ch);
            vector<string>ans;
            string temp = "";
            DFS(node,ans,temp);
            
            while (ans.size()>3)
                ans.pop_back();
            for (int j=0; j<ans.size(); j++)
                ans[j] = word+ans[j];
            rets.push_back(ans);                
        }
        
        return rets;
    }
    
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
        node->isEnd+=1;
    }   
    
    void DFS(TrieNode* node, vector<string>&ans, string temp) 
    {        
        if (node->isEnd>0)
        {
            for (int k=0; k<node->isEnd; k++)
                ans.push_back(temp);
        }
            
        
        for (int i=0; i<26; i++)
        {
            if (ans.size()>3) break;
            if (node->next[i]==NULL) continue;
            temp.push_back('a'+i);
            DFS(node->next[i],ans, temp);
            temp.pop_back();
        }        
    }
    
    
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) 
    {
        sort(products.begin(),products.end());
        vector<vector<string>>rets;
        
        string word;        
        for (int i=0; i<searchWord.size(); i++)
        {
            word.push_back(searchWord[i]);
            vector<string>ans;
            auto iter = lower_bound(products.begin(),products.end(),word);
            for (int k=0; k<3; k++)
            {
                if (iter==products.end()) break;
                if (iter->substr(0,word.size())!=word) break;
                ans.push_back(*iter);
                iter = next(iter,1);
            }
            rets.push_back(ans);
        }
        return rets;
    }
};
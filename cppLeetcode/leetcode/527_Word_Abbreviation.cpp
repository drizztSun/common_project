/*
 
 527. Word Abbreviation
 
 Given an array of n distinct non-empty strings, you need to generate minimal possible abbreviations for every word following rules below.

 Begin with the first character and then the number of characters abbreviated, which followed by the last character.
 If there are any conflict, that is more than one words share the same abbreviation, a longer prefix is used instead of only the first character until making the map from word to abbreviation become unique. In other words, a final abbreviation cannot map to more than one original words.
 If the abbreviation doesn't make the word shorter, then keep it as original.
 Example:
 Input: ["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"]
 Output: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]
 Note:
 Both n and the length of each word will not exceed 400.
 The length of each word is greater than 1.
 The words consist of lowercase English letters only.
 The return answers should be in the same order as the original array.
 
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::unordered_set;
using std::unordered_map;
using std::vector;
using std::string;

class WordsAbbreviation {

    /*
                527.Word-Abbreviation
        设置一个Map和一个Set。Map是从缩写到原单词(数组)的映射。Set盛装所有仍需要进一步求缩写的原单词，初始化的时候则装所有的原单词。

        在每次循环中，把Set里所有的单词都求其缩写加入Map，清空Set。然后查看Map的所有元素，对于那些仍然对应多个原单词的缩写，就把这些原单词加入Set。清空Map。

        重复这样的循环直至Set不再有元素。
    */
    vector<string> wordsAbbreviation(vector<string>& dict) 
    {
        unordered_map<string,int>Index;
        for (int i=0; i<dict.size(); i++)
            Index[dict[i]]=i;
        
        unordered_map<string,vector<string>>Map;
        vector<string>results(dict.size());
        int abbrNum=0;

        unordered_set<string>Set;
        for (int i=0; i<dict.size(); i++)
            Set.insert(dict[i]);
        
        while (1)
        {
            Map.clear();
            for (auto s:Set)
            {
                string abbr=getAbbr(s,abbrNum);
                Map[abbr].push_back(s);
            }
            Set.clear();
            
            for (auto a:Map)
            {
                if (a.second.size()>1)
                {
                    for (int i=0; i<a.second.size(); i++)
                        Set.insert(a.second[i]);
                }
                else
                {
                    results[Index[a.second[0]]]=a.first;
                }
            }
            
            if (Set.size()==0) break;
            abbrNum++;
        }
        
        return results;
        
    }
    
    string getAbbr(string s, int abbrNum)
    {
        string t;
        if (s.size()<=2) 
        {
            t=s;
            return t;
        }
        
        t=s.substr(0,abbrNum+1);
        t+=to_string(s.size()-abbrNum-2);
        t+=s.back();
        if (t.size()==s.size()) t=s;
        return t;
    }


public:

    /*
        Approach #3: Group + Trie [Accepted]
        Intuition and Algorithm

        As in Approach #1, let's group words based on length, first letter, and last letter, and discuss when words in a group do not share a longest common prefix.

        Put the words of a group into a trie (prefix tree), and count at each node (representing some prefix P) the number of words with prefix P. If the count is 1, we know the prefix is unique.


        Complexity Analysis

        Time Complexity: O(C) where CC is the number of characters across all words in the given array.

        Space Complexity: O(C).
    */
    vector<string> doit_trie(vector<string>& dict) {
        
        vector<string> res(dict.size());
        unordered_map<string, vector<int>> category;
        
        for (int i = 0; i < dict.size(); i++) {
            string id = dict[i].substr(0, 1) + dict[i].back() + std::to_string(dict[i].size());
            category[id].push_back(i);
        }

        for (const auto& [id, v] : category) {
            Trie tr;
            for (int i : v) tr.add(dict[i]);
            for (int i : v) res[i] = tr.getAbbr(dict[i]);
        }
        
        return res;
    }

    class Trie {
    public:
        struct Node {
            Node* child[26] = { nullptr };
            int count = 0;
        };

        void add(const string& s) {
            auto p = root;
            for (int i = 0; i < s.size() - 1; i++) {
                int index = s[i] - 'a';
                if (!p->child[index]) p->child[index] = new Node();
                p = p->child[index];
                p->count++;
            }
        }

        string getAbbr(const string& s) {
            string res;
            auto p = root;
            for (int i = 0; i < s.size() - 1; i++) {
                p = p->child[s[i] - 'a'];
                res += s[i];
                if (p->count == 1) break;
            }
            int nonAbbrLen = s.size() - res.size() - 1;
            if (nonAbbrLen <= 1) return s;
            return res + std::to_string(nonAbbrLen) + s.back();
        }

        Node* root = new Node();
    };

};
/*
49. Group Anagrams

Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]
 

Constraints:

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] consists of lower-case English letters.
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using std::unordered_map;
using std::string;
using std::vector;

class GroupAnagrams {

    /*
        049.Group-Anagrams  
        对每个string按从小到大排序，以此为key建立Hash表 map<string,vector>。属于同一组Anagrams的字符串必定有相同的键值。
    */
    vector<vector<string>> doit_(vector<string>& strs) 
    {
        unordered_map<string,vector<string>>Map;
        
        for (int i=0; i<strs.size(); i++)
        {
            string t = strs[i];
            std::sort(t.begin(),t.end());
            Map[t].push_back(strs[i]);
        }
        
        vector<vector<string>>results;
        for (auto a:Map)
            results.push_back(a.second);
        
        return results;
    }


public:
    
    vector<vector<string>> doit_hashtable(vector<string>& strs) {
        
        unordered_map<string, vector<string>> groups;
        
        for (auto word: strs) {
            
            vector<int> cnt(26);
            
            for (auto c: word) {
                cnt[c-'a']++;
            }
            
            string key;
            for (int i = 0; i < 26; i++) {
                if (cnt[i] > 0)
                    key += char('a' + i) + std::to_string(cnt[i]);
            }
            
            groups[key].push_back(word);
        }
        
        vector<vector<string>> ans;
        for (auto it : groups)
            ans.push_back(it.second);
        
        return ans;
    }
};
/*
249. Group Shifted Strings

Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"
Given a list of non-empty strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

Example:

Input: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Output: 
[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]
*/

#include <vector>
#include <map>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::map;
using std::vector;


class GroupShiftedStrings {

public:

    vector<vector<string>> doit_hashtable(vector<string>& strings) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> map;
        for(string s : strings){
            string str;
            for(int i = 1; i < s.size(); i++){
                int diff = s[i] - s[i - 1];
                if(diff < 0) diff += 26; // NOTE: circular
                str.push_back('a' + diff);                 
            }
            map[str].push_back(s);
        }
        
        for(const auto& pair : map){
            vector<string> vec = pair.second;
            sort(vec.begin(), vec.end());
            res.push_back(vec);
        }
        return res;
    }
    
    vector<vector<string>> doit_(vector<string>& strings) {
        
        map<string, vector<string>> buff;

        for (const auto& s : strings) {

            if (s.length() == 1)
                buff["a"].push_back(s);
            else {
                string key;
                for (int i = 0; i < s.length()-1; i++) {
                    auto diff = std::to_string((s[i+1] - s[i] + 26) % 26);
                    key += diff.length() == 1 ? ("0" + diff) : diff;
                }

                buff[key].push_back(s);
            }
        }

        vector<vector<string>> ans;
        for (auto it = begin(buff); it != end(buff); it++) {
            ans.push_back(it->second);
        }

        return ans;
    }
};
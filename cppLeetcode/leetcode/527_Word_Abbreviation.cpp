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

using std::unordered_map;
using std::vector;
using std::string;
/*

class WordsAbbreviation {
    
public:
    vector<string> doit_dp(vector<string>& dict) {
        
        auto longgest_common_str = [](auto& a, auto& b) {
            auto i = 0;
            while (i < a.length() && i < b.length() && a[i] == b[i]) {
                i++;
            }
            return i;
        };
        
        auto hash_cord = [](const auto& c) {
          return std::hash<int>()(std::get<1>(c)) ^ std::hash<int>()(std::get<2>(c)) ^ std::hash<int>()(std::get<3>(c));
        };

        auto equal_cord = [](const auto& a, const auto& b){
            return a == b;
        };
        
        unordered_map<std::tuple<char, char, int>, vector<std::pair<string, int>>, decltype(hash_cord), decltype(equal_cord)> groups(10, hash_cord, equal_cord);
        
        for (auto i = 0; i < dict.size(); i++) {
            auto c = dict[i];
            groups[{c[0], c[c.length()-1], c.length()}].push_back({c, i});
        }
        
        vector<string> res(dict.size());
        
        for (auto& k : groups) {
            
            auto& group = k.second;
            
            std::sort(group.begin(), group.end(), [](auto& a, auto& b) {
                return a.first < b.first;
            });
            
            vector<int> lcp(group.size(), 0);
            
            for (auto i = 1; i < group.size(); i++) {
                lcp[i] = longgest_common_str(group[i].first, group[i-1].first);
                lcp[i-1] = std::max(lcp[i-1], lcp[i]);
            }
            
            auto size = std::get<3>(k.first);
            for (auto i = 0; i < lcp.size(); i++) {
                int delta = size - 2 - lcp[i];
                auto [word, index] = group[i];
                if (delta < 1) {
                    res[index] = word;
                } else {
                    res[index] = word.substr(0, lcp[i]) + std::to_string(delta) + dict[index][dict[index].length()-1];
                }
            }
            
        }
        
        return res;
    }
};
*/

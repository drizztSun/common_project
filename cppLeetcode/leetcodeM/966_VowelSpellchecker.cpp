/*
 
 
 966. Vowel Spellchecker
 
 
 Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.

 For a given query word, the spell checker handles two categories of spelling mistakes:

 Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
 Example: wordlist = ["yellow"], query = "YellOw": correct = "yellow"
 Example: wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
 Example: wordlist = ["yellow"], query = "yellow": correct = "yellow"
 Vowel Errors: If after replacing the vowels ('a', 'e', 'i', 'o', 'u') of the query word with any vowel individually, it matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the match in the wordlist.
 Example: wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
 Example: wordlist = ["YellOw"], query = "yeellow": correct = "" (no match)
 Example: wordlist = ["YellOw"], query = "yllw": correct = "" (no match)
 In addition, the spell checker operates under the following precedence rules:

 When the query exactly matches a word in the wordlist (case-sensitive), you should return the same word back.
 When the query matches a word up to capitlization, you should return the first such match in the wordlist.
 When the query matches a word up to vowel errors, you should return the first such match in the wordlist.
 If the query has no matches in the wordlist, you should return the empty string.
 Given some queries, return a list of words answer, where answer[i] is the correct word for query = queries[i].

  

 Example 1:

 Input: wordlist = ["KiTe","kite","hare","Hare"], queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
 Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
 
 
 */

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <unordered_set>
using std::unordered_set;

#include <unordered_map>
using std::unordered_map;

class Spellchecker {
    
public:
    
    vector<string> doit(vector<string>&& wordlist, vector<string>&& queries) {
        
        auto to_lower = [](const string& word) {
            string res(word.length(), '0');
            
            for (int i = 0; i < word.length(); i++) {
                res[i] = std::tolower(word[i]);
            }
            return res;
        };
        
        auto replace_vom = [](const string& word) {
            string res(word.length(), '0');
            
            for (int i = 0; i < word.length(); i++) {
                char a = std::tolower(word[i]);
                if (a == 'a'|| a == 'e' || a == 'i' || a == 'o' || a == 'u')
                    a = '*';
                res[i] =a;
            }
            return res;
        };
        
        unordered_map<string, string> wordset;
        unordered_map<string, string> wordvomset;
        unordered_map<string, string> wordlowerset;
        
        for (auto& c : wordlist) {
            wordset[c] = c;
            
            auto lower = to_lower(c);
            if (wordlowerset.count(lower) == 0) {
                wordlowerset[lower] = c;
            }
            
            auto vom = replace_vom(c);
            if (wordvomset.count(vom) == 0)
                wordvomset[vom] = c;
        }
        
        vector<string> ans;
        for (auto& c: queries) {
            
            if (wordset.count(c) > 0) {
                ans.push_back(c);
                continue;
            }
                
            
            string lower = to_lower(c);
            if (wordlowerset.count(lower)) {
                ans.push_back(wordlowerset[lower]);
                continue;
            }
            
            string vom = replace_vom(c);
            if ((wordvomset.count(vom)) > 0) {
                ans.push_back(wordvomset[vom]);
                continue;
            }
                
            ans.push_back({""});
        }
        
        return ans;
    }
    
    
    
    vector<string> doit1(vector<string>& wordlist, vector<string>& queries) {
        
        unordered_set<string> sets(wordlist.begin(), wordlist.end());
        unordered_map<string, string> cap, vow;
        for(string& str: wordlist) {
            string lstr = tolow(str);
            if(!cap.count(lstr)) {
                cap[lstr] = str;
            }
            
            string lvow = devow(str);
            if(!vow.count(lvow)) {
                vow[lvow] = str;
            }
                
        }
        
        
        for(int i = 0; i < queries.size(); ++i) {
            if(sets.count(queries[i]))
                continue;
            string l = tolow(queries[i]), v = devow(queries[i]);
            if(cap.count(l)) {
                queries[i] = cap[l];
                continue;
            }
            if(vow.count(v)) {
                queries[i] = vow[v];
                continue;
            }
            queries[i] = "";
        }
        
        return queries;
    }
    
    string tolow(string s) {
        for(char& c: s) {
            c = tolower(c);
        }
        return s;
    }
    
    string devow(string s) {
        string ls = tolow(s);
        for(char& c: ls) {
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                c = '.';
        }
        
        return ls;
    }
};

void test_966_vowel_spellchecker() {
    
    auto res1 = Spellchecker().doit(vector<string>{"KiTe","kite","hare","Hare"}, vector<string>{"kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"});
    
    return;
}

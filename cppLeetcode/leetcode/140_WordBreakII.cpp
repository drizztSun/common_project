/*
 140. Word Break II
 
 Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

 Note:

 The same word in the dictionary may be reused multiple times in the segmentation.
 You may assume the dictionary does not contain duplicate words.
 Example 1:

 Input:
 s = "catsanddog"
 wordDict = ["cat", "cats", "and", "sand", "dog"]
 Output:
 [
   "cats and dog",
   "cat sand dog"
 ]
 Example 2:

 Input:
 s = "pineapplepenapple"
 wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
 Output:
 [
   "pine apple pen apple",
   "pineapple pen apple",
   "pine applepen apple"
 ]
 Explanation: Note that you are allowed to reuse a dictionary word.
 Example 3:

 Input:
 s = "catsandog"
 wordDict = ["cats", "dog", "sand", "and", "cat"]
 Output:
 []
 
 */
#include <string>
#include <vector>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;


class WordBreak {
public:
    
    void search(string s, int index, vector<string>& wordDict, unordered_map<int, vector<string>>& memo) {
        
        if (memo.count(index) != 0) {
            return;
        }
        
        vector<string> ans;
        for (auto& word : wordDict) {
            
            if (word == s.substr(index, word.length())) {
                
                if (index + word.length() == s.length()) {
                    ans.push_back(word);
                    continue;
                }
                search(s, index + word.length(), wordDict, memo);
                for (auto c : memo[index+word.length()]) {
                    ans.push_back(word + " " + c);
                }
            }
        }
        
        memo[index] = ans;
        return;
    }
    
    vector<string> doit_dp(string s, vector<string>&& wordDict) {
     
        unordered_map<int, vector<string>> memo;
        memo[s.length()] = vector<string>{};
        search(s, 0, wordDict, memo);
        return memo[0];
    }
};

void test_140_word_break() {
    WordBreak().doit_dp("catsanddog", vector<string>{"cat", "sand", "and", "cats", "dog"});
}

/*
 
 # 1048. Longest String Chain

 # Given a list of words, each word consists of English lowercase letters.

 # Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.
 # For example, "abc" is a predecessor of "abac".

 # A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1,
 # where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.

 # Return the longest possible length of a word chain with words chosen from the given list of words.


 # Example 1:

 # Input: ["a","b","ba","bca","bda","bdca"]
 # Output: 4
 # Explanation: one of the longest word chain is "a","ba","bda","bdca".


 # Note:

 # 1 <= words.length <= 1000
 # 1 <= words[i].length <= 16
 # words[i] only consists of English lowercase letters.
 
 */

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;
using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;

class LongestStrChain {
    
public:
    
    int doit1(vector<string>& words) {
        
        unordered_set<string> allwords;
        unordered_map<string, int> dp;
        
        std::sort(words.begin(), words.end(), [](auto& a, auto& b){
            return a.length() < b.length();
        });
        
        for(auto& w : words) {
            allwords.insert(w);
        }
        
        int ans = 0;
        for (auto& w : words) {
            dp[w] = 1;
            size_t length = w.length();
            for (size_t i = 0; i < length; i++) {
                
                string substring;
                if (i == 0)
                    substring = w.substr(1, length - 1);
                else if (i == length -1)
                    substring = w.substr(0, length - 1);
                else
                    substring = w.substr(0, i) + w.substr(i+1, length - i - 1);
                
                if (allwords.count(substring) > 0) {
                    if (dp[w] < dp[substring] + 1) {
                        dp[w] = dp[substring] + 1;
                    }
                }
            }
            if (ans < dp[w]) {
                ans = dp[w];
            }
        }
        
        return ans;
    }
    
    size_t recursive_search(const string& word, unordered_map<size_t, unordered_set<string>>& words_len_set, unordered_map<string, size_t>& memo) {
        
        auto res = memo.find(word);
        if (res != memo.end()) {
            return res->second;
        }
        
        size_t length = word.length();
        if (length == 1)
            return words_len_set[1].count(word);
        
        size_t ans = 1;
        for (size_t i = 0; i < length; i++) {
            
            string substring;
            if (i == 0)
                substring = word.substr(1, length - 1);
            else if (i == length -1)
                substring = word.substr(0, length - 1);
            else
                substring = word.substr(0, i) + word.substr(i+1, length - i - 1);
            
            if (words_len_set[substring.length()].count(substring) != 0) {
                ans = std::max(ans, recursive_search(substring, words_len_set, memo) + 1);
            }
        }
        
        memo[word] = ans;
        return ans;
    }
    
    int doit(vector<string>& words) {
        
        unordered_map<size_t, unordered_set<string>> words_len_set;
        unordered_map<string, size_t> memo;
        for (auto& w: words) {
            words_len_set[w.length()].insert(w);
        }
        
        size_t ans = 0;
        for (auto& w : words) {
            ans = std::max(ans, recursive_search(w, words_len_set, memo));
        }
        
        return static_cast<int>(ans);
    }
};


void test_1048_longest_string_chain() {
    
    vector<string> input{string("a"), string("b"), string("ba"), string("bca"), string("bda"), string("bdca")};
    int res = LongestStrChain().doit(input);
    printf("test_1048_longest_string_chain res %d", res);
}


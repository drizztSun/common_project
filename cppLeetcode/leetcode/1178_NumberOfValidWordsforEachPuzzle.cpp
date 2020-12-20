/*
 
 1178. Number of Valid Words for Each Puzzle
 
 With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
 1) word contains the first letter of puzzle.
 2) For each letter in word, that letter is in puzzle.
 For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage", and "baggage"; while invalid words are "beefed" (doesn't include "a") and "based" (includes "s" which isn't in the puzzle).
 Return an array answer, where answer[i] is the number of words in the given word list words that are valid with respect to the puzzle puzzles[i].
  

 Example :

 Input:
 words = ["aaaa","asas","able","ability","actt","actor","access"],
 puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
 Output: [1,1,3,2,4,0]
 Explanation:
 1 valid word for "aboveyz" : "aaaa"
 1 valid word for "abrodyz" : "aaaa"
 3 valid words for "abslute" : "aaaa", "asas", "able"
 2 valid words for "absoryz" : "aaaa", "asas"
 4 valid words for "actresz" : "aaaa", "asas", "actt", "access"
 There're no valid words for "gaswxyz" cause none of the words in the list contains letter 'g'.
  

 Constraints:

 1 <= words.length <= 10^5
 4 <= words[i].length <= 50
 1 <= puzzles.length <= 10^4
 puzzles[i].length == 7
 words[i][j], puzzles[i][j] are English lowercase letters.
 Each puzzles[i] doesn't contain repeated characters.
 
 
 */

#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>


using std::string;
using std::vector;
using std::unordered_map;


class NumberOfValidWords {

public:
    
    /*
    Solution: Compression / bitmap / hashtable

    Bruteforce: O(w * p) O(10^9) TLE


    Compress each word to a binary string, and computre the frequency of each binary string.

    "a" => 1, "aa" -> 1, "ab" -> 11, "bc"->110
    (1 -> 2, 11 -> 1, 110 -> 1) Its sparse, use hashtable instead of dense array.

    For each puzzle, compress it a binary string use the above method. Try all possible subsets of the binary string.

    There are at most 2^7 = 128, and we must contain the first charactor.

    ans = sum(freq[m] for m in subsets(p) if m[p[0]] == 1)

    Time complexity: O(sum(len(word) + 128 *|p|))
    Space complexity: O(|words|)
    */
    vector<int> doit_(vector<string>& words, vector<string>& puzzles) {
        
        vector<int> ans;
        unordered_map<int, int> freq;
        
        for (auto& w : words) {
            int mask = 0;
            for (auto c: w)
                mask |= 1 << (c - 'a');
            freq[mask]++;
        }
        
        for (auto& p : puzzles) {
            
            int l = p.length() - 1;
            int total = 0;
            for (int i = 0; i < (1 << l); i++) {
                
                int mask = (1 << (p[0] - 'a'));
         
                for (int j = 0; j < l; j++) {
                    
                    if (i & (1 << j))
                        mask |= 1 << (p[j+1] - 'a');
                    
                }
                
                auto it = freq.find(mask);
                if (it != freq.end())
                    total += it->second;
            }
            
            ans.push_back(total);
        }
        
        return ans;
    }
     
    vector<int> doit_bit_hashmap_compression(vector<string>& words, vector<string>& puzzles) {
        
        vector<int> ans;
        unordered_map<int, int> freq;
        
        for (const string& word : words) {
          int mask = 0;
          for (char c : word)
            mask |= 1 << (c - 'a');
          ++freq[mask];
        }
        
        for (const string& p : puzzles) {
          int mask = 0;
        
          for (char c : p)
            mask |= 1 << (c - 'a');
        
          int first = p[0] - 'a';
          int curr = mask;
          int total = 0;
          
          while (curr) {
            if ((curr >> first) & 1) {
              auto it = freq.find(curr);
              if (it != freq.end()) total += it->second;
            }
            curr = (curr - 1) & mask;
          }
          
          ans.push_back(total);
        }
        
        return ans;
    }
};

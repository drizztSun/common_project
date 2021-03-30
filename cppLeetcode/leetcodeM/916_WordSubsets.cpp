/*
916. Word Subsets

We are given two arrays A and B of words.  Each word is a string of lowercase letters.

Now, say that word b is a subset of word a if every letter in b occurs in a, including multiplicity.  For example, "wrr" is a subset of "warrior", but is not a subset of "world".

Now say a word a from A is universal if for every b in B, b is a subset of a. 

Return a list of all universal words in A.  You can return the words in any order.

 

Example 1:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","o"]
Output: ["facebook","google","leetcode"]
Example 2:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["l","e"]
Output: ["apple","google","leetcode"]
Example 3:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","oo"]
Output: ["facebook","google"]
Example 4:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["lo","eo"]
Output: ["google","leetcode"]
Example 5:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["ec","oc","ceo"]
Output: ["facebook","leetcode"]
 

Note:

1. 1 <= A.length, B.length <= 10000
2. 1 <= A[i].length, B[i].length <= 10
3. A[i] and B[i] consist only of lowercase letters.
4. All words in A[i] are unique: there isn't i != j with A[i] == A[j].

*/

#include <vector>
#include <string>

using std::string;
using std::vector;



class WordSubsets {

public:

    /*
        Approach 1: Reduce to Single Word in B
        Intuition

        If b is a subset of a, then say a is a superset of b. Also, say N_{\text{"a"}}(\text{word})N 
        "a"
        ​	
        (word) is the count of the number of \text{"a"}"a"'s in the word.

        When we check whether a word wordA in A is a superset of wordB, we are individually checking the counts of letters: that for each \text{letter}letter, we have N_{\text{letter}}(\text{wordA}) \geq N_{\text{letter}}(\text{wordB})N 
        letter
        ​	
        (wordA)≥N 
        letter
        ​	
        (wordB).

        Now, if we check whether a word wordA is a superset of all words \text{wordB}_iwordB 
        i
        ​	
        , we will check for each letter and each ii, that N_{\text{letter}}(\text{wordA}) \geq N_{\text{letter}}(\text{wordB}_i)N 
        letter
        ​	
        (wordA)≥N 
        letter
        ​	
        (wordB 
        i
        ​	
        ). This is the same as checking N_{\text{letter}}(\text{wordA}) \geq \max\limits_i(N_{\text{letter}}(\text{wordB}_i))N 
        letter
        ​	
        (wordA)≥ 
        i
        max
        ​	
        (N 
        letter
        ​	
        (wordB 
        i
        ​	
        )).

        For example, when checking whether "warrior" is a superset of words B = ["wrr", "wa", "or"], we can combine these words in B to form a "maximum" word "arrow", that has the maximum count of every letter in each word in B.

        Algorithm

        Reduce B to a single word bmax as described above, then compare the counts of letters between words a in A, and bmax.


        Complexity Analysis

        Time Complexity: O(\mathcal{A} + \mathcal{B})O(A+B), where \mathcal{A}A and \mathcal{B}B is the total amount of information in A and B respectively.
        Space Complexity: O(A\text{.length} + B\text{.length})O(A.length+B.length).
    */
    vector<string> doit_hashtable(vector<string>& A, vector<string>& B) {
        
        vector<int> allbytes(26, 0);
        
        auto count = [](const string& b) {
            vector<int> bits(26, 0);
            for (auto c : b) bits[c-'a']++;
            return bits;
        };
        
        for (const auto& word: B) {
            auto cnt = count(word);
            for (int i = 0; i < cnt.size(); i++) 
                allbytes[i] = std::max(allbytes[i], cnt[i]);
        }
        
        vector<string> ans;
        
        for (const auto& word: A) {
            
            auto cnt = count(word);
            bool covered = true;
            
            for (int i = 0; i < cnt.size(); i++) {
                if (cnt[i] < allbytes[i]) {
                    covered = false;
                    break;
                }
            }
            
            if (covered) ans.push_back(word);
        }
        
        return ans;
    }
};
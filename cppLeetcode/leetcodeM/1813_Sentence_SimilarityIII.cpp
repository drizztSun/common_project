/*
1813. Sentence Similarity III

A sentence is a list of words that are separated by a single space with no leading or trailing spaces. For example, "Hello World", "HELLO", "hello world hello world" are all sentences. Words consist of only uppercase and lowercase English letters.

Two sentences sentence1 and sentence2 are similar if it is possible to insert an arbitrary sentence (possibly empty) inside one of these sentences such that the two sentences become equal. For example, sentence1 = "Hello my name is Jane" and sentence2 = "Hello Jane" can be made equal by inserting "my name is" between "Hello" and "Jane" in sentence2.

Given two sentences sentence1 and sentence2, return true if sentence1 and sentence2 are similar. Otherwise, return false.

 

Example 1:

Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
Output: true
Explanation: sentence2 can be turned to sentence1 by inserting "name is" between "My" and "Haley".
Example 2:

Input: sentence1 = "of", sentence2 = "A lot of words"
Output: false
Explanation: No single sentence can be inserted inside one of the sentences to make it equal to the other.
Example 3:

Input: sentence1 = "Eating right now", sentence2 = "Eating"
Output: true
Explanation: sentence2 can be turned to sentence1 by inserting "right now" at the end of the sentence.
Example 4:

Input: sentence1 = "Luky", sentence2 = "Lucccky"
Output: false
 

Constraints:

1 <= sentence1.length, sentence2.length <= 100
sentence1 and sentence2 consist of lowercase and uppercase English letters and spaces.
The words in sentence1 and sentence2 are separated by a single space.
*/
#include <string>
#include <vector>
#include <deque>

using std::deque;
using std::string;
using std::vector;


class AreSentencesSimilar {

public:
    
    bool doit_greedy(string sentence1, string sentence2) {

        if (sentence1.size() < sentence2.size()) std::swap(sentence1, sentence2);

        deque<string> words2;
        for (int i = 0; i < sentence2.size(); i++) {
            int j = i;
            while (i < sentence2.size() && !isspace(sentence2[i])) i++;
            words2.push_back(sentence2.substr(j, i - j));
        }

        int i = 0;
        while (i < sentence1.size() && !words2.empty()) {
            int j = i;
            while (i < sentence1.size() && !isspace(sentence1[i])) i++;

            if (sentence1.substr(j, i - j) == words2.front())
                words2.pop_front();
            else 
                break;

            i++;
        }

        if (words2.empty()) return true;

        int j = sentence1.size() - 1;
        while (j >= i && !words2.empty()) {
            int k = j;
            while (j >= i && !isspace(sentence1[j])) j--;

            if (sentence1.substr(j + 1, k - j) == words2.back())
                words2.pop_back();
            else
                break;
            
            j--;
        }

        return words2.empty();
    }

    bool doit_str(string sentence1, string sentence2) {

        int m = sentence1.length();
        int n = sentence2.length();
        if (m == n) return sentence1 == sentence2;
        if (m == 0 || n == 0) return true;
        
        if (m > n) std::swap(sentence1, sentence2), std::swap(m, n);
        
        // auto i = sentence2.find(sentence1);
        // // "A" ~ "A B"
        // if (i == 0) return sentence2[m] == ' ';
        // // "B" ~ "A B"
        // if (i == n - m) return sentence2[i - 1] == ' ';
        
        int i1 = 0, j1 = m - 1;
        int i2 = 0, j2 = n - 1;
        
        while (i1 < m && sentence1[i1] == sentence2[i2]) 
            ++i1, ++i2;
        // "A" ~ "A B"
        if (i1 >= m && sentence2[m] == ' ') return true;
        
        while (j1 >= 0 && sentence1[j1] == sentence2[j2]) 
            --j1, --j2;
        // "B" ~ "A B"
        if (j1 < 0 && sentence2[n - m - 1] == ' ') return true;
        
        if (i1 >= m || j1 < 0) return false;
        if (i1 < j1) return false;
        
        return i2 > 0 && j2 < n - 1 && sentence2[i2 - 1] == ' ' && sentence2[j2 + 1] == ' ';
    }
};
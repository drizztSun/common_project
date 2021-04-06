/*
186. Reverse Words in a String II

Given a character array s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by a single space.

 

Example 1:

Input: s = ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
Output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
Example 2:

Input: s = ["a"]
Output: ["a"]
 

Constraints:

1 <= s.length <= 105
s[i] is an English letter (uppercase or lowercase), digit, or space ' '.
There is at least one word in s.
s does not contain leading or trailing spaces.
All the words in s are guaranteed to be separated by a single space.
 

Follow up: Could you do it in-place without allocating extra space?

*/
#include <vector>
#include <string>

using std::string;
using std::vector;

class ReverseWordsII {

public:
    
    void doit_str(vector<char>& s) {
        
        reverse(begin(s), end(s));
        
        int i = 0;
        
        while (i < s.size()) {
            
            int j = i;
            while (j < s.size() && !isspace(s[j])) j++;
            
            if (j - i > 0)
                reverse(begin(s)+i, begin(s)+j);
            
            while (j < s.size() && isspace(s[j])) j++;
            
            i = j;
        }
        
        int j = 0;
        
        for (int i = 0; i < s.size(); i++) {
            
            if (isspace(s[i])) {
                if (s[j] != ' ' || j == i) s[j++] = ' ';
                continue;
            }
            
            s[j++] = s[i];
        }
        
        s.resize(j);
    }
};


/*
    557. Reverse Words in a String III

Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

 

Example 1:

Input: s = "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Example 2:

Input: s = "God Ding"
Output: "doG gniD"


Constraints:

1 <= s.length <= 5 * 104
s contains printable ASCII characters.
s does not contain any leading or trailing spaces.
There is at least one word in s.
All the words in s are separated by a single space.
*/


class ReverseWordsIII {

public:
    
    string doit_(string s) {
        
        int i = 0;
        
        while (i < s.size()) {
            
            int j = i;
            while (j < s.size() && !isspace(s[j])) j++;
            
            if (j - i > 0)
                reverse(begin(s)+i, begin(s)+j);
            
            while (j < s.size() && isspace(s[j])) j++;
            
            i = j;
        }
        
        return s;
    }
};
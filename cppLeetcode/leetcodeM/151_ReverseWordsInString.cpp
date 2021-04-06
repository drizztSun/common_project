/*
151. Reverse Words in a String

Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

 

Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
Example 4:

Input: s = "  Bob    Loves  Alice   "
Output: "Alice Loves Bob"
Example 5:

Input: s = "Alice does not even like bob"
Output: "bob like even not does Alice"
 

Constraints:

1 <= s.length <= 104
s contains English letters (upper-case and lower-case), digits, and spaces ' '.
There is at least one word in s.
 

Follow up: Could you solve it in-place with O(1) extra space?

*/

#include <vector>
#include <string>

using std::vector;
using std::string;


class ReverseWords {

public:

    string doit_(string s) {

        vector<string> tmp;

        for (int i = 0; i < s.length(); i++) {

            int last = i;
            while (i < s.length() && !isspace(s[i]))i++;

            if (i - last > 0) tmp.push_back(s.substr(last, i - last));    
        }

        if (tmp.empty()) return "";

        string ans = tmp[tmp.size()-1];
        for (int i = tmp.size()-2; i >= 0; i--)
            ans += " " + tmp[i];
        return ans;
    }   

    string doit_str(string s) {
        
        // Reverse string
        reverse(s.begin(), s.end());
        
        // Reverse every word
        int i = 0, j = 0;
        
        while(i != s.size()){
            while(j < s.size() && s[j] != ' ') j++;
            reverse(s.begin() + i, s.begin() + j);
            i = j;
            while(i < s.size() && s[i] == ' ') i++, j++;
        }
        
        // Remove extra ' '
        i = 0, j = 0;
        while(j < s.size()) {
            bool new_word = false;
            while(j < s.size() && s[j] == ' '){
                new_word = true;
                j++;
            }
            if(j == s.size()) break;
            if(new_word && i > 0) s[i++] = ' ';
            s[i++] = s[j++];
        }
        s = s.substr(0, i);

        return s;
    }
};
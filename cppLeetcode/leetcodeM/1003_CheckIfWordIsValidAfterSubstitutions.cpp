/*
 
 # 1003. Check If Word Is Valid After Substitutions

 # We are given that the string "abc" is valid.

 # From any valid string V, we may split V into two pieces X and Y such that X + Y (X concatenated with Y) is equal to V.  (X or Y may be empty.)  Then, X + "abc" + Y is also valid.

 # If for example S = "abc", then examples of valid strings are: "abc", "aabcbc", "abcabc", "abcabcababcc".  Examples of invalid strings are: "abccba", "ab", "cababc", "bac".

 # Return true if and only if the given string S is valid.


 # Example 1:

 # Input: "aabcbc"
 # Output: true
 # Explanation:
 # We start with the valid string "abc".
 # Then we can insert another "abc" between "a" and "bc", resulting in "a" + "abc" + "bc" which is "aabcbc".

 # Example 2:

 # Input: "abcabcababcc"
 # Output: true
 # Explanation:
 # "abcabcabc" is valid after consecutive insertings of "abc".
 # Then we can insert "abc" before the last letter, resulting in "abcabcab" + "abc" + "c" which is "abcabcababcc".

 # Example 3:

 # Input: "abccba"
 # Output: false

 # Example 4:

 # Input: "cababc"
 # Output: false
 
 
 */

#include <string>
using std::string;

class IsValid {
public:
    bool doit(string S) {
        
        string st;
        
        for (auto c : S) {
            
            if (c != 'c')
                st += c;
            else
                if (st.length() < 2 || st.substr(st.length() - 2, 2) != "ab")
                    return false;
                else {
                    st.pop_back();
                    st.pop_back();
                }
        }
        
        return st.empty();
    }
};


void test_1003_check_if_word_is_valid_after_substitution() {
    
    auto res1 = IsValid().doit("aabcbc");
    
    auto res2 = IsValid().doit("abcabcababcc");
    
    auto res3 = IsValid().doit("abccba");
    
    auto res4 = IsValid().doit("cababc");
    
    return;
}

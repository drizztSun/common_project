/*
 
 984. String Without AAA or BBB
 
 
 Given two integers A and B, return any string S such that:

 S has length A + B and contains exactly A 'a' letters, and exactly B 'b' letters;
 The substring 'aaa' does not occur in S;
 The substring 'bbb' does not occur in S.
  

 Example 1:

 Input: A = 1, B = 2
 Output: "abb"
 Explanation: "abb", "bab" and "bba" are all correct answers.
 Example 2:

 Input: A = 4, B = 1
 Output: "aabaa"
 
 */

#include <string>
using std::string;


class StrWithout3a3b {
public:
    string doit(int A, int B) {
        
        string ans;
        
        while ( A > 0 && B > 0) {
            
            if (A > B) {
                ans += "aab";
                A -= 2;
                B -= 1;
            } else if (A < B) {
                ans += "bba";
                A -= 1;
                B -= 2;
            } else {
                for (; A; A--)
                    ans += "ab";
                A = 0;
                B = 0;
            }
        }
        
        if(A>0 || B >0)
            ans += (A > 0) ? (A == 1? "a" : "aa") : (B == 1 ? "b": "bb");
            
        return ans;
    }
    
    /*
     Approach 1: Greedy
     Intuition

     Intuitively, we should write the most common letter first.
     For example, if we have A = 6, B = 2, we want to write 'aabaabaa'.
     The only time we don't write the most common letter is if the last two letters we have written are also the most common letter

     Algorithm

     Let's maintain A, B: the number of 'a' and 'b''s left to write.

     If we have already written the most common letter twice, we'll write the other letter. Otherwise, we'll write the most common letter.
     
     Complexity Analysis

     Time Complexity: O(A+B).

     Space Complexity: O(A+B).
     */
    string doit1(int A, int B) {
        string ans;
        
        while (A > 0 || B > 0) {
            int len = ans.length();
            bool writeToA = false;
            if (len > 1 && ans[len-1] == ans[len-2])
                writeToA = ans[len-1] == 'b';
            else
                writeToA = A > B;
            
            if (writeToA) {
                ans += 'a';
                A--;
            } else {
                ans += 'b';
                B--;
            }
        }
        
        return ans;
    }
};


void test_984_string_without_aaa_or_bbb() {
    
    auto res1 = StrWithout3a3b().doit(1, 2);
    
    auto res2 = StrWithout3a3b().doit(4, 1);
    
    return;
}

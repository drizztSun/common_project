/*
 828. Count Unique Characters of All Substrings of a Given String
 
 
 Let's define a function countUniqueChars(s) that returns the number of unique characters on s, for example if s = "LEETCODE" then "L", "T","C","O","D" are the unique characters since they appear only once in s, therefore countUniqueChars(s) = 5.

 On this problem given a string s we need to return the sum of countUniqueChars(t) where t is a substring of s. Notice that some substrings can be repeated so on this case you have to count the repeated ones too.

 Since the answer can be very large, return the answer modulo 10 ^ 9 + 7.

  

 Example 1:

 Input: s = "ABC"
 Output: 10
 Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
 Evey substring is composed with only unique letters.
 Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
 Example 2:

 Input: s = "ABA"
 Output: 8
 Explanation: The same as example 1, except countUniqueChars("ABA") = 1.
 Example 3:

 Input: s = "LEETCODE"
 Output: 92
  

 Constraints:

 0 <= s.length <= 10^4
 s contain upper-case English letters only.
 
 
 */
#include <string>
#include <unordered_map>
#include <vector>


using std::vector;
using std::unordered_map;
using std::string;


class UniqueLetterString {
    
public:
    
    int doit_2(string S) {
        
        int index[26][2], res = 0, N = S.length(), mod = pow(10, 9) + 7;
        memset(index, -1, sizeof(int) * 52);
        
        for (int i = 0; i < N; ++i) {
            int c = S[i] - 'A';
            res = (res + (i - index[c][1]) * (index[c][1] - index[c][0]) % mod) % mod;
            index[c][0] = index[c][1];
            index[c][1] = i;
        }
        
        for (int c = 0; c < 26; ++c)
            res = (res + (N - index[c][1]) * (index[c][1] - index[c][0]) % mod) % mod;
        
        return res;
    }
    
    int doit_1(string s) {

        unordered_map<char, vector<int>> pos;
        int mod = pow(10, 9) + 7;
        
        for (int i = 0; i < s.length(); i++) {
            pos[s[i]].push_back(i);
        }
        
        int res = 0;
        for (auto& c : pos) {
            c.second.push_back(s.length());
            c.second.insert(c.second.begin(), -1);
            
            for (int i = 1; i < c.second.size() - 1; i++) {
                int tmp = ((c.second[i] - c.second[i-1]) * (c.second[i+1] - c.second[i])) % mod;
                if (tmp > mod - res) {
                    res -= mod;
                }
                res += tmp;
            }
        }
        
        return res;
    }
    
    int doit_twopoints(string s) {
    

        unordered_map<char, int> last, second_last;
        int total_sum = 0, current_sum = 0;
        int mod = 1e9+7;
        
        for (int i = 0; i < s.length(); i++) {
            
            char c = s[i];
            current_sum += 1;
            
            if (last.count(c) == 0) {
                last[c] = 0;
            }
            
            if (second_last.count(c) == 0) {
                second_last[c] = 0;
            }
            
            current_sum -= (last[c] - second_last[c]);
            
            current_sum += (i - last[c]);
            
            if (last[c] > 0) {
                second_last[c] = last[c];
            }
            
            last[c] = i+1;
            
            if (mod - total_sum <= current_sum) {
                total_sum -= mod;
            }
            
            total_sum += current_sum;
        }
        
        return total_sum;
    }
};

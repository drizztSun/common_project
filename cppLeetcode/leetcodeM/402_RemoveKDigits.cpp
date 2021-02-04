/*
402. Remove K Digits


Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.

*/
#include <string>
#include <vector>

using std::vector;
using std::string;

class RemoveKdigits {

public:
    
    string doit_stack(string num, int k) {
        
        vector<char> buff;
        int keep = num.length() - k;
        for (auto c: num) {
            while (!buff.empty() && k > 0 && buff.back() > c) {
                buff.pop_back();
                k--;
            }
            buff.push_back(c);
        }
        
        buff.resize(keep);
        if (buff.empty()) return "0";
        
        auto it = begin(buff);
        if (buff.size() > 1)
            while (it != end(buff) && *it == '0') it++;
        
        string res(it, buff.end());
        
        return res.empty() ? "0" : res;
    }
};
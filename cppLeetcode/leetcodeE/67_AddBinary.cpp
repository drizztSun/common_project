/*
 
 
 
 67. Add Binary
 
 
 Given two binary strings, return their sum (also a binary string).

 The input strings are both non-empty and contains only characters 1 or 0.

 Example 1:

 Input: a = "11", b = "1"
 Output: "100"
 Example 2:

 Input: a = "1010", b = "1011"
 Output: "10101"
 
 
 */

#include <string>
using std::string;


class AddBinary {
    
public:
    string doit(string a, string b) {
        
        bool add = false;
        int i = a.length()-1, j = b.length()-1;
        string ans;
        
        while ( i > -1 || j > -1) {
            
            int f = i > -1 && a[i] == '1' ? 1 : 0;
            int s = j > -1 && b[j] == '1' ? 1 : 0;
            
            s += f + (add ? 1 : 0);
            add = false;
            
            ans = (s % 2 == 1 ? '1' : '0') + ans;
            add = (s > 1);
            
            i--;
            j--;
        }
     
        if (add)
            ans = '1' + ans;
        return ans;
    }
};

void test_67_add_binary() {
    
    auto res1 = AddBinary().doit("11", "1");
    
    auto res2 = AddBinary().doit("1010", "1011");
    
    return;
}

/*
 
 # 1017. Convert to Base -2

 # Given a number N, return a string consisting of "0"s and "1"s that represents its value in base -2 (negative two).

 # The returned string must have no leading zeroes, unless the string is "0".


 # Example 1:

 # Input: 2
 # Output: "110"
 # Explantion: (-2) ^ 2 + (-2) ^ 1 = 2

 # Example 2:

 # Input: 3
 # Output: "111"
 # Explantion: (-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3

 # Example 3:

 # Input: 4
 # Output: "100"
 # Explantion: (-2) ^ 2 = 4


 # Note:

 # 0 <= N <= 10^9
 
 */

#include <string>
using std::string;

class BaseNeg2 {

    
public:
    string doit(int N) {
        string ans;
        while (N != 0) {
            if (N % 2 != 0) {
                ans = '1' + ans;
                N -= 1;
            }
            else
                ans = '0' + ans;
            
            N /= -2;
        }
        
        return ans;
    }
};

void test_1017_convert_to_base() {
    
    auto res1 = BaseNeg2().doit(2);
    
    auto res2 = BaseNeg2().doit(3);
    
    auto res3 = BaseNeg2().doit(4);
    
    return;
}

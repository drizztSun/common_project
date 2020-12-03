/*
 479. Largest Palindrome Product
 
 Find the largest palindrome made from the product of two n-digit numbers.

 Since the result could be very large, you should return the largest palindrome mod 1337.

  

 Example:

 Input: 2

 Output: 987

 Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

  

 Note:

 The range of n is [1,8].
 
*/
#include <cmath>
#include <string>

using std::string;

class LargestPalindrome{
    
    long createPalindrom(int n) {
        string left = std::to_string(n);
        string right = left;
        std::reverse(right.begin(), right.end());
        left += right;
        return atoi(left.c_str());
    }
    
public:
    
    int doit_(int n) {
        
        if (n == 1)
            return 9;
        
        int upperBound = pow(10, n) - 1;
        int lowerBound = upperBound / 10 + 1;
        long maxnum = (long) upperBound * (long) upperBound;
        int half = (int) (maxnum / (long) pow(10, n));
        long palindrom = 0;
        bool found = false;
        
        while (!found) {
            
            palindrom = createPalindrom(half);
            
            for (long i = upperBound; i >= lowerBound; i--) {
                if (i * i < palindrom)
                    break;
                
                if (palindrom % i == 0) {
                    found = true;
                    break;
                }
            }
            half--;
        }
        
        return (int) (palindrom % 1337);
    }
};

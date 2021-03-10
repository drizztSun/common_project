#include <vector>

using std::vector;

/*
263. Ugly Number

Given an integer n, return true if n is an ugly number.

Ugly number is a positive number whose prime factors only include 2, 3, and/or 5.

 

Example 1:

Input: n = 6
Output: true
Explanation: 6 = 2 × 3
Example 2:

Input: n = 8
Output: true
Explanation: 8 = 2 × 2 × 2
Example 3:

Input: n = 14
Output: false
Explanation: 14 is not ugly since it includes another prime factor 7.
Example 4:

Input: n = 1
Output: true
Explanation: 1 is typically treated as an ugly number.
 

Constraints:

-231 <= n <= 231 - 1
*/
class UglyNumberI {

public:
    
    bool isUgly(int n) {
        
        if (n <= 0) return false;
        
        while (n % 5 == 0) 
            n /= 5;
        
        while (n % 2 == 0)
            n /= 2;
        
        while (n % 3 == 0)
            n /= 3;
        
        return n == 1;
    }
};
/*
264. Ugly Number II

Given an integer n, return the nth ugly number.

Ugly number is a positive number whose prime factors only include 2, 3, and/or 5.

 

Example 1:

Input: n = 10
Output: 12
Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.
Example 2:

Input: n = 1
Output: 1
Explanation: 1 is typically treated as an ugly number.
 

Constraints:

1 <= n <= 1690

*/


class UglyNumberII {

public:

    int doit_(int n) {

        vector<int> res{1};

        int i2 = 0, i3 = 0, i5 = 0;

        while (--n) {

            int base2 = 2 * res[i2], base3 = 3 * res[i3], base5 = 5 * res[i5];
            int minv = std::min({base2, base3, base5});

            if (minv == base2) i2++;
            if (minv == base3) i3++;
            if (minv == base5) i5++;

            res.push_back(minv);
        }

        return res.back();
    }
};
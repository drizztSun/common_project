/*
 1680. Concatenation of Consecutive Binary Numbers
 
 Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.



 Example 1:

 Input: n = 1
 Output: 1
 Explanation: "1" in binary corresponds to the decimal value 1.
 Example 2:

 Input: n = 3
 Output: 27
 Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
 After concatenating them, we have "11011", which corresponds to the decimal value 27.
 Example 3:

 Input: n = 12
 Output: 505379714
 Explanation: The concatenation results in "1101110010111011110001001101010111100".
 The decimal value of that is 118505380540.
 After modulo 109 + 7, the result is 505379714.


 Constraints:

 1 <= n <= 105
 
 */
#include <cmath>
#include <vector>

using std::vector;

class ConcatenatedBinary {
    
public:
    
    // O(n)
    int doit_(int n) {
        long long res = 1;
        int M = 1e9 + 7;
        for (int s = 2; s <= n; s++) {
            int len = log(s)/log(2) + 1;
            res = ((res << len) + s) % M;
        }
        return res;
    }
    
    /* Reference: https://stackoverflow.com/questions/64450456/concatenation-of-binary-representation-of-first-n-positive-integers-in-ologn-t
    The idea is the calculation of the concatenatedBinary in range [a, b), where 2^(t-1) <= a < b <= 2^t can be done in roughly O(1) time (or O(log(b-a)) if considering the time to calculate power).
    Let l = 2^t, n = b - a, then concatenatedBinary(a, b) = a*l^(n-1) + (a+1)*l^(n-2) + (a+2)*l^(n-3)... + (b- 1)*l^0 (it's easy to verify if you expand the expression from b)
    So that concatenatedBinary(a, b) = (a*(l^n-1) + (l^n-1)/(l-1) - n) / (l-1)
    */
    int doi(int n) {

        if(n == 1){
            return 1;
        }
        
        long nL = n, ans = 0, l = 2, a = 1, b = 1;
        while(b < nL + 1){
            b = std::min(nL + 1, l);
            ans = (ans * myPow(l, b-a) + concatenateInterval(a, b, l)) % MOD;
            a = l;
            l = l << 1;
        }
        return ans;
    }
    
private:
    const int MOD = 1e9+7;
    int myPow(int x, int n){
        if(n == 0){
            return 1;
        }
        if(n == 1){
            return x;
        }
        long half = myPow(x, n/2);
        long ans = (half * half) % MOD;
        if(n % 2 == 1){
            ans = (ans * x) % MOD;
        }
        return ans;
    }

    int concatenateInterval(long a, long b, long l){
        // calculate the concatenatedBinary in range [a, b), where 2^(t-1) <= a < b <= 2^t = l
        // Note that don't use (ln-1)/(l-1) expression here, since l^n is the modulo result, the expression may give you the wrong result. Calculate the modular inverse of (l-1) instead
        long n = b - a, ln = myPow(l, n), inv = myPow(l - 1, MOD - 2), q = ((ln-1)*inv) % MOD;
        // cout << "  a = " << a << ", b = " << b << ", l = " << l << ", ln = " << ln << ", q = " << q << endl;
        return (a * q + (q - n) * inv) % MOD;
    }
};

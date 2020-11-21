/*
 372. Super Pow
 
 Your task is to calculate a**b mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.



 Example 1:

 Input: a = 2, b = [3]
 Output: 8
 Example 2:

 Input: a = 2, b = [1,0]
 Output: 1024
 Example 3:

 Input: a = 1, b = [4,3,3,8,5,2]
 Output: 1
 Example 4:

 Input: a = 2147483647, b = [2,0,0]
 Output: 1198


 Constraints:

 1 <= a <= 231 - 1
 1 <= b.length <= 2000
 0 <= b[i] <= 9
 b doesn't contain leading zeros.
 
 
 */
#include <vector>

using std::vector;

class SuperPow {
    
public:
    const int mod=1337;
    
    int binpow(int a, int b)
    {
        int res=1;
        while(b)
        {
            if(b&1) res=(res*a)%mod;
            a=((a%mod)*(a%mod))%mod;
            b>>=1;
        }
        return res;
    }
    
    int superPow(int a, vector<int>& b) {
        if(b.size()==0) return 1;
        int digit=b.back();
        b.pop_back();
        return (binpow(superPow(a,b),10)%mod)*binpow(a,digit)%mod;
    }
    
    int doit(int a, vector<int>&& b) {
        int result = 1;
        a %= 1337;
        for (auto n : b) {
            result = ((int(pow(result, 10)) % 1337) * (int(pow(a, n)) % 1337)) % 1337;
        }
        return result;
    }
    
    // ----
    /*
     
     Optimized Solution - Order of number of digits of b

     The algorithm can be described using this example where b = [7,8,5]
     a^785 = a^700 * a^80 * a^5 = ((a^70 * a^8)^10) * ( a^5)
     (((a^7)^10 * a^8)^10) * ( a^5)
     First iteration: a^7 and (a^7)^10 = a^70
     Second iteration = a^70 * a^8 and (a^78)^10 = a^780
     Third iteration = a^780 * a ^5 = a^785
     */
    int superPow_1(int a, vector<int>& b) {
        long res = 1;
        for (int i = 0; i < b.size(); ++i) {
            res = pow(res, 10) * pow(a, b[i]) % 1337;
        }
        return res;
    }
    
    int pow(int x, int n) {
        if (n == 0)
            return 1;
        if (n == 1)
            return x % 1337;
        
        return pow(x % 1337, n / 2) * pow(x % 1337, n - n / 2) % 1337;
    }
};


void test_372_superpow() {
    
    SuperPow().doit(2147483647, vector<int>{2,0,0});
}

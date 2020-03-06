/*
 
 
 # 1015. Smallest Integer Divisible by K

 # Given a positive integer K, you need find the smallest positive integer N such that N is divisible by K,
 # and N only contains the digit 1.

 # Return the length of N.  If there is no such N, return -1.


 # Example 1:

 # Input: 1
 # Output: 1
 # Explanation: The smallest answer is N = 1, which has length 1.

 # Example 2:

 # Input: 2
 # Output: -1
 # Explanation: There is no such positive integer N divisible by 2.

 # Example 3:

 # Input: 3
 # Output: 3
 # Explanation: The smallest answer is N = 111, which has length 3.


 # Note:

 # 1 <= K <= 10^5

 
 
 */


class SmallestRepunitDivByK {
    
public:
    
    int doit(int K) {
        
        if (K % 2 == 0 or K % 5 == 0)
            return -1;
        
        int i = 1;
        int n = 1;
        
        while (n % K != 0) {
            n = (10 * n + 1) % K;
            i++;
        }
        
        return i;
    }
};

void test_1015_Smallest_integer_divisible_by_K() {
    
    auto res1 = SmallestRepunitDivByK().doit(1);
    
    auto res2 = SmallestRepunitDivByK().doit(2);
    
    auto res3 = SmallestRepunitDivByK().doit(3);
    
    return;
}
